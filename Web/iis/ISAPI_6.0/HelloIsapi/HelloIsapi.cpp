/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: HelloIsapi.cpp

Abstract:

    A very simple ISAPI extension that demonstrates sending
    a basic response to an HTTP client.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <stdio.h>
#include <windows.h>
#include <httpext.h>

//
// Define a size for any CHAR arrays that we need
//

#define STRING_SIZE 256

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
             "HelloIsapi Sample Extension",
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
    //
    // Create a simple, canned response
    //

    CHAR    szResponse[] = "<html>\r\n"
                           "<head>\r\n"
                           "<title> HelloIsapi Sample Extension </title>\r\n"
                           "</head>\r\n"
                           "<h1> Hello ISAPI! </h1>\r\n"
                           "<hr>\r\n"
                           "This is a very simple ISAPI extension.";

    //
    // Determine the size of the response.  Note that HTTP responses
    // are not necessarily NULL terminated, so we'll not include
    // the terminator in our size.
    //

    DWORD   cbResponse = sizeof( szResponse ) - 1;

    //
    // Create the optional headers that we need.  We'll include the
    // content-type, so the client knows to render the response as
    // HTML, and we'll also include a content-length.
    //
    // The inclusion of a content-length when using
    // HSE_REQ_SEND_RESPONSE_HEADER will allow IIS to honor keep-alive
    // if the client has requested it.  Without a content-length,
    // IIS will close the connection at the conculsion of this
    // response.
    //

    CHAR    szHeaders[STRING_SIZE];

    _snprintf( szHeaders,
               STRING_SIZE,
               "Content-Type: text/html\r\n"
               "Content-Length: %d\r\n\r\n",
               cbResponse );

    //
    // Ensure that szHeaders buffer is NULL terminated in the case
    // where STRING_SIZE might have been insufficient to hold all
    // of the data.
    //
    // Note that this isn't strictly necessary for this particular
    // code, since we know that the headers will fit, and we won't
    // be calling any more string functions against szHeaders.
    // It is, however, a good practice to get into the habit of
    // protecting against any buffer overruns that result from some
    // later code assuming that this string is properly NULL
    // terminated.
    //

    szHeaders[STRING_SIZE-1] = '\0';

    //
    // Send back a 200 response, with the headers we've built
    //

    pecb->ServerSupportFunction( pecb->ConnID,
                                 HSE_REQ_SEND_RESPONSE_HEADER,
                                 "200 OK",
                                 NULL,
                                 (DWORD*)szHeaders );

    //
    // Send back the entity synchronously
    //

    pecb->WriteClient( pecb->ConnID,
                       szResponse,
                       &cbResponse,
                       HSE_IO_SYNC );

    //
    // All Done!
    //

    return HSE_STATUS_SUCCESS;
}
