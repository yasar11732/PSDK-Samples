/************************************************************
*                                                           *
* SetOptions.cpp                                            *
*                                                           *
* Copyright (c) Microsoft Corporation. All Rights Reserved. *
*                                                           *
************************************************************/

#include <windows.h>
#include <winhttp.h>
#include <stdio.h>

int main(int argc, char *argv []){

    HINTERNET hSession;
    BOOL httpResult;
    DWORD dwSize    = sizeof(DWORD);
    DWORD dwData = 0;
    DWORD dwNewData = 50000;
 
    // Print a description for the user.
    printf("This sample demonstrates the process for setting WinHTTP options\n");
    printf("programmatically from a C/C++ application. WinHTTP application\n");
    printf("programming interface (API) functions are used to change the connect\n");
    printf("time-out value.\n\n");

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(  L"A WinHTTP Example Program/1.0", 
                             WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                             WINHTTP_NO_PROXY_NAME, 
                             WINHTTP_NO_PROXY_BYPASS, 0);


    // Use WinHttpQueryOption to retrieve the connect time-out.
    httpResult = WinHttpQueryOption( hSession, WINHTTP_OPTION_CONNECT_TIMEOUT, 
                                     &dwData, &dwSize);
    printf("Old Connect Time-Out: %u\n", dwData);

    // Use WinHttpSetOption to set a new connect time-out.
    httpResult = WinHttpSetOption( hSession, WINHTTP_OPTION_CONNECT_TIMEOUT,
                                   &dwNewData, dwSize);

    // Use WinHttpQueryOption to verify the new connect time-out.
    httpResult = WinHttpQueryOption( hSession, WINHTTP_OPTION_CONNECT_TIMEOUT, 
                                     &dwData, &dwSize);
    printf("New Connect Time-Out: %u\n", dwData);

    // When finished, release the HINTERNET handle.
    httpResult = WinHttpCloseHandle(hSession);
    if (!httpResult)
        printf("Could not close the HINTERNET handle.\n");

    return 0;
}