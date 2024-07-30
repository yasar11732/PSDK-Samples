/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: DumpRequestInfo.cpp

Abstract:

    ISAPI extension that dumps all information from
    an HTTP request.

    This sample also demonstrates use of the ISAREQUEST
    object to asynchronously send a buffered response.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <IsapiTools.h>

//
// An array of server variables
//
// Note that this list comprises all of the available
// built-in server variables in the original release
// of IIS 6.
//

#define MAX_VAR_NAME    64

CHAR    g_rgVariableList[][MAX_VAR_NAME] = { "APP_POOL_ID",
                                             "APPL_MD_PATH",
                                             "APPL_PHYSICAL_PATH",
                                             "AUTH_PASSWORD",
                                             "AUTH_TYPE",
                                             "AUTH_USER",
                                             "CACHE_URL",
                                             "CERT_COOKIE",
                                             "CERT_FLAGS",
                                             "CERT_ISSUER",
                                             "CERT_KEYSIZE",
                                             "CERT_SECRETKEYSIZE",
                                             "CERT_SERIALNUMBER",
                                             "CERT_SERVER_ISSUER",
                                             "CERT_SERVER_SUBJECT",
                                             "CERT_SUBJECT",
                                             "CONTENT_LENGTH",
                                             "CONTENT_TYPE",
                                             "GATEWAY_INTERFACE",
                                             "HTTP_CFG_ENC_CAPS",
                                             "HTTP_URL",
                                             "HTTP_METHOD",
                                             "HTTP_VERSION",
                                             "HTTPS",
                                             "HTTPS_KEYSIZE",
                                             "HTTPS_SECRETKEYSIZE",
                                             "HTTPS_SERVER_ISSUER",
                                             "HTTPS_SERVER_SUBJECT",
                                             "INSTANCE_ID",
                                             "INSTANCE_META_PATH",
                                             "LOCAL_ADDR",
                                             "LOGON_USER",
                                             "PATH_INFO",
                                             "PATH_TRANSLATED",
                                             "QUERY_STRING",
                                             "REMOTE_ADDR",
                                             "REMOTE_HOST",
                                             "REMOTE_PORT",
                                             "REMOTE_USER",
                                             "REQUEST_METHOD",
                                             "SCRIPT_NAME",
                                             "SCRIPT_TRANSLATED",
                                             "SERVER_NAME",
                                             "SERVER_PORT",
                                             "SERVER_PORT_SECURE",
                                             "SERVER_PROTOCOL",
                                             "SERVER_SOFTWARE",
                                             "UNENCODED_URL",
                                             "UNMAPPED_REMOTE_USER",
                                             "URL",
                                             "" };

//
// A simple 500 response we can send in the case of error
//

CHAR    g_szErrorResponse[] = "<html>\r\n"
                              "<head> <title> DumpRequestInfo.dll "
                              "</title> </head>\r\n"
                              "<h1> DumpRequestInfo.dll </h1>\r\n"
                              "<hr>\r\n"
                              "The server was unable to process "
                              "your request.\r\n"
                              "</html>";


//
// Set some local definitions and prototypes
//

#define MAX_BUFFERED_RESPONSE_SIZE 128*1024
#define MAX_ALLOWED_ENTITY_SIZE    120*1024

VOID
WINAPI
AsyncCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       cbError
    );

DWORD
ProcessRequest(
    ISAPI_REQUEST * pRequest
    );

BOOL
WriteEcbDump(
    ISAPI_REQUEST * pRequest
    );

BOOL
WriteServerVariables(
    ISAPI_REQUEST * pRequest
    );

BOOL
WriteRequestHeaders(
    ISAPI_REQUEST * pRequest
    );

BOOL
WriteRequestEntity(
    ISAPI_REQUEST * pRequest
    );

//
// ISAPI entry point implementations
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
             "DumpRequestInfo Sample ISAPI Extension",
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
    ISAPI_REQUEST * pRequest;

    pRequest = new ISAPI_REQUEST( pecb );

    //
    // If we Fail to allocate the ISAREQUEST object.  The
    // best we can do now is to manually send an error
    // to the client.
    //

    if ( !pRequest )
    {
        DWORD   cbErrorResponse;

        //
        // Set the size of the response.  Note that HTTP entity bodies
        // are not NULL terminated.
        //

        cbErrorResponse = sizeof( g_szErrorResponse ) - 1;

        //
        // Set the ECB's status member to correctly log this
        // failure as a 500.
        //

        pecb->dwHttpStatusCode = 500;

        //
        // Send the response.  There is no real need to check
        // for an error here, as there is nothing we can do
        // to recover.
        //

        pecb->ServerSupportFunction( pecb->ConnID,
                                     HSE_REQ_SEND_RESPONSE_HEADER,
                                     "500 Server Error",
                                     NULL,
                                     (DWORD*)"Content-Type: text/html\r\n"
                                     "\r\n" );

        pecb->WriteClient( pecb->ConnID,
                           g_szErrorResponse,
                           &cbErrorResponse,
                           HSE_IO_SYNC );

        return HSE_STATUS_ERROR;
    }

    return ProcessRequest( pRequest );
}

//
// Local function implementations
//

VOID
WINAPI
AsyncCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       cbError
    )
/*++

Purpose:

    Handles cleaning up the request when the asynchronous
    TRANSMIT_FILE call completes.  Since the ISAREQUEST
    destructor takes care of cleaning up the ISAPI pieces,
    we basically just need to delete it here.

    Note that in the case of TRANSMIT_FILE, cbIO will
    reflect the number of file bytes sent, not including
    head and tail bytes.  Since ISAREQUEST::AsyncTransmitBufferedResponse
    works by using TRANSMIT_FILE with a NULL file handle,
    we expect that cbIO will be zero.

    Also, note that we will clean up the request any differently
    if an error occurs in transmission, so we don't need to
    check the cbError member.

Arguments:

    pecb     - pointer to the extenstion control block 
    pContext - pointer to the I/O context (the ISAREQUEST in our case)
    cbIO     - the number of file bytes associated with the I/O
    cbError  - if non-zero, the code associated with any error in
               transmission

Returns:

    None

--*/
{
    delete (ISAPI_REQUEST*)pContext;
}

DWORD
ProcessRequest(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Does the main work of processing the request

Arguments:

    pRequest - the ISAREQUEST object created in HttpExtensionProc

Returns:

    An HSE_STATUS code

--*/
{
    //
    // Set the maximum response that we are willing to send
    //

    pRequest->SetMaxResponseBufferSize( MAX_BUFFERED_RESPONSE_SIZE );

    //
    // Begin building the response buffer
    //

    if ( !pRequest->AddHeaderToBufferedResponse( "Content-Type",
                                                 "text/html" ) )
    {
        goto Failed;
    }

    if ( !pRequest->PrintfToResponseBuffer( "<html>\r\n"
                                            "<head> <title> DumpRequestInfo "
                                            "</title> </head>\r\n"
                                            "<h1> DumpRequestInfo.dll </h1>\r\n"
                                            "<hr>\r\n" ) )
    {
        goto Failed;
    }

    //
    // Dump the parts of the request into the response buffer
    //

    if ( !WriteEcbDump( pRequest ) )
    {
        goto Failed;
    }

    if ( !WriteServerVariables( pRequest ) )
    {
        goto Failed;
    }

    if ( !WriteRequestHeaders( pRequest ) )
    {
        goto Failed;
    }

    if ( !WriteRequestEntity( pRequest ) )
    {
        goto Failed;
    }

    //
    // Complete the response buffer
    //

    if ( !pRequest->PrintfToResponseBuffer( "</html>" ) )
    {
        goto Failed;
    }

    //
    // Transmit the response to the client.  If this call succeeds,
    // then we must assume that the completion will occur immediately
    // and clean up the request.  We must therefore avoid touching
    // pRequest and return HSE_STATUS_PENDING unless the call fails.
    //

    if ( pRequest->AsyncTransmitBufferedResponse( AsyncCompletion ) )
    {
        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to error handler
    //

Failed:

    //
    // Send a 500 response to the client
    //

    pRequest->SyncWriteCompleteResponse( "500 Server Error",
                                         "Content-Type: text/html\r\n\r\n",
                                         g_szErrorResponse );

    return HSE_STATUS_ERROR;
}

BOOL
WriteEcbDump(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Writes EXTENSION_CONTROL_BLOCK data into response buffer

Arguments:

    pRequest - the ISAREQUEST object created in HttpExtensionProc

Returns:

    An HSE_STATUS code

--*/
{
    EXTENSION_CONTROL_BLOCK *   pecb;
    BOOL                        fRet;

    pecb = pRequest->QueryEcb();

    fRet = pRequest->PrintfToResponseBuffer(
        "<h1> Dump of "
        "EXTENSION_CONTROL_BLOCK: </h1>\r\n"
        "<pre>\r\n"
        "cbSize             = %d\r\n"
        "dwVersion          = %08x\r\n"
        "ConnID             = %p\r\n"
        "dwHttpStatusCode   = %d\r\n"
        "cbTotalBytes       = %d\r\n"
        "cbAvailable        = %d\r\n"
        "lpbData            = %p\r\n"
        "lpszLogData        = %s\r\n"
        "lpszMethod         = %s\r\n"
        "lpszQueryString    = %s\r\n"
        "lpszPathInfo       = %s\r\n"
        "lpszPathTranslated = %s\r\n"
        "lpszContentType    = %s\r\n"
        "</pre>\r\n"
        "<hr>\r\n",
        pecb->cbSize,
        pecb->dwVersion,
        pecb->ConnID,
        pecb->dwHttpStatusCode,
        pecb->cbTotalBytes,
        pecb->cbAvailable,
        pecb->lpbData,
        pecb->lpszLogData,
        pecb->lpszMethod,
        pecb->lpszQueryString,
        pecb->lpszPathInfo,
        pecb->lpszPathTranslated,
        pecb->lpszContentType );

    return fRet;
}

BOOL
WriteServerVariables(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Writes server variable data into response buffer

Arguments:

    pRequest - the ISAREQUEST object created in HttpExtensionProc

Returns:

    An HSE_STATUS code

--*/
{
    ISAPI_STRING    strValue;
    DWORD           x = 0;
    BOOL            fResult;

    //
    // Write the start of the server variable output
    //

    if ( !pRequest->PrintfToResponseBuffer( "<h1> Server Variable Dump "
                                            "</h1>\r\n"
                                            "<pre>\r\n" ) )
    {
        return FALSE;
    }

    //
    // Loop through all of the server variables and
    // write them to the output buffer
    //

    while ( g_rgVariableList[x] &&
            g_rgVariableList[x][0] != '\0' )
    {
        fResult = pRequest->GetServerVariable( g_rgVariableList[x],
                                               &strValue );

        if ( fResult )
        {
            if ( !pRequest->PrintfToResponseBuffer( "%20s = %s\r\n",
                                                    g_rgVariableList[x],
                                                    strValue.QueryStr() ) )
            {
                return FALSE;
            }
        }
        else
        {
            if ( !pRequest->PrintfToResponseBuffer( "%20s = *** Error %d ***\r\n",
                                                    g_rgVariableList[x],
                                                    GetLastError() ) )
            {
                return FALSE;
            }
        }

        x++;
    }

    //
    // Write the final part of the server variable output
    //

    if ( !pRequest->PrintfToResponseBuffer( "</pre>\r\n"
                                            "<hr>\r\n" ) )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL
WriteRequestHeaders(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Writes request header data into response buffer

Arguments:

    pRequest - the ISAREQUEST object created in HttpExtensionProc

Returns:

    An HSE_STATUS code

--*/
{
    ISAPI_STRING    strHeaders;

    //
    // Write the start of the request header output
    //

    if ( !pRequest->PrintfToResponseBuffer( "<h1> Request Header Dump "
                                            "</h1>\r\n"
                                            "<pre>\r\n" ) )
    {
        return FALSE;
    }

    //
    // Get ALL_RAW, which contains the data as the client sent it
    //

    if ( !pRequest->GetServerVariable( "ALL_RAW",
                                       &strHeaders ) )
    {
        return FALSE;
    }

    if ( !pRequest->PrintfToResponseBuffer( strHeaders.QueryStr() ) )
    {
        return FALSE;
    }

    //
    // Write the final part of the request header output
    //

    if ( !pRequest->PrintfToResponseBuffer( "</pre>\r\n"
                                            "<hr>\r\n" ) )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL
WriteRequestEntity(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Writes request entity data into response buffer

Arguments:

    pRequest - the ISAREQUEST object created in HttpExtensionProc

Returns:

    An HSE_STATUS code

--*/
{
    ISAPI_BUFFER    buffEntity( MAX_ALLOWED_ENTITY_SIZE );

    //
    // If there is no entity, then just return
    //

    if ( pRequest->QueryEcb()->cbTotalBytes == 0 )
    {
        return TRUE;
    }

    //
    // Write the start of the entity output
    //

    if ( !pRequest->PrintfToResponseBuffer( "<h1> Request Entity Dump "
                                            "</h1>\r\n"
                                            "<pre>\r\n" ) )
    {
        return FALSE;
    }

    if ( !pRequest->ReadAllEntity( &buffEntity ) )
    {
        //
        // If the entity is too large for our buffer,
        // we'll just print something to that effect
        //

        if ( GetLastError() != ERROR_NOT_ENOUGH_MEMORY )
        {
            return FALSE;
        }

        if ( !pRequest->PrintfToResponseBuffer( "*** Entity Too Large "
                                                "***\r\n" ) )
        {
            return FALSE;
        }
    }

    //
    // Since we're not writing a formatted string, use the append
    // function instead of the write function.  Not only is this
    // higher performance, but it does not depend on the current
    // maximum write size.
    //

    if ( !pRequest->AddDataToResponseBuffer( buffEntity.QueryPtr(),
                                             buffEntity.QueryDataSize() ) )
    {
        return FALSE;
    }

    //
    // Write the final part of the request entity output
    //

    if ( !pRequest->PrintfToResponseBuffer( "</pre>\r\n"
                                            "<hr>\r\n" ) )
    {
        return FALSE;
    }

    return TRUE;
}
