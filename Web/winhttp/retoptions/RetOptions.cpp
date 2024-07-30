/************************************************************
*                                                           *
* RetOptions.cpp                                            *
*                                                           *
* Copyright (c) Microsoft Corporation. All Rights Reserved. *
*                                                           *
************************************************************/

#include <windows.h>
#include <winhttp.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    HINTERNET hSession;
    HINTERNET hConnect;
    HINTERNET hRequest;
    BOOL httpResult;
    DWORD data;
    DWORD dwSize = sizeof(DWORD);
    LPWSTR pwszURL;


    // Print a description of the sample.
    printf("This sample demonstrates the process for retrieving WinHTTP\n");
    printf("options programmatically from a C/C++ application. WinHTTP\n");
    printf("application programming interface (API) functions are used to\n");
    printf("determine the default connect time-out value and to find the\n");
    printf("current URL after an HTTP request is redirected.\n\n");

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(  L"A WinHTTP Example Program/1.0", 
                             WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                             WINHTTP_NO_PROXY_NAME, 
                             WINHTTP_NO_PROXY_BYPASS, 0);

    // Use WinHttpQueryOption to retrieve Internet options.
    httpResult = WinHttpQueryOption( hSession, WINHTTP_OPTION_CONNECT_TIMEOUT, 
                                     &data, &dwSize);
    if (httpResult) 
        printf("Connect time-out:\t%u ms\n",data);

    // Use WinHttpConnect to specify an HTTP server.
    hConnect = WinHttpConnect( hSession, L"msdn.microsoft.com",
                               INTERNET_DEFAULT_HTTP_PORT, 0);

    // Open and Send a Request Header.
    hRequest = WinHttpOpenRequest( hConnect, L"GET", 
                         L"/downloads/samples/internet/winhttp/retoptions/redirect.asp", 
                         NULL, WINHTTP_NO_REFERER, 
                         WINHTTP_DEFAULT_ACCEPT_TYPES, 0);                     
    httpResult = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 
                                     0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    httpResult = WinHttpReceiveResponse( hRequest, NULL);

    // Use WinHttpQueryOption again, this time to obtain a buffer size.
    httpResult = WinHttpQueryOption( hRequest, WINHTTP_OPTION_URL, 
                                     NULL, &dwSize);
    pwszURL = new WCHAR[dwSize/sizeof(WCHAR)];
    
    // Use WinHttpQueryOption to retrieve Internet options.
    httpResult = WinHttpQueryOption( hRequest, WINHTTP_OPTION_URL, 
                                     (void *)pwszURL, &dwSize);
    printf("Redirected URL:\t\t%S\n",pwszURL);

    // Free the allocated memory.
    delete [] pwszURL;

    // When finished, release the hRequest handle.
    httpResult = WinHttpCloseHandle(hRequest);
    if (!httpResult)
        printf("Could not close the hRequest handle.\n");

    // When finished, release the hConnect handle.
    httpResult = WinHttpCloseHandle(hConnect);
    if (!httpResult)
        printf("Could not close the hConnect handle.\n");

    // When finished, release the hSession handle.
    httpResult = WinHttpCloseHandle(hSession);
    if (!httpResult)
        printf("Could not close the hSession handle.\n");


    return 0;
}