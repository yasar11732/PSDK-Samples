/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: CachiIsapi.cpp

Abstract:

    ISAPI extension to demonstrate sending a response
    that's cacheable by the http.sys response cache.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#include <IsapiTools.h>

#define MODULE_NAME             "CacheIsapi"
#define DEFAULT_CACHE_SECONDS   60

#define CACHE_PAGE \
        "<html>\r\n"                                   \
        "<head><title>CacheIsapi</title></head>\r\n"   \
        "<h1> CacheIsapi.dll Sample </h1>\r\n"         \
        "<hr>\r\n"                                     \
        "This page is cacheable.<br><br>\r\n"          \
        "<table border=2 cellspacing=2 padding=0>\r\n" \
        "  <tr>\r\n"                                   \
        "    <td>User mode request count:</td>\r\n"    \
        "    <td>%d</td>\r\n"                          \
        "  </tr>\r\n"                                  \
        "  <tr>\r\n"                                   \
        "    <td>Page generation Time:</td>\r\n"       \
        "    <td>%s</td>\r\n"                          \
        "  </tr>\r\n"                                  \
        "  <tr>\r\n"                                   \
        "    <td>Cache Duration:</td>\r\n"             \
        "    <td>%d seconds</td>\r\n"                  \
        "  </tr>\r\n"                                  \
        "</table>\r\n"                                 \
        "<br>\r\n"                                     \
        "To invalidate the cache before it expires, "  \
        "add 'invalidate' to the query string "        \
        "and re-request this URL.  To change "         \
        "the cache duration, add the desired "         \
        "number of seconds to the query string "       \
        "and re-request this URL.\r\n"                 \
        "</html>"

#define INVALIDATE_PAGE \
        "<html>\r\n"                                 \
        "<head><title>CacheIsapi</title></head>\r\n" \
        "<h1>CacheIsapi.dll</h1>\r\n"                \
        "<hr>\r\n"                                   \
        "%s"                                         \
        "</html>"

#define CHANGE_DURATION_PAGE \
        "<html>\r\n"                                 \
        "<head><title>CacheIsapi</title></head>\r\n" \
        "<h1>CacheIsapi.dll</h1>\r\n"                \
        "<hr>\r\n"                                   \
        "Cache duration set to %d seconds\r\n"       \
        "</html>"

#define HELP_PAGE   \
        "<html>\r\n"                                            \
        "<head><title>CacheIsapi</title></head>\r\n"            \
        "<h1>CacheIsapi.dll</h1>\r\n"                           \
        "<hr>\r\n"                                              \
        "Request CacheIsapi.dll with no query string "          \
        "to generate a cacheable response.  Example:<br>\r\n"   \
        "<pre>\r\n"                                             \
        "\thttp://server/scripts/cacheisapi.dll\r\n"            \
        "</pre><br>\r\n"                                        \
        "Request CacheIsapi.dll with 'invalidate' on the "      \
        "query string to invalidate the current cached "        \
        "response.  Example:<br>\r\n"                           \
        "<pre>\r\n"                                             \
        "\thttp://server/scripts/cacheisapi.dll?invalidate\r\n" \
        "</pre><br>\r\n"                                        \
        "Request CacheIsapi.dll with a number on the query "    \
        "string, to change the cache duration to that number "  \
        "of seconds.  Example:<br>\r\n"                         \
        "<pre>\r\n"                                             \
        "\thttp://server/scripts/cacheisapi.dll?60\r\n"         \
        "</pre><br>\r\n"                                        \
        "Anything else returns this page."                      \
        "</html>\r\n"

//
// Global ISAPI_EXTENSION object
//

ISAPI_EXTENSION g_Extension;

//
// Cache invalidation URL.  Needs to be Unicode
// so that we can pass it to the below cache invalidation
// function.
//

ISAPI_STRINGW    g_strCacheUrl;

//
// Cache invalidation function pointer
//

PFN_HSE_CACHE_INVALIDATION_CALLBACK g_pfnInvalidateCacheUrl = NULL;

//
// Page counter
//

LONG    g_lRequests = 0;

//
// Cache expiration time
//

DWORD   g_dwCacheSeconds = DEFAULT_CACHE_SECONDS;

//
// Local prototypes
//

BOOL
WINAPI
Initialize(
    VOID *  pContext
    );

BOOL
DoCacheable(
    ISAPI_REQUEST * pRequest
    );

BOOL
DoInvalidate(
    ISAPI_REQUEST * pRequest
    );

BOOL
DoChangeDuration(
    ISAPI_REQUEST * pRequest
    );

BOOL
DoHelp(
    ISAPI_REQUEST * pRequest
    );

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIo,
    DWORD                       dwError
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
             "CacheIsapi Sample Extension",
             HSE_MAX_EXT_DLL_NAME_LEN );

    pVer->lpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN-1] = '\0';

    //
    // Initialize the IsapiTools and ISAPI_EXTENSION object
    //

    InitializeIsapiTools( MODULE_NAME );

    if ( g_Extension.Initialize( MODULE_NAME ) == FALSE )
    {
        goto Failed;
    }

    //
    // Return TRUE if we successfully initialized.
    //

    return TRUE;

Failed:

    WriteDebug( "GetExtensionVersion failed.  Error %d.\r\n",
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
    ISAPI_REQUEST * pRequest;
    DWORD           dwHseStatus;
    BOOL            fCacheResponse = FALSE;

    //
    // Initialize on the first hit
    //

    if ( g_Extension.InitOnce( Initialize, pecb ) == FALSE )
    {
        goto Failed;
    }

    //
    // Allocate an ISAPI_REQUEST object and set the status
    // and headers.
    //

    pRequest = new ISAPI_REQUEST( pecb );

    if ( !pRequest )
    {
        goto Failed;
    }

    if ( pRequest->SetBufferedResponseStatus( "200 OK" ) == FALSE )
    {
        goto Failed;
    }

    if ( pRequest->AddHeaderToBufferedResponse( "Content-Type",
                                                "text/html" ) == FALSE )
    {
        goto Failed;
    }

    //
    // Process the request appropriate for the actual query string
    //

    if ( *pecb->lpszQueryString == '\0' )
    {
        dwHseStatus = DoCacheable( pRequest );

        if ( dwHseStatus != HSE_STATUS_ERROR )
        {
            fCacheResponse = TRUE;
        }
    }
    else if ( stricmp( pecb->lpszQueryString, "invalidate" ) == 0 )
    {
        dwHseStatus = DoInvalidate( pRequest );
    }
    else if ( isdigit( *pecb->lpszQueryString ) )
    {
        dwHseStatus = DoChangeDuration( pRequest );
    }
    else
    {
        dwHseStatus = DoHelp( pRequest );
    }

    if ( dwHseStatus == HSE_STATUS_ERROR )
    {
        goto Failed;
    }

    //
    // Send the response asynchronousle.  Return HSE_STATUS_PENDING
    // if successful
    //

    if ( pRequest->AsyncTransmitBufferedResponse( HandleCompletion,
                                                  fCacheResponse?
                                                  g_dwCacheSeconds :
                                                  0 ) == TRUE )
    {
        return HSE_STATUS_PENDING;
    }

    //
    // Fall through to the error handler
    //

Failed:

    WriteDebug( "HttpExtensionProc failed. Error %d\r\n",
                GetLastError() );

    return SyncSendGenericServerError( pecb );
}

BOOL
WINAPI
Initialize(
    VOID *  pContext
    )
/*++

Purpose:

    Performs initialization of this extension

Arguments:

    pContext - The ISAPI_REQUEST associated with this request 

Returns:

    TRUE on success, FALSE on failure

--*/
{
    EXTENSION_CONTROL_BLOCK *   pecb;
    BOOL                        fResult = FALSE;
    WCHAR *                     pCursor;

    pecb = (EXTENSION_CONTROL_BLOCK*)pContext;

    ISAPI_ASSERT( pecb );

    ISAPI_REQUEST   Request( pecb );


    //
    // Get the cache invalidation callback function
    //

    if ( g_pfnInvalidateCacheUrl == NULL )
    {
        fResult = pecb->ServerSupportFunction( pecb->ConnID,
                                               HSE_REQ_GET_CACHE_INVALIDATION_CALLBACK,
                                               &g_pfnInvalidateCacheUrl,
                                               NULL,
                                               NULL );

        if ( !fResult )
        {
            goto Done;
        }
    }

    //
    // Initialize the cache invalidation URL.
    //
    // Note that that URL comes from represents the key
    // that http.sys used to identify the request from the,
    // and it includes the URL and query string as sent.
    // If we call the cache invalidation function, it will
    // invalidate exactly this key.
    //
    // To keep things simple, we are going to make a few
    // assumptions.
    //
    //   1. We will assume that this extensions will
    //      mark its response as cacheable only in the
    //      case where there is no query string.
    //
    //   2. We will assume that this extension was not
    //      called via HSE_REQ_EXEC_URL.  In this case,
    //      it's possible that the URL from the client
    //      looks nothing like the URL that would
    //      normally call this extension.  We don't need
    //      to worry about the case where a filter has
    //      rewritten the client's URL, because IIS would
    //      not allow such a modified request to be
    //      cached.
    //
    // As a result of these assumptions, we are just going
    // to take the first URL to reach this extension, and
    // strip any URL off of it.  This is what we'll pass
    // in the cache invalidation function to http.sys.
    //
    // If a real, production extension chose to use the
    // cache invalidation function, it would need to keep
    // a list of URLs, representing each request, and then
    // invalidate the specific ones desired.
    //
    // Note also, that IIS will examine the "Expires"
    // header in the response and automatically invalidate
    // the cache entry at the expiration time.  Because of
    // this, most extensions won't need to use the
    // invalidation function at all.
    //

    fResult = Request.GetServerVariable( "UNICODE_CACHE_URL",
                                         &g_strCacheUrl );

    if ( !fResult )
    {
        goto Done;
    }

    //
    // Strip any query string
    //

    pCursor = wcschr( g_strCacheUrl.QueryStr(), L'?' );

    if ( pCursor )
    {
        *pCursor = L'\0';

        g_strCacheUrl.CalcLen();
    }

Done:

    if ( !fResult )
    {
        WriteDebug( "Initialize failed.  Error %d.\r\n",
                    GetLastError() );
    }

    return fResult;
}

BOOL
DoCacheable(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Builds the cacheable response page

Arguments:

    pRequest - An ISAPI_REQUEST object for this request

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    FILETIME        ftCurrent;
    ISAPI_STRING    strCurrent;

    //
    // Get the current time
    //

    if ( GetCurrentTimeAsFileTime( &ftCurrent ) == FALSE )
    {
        goto Failed;
    }

    if ( GetFileTimeAsString( &ftCurrent, &strCurrent ) == FALSE )
    {
        goto Failed;
    }

    //
    // Bump the request count
    //

    InterlockedIncrement( &g_lRequests );

    if ( pRequest->PrintfToResponseBuffer( CACHE_PAGE,
                                           g_lRequests,
                                           strCurrent.QueryStr(),
                                           g_dwCacheSeconds ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "DoCacheable failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

BOOL
DoInvalidate(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Builds the invalidates the cache entry for 
    this URL and builds the response page

Arguments:

    pRequest - An ISAPI_REQUEST object for this request

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    ISAPI_STRING    strResult;
    HRESULT         hr;

    //
    // Invalidate the cache
    //

    ISAPI_ASSERT( g_strCacheUrl.QueryStr() );

    hr = g_pfnInvalidateCacheUrl( g_strCacheUrl.QueryStr() );

    if ( FAILED( hr ) )
    {
        SetLastError( hr );

        if ( strResult.Printf( "Error %d occurred flushing cache.",
                               GetLastError() ) == FALSE )
        {
            goto Failed;
        }
    }
    else
    {
        if ( strResult.Printf( "Successfully flushed the cache.") == FALSE )
        {
            goto Failed;
        }
    }

    //
    // Build a page with the results
    //

    if ( pRequest->PrintfToResponseBuffer( INVALIDATE_PAGE,
                                           strResult.QueryStr() ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "DoCacheable failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

BOOL
DoChangeDuration(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Changes the cache lifetime for cacheable responses from this
    extension.

Arguments:

    pRequest - An ISAPI_REQUEST object for this request

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    DWORD   dwNewDuration;
    HRESULT hr;

    dwNewDuration = atol( pRequest->QueryEcb()->lpszQueryString );

    g_dwCacheSeconds = dwNewDuration;

    //
    // Flush the cache
    //

    hr = g_pfnInvalidateCacheUrl( g_strCacheUrl.QueryStr() );

    if ( FAILED( hr ) )
    {
        SetLastError( hr );

        goto Failed;
    }

    //
    // Build the response
    //
    
    if ( pRequest->PrintfToResponseBuffer( CHANGE_DURATION_PAGE,
                                           g_dwCacheSeconds ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "DoCacheable failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

BOOL
DoHelp(
    ISAPI_REQUEST * pRequest
    )
/*++

Purpose:

    Builds the help page for this extension

Arguments:

    pRequest - An ISAPI_REQUEST object for this request

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    if ( pRequest->AddDataToResponseBuffer( HELP_PAGE,
                                            sizeof(HELP_PAGE) - 1 ) == FALSE )
    {
        goto Failed;
    }

    return TRUE;

Failed:

    WriteDebug( "DoCacheable failed.  Error %d.\r\n",
                GetLastError() );

    return FALSE;
}

VOID
WINAPI
HandleCompletion(
    EXTENSION_CONTROL_BLOCK *   pecb,
    VOID *                      pContext,
    DWORD                       cbIo,
    DWORD                       dwError
    )
/*++

Purpose:

    Handles completion of asynchronous I/O by deleting
    the ISAPI_REQUEST associated with the request.  The
    destructor for this object takes care of calling
    HSE_REQ_DONE_WITH_SESSION as appropriate.

Arguments:

    pRequest - An ISAPI_REQUEST object for this request

Returns:

    TRUE on success, FALSE on failure.

--*/
{
    ISAPI_REQUEST * pRequest = (ISAPI_REQUEST*)pContext;

    //
    // We just need to delete the ISAPI_REQUEST object
    // it's destructor will do the rest.
    //

    if ( pRequest )
    {
        delete pRequest;
        pRequest = NULL;
    }
}
