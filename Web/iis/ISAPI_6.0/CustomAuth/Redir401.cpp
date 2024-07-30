/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: Redir401.cpp

Abstract:

	ISAPI filter to modify 401 responses so that they
    send a 302 redirect to another URL.

Author:

	ISAPI developer (Microsoft employee), November 2002

--*/

//
// We need to define _WIN32_WINNT to version
// 5 so that LOGON32_LOGON_NETWORK_CLEARTEXT
// gets defined.
//

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif

#include <stdio.h>
#include <windows.h>
#include <httpfilt.h>
#include <IsapiTools.h>
#include "CustomAuth.h"

#define MAX_CONFIG_LINE 1024

ISAPI_STRING    g_strRedirectResponse;

//
// Enumeration for filter state
//

enum FILTER_STATE
{
    IgnoreNotification = 0,
    ReplaceDataWithRedirectBlob,
    SuppressData
};

//
// Local prototypes
//

DWORD
DoPreprocHeaders(
    HTTP_FILTER_CONTEXT *           pfc,
    HTTP_FILTER_PREPROC_HEADERS *   pPreproc
    );

DWORD
DoSendResponse(
    HTTP_FILTER_CONTEXT *       pfc,
    HTTP_FILTER_SEND_RESPONSE * pSendResponse
    );

DWORD
DoSendRawData(
    HTTP_FILTER_CONTEXT *   pfc,
    HTTP_FILTER_RAW_DATA *  pRawData
    );

DWORD
DoEndOfRequest(
    HTTP_FILTER_CONTEXT *       pfc
    );

VOID
TrimCommentAndTrailingWhitespace(
    CHAR *  szString
    );

BOOL
LoadModuleConfig(
    VOID
    );

BOOL
GetStringFromConfig(
    CHAR *          szKey,
    CHAR *          szDefault,
    ISAPI_STRING *  pstrString
    );

INT
GetIntFromConfig(
    CHAR *  szKey,
    INT     nDefault
    );

BOOL WINAPI GetFilterVersion(
	PHTTP_FILTER_VERSION pVer
	)
/*++

Purpose:

    Required entry point for ISAPI filters.  This function
    is called when the server initially loads this DLL.

Arguments:

    pVer - Points to the filter version info structure

Returns:

    TRUE on successful initialization
    FALSE on initialization failure

--*/
{
	pVer->dwFilterVersion = HTTP_FILTER_REVISION;
	lstrcpy(pVer->lpszFilterDesc, "Redir401 ISAPI Filter");
	pVer->dwFlags =
		SF_NOTIFY_ORDER_DEFAULT |
        SF_NOTIFY_PREPROC_HEADERS |
        SF_NOTIFY_SEND_RESPONSE |
        SF_NOTIFY_SEND_RAW_DATA
		;

    //
    // Initialize IsapiTools
    //

    InitializeIsapiTools( MODULE_NAME );

    //
    // Initialize the global extension object.
    //
    // Normally, this would occur in GetExtensionVersion on
    // an extension, but since we want access to the data
    // here as well and the filter part is guaranteed to
    // be called before the extension, we'll do it here.
    //

    if ( g_Extension.Initialize( MODULE_NAME ) == FALSE )
    {
        goto Failed;
    }

    //
    // Get the config filename
    //

    if ( g_strIniFile.Printf( "%s\\%s.ini",
                              g_Extension.QueryModulePath(),
                              MODULE_NAME ) == FALSE )
    {
        goto Failed;
    }

    //
    // Read the config data
    //

    if ( LoadModuleConfig() == FALSE )
    {
        goto Failed;
    }

    g_fFilterInitialized = TRUE;

	return TRUE;

Failed:

    return FALSE;
}

DWORD WINAPI HttpFilterProc(
	PHTTP_FILTER_CONTEXT pfc,
	DWORD dwNotificationType,
	LPVOID pvNotification
	)
/*++

Purpose:

    Required filter notification entry point.  This function is called
    whenever one of the events (as registered in GetFilterVersion) occurs.

Arguments:

    pfc              - A pointer to the filter context for this notification
    NotificationType - The type of notification
    pvNotification   - A pointer to the notification data

Returns:

    One of the following valid filter return codes:
    - SF_STATUS_REQ_FINISHED
    - SF_STATUS_REQ_FINISHED_KEEP_CONN
    - SF_STATUS_REQ_NEXT_NOTIFICATION
    - SF_STATUS_REQ_HANDLED_NOTIFICATION
    - SF_STATUS_REQ_ERROR
    - SF_STATUS_REQ_READ_NEXT

--*/
{
    DWORD   status = SF_STATUS_REQ_NEXT_NOTIFICATION;

    //
    // Route the notification to the proper handler function
    //

    switch ( dwNotificationType )
    {
    case SF_NOTIFY_PREPROC_HEADERS:

        status = DoPreprocHeaders( pfc,
                                   (HTTP_FILTER_PREPROC_HEADERS*)pvNotification );

        break;

    case SF_NOTIFY_SEND_RESPONSE:

        status = DoSendResponse( pfc,
                                 (HTTP_FILTER_SEND_RESPONSE*)pvNotification );

        break;

    case SF_NOTIFY_SEND_RAW_DATA:

        status = DoSendRawData( pfc,
                                (HTTP_FILTER_RAW_DATA*)pvNotification );

        break;
    }

    return status;
}

DWORD
DoPreprocHeaders(
    HTTP_FILTER_CONTEXT *           pfc,
    HTTP_FILTER_PREPROC_HEADERS *   pPreproc
    )
{
    ISAPI_STRING    strPFC;
    DWORD           status = SF_STATUS_REQ_NEXT_NOTIFICATION;

    //
    // Initialize the filter state for this request
    //

    pfc->pFilterContext = (VOID*)IgnoreNotification;

    //
    // We are going to store a string version of pfc in
    // a custom request header.  This will allow the extension
    // part of this dll to call AddResponseHeaders.
    //
    // First, ensure that our string is big enough to store 8
    // characters, plus terminator.
    //

    if ( strPFC.ResizeBuffer( 9 ) == FALSE )
    {
        goto Failed;
    }

    //
    // Add a CustomAuth-Context header with a string
    // version of pfc.
    //

    _snprintf( strPFC.QueryStr(),
               strPFC.QueryBufferSize() - 1,
               "%08x",
               pfc );

    if ( pPreproc->AddHeader( pfc,
                              "CustomAuth-Context:",
                              strPFC.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    return status;

Failed:

    WriteDebug( "DoPreprocHeaders failed.  Error %d\r\n",
                GetLastError() );

    return SF_STATUS_REQ_ERROR;
}

DWORD
DoSendResponse(
    HTTP_FILTER_CONTEXT *       pfc,
    HTTP_FILTER_SEND_RESPONSE * pSendResponse
    )
/*++

Purpose:

    Handles SF_NOTIFY_SEND_RESPONSE.

    If we detect that we are sending a 401 response, and that
    no built-in authentication schemes are in use for this request,
    we will set the filter context to replace the 401 with a
    302 redirect to the logon page.

    If this is not a 401 response, we will disable further
    notifications for this request for performance reasons.

Arguments:

    pfc           - A pointer to the filter context for this notification
    pSendResponse - The HTTP_FILTER_SEND_RESPONSE structure

Returns:

    SF_STATUS_REQ_NEXT_NOTIFICATION on success
    SF_STATUS_REQ_ERROR on failure

--*/
{
    CHAR    szWwwAuthenticate[256];
    DWORD   status = SF_STATUS_REQ_NEXT_NOTIFICATION;
    DWORD   cbWwwAuthenticate;
    BOOL    fResult;


    //
    // We care about 401 responses.  If this is not a
    // 401, then we should disable further notifications.
    //

    if ( pSendResponse->HttpStatus != 401 )
    {
        goto DisableFurtherNotifications;
    }

    //
    // Do one more check.  If this request has any www-authenticate
    // response headers, then we know that one or more authentication
    // schemes are supported.  In this case, we'll defer to the
    // built-in authentication schemes.
    //

    cbWwwAuthenticate = 256;

    fResult =  pSendResponse->GetHeader( pfc,
                                         "WWW-AUTHENTICATE:",
                                         szWwwAuthenticate,
                                         &cbWwwAuthenticate );

    if ( fResult == TRUE ||
         GetLastError() != ERROR_INVALID_INDEX )
    {
        goto DisableFurtherNotifications;
    }

    //
    // Set the filter state such that the send raw
    // handler replaces the first packet with the
    // redirect blob.
    //

    pfc->pFilterContext = (VOID*)ReplaceDataWithRedirectBlob;

    return status;

DisableFurtherNotifications:

    pfc->ServerSupportFunction( pfc,
                                SF_REQ_DISABLE_NOTIFICATIONS,
                                NULL,
                                SF_NOTIFY_SEND_RAW_DATA |
                                SF_NOTIFY_END_OF_REQUEST,
                                0 );

    return status;
}

DWORD
DoSendRawData(
    HTTP_FILTER_CONTEXT *   pfc,
    HTTP_FILTER_RAW_DATA *  pRawData
    )
/*++

Purpose:

    Handles SF_NOTIFY_SEND_RAW_DATA.

    Replaces the raw data going to the client with the redirect
    response data, or suppresses the data as directed by the
    request state.

Arguments:

    pfc      - A pointer to the filter context for this notification
    pRawData - The HTTP_FILTER_RAW_DATA structure

Returns:

    SF_STATUS_REQ_NEXT_NOTIFICATION

--*/
{
    FILTER_STATE    state = (FILTER_STATE)((DWORD)pfc->pFilterContext);
    DWORD           status = SF_STATUS_REQ_NEXT_NOTIFICATION;

    //
    // Do the right thing for the current state
    //

    switch ( state )
    {
    case IgnoreNotification:

        goto Done;

    case ReplaceDataWithRedirectBlob:

        pRawData->pvInData = g_strRedirectResponse.QueryStr();
        pRawData->cbInBuffer = g_strRedirectResponse.QueryBufferSize();
        pRawData->cbInData = g_strRedirectResponse.QueryCB();

        //
        // Set the state to suppress data, so any further notifications
        // on this response won't reach the client.
        //

        pfc->pFilterContext = (VOID*)SuppressData;

        goto Done;

    case SuppressData:

        pRawData->cbInData = 0;

        goto Done;
    }

Done:

    return status;
}

DWORD
DoEndOfRequest(
    HTTP_FILTER_CONTEXT *       pfc
    )
/*++

Purpose:

    Handles SF_NOTIFY_END_OF_REQUEST

    Resets the filter state for subsequent requests over
    this same client connection.

Arguments:

    pfc      - A pointer to the filter context for this notification

Returns:

    SF_STATUS_REQ_NEXT_NOTIFICATION

--*/
{
    DWORD   status = SF_STATUS_REQ_NEXT_NOTIFICATION;

    //
    // Reset the filter state
    //

    pfc->pFilterContext = (VOID*)IgnoreNotification;

    return status;
}

BOOL
LoadModuleConfig(
    VOID
    )
/*++

Purpose:

    Loads the configuration for this ISAPI from
    the ini file.

Arguments:

    None

Returns:

    TRUE on success, FALSE on failure

--*/
{
    ISAPI_STRING    strLogonType;
    INT             nFlag;

    //
    // Get LogonUrl as a string
    //

    if ( GetStringFromConfig( "LogonUrl",
                              DEFAULT_LOGON_URL,
                              &g_strLogonUrl ) == FALSE )
    {
        goto Failed;
    }

    //
    // Get LogoffUrl as a string
    //

    if ( GetStringFromConfig( "LogoffUrl",
                              DEFAULT_LOGON_URL,
                              &g_strLogoffUrl ) == FALSE )
    {
        goto Failed;
    }

    //
    // Get UseBuiltInLogonPage as a boolean
    //

    nFlag = GetIntFromConfig( "UseBuiltInLogonPage",
                              DEFAULT_USE_BUILTIN_LOGON );

    g_fUseBuiltInLogon = ( nFlag != 0 );

    //
    // Get UseBuiltInLogoffPage as a boolean
    //

    nFlag = GetIntFromConfig( "UseBuiltInLogoffPage",
                              DEFAULT_USE_BUILTIN_LOGOFF );

    g_fUseBuiltInLogoff = ( nFlag != 0 );

    //
    // Get UseSSLForFormSubmission as a boolean
    //

    nFlag = GetIntFromConfig( "UseSSLForFormSubmission",
                              DEFAULT_USE_SSL );

    g_fUseSSLForSubmission = ( nFlag != 0 );

    //
    // Get UseClientIpForEncryption as a boolean
    //

    nFlag = GetIntFromConfig( "UseClientIpForEncryption",
                              DEFAULT_USE_CLIENT_IP );

    g_fUseClientIpForEncryption = ( nFlag != 0 );

    //
    // Get LogonTimeout as an int
    //

    g_LogonTimeoutSeconds = GetIntFromConfig( "LogonTimeout",
                                              DEFAULT_LOGON_TIMEOUT );

    //
    // Get LogonSuccessUrl as a string
    //

    if ( GetStringFromConfig( "LogonSuccessUrl",
                              DEFAULT_LOGON_SUCCESS_URL,
                              &g_strLogonSuccessUrl ) == FALSE )
    {
        goto Failed;
    }

    //
    // Get LogonType as a string, and resolve it to a LOGON32_LOGON value
    //

    if ( GetStringFromConfig( "LogonType",
                              DEFAULT_LOGON_TYPE,
                              &strLogonType ) == FALSE )
    {
        goto Failed;
    }

    if ( stricmp( strLogonType.QueryStr(), "network_cleartext" ) == 0 )
    {
        g_LogonType = LOGON32_LOGON_NETWORK_CLEARTEXT;
    }
    else if ( stricmp( strLogonType.QueryStr(), "batch" ) == 0 )
    {
        g_LogonType = LOGON32_LOGON_BATCH;
    }
    else if ( stricmp( strLogonType.QueryStr(), "network" ) == 0 )
    {
        g_LogonType = LOGON32_LOGON_NETWORK;
    }
    else if ( stricmp( strLogonType.QueryStr(), "interactive" ) == 0 )
    {
        g_LogonType = LOGON32_LOGON_INTERACTIVE;
    }
    else
    {
        g_LogonType = LOGON32_LOGON_NETWORK_CLEARTEXT;
    }

    //
    // Build up the redirect response
    //

    if ( g_strRedirectResponse.Printf( "HTTP/1.1 302 Object Moved\r\n"
                                       "Location: %s\r\n"
                                       "Set-Cookie: %s\r\n"
                                       "\r\n"
                                       REDIRECT_ENTITY,
                                       g_strLogonUrl.QueryStr(),
                                       DELETE_COOKIE,
                                       g_strLogonUrl.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "LoadModuleConfig failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

BOOL
GetStringFromConfig(
    CHAR *          szKey,
    CHAR *          szDefault,
    ISAPI_STRING *  pstrString
    )
/*++

Purpose:

    Gets a string from the ini file

Arguments:

    szKey      - The key to retrieve (from the [Options] section)
    szDefault  - Default value to use if the key is not found
    pstrString - On successful return, contains the value

Returns:

    TRUE on success, FALSE on failure

--*/
{
    CHAR    szValue[MAX_CONFIG_LINE];
    BOOL    fResult;

    GetPrivateProfileString( "Options",
                             szKey,
                             "",
                             szValue,
                             MAX_CONFIG_LINE,
                             g_strIniFile.QueryStr() );

    TrimCommentAndTrailingWhitespace( szValue );

    if ( szValue[0] == '\0' )
    {
        WriteDebug( "GetStringFromConfig returning default value for %s.\r\n",
                    szDefault );

        fResult = pstrString->Copy( szDefault );
    }
    else
    {
        fResult = pstrString->Copy( szValue );
    }

    if ( !fResult )
    {
        WriteDebug( "GetStringFromConfig failed.  Error %d.\r\n",
                    GetLastError() );
    }

    return fResult;
}

INT
GetIntFromConfig(
    CHAR *  szKey,
    INT     nDefault
    )
/*++

Purpose:

    Gets an integer value from the ini file

Arguments:

    szKey    - The key to retrieve (from the [Options] section)
    nDefault - Default value to use if the key is not found

Returns:

    The requested value, or the default if it wasn't found

--*/
{
    return GetPrivateProfileInt( "Options",
                                 szKey,
                                 nDefault,
                                 g_strIniFile.QueryStr() );
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
