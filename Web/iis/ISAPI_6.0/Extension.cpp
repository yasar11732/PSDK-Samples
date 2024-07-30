/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: ***

Abstract:

    ISAPI extension ***

Author:

    ISAPI developer (Microsoft employee), ***

--*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <httpext.h>

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
             "***",
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
    return HSE_STATUS_SUCCESS;
}

BOOL
WINAPI
TerminateExtension(
    DWORD   dwFlags
    )
/*++

Purpose:

    Entry point for ISAPI extension termination.  Optional.

    If present, IIS will call this function just before it
    unloads the extension.  In general, this function will
    be called after all of the running requests for this
    extension have completed.

    Any complex or long-running uninitialization tasks should
    be performed here.  This function is called outside of the
    system loader lock, so it does not have the same
    restrictions as DllMain.
    
Arguments:
    
    dwFlags - specifies whether the DLL can refuse to unload or not
    
Returns:
    
    TRUE, if the DLL can be unloaded

    Note that the HSE_TERM_ADVISORY_UNLOAD flag is not used by
    IIS, so it's not necessary to consider any cases where the
    extension can refuse to unload.
    
--*/
{
    BOOL    fReturn = TRUE;

    switch ( dwFlags )
    {
    case HSE_TERM_ADVISORY_UNLOAD:

        //
        // Return TRUE if ok to unload or FALSE if not
        //

        fReturn = TRUE;

    case HSE_TERM_MUST_UNLOAD:

        //
        // Cannot refuse to unload
        //

        fReturn = TRUE;
    }

    return fReturn;
}
