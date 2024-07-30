/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: PoolWrap.cpp

Abstract:

    Wrapper to provide a queue and thread pool for ISAPI extensions

Author:

    ISAPI developer (Microsoft employee)

--*/

#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <httpext.h>
#include "PoolWrap.h"

//
// Definitions
//

#define DEFAULT_THREADS            5
#define DEFAULT_QUEUE             10
#define LOG_MAX_LINE            1024
#define RESPONSE_MAX_BUFFER     1024

//
// Globals
//

// Thread pool
HANDLE *                    g_pThreads = NULL;
HANDLE                      g_hCompletionPort = NULL;
LONG                        g_ItemsInQueue = 0;
LONG                        g_QueueSize = 0;
DWORD                       g_NumThreads = 0;
BOOL                        g_UseThreadPool = TRUE;
CHAR                        g_QueueFullResponse[RESPONSE_MAX_BUFFER+1] = {0};
CHAR                        g_QueueFullHeaders[RESPONSE_MAX_BUFFER+1] = {0};
DWORD                       g_cchQueueFullResponse;
DWORD                       g_cchQueueFullHeaders;

// Initialization verification
BOOL                        g_InitSuccess = TRUE;
DWORD                       g_InitResultCode = ERROR_SUCCESS;

// Logging
HANDLE                      g_hLogFile = INVALID_HANDLE_VALUE;
CRITICAL_SECTION            g_LogFileLock;
BOOL                        g_EnableLogging = TRUE;

// Statistics
LONG                        g_QueueFullPages = 0;
LONG                        g_TotalRequests = 0;

//
// Wrapper function declarations
//

BOOL
WINAPI
GetExtensionVersionWrapper(
    HSE_VERSION_INFO *  pVer
    );

DWORD
WINAPI
HttpExtensionProcWrapper(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

BOOL
WINAPI
TerminateExtensionWrapper(
    DWORD   dwFlags
    );

//
// Thread pool and queue functions
//

BOOL
InitThreadPool(
    DWORD   dwQueueSize,
    DWORD   dwNumThreads
    );

VOID
ShutdownThreadPool(
    VOID
    );

BOOL
QueueRequest(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

DWORD
WINAPI
WorkerThreadProc(
    VOID *  pVoid
    );

//
// Send error functions
//

DWORD
SendExtensionInitFailed(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

DWORD
SendQueueFull(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

BOOL
SendThreadInitFailed(
    EXTENSION_CONTROL_BLOCK *   pecb,
    DWORD                       dwError
    );

//
// Helper functions
//

BOOL
AllocateAndFormatErrorMessage(
    DWORD   dwError,
    LPSTR * ppBuffer
    );

//
// Function implementations
//

BOOL
WINAPI
GetExtensionVersionWrapper(
    HSE_VERSION_INFO *  pVer
    )
/*++

Purpose:

    This function wraps GetExtensionVersion.  If GetExtensionVersion
    succeeds, this wrapper then creates a thread pool and queue for
    processing requests.

Arguments:

    pVer - poins to extension version info structure 

Returns:

    Always returns TRUE.  In the event of a FALSE return from
    GetExtensionVersion, or an error creating the thread pool,
    the result code will be stored.  Any requests to this extension
    will then return an error page.

--*/
{
    CHAR    szPath[MAX_PATH+1] = {0};
    CHAR    szLogFile[MAX_PATH+1] = {0};
    LPSTR   pCursor;

    //
    // Before doing anything, get the path to this extension.  This
    // will be used to find the INI file and open the log file.
    //
    // Note that we'll avoid crashing if an error occurs during this
    // phase of initialization, but we don't have any way of logging
    // errors until we open the log file (and if we fail to open the
    // log file, we won't ever be able to log errors.)
    //

    GetModuleFileName(
        GetModuleHandle( MODULE_NAME ),
        szPath,
        MAX_PATH
        );

    pCursor = strrchr( szPath, '.' );

    if ( pCursor )
    {
        *pCursor = '\0';

        //
        // Set the log file name
        //

        strcpy( szLogFile, szPath );
        strcat( szLogFile, ".log" );

        //
        // Now tweak the path so that it points
        // to the INI file for this extension
        //

        strcat( szPath, ".ini" );
    }

    //
    // Check to see if logging is enabled
    //

    g_EnableLogging = GetPrivateProfileInt(
        "ThreadPool",
        "EnableLogging",
        1, // Enable logging TRUE by default
        szPath
        );

    if ( g_EnableLogging )
    {
        //
        // Open the log file.  We'll allow read sharing so that the log
        // can be read while the extension is running.  Don't bother to
        // check for error, since we couldn't report it, and the
        // IsapiWriteLog function is smart enough to deal with it.
        //
        // In the event of a successful call, though, we will set the
        // last error to ERROR_SUCCESS, in case CreateFile set it to
        // ERROR_ALREADY_EXISTS.
        //

        g_hLogFile = CreateFile(
            szLogFile,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );
    }

    //
    // Initialize the log file lock.  From now on, the IsapiWriteLog
    // function is available for use.
    //

    if ( g_hLogFile != INVALID_HANDLE_VALUE )
    {
        SetLastError( ERROR_SUCCESS );
        InitializeCriticalSection( &g_LogFileLock );
    }

    //
    // Call the "real" GetExtensionVersion
    //

    g_InitSuccess = GetExtensionVersion( pVer );

    if ( g_InitSuccess == FALSE )
    {
        goto InitFailed;
    }

    //
    // Read thread pool settings from INI file
    //

    g_UseThreadPool = GetPrivateProfileInt(
        "ThreadPool",
        "UseThreadPool",
        1, // UseThreadPool = TRUE by default
        szPath
        );

    if ( g_UseThreadPool == 0 )
    {
        //
        // Don't initialize the thread pool, just return TRUE
        //

        IsapiWriteLog(
            "Extension %s configured to not use thread pool.\r\n",
            MODULE_NAME
            );

        return TRUE;
    }

    g_NumThreads = GetPrivateProfileInt(
        "ThreadPool",
        "NumThreads",
        0,
        szPath
        );

    g_QueueSize = GetPrivateProfileInt(
        "ThreadPool",
        "QueueSize",
        0,
        szPath
        );

    //
    // A zero value for either g_NumThreads or g_Queue size means that
    // we should use the defaults.  Also, don't let the number of threads
    // exceed the queue size. 
    //

    if ( g_NumThreads == 0 )
    {
        g_NumThreads = DEFAULT_THREADS;
    }

    if ( g_QueueSize == 0 )
    {
        g_QueueSize = DEFAULT_QUEUE;
    }

    if ( g_NumThreads > static_cast<DWORD>( g_QueueSize ) )
    {
        g_NumThreads = g_QueueSize;
    }

    //
    // Build the "queue full" response.  Since this is supposed to
    // happen when the server is busy, we'll create it here at init
    // time, so that we only have to blast it out at run time.
    //

    _snprintf(
        g_QueueFullResponse,
        RESPONSE_MAX_BUFFER,
        "<html>\r\n"
        "<head><title> Extension '%s.dll' too busy </title></head>\r\n"
        "<h1> Extension '%s.dll' Too Busy. </h1>\r\n"
        "<hr>\r\n"
        "Extension '%s.dll' is too busy right now.  Please try your "
        "request again in a few minutes.\r\n"
        "</html>",
        MODULE_NAME,
        MODULE_NAME,
        MODULE_NAME
        );

    g_cchQueueFullResponse = strlen( g_QueueFullResponse );

    _snprintf(
        g_QueueFullHeaders,
        RESPONSE_MAX_BUFFER,
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
        g_cchQueueFullResponse
        );

    g_cchQueueFullHeaders = strlen( g_QueueFullHeaders );

    //
    // Initialize the pool and queue
    //

    g_InitSuccess = InitThreadPool( g_QueueSize, g_NumThreads );

    if ( g_InitSuccess == FALSE )
    {
        goto InitFailed;
    }

    IsapiWriteLog(
        "Successfully initialized thread pool. QueueSize=%d, "
        "NumThreads=%d.\r\n",
        g_QueueSize,
        g_NumThreads
        );

    //
    // That's it, we're ready to go
    //

    return TRUE;

InitFailed:

    g_InitResultCode = GetLastError();

    IsapiWriteLog(
        "Attempt to initialize %s.dll failed with error %d.\r\n",
        MODULE_NAME,
        g_InitResultCode
        );

    return TRUE;
}

DWORD
WINAPI
HttpExtensionProcWrapper(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    This function handles queuing requests to be picked up by
    worker threads.  Before processing, it checks for a successful
    initialization.  If initialization failed, it sends back an
    error page to the client.  If it cannot successfully queue the
    request, it will return a "busy" page to the client (since the
    only practical reason for a queue failure is that the queue is
    full).

Arguments:

    pecb - A pointer to the EXTENSION_CONTROL_BLOCK for this request

Returns:

    One of the HSE_STATUS result codes

--*/
{
    BOOL    fResult;

    InterlockedIncrement( &g_TotalRequests );

    //
    // First, check to see if the extension initialized OK.
    //

    if ( g_InitSuccess == FALSE )
    {
        return SendExtensionInitFailed( pecb );
    }

    //
    // Check to see if we are using the thread pool.  If not,
    // then just call the "real" HttpExtensionProc
    //

    if ( g_UseThreadPool == FALSE )
    {
        return HttpExtensionProc( pecb );
    }

    //
    // Now attempt to queue the request.  If not successful,
    // send the "too busy" page.
    //

    fResult = QueueRequest( pecb );

    if ( fResult == FALSE )
    {
        return SendQueueFull( pecb );
    }

    //
    // Ok, so the request has been queued.  Return HSE_STATUS_PENDING
    // now.
    //

    return HSE_STATUS_PENDING;
}

BOOL
WINAPI
TerminateExtensionWrapper(
    DWORD   dwFlags
    )
/*++

Purpose:

    This function wraps TerminateExtension.  After calling
    TerminateExtension, it cleans up the queue and thread pool
    for this extension.

    Note that the TerminateExtension function implies that it
    is possible for an extension to refuse terminatation.  This
    feature was never implemented, so this wrapper always
    returns TRUE.

Arguments:

    dwFlags - Inidication that termination is optional (note
              that this will never happen)

Returns:

    Always returns TRUE.

--*/
{
    IsapiWriteLog(
        "Extension %s.dll terminating.\r\n",
        MODULE_NAME
        );
    
    //
    // Call the "real" TerminateExtension.  We don't need
    // its return value
    //

    TerminateExtension( dwFlags );

    //
    // Clean up the thread pool
    //

    ShutdownThreadPool();

    //
    // Close the log file
    //

    if ( g_hLogFile != INVALID_HANDLE_VALUE )
    {
        CloseHandle( g_hLogFile );
        g_hLogFile = INVALID_HANDLE_VALUE;

        DeleteCriticalSection( &g_LogFileLock );
    }

    return TRUE;
}

BOOL
InitThreadPool(
    DWORD   dwQueueSize,
    DWORD   dwNumThreads
    )
/*++

Purpose:

    This function initializes the thread pool and queue to the
    specified sizes

Arguments:

    dwQueueSize  - The size of the request queue
    dwNumThreads - The number of threads in the pool

Returns:

    TRUE on success, FALSE on failure

--*/
{
    DWORD   dwError = ERROR_SUCCESS;
    DWORD   dwThreadId;
    DWORD   x;

    //
    // If not using a thread pool, return now
    //

    if ( g_UseThreadPool == FALSE )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }

    //
    // Initialize the queue item count
    //

    g_ItemsInQueue = 0;

    //
    // Allocate storage for the thread handles
    //

    g_pThreads = reinterpret_cast<HANDLE*>( LocalAlloc(
        LPTR,
        g_NumThreads * sizeof( HANDLE * )
        ) );

    if ( g_pThreads == NULL )
    {
        IsapiWriteLog(
            "Insufficient memory to allocate thread handle storage.\r\n"
            );

        SetLastError( ERROR_NOT_ENOUGH_MEMORY );

        goto InitFailed;
    }

    //
    // Create the completion port for the thread pool
    //

    g_hCompletionPort = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE,
        NULL,
        0,
        0
        );

    if ( g_hCompletionPort == NULL )
    {
        IsapiWriteLog(
            "Error %d occured creating the pool's completion port.\r\n",
            GetLastError()
            );

        goto InitFailed;
    }

    //
    // Create the threads
    //

    for ( x = 0; x < g_NumThreads; x++ )
    {
        g_pThreads[x] = CreateThread(
            NULL,               // Security attributes
            0,                  // Stack size
            WorkerThreadProc,   // Start routine
            NULL,               // Parameter
            0,                  // Creation flags
            &dwThreadId         // ThreadId
            );

        if ( g_pThreads[x] == NULL )
        {
            IsapiWriteLog(
                "Error %d occured creating pool thread #%d.\r\n",
                GetLastError(),
                x
                );

            goto InitFailed;
        }
    }

    return TRUE;

InitFailed:

    dwError = GetLastError();

    //
    // ShutdownThreadPool is smart enough to clean up a partially
    // initialized pool.
    //

    ShutdownThreadPool();

    SetLastError( dwError );

    return FALSE;
}

VOID
ShutdownThreadPool(
    VOID
    )
/*++

Purpose:

    This function shuts down the thread pool and queue and deallocates
    any existing associated structures

Arguments:

    None

Returns:

    None

--*/
{
    DWORD   dwBlockIndex;
    DWORD   dwThreadsRemaining;
    DWORD   dwWaitCount;
    DWORD   x;

    //
    // If we're not using the thread pool, do nothing
    //

    if ( g_UseThreadPool == FALSE )
    {
        return;
    }

    //
    // If the completion port has been created and we have threads,
    // post completions with a NULL LPOVERLAPPED for each thread in
    // the pool, and delete it.  By setting LPOVERLAPPED to NULL,
    // we are signalling the threads that it's time to quit.
    //

    if ( g_hCompletionPort )
    {
        if ( g_pThreads != NULL )
        {
            for ( x = 0; x < g_NumThreads; x++ )
            {
                PostQueuedCompletionStatus(
                    g_hCompletionPort,
                    0,
                    0,
                    NULL
                    );
            }
        }

        CloseHandle( g_hCompletionPort );
        g_hCompletionPort = NULL;
    }

    if ( g_pThreads == NULL )
    {
        //
        // If no threads - we're done
        //

        goto Done;
    }

    //
    // Now wait for each of the threads to exit.  Note that we'll wait
    // an infinite amount of time here.
    //
    // There are only two conditions in which we'd expect to see
    // ShutdownThreadPool called: in the event of an init failure, or
    // when the TerminateExtension is called by the server.  In each
    // of these cases, we expect that all of the pool threads are
    // idle (TerminateExtension isn't called until all pending requests
    // are cleaned up).  As a result, we expect them to exit very
    // quickly.
    //
    // The only real action we could take in the event some thread
    // didn't exit would be to terminate it.  TerminateThread is documented
    // to be a dangerous function in that it leaks lots of resources, and
    // doesn't allow the thread to complete any work it's doing.  As such,
    // the remedy would be as bad as the problem - the process would be
    // in a potentially unstable state.  Consequently, we'll make no
    // attempt to recover from a thread that doesn't exit.
    //

    dwBlockIndex = 0;
    dwThreadsRemaining = g_NumThreads;

    while ( dwThreadsRemaining )
    {
        dwWaitCount = 
            ( dwThreadsRemaining < MAXIMUM_WAIT_OBJECTS ) ?
            dwThreadsRemaining :
            MAXIMUM_WAIT_OBJECTS;

        WaitForMultipleObjects(
            dwWaitCount,
            g_pThreads + ( dwBlockIndex * MAXIMUM_WAIT_OBJECTS ),
            TRUE,
            INFINITE
            );

        dwThreadsRemaining -= dwWaitCount;
        dwBlockIndex++;
    }

    //
    // Close our handles for each thread
    //

    for ( x = 0; x < g_NumThreads; x++ )
    {
        CloseHandle( g_pThreads[x] );
        g_pThreads[x] = NULL;
    }

    //
    // Finally, deallocate the thread handle storage buffer
    //

    LocalFree( g_pThreads );
    g_pThreads = NULL;

Done:

    g_QueueSize = 0;
    g_NumThreads = 0;
    g_ItemsInQueue = 0;

    return;
}

BOOL
QueueRequest(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    This function queues a request and signals the pool so that it
    can be picked up by the next available thread

Arguments:

    pecb - The EXTENSION_CONTROL_BLOCK for the request to be queued

Returns:

    TRUE on success, FALSE on failure

--*/
{
    LONG    lItems;
    BOOL    fResult;

    //
    // Can't do this if not using the thread pool
    //

    if ( g_UseThreadPool == FALSE )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }

    //
    // Increment the number of items in the queue.  If this call
    // pushes us over the limit, then back down the count and return
    // FALSE
    //

    lItems = InterlockedIncrement( &g_ItemsInQueue );

    if ( lItems > g_QueueSize )
    {
        InterlockedDecrement( &g_ItemsInQueue );

        //
        // If we return ERROR_SUCCESS and FALSE, then the caller knows
        // that the queue is full.
        //
        
        SetLastError( ERROR_SUCCESS );

        return FALSE;
    }

    //
    // Post a completion for this action.  This will release a pool
    // thread.  Note that we are overloading LPOVERLAPPED to pass
    // the EXTENSION_CONTROL_BLOCK to the worker thread.
    //

    fResult = PostQueuedCompletionStatus(
        g_hCompletionPort,
        0,
        0,
        reinterpret_cast<LPOVERLAPPED>( pecb )
        );

    if ( fResult == FALSE )
    {
        IsapiWriteLog(
            "Failed to post completion.  Error %d.\r\n",
            GetLastError()
            );

        InterlockedDecrement( &g_ItemsInQueue );

        return FALSE;
    }

    return TRUE;
}

DWORD
WINAPI
WorkerThreadProc(
    VOID *  pVoid
    )
/*++

Purpose:

    This function implements the worker thread loop that dispatches
    calls to the "real" HttpExtensionProc.

Arguments:

    pVoid - Required by CreateThread; not used.

Returns:

    Always returns 0

--*/
{
    EXTENSION_CONTROL_BLOCK *   pecb;
    HANDLE                      hToken = NULL;
    DWORD                       cbIo;
    DWORD                       dwKey;
    DWORD                       dwInitResultCode = ERROR_SUCCESS;
    DWORD                       dwThreadId;
    DWORD                       dwError;
    DWORD                       HseResult;
    BOOL                        fInitSuccess = TRUE;
    BOOL                        fCompletionResult = TRUE;

    dwThreadId = GetCurrentThreadId();

    //
    // Call the thread initialization function
    //

    fInitSuccess = InitThread();

    if ( fInitSuccess == FALSE )
    {
        dwInitResultCode = GetLastError();

        IsapiWriteLog(
            "Attempt to initialized thread %d failed.  Error %d.\r\n",
            dwThreadId,
            dwInitResultCode
            );
    }

    while ( TRUE )
    {
        //
        // Wait for some work
        //

        fCompletionResult = GetQueuedCompletionStatus(
            g_hCompletionPort,
            &cbIo,
            &dwKey,
            reinterpret_cast<LPOVERLAPPED*>( &pecb ),
            INFINITE
            );

        dwError = GetLastError();

        //
        // Before doing anything else, back down the queue item count
        //

        InterlockedDecrement( &g_ItemsInQueue );

        if ( fCompletionResult == FALSE )
        {
            IsapiWriteLog(
                "Thread %d: GetQueuedCompletionStatus failed with error %d. "
                "Thread will terminate.\r\n",
                dwThreadId,
                dwError
                );

            break;
        }

        //
        // If pecb is NULL, then we are supposed to exit the thread, else
        // we'll process the request.
        //

        if ( pecb == NULL )
        {
            break;
        }

        //
        // If the thread initialization failed, return an error to the
        // client
        //

        if ( fInitSuccess == FALSE )
        {
            SendThreadInitFailed( pecb, dwInitResultCode );
            continue;
        }

        //
        // Impersonate the authenticated user
        //

        pecb->ServerSupportFunction(
            pecb->ConnID,
            HSE_REQ_GET_IMPERSONATION_TOKEN,
            &hToken,
            NULL,
            NULL
            );

        ImpersonateLoggedOnUser( &hToken );

        //
        // Finally, call into the "real" HttpExtensionProc.  If it returns
        // HSE_STATUS_PENDING, then we're done.  Otherwise, we'll need to
        // call HSE_REQ_DONE_WITH_SESSION and pass along the result.
        //
        // Note that there is a potential incompatibility with the
        // HSE_STATUS_PENDING case.  Specifically, IIS cleans up the ECB in
        // such a way that both HttpExtensionProc must return, and
        // HSE_REQ_DONE_WITH_SESSION must be called (assuming a pending
        // extension) before IIS frees the ECB.
        //
        // If this wrapper is used with an extension that depends on this
        // protection from IIS, then a potential crash could occur in the
        // "real" HttpExtensionProc if DONE_WITH_SESSION occurs before it
        // returns with HSE_STATUS_PENDING.  This is because the wrapper
        // already returned STATUS_PENDING before we get here.  Thus, the
        // ECB will get freed immediately upon DONE_WITH_SESSION, even if
        // the "real" HttpExtensionProc hasn't returned yet.
        //
        // This won't be a problem if the "real" HttpExtensionProc doesn't
        // touch the ECB after DONE_WITH_SESSION could potentially be
        // called.
        //
        // And just a final note that any extension that already returns
        // HSE_STATUS_PENDING is not a good candidate to be wrapped by
        // PoolWrap, since it's already asynchronous in nature.
        //

        HseResult = HttpExtensionProc( pecb );

        RevertToSelf();
        hToken = NULL;

        if ( HseResult == HSE_STATUS_PENDING )
        {
            continue;
        }

        pecb->ServerSupportFunction(
            pecb->ConnID,
            HSE_REQ_DONE_WITH_SESSION,
            &HseResult,
            NULL,
            NULL
            );

        //
        // Done, just let the thread loop around and wait again.
        //
    }

    //
    // Uninitialize the thread
    //

    UninitThread();

    return 0;
}

BOOL
IsapiWriteLog(
    LPSTR   szString,
    ...
    )
/*++

Purpose:

    This function writes a line to the log for this extension using
    printf-style formatting.

Arguments:

    szString - The format string
    ...      - Additional arguments

Returns:

    TRUE on success, FALSE on failure

--*/
{
    SYSTEMTIME  st;
    CHAR        szCookedString[LOG_MAX_LINE+1];
    CHAR        szTime[32];
    CHAR        szDate[32];
    CHAR        szTimeStamp[64];
    INT         cchCookedString;
    DWORD       cbToWrite;
    va_list     args;
    BOOL        fResult;

    //
    // If we don't have a log file handle, just return
    //

    if ( g_hLogFile == INVALID_HANDLE_VALUE )
    {
        SetLastError( ERROR_FILE_NOT_FOUND );
        return FALSE;
    }

    //
    // Apply formatting to the string
    //

    va_start( args, szString );

    cchCookedString = _vsnprintf(
        szCookedString,
        LOG_MAX_LINE,
        szString,
        args
        );

    va_end(args);

    //
    // Generate the time stamp
    //

    GetLocalTime( &st );

	GetTimeFormat(
        LOCALE_SYSTEM_DEFAULT,
        0,
        &st,
        "HH':'mm':'ss",
        szTime,
        32
        );

	GetDateFormat(
        LOCALE_SYSTEM_DEFAULT,
        0,
        &st,
        "ddd',' MMM dd yyyy",
        szDate,
        32
        );

    wsprintf( szTimeStamp, "[%s - %s] ", szDate, szTime );

    //
    // Acquire the lock and write out the log entry
    //

    EnterCriticalSection( &g_LogFileLock );

    SetFilePointer( g_hLogFile, 0, NULL, FILE_END );

    cbToWrite = strlen( szTimeStamp );

    WriteFile(
        g_hLogFile,
        szTimeStamp,
        cbToWrite,
        &cbToWrite,
        NULL
        );

    cbToWrite = cchCookedString;

    fResult = WriteFile(
        g_hLogFile,
        szCookedString,
        cbToWrite,
        &cbToWrite,
        NULL
        );

    LeaveCriticalSection( &g_LogFileLock );
    
	return fResult;
}

DWORD
SendExtensionInitFailed(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Sends back a message to the client in the event that initialization
    of this extension failed.

Arguments:

    pecb - Pointer to the EXTENSION_CONTROL_BLOCK for this request

Returns:

    HSE_STATUS_ERROR

--*/
{
    HSE_SEND_HEADER_EX_INFO HeaderInfo;
    CHAR                    szResponse[RESPONSE_MAX_BUFFER+1] = {0};
    CHAR                    szHeaders[RESPONSE_MAX_BUFFER+1] = {0};
    CHAR                    szDefaultError[64] = {0};
    LPSTR                   szTranslatedError = NULL;\
    LPSTR                   szError = NULL;
    DWORD                   cbToWrite;
    DWORD                   cchResponse;
    DWORD                   cchError;
    BOOL                    fResult;

    //
    // Build the response and error information
    //

    _snprintf(
        szResponse,
        RESPONSE_MAX_BUFFER,
        "<html>\r\n"
        "<head><title> Extension '%s.dll' not initialized </title></head>\r\n"
        "<h1> Extension '%s.dll' Not Initialized. </h1>\r\n"
        "Extension '%s.dll' failed to initialize with the following error. "
        "Please notify the administrator for this site."
        "<hr>\r\n",
        MODULE_NAME,
        MODULE_NAME,
        MODULE_NAME
        );

    cchResponse = strlen( szResponse );

    fResult = AllocateAndFormatErrorMessage(
        g_InitResultCode,
        &szTranslatedError
        );

    if ( fResult == FALSE )
    {
        _snprintf(
            szDefaultError,
            63,
            "%d (0x%08x)\r\n"
            "</html>",
            g_InitResultCode,
            g_InitResultCode
            );

        szError = szDefaultError;
    }
    else
    {
        szError = szTranslatedError;
    }

    cchError = strlen( szError );

    //
    // Send the response to the client
    //

    _snprintf(
        szHeaders,
        RESPONSE_MAX_BUFFER,
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
        cchResponse + cchError
        );

    HeaderInfo.pszStatus = "500 Server Error";
    HeaderInfo.pszHeader = szHeaders;
    HeaderInfo.cchStatus = strlen( HeaderInfo.pszStatus );
    HeaderInfo.cchHeader = strlen( HeaderInfo.pszHeader );
    HeaderInfo.fKeepConn = TRUE;

    pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_SEND_RESPONSE_HEADER_EX,
        &HeaderInfo,
        NULL,
        NULL
        );

    cbToWrite = cchResponse;

    pecb->WriteClient(
        pecb->ConnID,
        szResponse,
        &cbToWrite,
        HSE_IO_SYNC
        );

    cbToWrite = cchError;

    pecb->WriteClient(
        pecb->ConnID,
        szError,
        &cbToWrite,
        HSE_IO_SYNC
        );

    //
    // Clean up the formatted error if we got it
    //

    if ( szTranslatedError != NULL )
    {
        LocalFree( szTranslatedError );
        szTranslatedError = NULL;
    }

    return HSE_STATUS_ERROR;
}

DWORD
SendQueueFull(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Sends back a "too busy" message to the client.  Note that
    all of the parts of the response were created at extension
    init time, so that we can just blast the result back to the
    client (since presumably, the server is really busy when
    this function is called.)

Arguments:

    pecb - Pointer to the EXTENSION_CONTROL_BLOCK for this request

Returns:

    HSE_STATUS_ERROR

--*/
{
    HSE_SEND_HEADER_EX_INFO HeaderInfo;
    DWORD                   cbToWrite;

    InterlockedIncrement( &g_QueueFullPages );

    HeaderInfo.pszStatus = "500 Server Error";
    HeaderInfo.cchStatus = 16; // length of "500 Server Error"
    HeaderInfo.pszHeader = g_QueueFullHeaders;
    HeaderInfo.cchHeader = g_cchQueueFullHeaders;
    HeaderInfo.fKeepConn = TRUE;

    cbToWrite = g_cchQueueFullResponse;

    pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_SEND_RESPONSE_HEADER_EX,
        &HeaderInfo,
        NULL,
        NULL
        );

    pecb->WriteClient(
        pecb->ConnID,
        g_QueueFullResponse,
        &cbToWrite,
        HSE_IO_SYNC
        );

    return HSE_STATUS_ERROR;
}

BOOL
SendThreadInitFailed(
    EXTENSION_CONTROL_BLOCK *   pecb,
    DWORD                       dwError
    )
/*++

Purpose:

    Sends a response back to the client indicating that the
    thread failed to initialize.

Arguments:

    pecb     - Pointer to the EXTENSION_CONTROL_BLOCK for the request
    dwError  - The initialization error

Returns:

    TRUE on success, FALSE on failure

--*/
{
    HSE_SEND_HEADER_EX_INFO HeaderInfo;
    CHAR                    szResponse[RESPONSE_MAX_BUFFER+1] = {0};
    CHAR                    szHeaders[RESPONSE_MAX_BUFFER+1] = {0};
    CHAR                    szDefaultError[64] = {0};
    LPSTR                   szTranslatedError = NULL;\
    LPSTR                   szError = NULL;
    DWORD                   cbToWrite;
    DWORD                   cchResponse;
    DWORD                   cchError;
    DWORD                   HseResult;
    BOOL                    fResult;

    //
    // Build the response and error information
    //

    _snprintf(
        szResponse,
        RESPONSE_MAX_BUFFER,
        "<html>\r\n"
        "<head><title> Extension '%s.dll' error. </title></head>\r\n"
        "<h1> Extension '%s.dll' failed to fully initialize. </h1>\r\n"
        "Extension '%s.dll': Thread %d failed to initialize with the "
        "following error.  Please notify the administrator for this site."
        "<hr>\r\n",
        MODULE_NAME,
        MODULE_NAME,
        MODULE_NAME,
        GetCurrentThreadId()
        );

    cchResponse = strlen( szResponse );

    fResult = AllocateAndFormatErrorMessage(
        dwError,
        &szTranslatedError
        );

    if ( fResult == FALSE )
    {
        _snprintf(
            szDefaultError,
            63,
            "%d (0x%08x)\r\n"
            "</html>",
            dwError,
            dwError
            );

        szError = szDefaultError;
    }
    else
    {
        szError = szTranslatedError;
    }

    cchError = strlen( szError );

    //
    // Send the response to the client
    //

    _snprintf(
        szHeaders,
        RESPONSE_MAX_BUFFER,
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
        cchResponse + cchError
        );

    HeaderInfo.pszStatus = "500 Server Error";
    HeaderInfo.pszHeader = szHeaders;
    HeaderInfo.cchStatus = strlen( HeaderInfo.pszStatus );
    HeaderInfo.cchHeader = strlen( HeaderInfo.pszHeader );
    HeaderInfo.fKeepConn = TRUE;

    pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_SEND_RESPONSE_HEADER_EX,
        &HeaderInfo,
        NULL,
        NULL
        );

    cbToWrite = cchResponse;

    pecb->WriteClient(
        pecb->ConnID,
        szResponse,
        &cbToWrite,
        HSE_IO_SYNC
        );

    cbToWrite = cchError;

    pecb->WriteClient(
        pecb->ConnID,
        szError,
        &cbToWrite,
        HSE_IO_SYNC
        );

    //
    // Since this error is always called on pending request,
    // we need to call DONE_WITH_SESSION
    //

    HseResult = HSE_STATUS_ERROR;

    pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_DONE_WITH_SESSION,
        &HseResult,
        NULL,
        NULL
        );

    //
    // Clean up the formatted error if we got it
    //

    if ( szTranslatedError != NULL )
    {
        LocalFree( szTranslatedError );
        szTranslatedError = NULL;
    }

    return TRUE;
}

BOOL
AllocateAndFormatErrorMessage(
    DWORD   dwError,
    LPSTR * ppBuffer
    )
/*++

Purpose:

    Maps an error code into a text message into a new buffer.
    The caller needs to free the buffer with LocalFree when done.

Arguments:

    dwError  - The error to map.
    ppBuffer - Upon successful return, the error text buffer

Returns:

    TRUE on success, FALSE on failure

--*/
{
    BOOL    fResult;

    fResult = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_IGNORE_INSERTS |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dwError,
        0,
        reinterpret_cast<CHAR*>( ppBuffer ),
        0,
        NULL
        );

    IsapiWriteLog(
        "FormatMessage failed. Error %d.\r\n",
        GetLastError()
        );

    return fResult;
}
