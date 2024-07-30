/************************************************************
*                                                           *
* AsyncDemo.cpp                                             *
*                                                           *
* Copyright (c) Microsoft Corporation. All Rights Reserved. *
*                                                           *
************************************************************/

#define UNICODE
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include "resource.h"

//********************************************************************
//                                                  Global Variables  
//********************************************************************

// Context value structure.
typedef struct {
    HWND        hWindow;        // Handle for the dialog box
    HINTERNET   hConnect;       // Connection handle
    HINTERNET   hRequest;       // Resource request handle
    int         nURL;           // ID of the URL edit box
    int         nHeader;        // ID of the header output box
    int         nResource;      // ID of the resource output box
    DWORD       dwSize;         // Size of the latest data block
    DWORD       dwTotalSize;    // Size of the total data
    LPSTR       lpBuffer;       // Buffer for storing read data
    WCHAR       szMemo[512];    // String providing state information
} REQUEST_CONTEXT;


//********************************************************************
//                                              Additional Functions  
//********************************************************************




//********************************************************************
//                                                   Status Callback  
//********************************************************************

void __stdcall AsyncCallback( HINTERNET hInternet, DWORD dwContext,
                              DWORD dwInternetStatus,
                              LPVOID lpvStatusInformation,
                              DWORD dwStatusInformationLength)
{
    REQUEST_CONTEXT *cpContext;
    WCHAR szBuffer[256];
    cpContext = (REQUEST_CONTEXT*)dwContext;

    // Create a string that reflects the status flag.
    switch (dwInternetStatus)
    {
        case WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE:
            swprintf(szBuffer,L"%s: DATA_AVAILABLE (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE:
            swprintf(szBuffer,L"%s: HEADERS_AVAILABLE (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_INTERMEDIATE_RESPONSE:
            swprintf(szBuffer,L"%s: INTERMEDIATE_RESPONSE (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_READ_COMPLETE:
            swprintf(szBuffer,L"%s: READ_COMPLETE (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_REDIRECT:
            swprintf(szBuffer,L"%s: REDIRECT (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_REQUEST_ERROR:
            swprintf(szBuffer,L"%s: REQUEST_ERROR (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        case WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE:
            swprintf(szBuffer,L"%s: SENDREQUEST_COMPLETE (%d)", 
                cpContext->szMemo, dwStatusInformationLength);
            break;
        default:
            swprintf(szBuffer,L"%s: Unknown callback - status %d given",
                cpContext->szMemo, dwInternetStatus);
            break;
    }

    // Add the callback information to the listbox.
    SendDlgItemMessage( cpContext->hWindow, IDC_CBLIST, LB_ADDSTRING, 0, 
                        (LPARAM)szBuffer);
}


//********************************************************************
//                                                   Dialog Function  
//********************************************************************

BOOL CALLBACK AsyncDialog( HWND hX, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_INITDIALOG:
        // Set the default web sites.
        SetDlgItemText(hX, IDC_URL1, L"http://www.microsoft.com");
        SetDlgItemText(hX, IDC_URL2, L"http://www.msn.com");

        return TRUE;
    case WM_CLOSE:
        EndDialog(hX,0);
        return TRUE;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case IDC_EXIT:
                EndDialog(hX,0);
                return TRUE;
            case IDC_DOWNLOAD:
                WCHAR szURL1[256], szURL2[256];

                // Reset the edit boxes.
                SetDlgItemText( hX, IDC_HEADER1, NULL );
                SetDlgItemText( hX, IDC_HEADER2, NULL );
                SetDlgItemText( hX, IDC_RESOURCE1, NULL );
                SetDlgItemText( hX, IDC_RESOURCE2, NULL );

                // Obtain the URLs from the dialog box.
                GetDlgItemText( hX, IDC_URL1, szURL1, 256);
                GetDlgItemText( hX, IDC_URL2, szURL2, 256);

                return TRUE;
        }
    default:
        return FALSE;
    }
}


//********************************************************************
//                                                      Main Program  
//********************************************************************

int WINAPI WinMain( HINSTANCE hThisInst, HINSTANCE hPrevInst,
                    LPSTR lpszArgs, int nWinMode)
{
    // Show the dialog box.
    DialogBox( hThisInst, MAKEINTRESOURCE(IDD_DIALOG1), 
               HWND_DESKTOP, (DLGPROC)AsyncDialog );

    return 0;
}