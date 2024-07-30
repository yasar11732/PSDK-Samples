/*++

Copyright (c) 2003  Microsoft Corporation

Module Name:  WildCardMap.cpp

Abstract:

    ISAPI extension to demonstrate a very simple wildcard
    script map that sees a request and passes it along for
    further processing.

Author:

    ISAPI developer (Microsoft employee), July 2002

--*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <stdio.h>
#include <windows.h>
#include <httpext.h>

#define MODULE_NAME         "WildCardMap"
#define WRITE_BUFFER_SIZE   1000

VOID
WINAPI
ExecUrlCompletion (
    EXTENSION_CONTROL_BLOCK *   pecb,
    PVOID                       pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    );

BOOL
SendServerError(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

VOID
WriteDebug(
    LPSTR   szFormat,
    ...
    );

BOOL
WINAPI
GetExtensionVersion(
    HSE_VERSION_INFO *  pVer
    )
/*++

Purpose:

    Entry point for ISAPI extension initialization.  Required.

    This function will be called exactly once in the lifetime
    of the extension, at initialization time.  This function is
    a useful point to do complex initialization tasks.  This
    function is called outside of the system loader lock, so
    it does not have the same restrictions as DllMain.

Arguments:

    pVer - points to extension version info structure 

Returns:

    TR2UE on success, FALSE on failure.
    
    Note that in the case of FALSE, IIS will call GetLastError()
    and return an error page to the client.  The entity body of
    the page may be textual if the FormatMessage API can resolve
    it, or it may just be an error number if FormatMessage can't
    resolve it.

--*/
{
    //
    // Tell IIS which version of ISAPI this extension was build from.
    //

    pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR,
                                         HSE_VERSION_MAJOR);

    //
    // Report the description string for this extension.  Ensure
    // that it does not exceed the maximum length and is NULL
    // terminated.
    //

    strncpy( pVer->lpszExtensionDesc,
             "WildCardMap Sample ISAPI Extension",
             HSE_MAX_EXT_DLL_NAME_LEN );

    pVer->lpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN-1] = '\0';

    //
    // Return TRUE if we successfully initialized.
    //

	return TRUE;
}

DWORD
WINAPI
HttpExtensionProc(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Entry point for ISAPI requests.  Required.

    This function is called once per request.  The EXTENSION_CONTROL_BLOCK
    passed in contains information and function pointers sufficient to
    interact with the server during this processing.

    Note that, once HttpExtensionProc is called, it is the responsibility
    of the extension to send back any data that the client should receive.
    IIS will not automatically generate any response, even in the case of
    HSE_STATUS_ERROR once the request has progressed to the point where
    this function is called.

    Also note that you should not make any blocking calls or do long-running
    operations within this function.  To allow efficient scaling of your
    server, you should consider creating a pool of private threads to handle
    the requests.  In that case, the implementation of this function would
    be just to add the pecb to a queue and return HSE_STATUS_PENDING.  The
    threads in the pool would be responsible for dequeing a pecb and calling
    HSE_REQ_DONE_WITH_SESSION when they are finished processing it.

Arguments:

    pecb - pointer to the extenstion control block 

Returns:

    HSE_STATUS_SUCCESS - Indicates successful request.
    HSE_STATUS_ERROR   - Indicates failed request.
    HSE_STATUS_PENDING - Indicates that processing of the request
                         should continue after this function returns.
                         It HSE_STATUS_PENDING is used, it is necessary
                         that HSE_REQ_DONE_WITH_SESSION is called
                         exactly once when processing is completed for
                         the request.

--*/
{
    HSE_EXEC_URL_INFO   ExecUrlInfo;
    LPSTR               pUrl = NULL;
    DWORD               cbData;

    //
    // Acquire the URL for the current request.
    //

    if ( pecb->GetServerVariable( pecb->ConnID,
                                  "URL",
                                  NULL,
                                  &cbData ) == FALSE )
    {
        if ( GetLastError() == ERROR_INSUFFICIENT_BUFFER )
        {
            pUrl = (LPSTR)LocalAlloc( LPTR, cbData );

            if ( pUrl )
            {
                pecb->GetServerVariable( pecb->ConnID,
                                         "URL",
                                         pUrl,
                                         &cbData );
            }
        }
    }

    if ( !pUrl )
    {
        WriteDebug( "Error %d occurred acquiring URL.\r\n",
                    GetLastError() );

        goto Failed;
    }

    //
    // Since this is just a sample to demonstrate a very simple
    // wildcard script map, we aren't going to actually modify
    // or otherwise process the request.  We'll just report our
    // presence and then call the original URL using
    // HSE_REQ_EXEC_URL.
    //

    WriteDebug( "Request Received: URL=%s\r\n",
                pUrl );

    ExecUrlInfo.pszUrl = NULL;          // Use original request URL
    ExecUrlInfo.pszMethod = NULL;       // Use original request method
    ExecUrlInfo.pszChildHeaders = NULL; // Use original request headers
    ExecUrlInfo.pUserInfo = NULL;       // Use original request user info
    ExecUrlInfo.pEntity = NULL;         // Use original request entity

    //
    // Since this extension is intended to be used as a wildcard script
    // map, we need to set the below flag to prevent recursion, which
    // can occur in some cases.
    //

    ExecUrlInfo.dwExecUrlFlags = HSE_EXEC_URL_IGNORE_CURRENT_INTERCEPTOR;

    //
    // Associate the completion routine and the current URL with
    // this request.
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_IO_COMPLETION,
                                      ExecUrlCompletion,
                                      NULL,
                                      (LPDWORD)pUrl ) == FALSE )
    {
        WriteDebug( "Error %d occurred setting I/O completion.\r\n",
                     GetLastError() );

        goto Failed;
    }

    //
    // Ok, now that everything is set up, let's call the child request.
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_EXEC_URL,
                                      &ExecUrlInfo,
                                      NULL,
                                      NULL ) == FALSE )
    {
        WriteDebug( "Error %d occurred calling HSE_REQ_EXEC_URL.\r\n",
                     GetLastError() );

        goto Failed;
    }

    //
    // Return pending and let the completion clean up.
    //

    return HSE_STATUS_PENDING;

Failed:

    if ( pUrl )
    {
        LocalFree( pUrl );
        pUrl = NULL;
    }

    SendServerError( pecb );

    return HSE_STATUS_ERROR;
}

VOID
WINAPI
ExecUrlCompletion (
    EXTENSION_CONTROL_BLOCK *   pecb,
    PVOID                       pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    )
{
    HSE_EXEC_URL_STATUS ExecUrlStatus;
    CHAR                szStatus[32] = "";
    CHAR                szWin32Error[32] = "";
    LPSTR               pChildUrl;
    BOOL                fResult;

    pChildUrl = (LPSTR)pContext;

    //
    // Get the results of the child request and report it.
    //
    
    fResult = pecb->ServerSupportFunction( pecb->ConnID,
                                           HSE_REQ_GET_EXEC_URL_STATUS,
                                           &ExecUrlStatus,
                                           NULL,
                                           NULL );

    if ( fResult )
    {
        if ( ExecUrlStatus.uHttpSubStatus != 0 )
        {
            _snprintf( szStatus,
                       32,
                       "Child Status=%d.%d",
                       ExecUrlStatus.uHttpStatusCode,
                       ExecUrlStatus.uHttpSubStatus );
        }
        else
        {
            _snprintf( szStatus,
                       32,
                       "%d",
                       ExecUrlStatus.uHttpStatusCode );
        }

        szStatus[31] = '\0';

        if ( ExecUrlStatus.dwWin32Error != ERROR_SUCCESS )
        {
            _snprintf( szWin32Error,
                       16,
                       "ErrorCode=%d, ",
                       ExecUrlStatus.dwWin32Error );

            szWin32Error[31] = '\0';
        }

        WriteDebug( "ExecUrl Completion: %s, %sURL=%s.\r\n",
                    szStatus,
                    szWin32Error,
                    pChildUrl );
    }
    else
    {
        WriteDebug( "ExecUrl Completion: Error %d, URL=%s.\r\n",
                    GetLastError(),
                    pChildUrl );
    }

    //
    // Clean up the context pointer
    //

    if ( pChildUrl )
    {
        LocalFree( pChildUrl );
        pChildUrl = NULL;
    }

    //
    // Notify IIS that we are done with this request
    //

    pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_DONE_WITH_SESSION,
        NULL,
        NULL,
        NULL
        );
}

BOOL
SendServerError(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
{
    DWORD   cbData;
    CHAR    szError[] = "<html>\r\n"
                        "<head><title> A server error occurred. </title></head>\r\n"
                        "<h1> Server Error </h1>\r\n"
                        "<hr>\r\n"
                        "An error occurred processing this request.";

    //
    // Set the status code so that a 500 gets logged in the w3svc log.
    //

    pecb->dwHttpStatusCode = 500;

    //
    // Send headers and response
    //

    pecb->ServerSupportFunction( pecb->ConnID,
                                 HSE_REQ_SEND_RESPONSE_HEADER,
                                 "500 Server Error",
                                 NULL,
                                 (LPDWORD)"Content-Type: text/html\r\n\r\n" );

    cbData = sizeof( szError );

    return pecb->WriteClient( pecb->ConnID,
                              szError,
                              &cbData,
                              HSE_IO_SYNC );
}

VOID
WriteDebug(
    LPSTR   szFormat,
    ...
    )
{
    CHAR    szBuffer[WRITE_BUFFER_SIZE];
    LPSTR   pCursor;
    DWORD   cbToWrite;
    INT     nWritten;
    va_list args;

    if ( WRITE_BUFFER_SIZE < 3 )
    {
        //
        // This is just too small to deal with...
        //

        return;
    }

    //
    // Inject the module name tag into the buffer
    //

    nWritten = _snprintf( szBuffer,
                          WRITE_BUFFER_SIZE,
                          "[%s.dll] ",
                          MODULE_NAME );

    if ( nWritten == -1 )
    {
        return;
    }

    pCursor = szBuffer + nWritten;
    cbToWrite = WRITE_BUFFER_SIZE - nWritten;

    va_start( args, szFormat );

    nWritten = _vsnprintf( pCursor,
                           cbToWrite,
                           szFormat,
                           args );

    va_end( args );

    if ( nWritten == -1 )
    {
        szBuffer[WRITE_BUFFER_SIZE-3] = '\r';
        szBuffer[WRITE_BUFFER_SIZE-2] = '\n';
    }

    szBuffer[WRITE_BUFFER_SIZE-1] = '\0';

    OutputDebugString( szBuffer );
}
