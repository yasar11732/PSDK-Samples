/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: UpCaseMap.cpp

Abstract:

    ISAPI extension to demonstrate a wildcard script map
    that modifies request entity in a filter-like manner.

    UpCaseMap will intercept requests and acquire the
    entity body.  If the entity body is of a text mime
    type, then UpCaseMap will convert all characters to
    upper case and use HSE_REQ_EXEC_URL to hand off the
    modified request to be handled.

    UpCaseMap also does bounds checking to enforce a
    size limit on the amount of entity that will be
    accepted.  If this size is exceeded by the client,
    a "413 Entity Too Large" response will be sent.

    UpCaseMap uses the ISABUFFER and ISAREQUEST helper
    objects.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <IsapiTools.h>

//
// Local definitions
//

#define MAX_ALLOWED_REQUEST_ENTITY 64*1024

#define UPCASE_ANSI_CHAR(c) ((((unsigned char)c & 0xdf) < 'A' || \
                              ((unsigned char)c & 0xdf) > 'Z') ? \
                              c : \
                              (c & 0xdf))

//
// Local prototypes
//

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
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
             "UpCaseMap Sample ISAPI Extension",
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
    HSE_EXEC_URL_INFO           ExecUrlInfo;
    HSE_EXEC_URL_ENTITY_INFO    EntityInfo;
    ISAPI_BUFFER *              pbuffEntity = NULL;
    ISAPI_REQUEST               Request( pecb );
    BOOL                        fModifiedEntity = FALSE;

    //
    // If there is no entity body on this request, we
    // don't need to do any processing.
    //

    if ( pecb->cbTotalBytes == 0 )
    {
        goto CallExecUrl;
    }

    //
    // Since we are going to ultimately pass our entity buffer
    // to someone else, we need to allocate it on the heap, and
    // keep it valid until they are done.
    //

    pbuffEntity = new ISAPI_BUFFER();

    if ( !pbuffEntity )
    {
        goto Failed;
    }

    //
    // Set the maximum entity body that we will allow
    //

    pbuffEntity->SetMaxAlloc( MAX_ALLOWED_REQUEST_ENTITY );

    //
    // Read the entity body.  If we fail due to
    // ERROR_NOT_ENOUGH_MEMORY, then we'll send a 413
    // response, else we'll send a 500.
    //

    if ( !Request.ReadAllEntity( pbuffEntity ) )
    {
        //
        // Since we failed to read the entity, we can
        // clean up the buffer now.
        //

        delete pbuffEntity;
        pbuffEntity = NULL;

        if ( GetLastError() == ERROR_NOT_ENOUGH_MEMORY )
        {
            HSE_CUSTOM_ERROR_INFO CustomError;

            //
            // Send a 413 response synchronously using
            // HSE_REQ_SEND_CUSTOM_ERROR
            //

            CustomError.pszStatus = "413 Entity Too Large";
            CustomError.uHttpSubError = 0;
            CustomError.fAsync = FALSE;

            if ( pecb->ServerSupportFunction( pecb->ConnID,
                                              HSE_REQ_SEND_CUSTOM_ERROR,
                                              &CustomError,
                                              NULL,
                                              NULL ) == FALSE )
            {
                //
                // The custom error call failed (which is likely, since
                // IIS does not include a custom error for this by default).
                //
                // Go ahead and send it manually.
                //

                Request.SyncWriteCompleteResponse( "413 Entity Too Large",
                                                   "Content-Type: text/html\r\n\r\n",
                                                   "<html>\r\n"
                                                   "<head> <title> Entity Too Large "
                                                   "</head> </title>\r\n"
                                                   "<h1> 413 Entity Too Large </h1>\r\n"
                                                   "<hr>\r\n"
                                                   "The size of the request entity "
                                                   "is too large.\r\n"
                                                   "</html>");
            }

            return HSE_STATUS_ERROR;
        }

        goto Failed;
    }

    //
    // If the entity is a text type, then convert it to
    // upper case.
    //
    // Note that we could modify the entity body in any
    // way that we want to here.  When we pass the details
    // of the resulting buffer through the EXEC_URL call,
    // the request will be processed as if the client had
    // originally sent the contents of our buffer.
    //
    // This is substantially different than writing a
    // READ_RAW_DATA filter in IIS versions earlier than
    // 6.0 for a number of reasons.  For example:
    //
    // - It is easy to assemble the data in a single,
    //   contiguous chunk for parsing.
    // - We can change the size of the entity body and
    //   EXEC_URL will handle the details of making the
    //   child request properly recognize it.
    // - We could acquire the entity asynchronously (although
    //   this sample does not demonstrate async reads).
    // - We don't have to worry about writing logic to handle
    //   chunk transfer encoding.
    // - The request has been authenticed by the time this
    //   extension runs, so we don't have to worry about
    //   recognizing raw authentication data streams.
    //

    if ( strnicmp( pecb->lpszContentType, "text/", 5 ) == 0 )
    {
        //
        // Walk the entity body and convert ANSI characters
        // to upper case.  We won't use _strupr for this, since
        // it assumes that the data is NULL terminated.  This
        // is not necessarily true for HTTP entity bodies.
        //

        CHAR *  pCursor;

        //
        // Get a pointer to the start of the entity data.
        // Note that we will use QueryPtr, and not QueryStr.
        // The reason for this is that QueryStr enforces
        // NULL termination.  In the case where the entity
        // body is already the maximum allowed size, adding
        // the NULL will push the buffer one byte over and
        // cause it to fail to return the string (with
        // last error ERROR_NOT_ENOUGH_MEMORY).
        //

        pCursor = (CHAR*)pbuffEntity->QueryPtr();

        for ( DWORD x = 0; x < pbuffEntity->QueryDataSize(); x++ )
        {
            *(pCursor + x) = UPCASE_ANSI_CHAR( *(pCursor + x) );
        }

        fModifiedEntity = TRUE;
    }

    //
    // Associate our modified buffer with the child request
    //

    EntityInfo.lpbData = pbuffEntity->QueryPtr();
    EntityInfo.cbAvailable = pbuffEntity->QueryDataSize();

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
    // flag.  This will ensure that UpCaseMap is not called again
    // on this request (which could otherwise happen in some cases).
    //

    ExecUrlInfo.pszUrl = NULL;
    ExecUrlInfo.pszMethod = NULL;
    ExecUrlInfo.pszChildHeaders = NULL;
    ExecUrlInfo.pUserInfo = NULL;
    ExecUrlInfo.pEntity = NULL;
    ExecUrlInfo.dwExecUrlFlags = HSE_EXEC_URL_IGNORE_CURRENT_INTERCEPTOR;

    if ( fModifiedEntity )
    {
        ExecUrlInfo.pEntity = &EntityInfo;
    }

    //
    // Associate the completion routine and the current URL with
    // this request.
    //

    if ( pecb->ServerSupportFunction( pecb->ConnID,
                                      HSE_REQ_IO_COMPLETION,
                                      HandleCompletion,
                                      NULL,
                                      (DWORD*)pbuffEntity ) == FALSE )
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

    //
    // If we've successfully allocated our own entity buffer,
    // delete it now.
    //

    if ( pbuffEntity )
    {
        delete pbuffEntity;
        pbuffEntity = NULL;
    }

    //
    // Send a 500 error
    //

    return SyncSendGenericServerError( pecb );
}

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIO,
    DWORD                       dwError
    )
{
    ISAPI_BUFFER * pEntity = (ISAPI_BUFFER*)pContext;

    //
    // The child is done.  Delete the entity buffer now.
    //

    if ( pEntity )
    {
        delete pEntity;
        pEntity = 0;
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
