/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: CustomAuth.cpp

Abstract:

    ISAPI extension to demonstrate using a wildcard script
    map with HSE_REQ_EXEC_URL to implement a custom forms
    based authentication scheme.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#include <IsapiTools.h>
#include <httpfilt.h>
#include "CustomAuth.h"

//
// Globals
//

ISAPI_EXTENSION  g_Extension;
ISAPI_STRING     g_strIniFile;
ISAPI_STRING     g_strLogonUrl;
ISAPI_STRING     g_strLogonSuccessUrl;
ISAPI_STRING     g_strLogoffUrl;
INT              g_LogonTimeoutSeconds;
BOOL             g_fFilterInitialized;
BOOL             g_fUseBuiltInLogon;
BOOL             g_fUseBuiltInLogoff;
BOOL             g_fUseSSLForSubmission;
BOOL             g_fUseClientIpForEncryption;
DWORD            g_LogonType;

//
// Local prototypes
//

VOID
WINAPI
HandleExecUrlCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    );

VOID
WINAPI
HandleSendPageCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    );

DWORD
ProcessLogon(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

DWORD
ProcessLogoff(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

DWORD
SendBuiltinLogonPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    );

BOOL
GetUserInfoAndUpdateCookie(
    ISAPI_STRING *              pstrCookie,
    CHAR *                      szClientIP,
    HSE_EXEC_URL_USER_INFO *    pUserInfo,
    ISAPI_STRING *              pstrUser    );

BOOL
EncryptAndEncodeCredentials(
    CHAR *          szUser,
    CHAR *          szPassword,
    CHAR *          szClientIP,
    ISAPI_STRING *  pstrResult
    );

BOOL
DecodeAndDecryptCredentials(
    CHAR *          szCredentials,
    CHAR *          szClientIP,
    ISAPI_STRING *  pstrUser,
    ISAPI_STRING *  pstrPassword,
    FILETIME *      pft
    );

//
// Extension entry point implementations
//

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
             "CustomAuth ISAPI Sample",
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
    HTTP_FILTER_CONTEXT *   pfc = NULL;
    HSE_EXEC_URL_INFO       ExecUrlInfo;
    HSE_EXEC_URL_USER_INFO  UserInfo = {0};
    ISAPI_REQUEST           Request( pecb );
    ISAPI_STRING            strUrl;
    ISAPI_STRING            strCookie;
    ISAPI_STRING            strClientIP;
    ISAPI_STRING            strUser;
    ISAPI_STRING            strFilterContext;
    ISAPI_STRING            strAuthType;
    HANDLE                  hToken = NULL;
    BOOL                    fModifiedUserInfo = FALSE;
    DWORD                   dwResult;
    BOOL                    fResult;

    //
    // Before doing anythine else, check to see if this request
    // has already been authenticated.  If so, just let the
    // request run.
    //

    fResult = Request.GetServerVariable( "AUTH_TYPE", &strAuthType );

    if ( !fResult )
    {
        goto Failed;
    }

    if ( *( strAuthType.QueryStr() ) != '\0' )
    {
        goto CallExecUrl;
    }

    //
    // Get the URL and check to see if it's one that we should
    // deal with.
    //

    fResult = Request.GetServerVariable( "URL", &strUrl );

    if ( !fResult )
    {
        goto Failed;
    }

    //
    // Logon request?
    //

    if ( stricmp( strUrl.QueryStr(), "/Logon" ) == 0 )
    {
        dwResult = ProcessLogon( pecb );

        if ( dwResult == HSE_STATUS_ERROR )
        {
            goto Failed;
        }

        return dwResult;
    }

    //
    // Logoff request?
    //

    if ( stricmp( strUrl.QueryStr(), "/Logoff" ) == 0 )
    {
        dwResult = ProcessLogoff( pecb );

        if ( dwResult == HSE_STATUS_ERROR )
        {
            goto Failed;
        }

        return dwResult;
    }
        
    //
    // Use built-in logon page?
    //

    if ( g_fUseBuiltInLogon == TRUE &&
         stricmp( strUrl.QueryStr(), g_strLogonUrl.QueryStr() ) == 0 )
    {
        dwResult = SendBuiltinLogonPage( pecb );

        if ( dwResult == HSE_STATUS_ERROR )
        {
            goto Failed;
        }

        return dwResult;
    }

    //
    // Check for a cookie and process it if found
    //

    fResult = Request.GetServerVariable( "HTTP_COOKIE",
                                         &strCookie );

    if ( fResult )
    {
        fResult = Request.GetServerVariable( "REMOTE_ADDR",
                                             &strClientIP );

        if ( !fResult )
        {
            goto Failed;
        }

        fResult = Request.UnimpersonateClient();

        if ( !fResult )
        {
            goto Failed;
        }

        fResult = GetUserInfoAndUpdateCookie( &strCookie,
                                              strClientIP.QueryStr(),
                                              &UserInfo,
                                              &strUser );

        Request.ImpersonateClient();

        //
        // If we didn't get any user info from the cookie, then
        // just allow the request through as anonymous.
        //

        if ( !fResult )
        {
            goto CallExecUrl;
        }

        //
        // Set the updated cookie back into the client.
        //
        // Note that this action has a bit of cleverness to it.
        // Since we are going to call a child URL, and not send
        // response headers directly, we can't just send the
        // response header as an extension normally would.  Instead,
        // since this dll has both a filter and extension component,
        // we are getting the HTTP_FILTER_CONTEXT for the request
        // from the filter via a custom request header (which the
        // client never sees), and using a filter function to add
        // our set-cookie header so that it will be included when
        // the response headers are sent, as if it were an IIS
        // built-in header
        //

        fResult = Request.GetServerVariable( "HTTP_CUSTOMAUTH_CONTEXT",
                                             &strFilterContext );

        if ( fResult )
        {
            pfc = (HTTP_FILTER_CONTEXT*)strtoul( strFilterContext.QueryStr(),
                                                 NULL,
                                                 16 );
        }

        if ( pfc )
        {
            ISAPI_STRING    strSetCookie;

            if ( strSetCookie.Printf( "Set-Cookie: %s\r\n",
                                      strCookie.QueryStr() ) == FALSE )
            {
                goto Failed;
            }

            if ( pfc->AddResponseHeaders( pfc,
                                          strSetCookie.QueryStr(),
                                          0 ) == FALSE )
            {
                goto Failed;
            }
        }

        fModifiedUserInfo = TRUE;
    }

    //
    // Fall through
    //

CallExecUrl:

    //
    // Use EXEC_URL to pass the request along
    //
    // We will pass NULL for all of the parts of the request
    // that we don't want to modify.
    //
    // We will also use the HSE_EXEC_URL_IGNORE_CURRENT_INTERCEPTOR
    // flag.  This will ensure that this extension is not called again
    // on this request (which could otherwise happen in some cases).
    //

    ExecUrlInfo.pszUrl = NULL;
    ExecUrlInfo.pszMethod = NULL;
    ExecUrlInfo.pszChildHeaders = NULL;
    ExecUrlInfo.pUserInfo = NULL;
    ExecUrlInfo.pEntity = NULL;
    ExecUrlInfo.dwExecUrlFlags = HSE_EXEC_URL_IGNORE_CURRENT_INTERCEPTOR;

    if ( fModifiedUserInfo )
    {
        ExecUrlInfo.pUserInfo = &UserInfo;
    }

    //
    // Associate the completion routine and the current URL with
    // this request.
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_IO_COMPLETION,
                                      HandleExecUrlCompletion,
                                      NULL,
                                      (DWORD*)UserInfo.hImpersonationToken ) == FALSE )
    {
        goto Failed;
    }

    //
    // Call ExecUrl
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_EXEC_URL,
                                      &ExecUrlInfo,
                                      NULL,
                                      NULL ) == FALSE )
    {
        goto Failed;
    }

    //
    // Since EXEC_URL is asynchonous, we need to return STATUS_PENDING.
    // The I/O completion routine will clean up.
    //

    return HSE_STATUS_PENDING;

Failed:

    WriteDebug( "HttpExtensionProc failed.  Error %d.\r\n",
                GetLastError() );

    //
    // If we've already got a token, close it now.
    //

    if ( UserInfo.hImpersonationToken )
    {
        CloseHandle( UserInfo.hImpersonationToken );
        UserInfo.hImpersonationToken = NULL;
    }

    //
    // Send a 500 error
    //

    Request.SyncWriteCompleteResponse( "500 Server Error",
                                       "Content-Type: text/html\r\n\r\n",
                                       SERVER_ERROR );

    return HSE_STATUS_ERROR;

}

VOID
WINAPI
HandleExecUrlCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    )
/*++

Purpose:

    Handles completion of an asynchronous HSE_REQ_EXEC_URL
    call.  The pContext passed into this function is the
    token that was set in the HSE_EXEC_URL_USER_INFO
    structure that did the EXEC_URL.  This function needs
    to close that handle.

Arguments:

    pecb     - Pointer to the EXTENSION_CONTROL_BLOCK
    pContext - The completion context (token per above)
    cbIO     - I/O bytes associated with this completion
    dwError  - Error associated with this completion

Returns:

    None

--*/
{
    HSE_EXEC_URL_STATUS ExecUrlStatus;
    HANDLE              hToken = (HANDLE)pContext;

    //
    // The child is done.  Delete the entity buffer now.
    //

    if ( hToken )
    {
        CloseHandle( hToken );
        hToken = NULL;
    }

    //
    // Get the child's HTTP status and set it into the ECB
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_GET_EXEC_URL_STATUS,
                                      &ExecUrlStatus,
                                      NULL,
                                      NULL ) == TRUE )
    {
        pecb->dwHttpStatusCode = ExecUrlStatus.uHttpStatusCode;
    }

    //
    // Let IIS know that we are done with the
    // ECB and return.
    //

    pecb->ServerSupportFunction( pecb->ConnID,
                                 HSE_REQ_DONE_WITH_SESSION,
                                 NULL,
                                 NULL,
                                 NULL );

}

VOID
WINAPI
HandleSendPageCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    )
/*++

Purpose:

    Handles completion of a send through AsyncTransmitBufferedResponse
    call.  The pContext passed into this function is the ISAPI_REQUEST
    object used.  We need to delete that object.  It's destructor will
    take care of doing HSE_REQ_DONE_WITH_SESSION as appropriate.

Arguments:

    pecb     - Pointer to the EXTENSION_CONTROL_BLOCK
    pContext - The completion context (ISAPI_REQUEST per above)
    cbIO     - I/O bytes associated with this completion
    dwError  - Error associated with this completion

Returns:

    None

--*/
{
    ISAPI_REQUEST * pRequest = (ISAPI_REQUEST*)pContext;

    //
    // Delete the request object.  Its destructor will
    // take care of doing the right DONE_WITH_SESSION stuff.
    //

    if ( pRequest )
    {
        delete pRequest;
        pRequest = NULL;
    }
}

DWORD
ProcessLogon(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    Handles logon requests by reading the entity body, parsing
    it for username and password information, creating a
    cookie to store them on the client (encrypted and base64
    encoded), and sending a 302 redirect to the configured
    logon success URL.

    This send is done asynchronously.

Arguments:

    pecb     - Pointer to the EXTENSION_CONTROL_BLOCK

Returns:

    HSE_STATUS_PENDING on success, or HSE_STATUS_ERROR
    on failure.

--*/
{
    ISAPI_REQUEST * pRequest;
    ISAPI_STRING    strClientIP;
    ISAPI_STRING    strCredentials;
    ISAPI_STRING    strSetCookie;
    ISAPI_STRING    strUser;
    ISAPI_STRING    strPassword;
    ISAPI_STRING    strEntity;
    ISAPI_BUFFER    Entity;
    CHAR *          pCursor;
    CHAR *          pDelimiter;
    BOOL            fResult;

    pRequest = new ISAPI_REQUEST( pecb );

    if ( !pRequest )
    {
        goto Failed;
    }

    //
    // Get the entity body for this request and store
    // it in an ISAPI_STRING
    //

    if ( pRequest->ReadAllEntity( &Entity ) == FALSE )
    {
        goto Failed;
    }

    if ( strEntity.Copy( (CHAR*)Entity.QueryPtr(),
                         Entity.QueryDataSize() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Parse the username out of the entity
    //

    pCursor = strEntity.FindStr( "username=", TRUE );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_DATA );
        goto Failed;
    }

    pCursor += sizeof("username=") - 1;

    pDelimiter = strchr( pCursor, '&' );

    if ( pDelimiter )
    {
        fResult = strUser.Copy( pCursor, pDelimiter - pCursor );
    }
    else
    {
        fResult = strUser.Copy( pCursor );
    }

    if ( !fResult )
    {
        goto Failed;
    }

    strUser.Unescape();

    //
    // Parse the password  out of the entity
    //

    pCursor = strEntity.FindStr( "password=", TRUE );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_DATA );
        goto Failed;
    }

    pCursor += sizeof("password=") - 1;

    pDelimiter = strchr( pCursor, '&' );

    if ( pDelimiter )
    {
        fResult = strPassword.Copy( pCursor, pDelimiter - pCursor );
    }
    else
    {
        fResult = strPassword.Copy( pCursor );
    }

    if ( !fResult )
    {
        goto Failed;
    }

    strPassword.Unescape();

    //
    // Get the IP address of the client.  This will be passed to the
    // encryption routine so that the resulting encrypted blob can
    // only be decrypted on a request from the same client.
    //

    if ( pRequest->GetServerVariable( "REMOTE_ADDR",
                                      &strClientIP ) == FALSE )
    {
        goto Failed;
    }

    //
    // Get the encrypted credentials and build a
    // set-cookie header with them
    //
    // Temporarily stop impersonating the client while
    // calling the encryption code.
    //

    if ( pRequest->UnimpersonateClient() == FALSE )
    {
        goto Failed;
    }

    fResult = EncryptAndEncodeCredentials( strUser.QueryStr(),
                                           strPassword.QueryStr(),
                                           strClientIP.QueryStr(),
                                           &strCredentials );

    pRequest->ImpersonateClient();

    if ( !fResult )
    {
        goto Failed;
    }

    if ( strSetCookie.Printf( "CustomAuth=%s; Path=/",
                              strCredentials.QueryStr() ) == FALSE )
    {
        goto Failed;
    }
    
    //
    // Set the status for the response, which will be a redirect
    // to the logon success URL.
    //

    if ( pRequest->SetBufferedResponseStatus( "302 Object Moved" ) == FALSE )
    {
        goto Failed;
    }

    //
    // Add the set-cookie with the credentials
    //

    if ( pRequest->AddHeaderToBufferedResponse( "Set-Cookie",
                                                strSetCookie.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Add the location header
    //

    if ( pRequest->AddHeaderToBufferedResponse( "Location",
                                                g_strLogonSuccessUrl.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Add "Expires: 0" so that the client doesn't cache this page.
    //

    if ( pRequest->AddHeaderToBufferedResponse( "Expires",
                                                "0" ) == FALSE )
    {
        goto Failed;
    }

    //
    // Add the entity for the page
    //

    if ( pRequest->PrintfToResponseBuffer( REDIRECT_ENTITY,
                                           g_strLogonSuccessUrl.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Zero out any buffers that contain unencrypted password
    // information
    //

    Entity.ZeroBuffer();
    strEntity.ZeroBuffer();
    strPassword.ZeroBuffer();

    //
    // Send the request asynchronously
    //

    if ( pRequest->AsyncTransmitBufferedResponse( HandleSendPageCompletion ) == TRUE )
    {
        //
        // On success, we need to immediately return status pending
        //

        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to error handler
    //

Failed:

    WriteDebug( "ProcessLogon failed.  Error %d\r\n",
                GetLastError() );

    //
    // Zero out any buffers that contain unencrypted password
    // information
    //

    Entity.ZeroBuffer();
    strEntity.ZeroBuffer();
    strPassword.ZeroBuffer();

    if ( pRequest )
    {
        delete pRequest;
        pRequest = NULL;
    }

    return HSE_STATUS_ERROR;
}

DWORD
ProcessLogoff(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
{
    ISAPI_REQUEST * pRequest;

    pRequest = new ISAPI_REQUEST( pecb );

    if ( !pRequest )
    {
        goto Failed;
    }

    //
    // Build the response.  If we are supposed to use the built-in
    // logoff page, then we'll send it directly.  Otherwise, the
    // response will be a 302 to the configured page.
    //

    if ( g_fUseBuiltInLogoff == TRUE )
    {
        if ( pRequest->SetBufferedResponseStatus( "200 OK" ) ==  FALSE )
        {
            goto Failed;
        }

        if ( pRequest->AddHeaderToBufferedResponse( "Expires",
                                                    "0" ) == FALSE )
        {
            goto Failed;
        }

        if ( pRequest->AddDataToResponseBuffer( LOGOFF_PAGE,
                                                sizeof(LOGOFF_PAGE) - 1 ) == FALSE )
        {
            goto Failed;
        }
    }
    else
    {
        if ( pRequest->SetBufferedResponseStatus( "302 Object Moved" ) ==  FALSE )
        {
            goto Failed;
        }

        if ( pRequest->AddHeaderToBufferedResponse( "Location",
                                                    g_strLogoffUrl.QueryStr() ) == FALSE )
        {
            goto Failed;
        }

        if ( pRequest->PrintfToResponseBuffer( REDIRECT_ENTITY,
                                               g_strLogoffUrl ) == FALSE )
        {
            goto Failed;
        }
    }

    //
    // Add a set-cookie header to remove the credentials
    //

    if ( pRequest->AddHeaderToBufferedResponse( "Set-Cookie",
                                                DELETE_COOKIE ) == FALSE )
    {
        goto Failed;
    }

    //
    // Send the response
    //

    if ( pRequest->AsyncTransmitBufferedResponse( HandleSendPageCompletion ) == TRUE )
    {
        //
        // On success, we need to return HSE_STATUS_PENDING
        //

        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to error handler
    //

Failed:

    WriteDebug( "ProcessLogoff failed.  Error %d.\r\n",
                GetLastError() );

    if ( pRequest )
    {
        delete pRequest;
        pRequest = NULL;
    }

    return HSE_STATUS_ERROR;
}

DWORD
SendBuiltinLogonPage(
    EXTENSION_CONTROL_BLOCK *   pecb
    )
/*++

Purpose:

    If we are configured to send back the built-in logon
    page (instead of using a user-provided custom page),
    this function does the work.

Arguments:

    pecb     - Pointer to the EXTENSION_CONTROL_BLOCK

Returns:

    HSE_STATUS_PENDING on success, or HSE_STATUS_ERROR
    on failure.

--*/
{
    ISAPI_REQUEST * pRequest;
    ISAPI_STRING    strServerName;
    ISAPI_STRING    strHttps;

    pRequest = new ISAPI_REQUEST( pecb );

    if ( !pRequest )
    {
        goto Failed;
    }

    //
    // Set the status for the response
    //

    if ( pRequest->SetBufferedResponseStatus( "200 OK" ) == FALSE )
    {
        goto Failed;
    }

    //
    // Set the entity body for the response
    //

    strHttps.ZeroBuffer();

    if ( g_fUseSSLForSubmission )
    {
        if ( pRequest->GetServerVariable( "SERVER_NAME",
                                          &strServerName ) == FALSE )
        {
            goto Failed;
        }

        if ( strHttps.Printf( "https://%s", strServerName.QueryStr() ) == FALSE )
        {
            goto Failed;
        }
    }

    if ( pRequest->PrintfToResponseBuffer( LOGON_PAGE,
                                           strHttps.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Now send the page asynchronously
    //

    if ( pRequest->AsyncTransmitBufferedResponse( HandleSendPageCompletion ) == TRUE )
    {
        //
        // On success, we should return status pending immediately.
        //

        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to error handler
    //

Failed:

    WriteDebug( "SendBuiltinLogonPage failed.  Error %d.\r\n",
                GetLastError() );

    if ( pRequest )
    {
        delete pRequest;
        pRequest = NULL;
    }

    return HSE_STATUS_ERROR;
}

BOOL
GetUserInfoAndUpdateCookie(
    ISAPI_STRING *              pstrCookie,
    CHAR *                      szClientIP,
    HSE_EXEC_URL_USER_INFO *    pUserInfo,
    ISAPI_STRING *              pstrUser    )
/*++

Purpose:

    Accepts a raw cookie header value from the client, extracts the
    username and password from it, and uses the resulting credentials
    to get a token and populate an HSE_EXEC_URL_USER_INFO structure.

    Upon return, pstrCookie will be modified to hold an updated cookie
    value, modified to reflect the current time.

Arguments:

    pstrCookie - The raw cookie value to process
    szClientIP - The IP address of the client
    pUserInfo  - The caller's HSE_EXEC_URL_USER_INFO to popluate
    pstrUser   - Upon return, contains the processed username

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    ISAPI_STRING    strLastVisit;
    ISAPI_STRING    strCredentials;
    ISAPI_STRING    strPassword;
    ISAPI_STRING    strUpdatedCredentials;
    FILETIME        ftLastVisit;
    CHAR *          pCursor;
    CHAR *          pDelimiter;
    HANDLE          hToken = NULL;
    BOOL            fResult;

    //
    // Get the credentials from the cookie
    //

    pCursor = pstrCookie->FindStr( "customauth=", TRUE );

    if ( pCursor == NULL )
    {
        //
        // credentials not found
        //

        goto Failed;
    }

    pCursor += sizeof("customauth=") - 1;

    pDelimiter = strchr( pCursor, ';' );

    if ( pDelimiter != NULL )
    {
        if ( pDelimiter == pCursor )
        {
            //
            // Empty CustomAuth value
            //

            goto Failed;
        }

        fResult = strCredentials.Copy( pCursor, pDelimiter - pCursor );
    }
    else
    {
        if ( *pCursor == '\0' )
        {
            //
            // Empty CustomAuth value
            //

            goto Failed;
        }

        fResult = strCredentials.Copy( pCursor );
    }

    if ( !fResult )
    {
        goto Failed;
    }

    //
    // Decrypt them.
    //

    fResult = DecodeAndDecryptCredentials( strCredentials.QueryStr(),
                                           szClientIP,
                                           pstrUser,
                                           &strPassword,
                                           &ftLastVisit );

    if ( !fResult )
    {
        goto Failed;
    }

    //
    // If the last visit is older than the logon timeout period,
    // then fail.
    //

    if ( g_LogonTimeoutSeconds )
    {
        FILETIME    ftCurrent;

        if ( GetCurrentTimeAsFileTime( &ftCurrent ) == FALSE )
        {
            goto Failed;
        }

        if ( DiffFileTimeInSeconds( &ftLastVisit, &ftCurrent ) > (DWORD)g_LogonTimeoutSeconds )
        {
            SetLastError( ERROR_SEM_TIMEOUT );
            goto Failed;
        }
    }

    //
    // Update the cookie
    //

    if ( EncryptAndEncodeCredentials( pstrUser->QueryStr(),
                                      strPassword.QueryStr(),
                                      szClientIP,
                                      &strUpdatedCredentials ) == FALSE )
    {
        goto Failed;
    }

    if ( pstrCookie->Printf( "CustomAuth=%s; Path=/",
                             strUpdatedCredentials.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    //
    // Log on the user
    //

    fResult = LogonUser( pstrUser->QueryStr(),
                         NULL,
                         strPassword.QueryStr(),
                         g_LogonType,
                         LOGON32_PROVIDER_DEFAULT,
                         &hToken );

    //
    // Regardless of the result, we are done with the password
    //

    strPassword.ZeroBuffer();

    if ( !fResult )
    {
        goto Failed;
    }

    //
    // Populate the user info from the caller
    //

    pUserInfo->hImpersonationToken = hToken;
    pUserInfo->pszCustomUserName = pstrUser->QueryStr();
    pUserInfo->pszCustomAuthType = "CustomAuth";

    return TRUE;
    
Failed:

    WriteDebug( "GetUserInfoAndUpdateCookie failed.  Error %d.\r\n",
                GetLastError() );

    if ( hToken != NULL )
    {
        CloseHandle( hToken );
        hToken = NULL;
    }

    return FALSE;
}

BOOL
EncryptAndEncodeCredentials(
    CHAR *          szUser,
    CHAR *          szPassword,
    CHAR *          szClientIP,
    ISAPI_STRING *  pstrResult
    )
/*++

Purpose:

    Accepts username and password information from the caller,
    encrypts and base64 encodes the data, and populates an
    ISAPI_STRING with the result.  The client's IP address is
    used in the encryption process to ensure that only requests
    from this same client will be able to decrypt them.

Arguments:

    szUser     - The user name to encrypt
    szPassword - The password to encrypt
    szClientIP - The client's IP address
    pstrResult - On successful return, contains the result

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    DATA_BLOB       ClearBlob = {0};
    DATA_BLOB       EncryptedBlob = {0};
    DATA_BLOB       EntropyBlob = {0};
    ISAPI_STRING    strEncodedUser;
    ISAPI_STRING    strEncodedPassword;
    ISAPI_STRING    strCurrentTime;
    ISAPI_STRING    strCookedCredentials;
    BOOL            fResult = FALSE;

    //
    // Encode the username and credentials
    //

    if ( strEncodedUser.Copy( szUser ) == FALSE )
    {
        goto Done;
    }

    if ( strEncodedUser.Escape( TRUE ) == FALSE )
    {
        goto Done;
    }

    if ( strEncodedPassword.Copy( szPassword ) == FALSE )
    {
        goto Done;
    }

    if ( strEncodedPassword.Escape() == FALSE )
    {
        goto Done;
    }

    //
    // Get the current time and escape it
    //

    if ( GetCurrentTimeAsString( &strCurrentTime ) == FALSE )
    {
        goto Done;
    }

    if ( strCurrentTime.Escape() == FALSE )
    {
        goto Done;
    }

    //
    // Create the raw cookie value
    //

    if ( strCookedCredentials.Printf( "%s#%s#%s",
                                       strEncodedUser.QueryStr(),
                                       strEncodedPassword.QueryStr(),
                                       strCurrentTime.QueryStr() ) == FALSE )
    {
        goto Done;
    }

    //
    // Set up the input data blobs.
    //
    // Use the client IP for the entropy blob, and
    // cooked credentials for the clear data blob.
    //

    EntropyBlob.pbData = (BYTE*)szClientIP;
    EntropyBlob.cbData = strlen( szClientIP );

    ClearBlob.pbData = (BYTE*)strCookedCredentials.QueryStr();
    ClearBlob.cbData = strCookedCredentials.QueryCB() + sizeof(CHAR);

    //
    // Encrypt the data.  Zero out the clear data blob right afterward.
    //

    if ( CryptProtectData( &ClearBlob,
                           L"",
                           g_fUseClientIpForEncryption ? &EntropyBlob : NULL,
                           NULL,
                           NULL,
                           CRYPTPROTECT_UI_FORBIDDEN,
                           &EncryptedBlob ) == FALSE )
    {
        goto Done;
    }

    //
    // Now encode the data into the caller's buffer
    //

    fResult = pstrResult->Base64Encode( EncryptedBlob.pbData,
                                        EncryptedBlob.cbData );

Done:

    if ( fResult == FALSE )
    {
        WriteDebug( "EncryptAndEncodeCredentials failed.  Error %d.\r\n",
                    GetLastError() );
    }

    //
    // Clean up data structures
    //

    if ( EncryptedBlob.pbData )
    {
        LocalFree( EncryptedBlob.pbData );
        EncryptedBlob.pbData = NULL;
        EncryptedBlob.cbData = 0;
    }

    //
    // Zero out our buffer that held the cooked credentials
    //
                             
    strCookedCredentials.ZeroBuffer();

    return fResult;
}

BOOL
DecodeAndDecryptCredentials(
    CHAR *          szCredentials,
    CHAR *          szClientIP,
    ISAPI_STRING *  pstrUser,
    ISAPI_STRING *  pstrPassword,
    FILETIME *      pft
    )
/*++

Purpose:

    Accepts a string from the caller containing credentials
    that have been encrypted and base64 encoded, and returns
    the username and password.  The correct client's IP
    address is required to successfully complete the process.

Arguments:

    szCredentials - The encrypted and encoded credentials
    szClientIP    - The client's IP address
    pstrUser      - On successful return, contains the username
    pstrPassword  - On successful return, contains the password
    pft           - On successful return, contains the time stamp

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    DATA_BLOB       ClearData = {0};
    DATA_BLOB       EncryptedData = {0};
    DATA_BLOB       EntropyData = {0};
    ISAPI_BUFFER    Buffer;
    ISAPI_STRING    strTimeStamp;
    CHAR *          pUsername;
    CHAR *          pPassword;
    CHAR *          pTimeStamp;
    CHAR *          pCursor;
    BOOL            fResult = FALSE;

    //
    // Decode the credentials
    //

    if ( Buffer.Base64Decode( szCredentials ) == FALSE )
    {
        goto Done;
    }

    //
    // Now decrypt them
    //

    EntropyData.pbData = (BYTE*)szClientIP;
    EntropyData.cbData = strlen( szClientIP );

    EncryptedData.pbData = (BYTE*)Buffer.QueryPtr();
    EncryptedData.cbData = Buffer.QueryDataSize();

    if ( CryptUnprotectData( &EncryptedData,
                             NULL,
                             g_fUseClientIpForEncryption ? &EntropyData : NULL,
                             NULL,
                             NULL,
                             CRYPTPROTECT_UI_FORBIDDEN,
                             &ClearData ) == FALSE )
    {
        goto Done;
    }
    
    //
    // Now parse the data for the username and password.
    // We assume the the code that encrypted the data
    // did so with the NULL terminator.
    //

    pUsername = (CHAR*)ClearData.pbData;

    pCursor = strchr( pUsername, '#' );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        goto Done;
    }

    *pCursor = '\0';

    pPassword = pCursor + 1;

    pCursor = strchr( pPassword, '#' );

    if ( !pCursor )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        goto Done;
    }

    *pCursor = '\0';

    pTimeStamp = pCursor + 1;

    if ( pstrUser->Copy( pUsername ) == FALSE )
    {
        goto Done;
    }

    pstrUser->Unescape();

    if ( pstrPassword->Copy( pPassword ) == FALSE )
    {
        goto Done;
    }

    pstrPassword->Unescape();

    if ( strTimeStamp.Copy( pTimeStamp ) == FALSE )
    {
        goto Done;
    }

    strTimeStamp.Unescape();

    if ( GetFileTimeFromString( pft, strTimeStamp.QueryStr() ) == FALSE )
    {
        goto Done;
    }

    fResult = TRUE;

Done:

    if ( fResult == FALSE )
    {
        WriteDebug( "DecodeAndDecryptCredentials failed.  Error %d.\r\n",
                    GetLastError() );
    }

    //
    // Clean up data structures
    //

    if ( ClearData.pbData )
    {
        LocalFree( ClearData.pbData );
        ClearData.pbData = 0;
        ClearData.cbData = 0;
    }

    return fResult;
}


