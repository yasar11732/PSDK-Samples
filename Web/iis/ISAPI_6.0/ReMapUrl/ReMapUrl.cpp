/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: ReMapUrl.cpp

Abstract:

    ISAPI extension to run as a wildcard script map and
    remap URLs

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#include <IsapiTools.h>

#define MODULE_NAME             "ReMapUrl"
#define MAX_CONFIG_LINE         1024
#define DEFAULT_ALLOW_UNMAPPED  1

#define REDIRECT_ENTITY \
    "<head><title>Document Moved</title></head>\r\n" \
    "<body><h1>Object Moved</h1>This document may "  \
    "be found <a HREF=\"%s\">here</a></body>"


ISAPI_STRING    g_strIniFile;

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIo,
    DWORD                       dwError
    );

VOID
TrimCommentAndTrailingWhitespace(
    CHAR *  szString
    );

BOOL
GetMapping(
    CHAR *          szUrl,
    ISAPI_STRING *  pstrMapping
    );

DWORD
DoCustomError(
    EXTENSION_CONTROL_BLOCK *   pecb,
    CHAR *                      szConfigLine
    );

BOOL
SendRedirectResponse(
    EXTENSION_CONTROL_BLOCK *   pecb,
    CHAR *                      szLocation
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

    TRUE on success, FALSE on failure.
    
    Note that in the case of FALSE, IIS will call GetLastError()
    and return an error page to the client.  The entity body of
    the page may be textual if the FormatMessage API can resolve
    it, or it may just be an error number if FormatMessage can't
    resolve it.

--*/
{
    ISAPI_EXTENSION Extension;
    //
    // Tell IIS which version of ISAPI this extension was built from.
    //

    pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR,
                                         HSE_VERSION_MAJOR);

    //
    // Report the description string for this extension.  Ensure
    // that it does not exceed the maximum length and is NULL
    // terminated.
    //

    strncpy( pVer->lpszExtensionDesc,
             "ReMapUrl ISAPI Sample",
             HSE_MAX_EXT_DLL_NAME_LEN );

    pVer->lpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN-1] = '\0';

    //
    // Get the INI filename
    //

    InitializeIsapiTools( MODULE_NAME );

    if ( Extension.Initialize( MODULE_NAME ) == FALSE )
    {
        goto Failed;
    }

    if ( g_strIniFile.Printf( "%s\\%s.ini",
                              Extension.QueryModulePath(),
                              MODULE_NAME ) == FALSE )
    {
        goto Failed;
    }

    //
    // Return TRUE if we successfully initialized.
    //

    return TRUE;

Failed:

    WriteDebug( "GetExtensionVersion failed. Error %d.\r\n",
                GetLastError() );

    return FALSE;
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
    HSE_EXEC_URL_INFO   ExecUrlInfo = {0};
    ISAPI_STRING        strUrl;
    ISAPI_STRING        strMapping;
    ISAPI_REQUEST       Request( pecb );

    //
    // Get the current URL and check to see if we have a
    // mapping for it.
    //

    if ( Request.GetServerVariable( "SCRIPT_NAME",
                                    &strUrl ) == FALSE )
    {
        goto Failed;
    }

    if ( GetMapping( strUrl.QueryStr(), &strMapping ) == FALSE )
    {
        goto Failed;
    }

    //
    // Ok, so there are 4 scenarios here:
    //
    //  1 - The mapping is an empty string.  In that
    //      case, we should just run the original URL
    //  2 - The mapping starts with a numeric, in which
    //      case, we should parse it as a custom error
    //      mapping
    //  3 - The mapping starts with "http", in which
    //      case, we should redirect via a 302 response
    //  4 - Else, the mapping is a URL on this site
    //

    if ( strMapping.QueryCCH() == 0 )
    {
        goto CallExecUrl;
    }
    else if ( isdigit( *(strMapping.QueryStr()) ) )
    {
        return DoCustomError( pecb, strMapping.QueryStr() );
    }

    //
    // Ok, so we know that we will be doing some kind of redirect.
    //
    // If there is a query string on this request, append it to
    // the mapping data
    //

    if ( pecb->lpszQueryString[0] != '\0' )
    {
        if ( strMapping.Append( "?" ) == FALSE )
        {
            goto Failed;
        }

        if ( strMapping.Append( pecb->lpszQueryString ) == FALSE )
        {
            goto Failed;
        }
    }

    //
    // Do the appropriate redirect
    //

    if ( strnicmp( strMapping.QueryStr(), "http", 4 ) == 0 )
    {
        //
        // Do a 302.
        //
        
        if ( SendRedirectResponse( pecb, strMapping.QueryStr() ) == FALSE )
        {
            goto Failed;
        }

        return HSE_STATUS_SUCCESS;
    }

    //
    // Finally, if we fall through to here, then we are going to redirect
    // this request to another URL on this site.  We just need to point
    // at the new URL and call HSE_REQ_EXEC_URL.
    //

    ExecUrlInfo.pszUrl = strMapping.QueryStr();

    //
    // Fall through to CallExecUrl
    //

CallExecUrl:

    //
    // Set up the IO completion (passing TRUE as the context
    // will notify the completion routine that this is an
    // ExecUrl call.
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_IO_COMPLETION,
                                      HandleCompletion,
                                      NULL,
                                      (DWORD*)TRUE ) == FALSE )
    {
        goto Failed;
    }

    ExecUrlInfo.dwExecUrlFlags = HSE_EXEC_URL_IGNORE_CURRENT_INTERCEPTOR;

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_EXEC_URL,
                                      &ExecUrlInfo,
                                      NULL,
                                      NULL ) == TRUE )
    {
        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to error handler
    //

Failed:

    WriteDebug( "HttpExtensionProc failed.  Error %d.\r\n",
                GetLastError() );

    return SyncSendGenericServerError( pecb );
}

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIo,
    DWORD                       dwError
    )
{
    HSE_EXEC_URL_STATUS ExecUrlStatus;
    BOOL                fIsExecCompletion = (DWORD)pContext;
    BOOL                fResult = TRUE;

    //
    // If this is not an EXEC_URL completion, then we can just
    // skip to calling DONE_WITH_SESSION.  Otherwise, we need
    // to check the result of the child.
    //

    if ( !fIsExecCompletion )
    {
        goto Done;
    }

    fResult = pecb->ServerSupportFunction( pecb->ConnID,
                                           HSE_REQ_GET_EXEC_URL_STATUS,
                                           &ExecUrlStatus,
                                           NULL,
                                           NULL );

    if ( !fResult )
    {
        goto Done;
    }

    //
    // If the status is 403.18, then that means that we tried to
    // redirect to another URL on this site, but in another
    // app pool.  In that case. the best we can do is to try a
    // 302 redirect.
    //
    // Note that we are rebuilding the remapping information here.
    // The reason for this is that we are optimizing for the case
    // when the EXEC_URL call works.  We don't want to do a heap
    // allocation in that case if we can avoid it, so we aren't
    // passing it as context to this completion routine.
    //

    if ( ExecUrlStatus.uHttpStatusCode == 403 &&
         ExecUrlStatus.uHttpSubStatus == 18 )
    {
        ISAPI_REQUEST   Request( pecb );
        ISAPI_STRING    strUrl;
        ISAPI_STRING    strMapping;

        fResult = Request.GetServerVariable( "SCRIPT_NAME",
                                             &strUrl );
        
        if ( !fResult )
        {
            goto Done;
        }

        fResult = GetMapping( strUrl.QueryStr(), &strMapping );

        if ( !fResult )
        {
            goto Done;
        }

        if ( pecb->lpszQueryString[0] != '\0' )
        {
            fResult = strMapping.Append( "?" );

            if ( !fResult )
            {
                goto Done;
            }

            fResult = strMapping.Append( pecb->lpszQueryString );

            if ( !fResult )
            {
                goto Done;
            }
        }

        fResult = SendRedirectResponse( pecb,
                                        strMapping.QueryStr() );

        if ( !fResult )
        {
            SyncSendGenericServerError( pecb );
        }
    }
    else
    {
        //
        // Just set the ECB's status member to match the child's
        // result
        //

        pecb->dwHttpStatusCode = ExecUrlStatus.uHttpStatusCode;
    }

Done:

    if ( !fResult )
    {
        WriteDebug( "Error processing I/O completion.  Error %d.\r\n",
                    GetLastError() );
    }

    //
    // Notify IIS that we are done with the request
    //

    pecb->ServerSupportFunction( pecb->ConnID,
                                 HSE_REQ_DONE_WITH_SESSION,
                                 NULL,
                                 NULL,
                                 NULL );
}

VOID
TrimCommentAndTrailingWhitespace(
    CHAR *  szString
    )
/*++

Purpose:

    This function trims a text line from an INI file
    such that it's truncated at the first instance of
    a ';'. Any trailing whitespace is also removed.

Arguments:

    szString - The string to trim

Returns:

    None

--*/
{
    LPSTR   pCursor = szString;
    LPSTR   pWhite = NULL;

    while ( *pCursor )
    {
        if ( *pCursor == ';' )
        {
            *pCursor = '\0';
            break;
        }

        if ( *pCursor == ' ' || *pCursor == '\t' )
        {
            if ( !pWhite )
            {
                pWhite = pCursor;
            }
        }
        else
        {
            pWhite = NULL;
        }

        pCursor++;
    }

    if ( pWhite )
    {
        *pWhite = '\0';
    }

    return;
}


BOOL
GetMapping(
    CHAR *          szUrl,
    ISAPI_STRING *  pstrMapping
    )
{
    //
    // Make sure that the output string is
    // at least as big as our config line
    //

    if ( pstrMapping->ResizeBuffer( MAX_CONFIG_LINE ) == FALSE )
    {
        goto Failed;
    }

    GetPrivateProfileString( "Mappings",
                             szUrl,
                             "",
                             pstrMapping->QueryStr(),
                             pstrMapping->QueryBufferSize(),
                             g_strIniFile.QueryStr() );

    if ( *pstrMapping->QueryStr() == 0 )
    {
        //
        // If we didn't get a mapping the first time, try
        // to get the default
        //

        GetPrivateProfileString( "Mappings",
                                 "Default",
                                 "",
                                 pstrMapping->QueryStr(),
                                 pstrMapping->QueryBufferSize(),
                                 g_strIniFile.QueryStr() );
    }

    TrimCommentAndTrailingWhitespace( pstrMapping->QueryStr() );

    pstrMapping->CalcLen();

    return TRUE;

Failed:

    WriteDebug( "GetMapping failed. Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

DWORD
DoCustomError(
    EXTENSION_CONTROL_BLOCK *   pecb,
    CHAR *                      szConfigLine
    )
{
    HSE_CUSTOM_ERROR_INFO   CustomError;
    ISAPI_REQUEST           Request( pecb );
    ISAPI_STRING            strStatus;
    ISAPI_STRING            strAlternateEntity;
    USHORT                  uSubStatus;
    CHAR *                  pCursor;

    //
    // We expect the config line to be in the
    // form:
    //
    //   500,13,Server Too Busy
    //

    if ( strStatus.Copy( szConfigLine ) == FALSE )
    {
        goto Failed;
    }

    pCursor = strchr( strStatus.QueryStr(), ',' );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        
        goto Failed;
    }

    *pCursor = '\0';

    strStatus.CalcLen();
    
    pCursor++;

    uSubStatus = atoi( pCursor );

    pCursor = strchr( pCursor, ',' );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        
        goto Failed;
    }

    if ( strAlternateEntity.Copy( pCursor+1 ) == FALSE )
    {
        goto Failed;
    }

    //
    // Set up for an asynchronous call to HSE_REQ_SEND_CUSTOM_ERROR
    //

    if ( strStatus.Append( " " ) == FALSE ||
         strStatus.Append( strAlternateEntity.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    CustomError.pszStatus = strStatus.QueryStr();
    CustomError.uHttpSubError = uSubStatus;
    CustomError.fAsync = TRUE;

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_IO_COMPLETION,
                                      &HandleCompletion,
                                      NULL,
                                      NULL ) == FALSE )
    {
        goto Failed;
    }

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_SEND_CUSTOM_ERROR,
                                      &CustomError,
                                      NULL,
                                      NULL ) == TRUE )
    {
        //
        // The async call succeeded.  We need to return STATUS_PENDING
        // without doing anything else to the ECB.
        //

        return HSE_STATUS_PENDING;
    }

    //
    // If we get here, then the asynchronous call failed. We'll go
    // ahead and send back a synchronous error manually.
    //

    if ( Request.SyncWriteCompleteResponse( strStatus.QueryStr(),
                                            "Content-Type: text/plain\r\n\r\n",
                                            strAlternateEntity.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    return HSE_STATUS_SUCCESS;

Failed:

    WriteDebug( "DoCustomError failed.  Error %d.\r\n",
                GetLastError() );

    return SyncSendGenericServerError( pecb );
}

BOOL
SendRedirectResponse(
    EXTENSION_CONTROL_BLOCK *   pecb,
    CHAR *                      szLocation
    )
{
    ISAPI_REQUEST   Request( pecb );
    ISAPI_STRING    strEscapedLocation;
    ISAPI_STRING    strHeaders;

    //
    // Since this redirect might go to another machine,
    // we should be conscious of certain client behaviors.
    // Specifically, we want to make sure that the client
    // doesn't try and run any part of szLocation as a
    // script, especially the query string, since the query
    // string was originally submitted from an untrusted
    // source (the client).  To deal with this, we will
    // escape encode the instance of the location data that
    // appears in the entity body of the redirect response
    //

    if ( strEscapedLocation.Copy( szLocation ) == FALSE )
    {
        goto Failed;
    }

    if ( strEscapedLocation.Escape() == FALSE )
    {
        goto Failed;
    }

    if ( strHeaders.Printf( "Content-Type: text/html\r\n"
                            "Location: %s\r\n\r\n",
                            szLocation ) == FALSE )
    {
        goto Failed;
    }

    if ( Request.SyncWriteCompleteResponse( "302 Object Moved",
                                            strHeaders.QueryStr(),
                                            REDIRECT_ENTITY,
                                            strEscapedLocation.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "SendRedirectResponse failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}
