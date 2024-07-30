/*++

Copyright (c) 2003 Microsoft Corporation

Module Name: Extension.cpp

Abstract:

    ISAPI extension to demonstrate the PoolWrap thread pool wrapper.
    This could be just about any extension.

    Basic functionality is as follows:

    - A request with no query string will display the help page
    - A request with query string of "statistics" will return a page
      listing total request and busy page counts since this extension
      was initialized
    - A request with a single numeric argument on the query string will
      simulate waiting on a blocking call by sleeping for that number
      of milliseconds
    - A request with two numeric arguments on the query string separated
      by a '+' will simulate waiting on a blocking call by sleeping for
      a random amount of time between the first number and second number
      in milliseconds (if the second number is smaller than the first,
      then the help page will be returned)

Author:

    ISAPI developer (Microsoft employee), January 2001

--*/

#define _WIN32_WINNT 0x0500

#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <httpext.h>
#include "PoolWrap.h"

#define STRING_BUFFER   1024

//
// Globals
//

SYSTEMTIME  g_StartTime;

//
// Private definitions
//

VOID
CopyStringAndTerminate(
    LPSTR   szTarget,
    LPSTR   szSource,
    DWORD   cbTarget = 0
    );

DWORD
SendHelpPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

DWORD
SendStatisticsPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

BOOL
SendHeaders(
    EXTENSION_CONTROL_BLOCK *   pecb,
    LPSTR                       szStatus,
    LPSTR                       szHeaders,
    DWORD                       cbContent = 0
    );

//
// Implement functions required by PoolWrap.  This includes the 3 well
// known ISAPI entry points, plus the InitThread function.
//

BOOL
InitThread(
    VOID
    )
{
    //
    // Don't do any special initialization
    //

    return TRUE;
}

VOID
UninitThread(
    VOID
    )
{
    //
    // Don't do any special uninitialization
    //

    return;
}

BOOL
WINAPI
GetExtensionVersion(
    HSE_VERSION_INFO *pVer
    )
/*++

Purpose:

    This is a required ISAPI Extension DLL entry point.

Arguments:

    pVer - points to extension version info structure 

Returns:

    TRUE on success, FALSE on failure.  Note that on a FALSE
    return, it should ensure that the Win32 last error is set.

--*/
{
	//
    // Set the extension version
    //
    
    pVer->dwExtensionVersion = MAKELONG(
        HSE_VERSION_MINOR,
        HSE_VERSION_MAJOR
        );

    //
    // Set the extension description
    //

	lstrcpyn(
        pVer->lpszExtensionDesc,
        "TestPoolWrap test ISAPI extension",
        HSE_MAX_EXT_DLL_NAME_LEN
        );

    //
    // Seed the random number generator and get the
    // time at which this extension initialized
    //

    srand( (unsigned)time( NULL ) );

    GetLocalTime( &g_StartTime );

	return TRUE;
}

DWORD
WINAPI
HttpExtensionProc(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Entry point for requests to this extension

    Note that we assume that the response will fit into our
    string buffer, and don't take any action to prevent a
    problem with this (since the client can't do anything
    to increase the size of the response).

Arguments:

    pecb - Pointer to the EXTENSION_CONTROL_BLOCK for this request

Returns:

    One of the HSE_STATUS result codes

--*/
{
    CHAR    szQuery[STRING_BUFFER+1] = {0};
    CHAR    szContent[STRING_BUFFER+1] = {0};
    LPSTR   pCursor;
    DWORD   dwMinWait;
    DWORD   dwMaxWait;
    DWORD   dwSleepTime;
    DWORD   cbToSend;

    //
    // Process the query string
    //

    if ( pecb->lpszQueryString[0] == '\0' )
    {
        return SendHelpPage( pecb );
    }

    if ( stricmp( pecb->lpszQueryString, "statistics" ) == NULL )
    {
        return SendStatisticsPage( pecb );
    }

    CopyStringAndTerminate( szQuery, pecb->lpszQueryString, STRING_BUFFER );

    pCursor = strchr( szQuery, '+' );

    if ( pCursor == NULL )
    {
        dwMinWait = atol( szQuery );
        dwMaxWait = dwMinWait;
    }
    else
    {
        *pCursor = '\0';

        dwMinWait = atol( szQuery );
        dwMaxWait = atol( pCursor + 1 );
    }

    //
    // Calculate the sleep time and do it
    //

    if ( dwMaxWait < dwMinWait )
    {
        return SendHelpPage( pecb );
    }

    if ( dwMaxWait > dwMinWait )
    {
        dwSleepTime = dwMinWait + ( rand() % ( dwMaxWait - dwMinWait ) );
    }
    else
    {
        dwSleepTime = dwMinWait;
    }

    Sleep( dwSleepTime );

    //
    // Now send the response
    //

    _snprintf(
        szContent,
        STRING_BUFFER,
        "<html>\r\n"
        "<head> <title> %s.dll </title> </head>\r\n"
        "<h1> %s.dll </h1>\r\n"
        "<hr>\r\n"
        "%s.dll has sent this response after simulating a wait "
        "for %d milliseconds.",
        MODULE_NAME,
        MODULE_NAME,
        MODULE_NAME,
        dwSleepTime
        );

    cbToSend = strlen( szContent );

    SendHeaders(
        pecb,
        "200 OK",
        "Content-Type: text/html\r\n\r\n",
        cbToSend
        );

    pecb->WriteClient(
        pecb->ConnID,
        szContent,
        &cbToSend,
        HSE_IO_SYNC | HSE_IO_NODELAY
        );

    return HSE_STATUS_SUCCESS;
}

BOOL
WINAPI
TerminateExtension(
    DWORD dwFlags
    )
/*++

Purpose:

    This is optional ISAPI extension DLL entry point.
    If present, it will be called before unloading the DLL,
    giving it a chance to perform any shutdown procedures.
    
Arguments:
    
    dwFlags - Specifies whether the DLL can refuse to unload or not.  Note
              that the case where refusal is allowed is not supported and
              should not be expected.
    
Returns:
    
    TRUE, if the DLL can be unloaded
    
--*/
{
    switch ( dwFlags )
    {
    case HSE_TERM_ADVISORY_UNLOAD:
        
        //
        // Return TRUE if ok to unload or FALSE if not.
        //
        // This case is not expected to occur
        //

        return TRUE;

    case HSE_TERM_MUST_UNLOAD:

        //
        // Cannot refuse to unload
        //

        return TRUE;
    }

    return TRUE;
}

VOID
CopyStringAndTerminate(
    LPSTR   szTarget,
    LPSTR   szSource,
    DWORD   cbTarget
    )
/*++

Purpose:

    This function is just a wrapper for strncpy.  If cbTarget is
    non-zero, it will NULL terminate the last character in the
    buffer.  This will help prevent buffer overruns by ensuring
    it's always safe to call string functions on the target.

    If you use strncpy without taking this extra step, and
    szSource is longer than szTarget, then szTarget will not be
    NULL terminated, and string operations can overrun the buffer.
    
Arguments:
    
    szTarget - The target buffer
    szSource - The data to be copied
    cbTarget - The size of szTarget
  
Returns:
    
    None
    
--*/
{
    if ( cbTarget == 0 )
    {
        strcpy( szTarget, szSource );
    }
    else
    {
        strncpy( szTarget, szSource, cbTarget );
        szTarget[cbTarget-1] = '\0';
    }
}

DWORD
SendHelpPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Returns the help page to the client
  
Arguments:

    pecb - The EXTENSION_CONTROL_BLOCK for the request
  
    Note that we assume that the response will fit into our
    string buffer, and don't take any action to prevent a
    problem with this (since the client can't do anything
    to increase the size of the response).
    
Returns:
    
    HSE_STATUS_SUCCESS
    
--*/
{
    CHAR    szContent[STRING_BUFFER+1] = {0};
    DWORD   cbToSend;

    _snprintf(
        szContent,
        STRING_BUFFER,
        "<html>\r\n"
        "<head> <title> %s.dll </title> </head>\r\n"
        "<h1> %s.dll </h1>\r\n"
        "A simple extension to demonstrate PoolWrap.cpp."
        "<hr>\r\n"
        "A request with no query string, or an invalid query "
        "string, will return this page.  The following querys "
        "will produce the specified results:<br>\r\n"
        "<br>\r\n"
        "<code>http://server/DemoPoolWrap.dll?statistics</code><br>\r\n"
        "Returns some statistics from this extension <br><br>\r\n"
        "<code>http://server/DemoPoolWrap.dll?&lttime&gt</code><br>\r\n"
        "Returns a page after waiting on a blocking call for the "
        "specified number of milliseconds <br><br>\r\n"
        "<code>http://server/DemoPoolWrap.dll?&ltmin-time&gt+&ltmax-time&gt</code><br>\r\n"
        "Returns a page after waiting on a blocking call for a random "
        "interval in the specified range in milliseconds",
        MODULE_NAME,
        MODULE_NAME
        );

    cbToSend = strlen( szContent );

    SendHeaders(
        pecb,
        "200 OK",
        "Content-Type: text/html\r\n\r\n",
        cbToSend
        );

    pecb->WriteClient(
        pecb->ConnID,
        szContent,
        &cbToSend,
        HSE_IO_SYNC | HSE_IO_NODELAY
        );

    return HSE_STATUS_SUCCESS;
}

DWORD
SendStatisticsPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Returns the statistics page to the client.

    Note that we assume that the response will fit into our
    string buffer, and don't take any action to prevent a
    problem with this (since the client can't do anything
    to increase the size of the response).
  
Arguments:

    pecb - The EXTENSION_CONTROL_BLOCK for the request
  
Returns:
    
    HSE_STATUS_SUCCESS
    
--*/
{
    CHAR    szContent[STRING_BUFFER+1];
    CHAR    szStartTime[64];
    CHAR    szTime[32];
    CHAR    szDate[32];
    DWORD   cbToSend;

    //
    // Generate the start time stamp
    //

    GetLocalTime( &g_StartTime );

	GetTimeFormat(
        LOCALE_SYSTEM_DEFAULT,
        0,
        &g_StartTime,
        "HH':'mm':'ss",
        szTime,
        32
        );

	GetDateFormat(
        LOCALE_SYSTEM_DEFAULT,
        0,
        &g_StartTime,
        "ddd',' MMM dd yyyy",
        szDate,
        32
        );

    wsprintf( szStartTime, "[%s - %s] ", szDate, szTime );

    //
    // Generate the response
    //

    _snprintf(
        szContent,
        STRING_BUFFER,
        "<html>\r\n"
        "<head> <title> %s.dll </title> </head>\r\n"
        "<h1> %s.dll Statistics:</h1>\r\n"
        "<hr>\r\n"
        "The extension was started at: %s<br>\r\n\r\n"
        "Total Pages Served: %d<br>\r\n"
        "Busy Pages Served: %d<br>",
        MODULE_NAME,
        MODULE_NAME,
        szStartTime,
        g_TotalRequests,
        g_QueueFullPages
        );

    cbToSend = strlen( szContent );

    SendHeaders(
        pecb,
        "200 OK",
        "Content-Type: text/html\r\n\r\n",
        cbToSend
        );

    pecb->WriteClient(
        pecb->ConnID,
        szContent,
        &cbToSend,
        HSE_IO_SYNC | HSE_IO_NODELAY
        );

    return HSE_STATUS_SUCCESS;
}

BOOL
SendHeaders(
    EXTENSION_CONTROL_BLOCK *   pecb,
    LPSTR                       szStatus,
    LPSTR                       szHeaders,
    DWORD                       cbContent
    )
/*++

Purpose:

    A simple HSE_REQ_SEND_RESPONSE_HEADER_EX wrapper that adds
    an optional content-length header to the response
  
Arguments:
    
    pecb      - The EXTENSION_CONTROL_BLOCK for the request
    szStatus  - The status (ie. "200 OK") to be sent
    szHeaders - The headers (ie. "content-type: text/html\r\n\r\n"
                to be sent
    cbContent - If non-zero, will be used to generate a
                content-length header to add to the response
  
Returns:
    
    None
    
--*/
{
    HSE_SEND_HEADER_EX_INFO HeaderInfo;
    CHAR                    szCookedHeaders[STRING_BUFFER+1] = {0};
    LPSTR                   pHeaders;

    if ( cbContent == 0 )
    {
        pHeaders = szHeaders;
    }
    else
    {
        _snprintf(
            szCookedHeaders,
            STRING_BUFFER,
            "Content-Length: %d\r\n%s",
            cbContent,
            szHeaders
            );

        pHeaders = szCookedHeaders;
    }

    HeaderInfo.pszHeader = pHeaders;
    HeaderInfo.pszStatus = szStatus;
    HeaderInfo.cchHeader = strlen( HeaderInfo.pszHeader );
    HeaderInfo.cchStatus = strlen( HeaderInfo.pszStatus );
    HeaderInfo.fKeepConn = cbContent ? TRUE : FALSE;

    return pecb->ServerSupportFunction(
        pecb->ConnID,
        HSE_REQ_SEND_RESPONSE_HEADER_EX,
        &HeaderInfo,
        NULL,
        NULL
        );
}



	