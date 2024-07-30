//
//  This is part of the Microsoft Tablet PC Platform SDK
//  Copyright (C) 2002 Microsoft Corporation
//  All rights reserved.
//
//  This source code is only intended as a supplement to the
//  Microsoft Tablet PC Platform SDK Reference and related electronic 
//  documentation provided with the Software Development Kit.
//  See these sources for more detailed information. 
//
// Module:       
//        FactReg.cpp
//
// Description:
//      This program demonstrates how one can take advantage of using 
//      factoids with neither Ink nor Text Services Framework aware applications.
//      In this case, factoids are set in the registry. 
//
//      This sample application is a simple dialog with standard Edit
//      and RichEdit controls. It's assumed that the text is entered into the dialog's
//      controls using handwriting through a Tablet Input Panel (TIP). 
//      The handwriting recognition accuracy is greatly improved when factoids for
//      each control are specified in the registry. To benefit from factoids 
//      no application's source code modification is required. All one needs to do,
//      in order to take advantage of factoids, is create entries for the dialog 
//      controls in the system registry using the following format:
//      
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\DownLevel]
//            "control_class_name control_caption control_id"="factoid_name"
//         
//      where 
//      control_class_name is the registered window class name of the control;
//      control_caption is the window name of the control. If the control doesn't 
//            have a name, the name of the control preceding this one in the dialog 
//            order can be used;
//      control_id is the unique child window identifier of the control (decimal integer)
//      factoid_name is a string that addresses the type of the factoid to be used 
//            with the control. The full list of the factoid types can be found
//            in the "Using Factoids For Increased Handwriting Recognition".
//      All the strings must be case-sensitive.
//
//      So, for example, the entry for the Edit control that has an id 1002 
//      and, in the dialog order, goes right after a static control with 
//      caption "Phone1" will be 
//              
//            "Edit Phone1 1002"="TELEPHONE"
//        
//      Also, predefined dictionaries can be used with some of the factoid types. 
//      The dictionaries should be persisted either in the system registry or as text files.
//      In any case an additional registry entry is required.
//      For a factoid with a dictionary in the registry, the entry should be
//        
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\mru]
//            "control_class_name control_caption control_id"="hkcu_registry_key"
//
//      where
//      "control_class_name control_caption control_id" should be exactly 
//            the same as in the corresponding entry under 
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\DownLevel]
//      hkcu_registry_key is a key with the root HKEY_CURRENT_USER in the registry.
//            The values found under that key will comprise the factoid dictionary.
//
//      Example:
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\DownLevel]
//            "Edit URL 1010"="WEB|WORDLIST"
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\mru]
//            "Edit URL 1010"="Software\\Microsoft\\Internet Explorer\\TypedURLs"
//
//      If the factoid dictionary is provided as a text file, a registry entry 
//      with the following format needs to be added:
//        
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\wordlist]
//            "control_class_name control_caption control_id"="filename"
//
//      where
//      "control_class_name control_caption control_id" should be exactly 
//            the same as in the corresponding entry under 
//            [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\DownLevel]
//      filename is the name of the dictionary file. Usually it includes the fully 
//            qualified path to the file, but it's not required if the path is 
//            mentioned in the value of the environment variable PATH.
//
//      Registry-based as well as file-based dictionaries may also be used without 
//      applying any particular factoid type, just as wordlists.
//      In this case there is no need to create an entry under 
//      [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\DownLevel], but only 
//      an appropriate entry under [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\mru] 
//      or [HKEY_LOCAL_MACHINE\Software\Microsoft\factoidClient\wordlist] is required.
//
//      For more details on using factoids please refer to the "Using Factoids For 
//      Increased Handwriting Recognition".
//
//      The registry settings for this sample are in the accompanying file Factoid.reg. 
//      To add them into the registry, click the right mouse button on the file and 
//      select Merge from the context menu.
//      The same way you need to merge into the registry the data from the Wordlist.reg. 
//      The file contains the sample registry-based wordlist referred to in the Factoids.reg.
//      Also, for the file-based wordlist to be found, make sure that the path to the 
//      Wordlist.txt is either listed in the PATH environment variable or explicitly 
//      specified in the Factoids.reg (ex.: "RICHEDIT Wordlist (from file) 1013"=
//      "C:\\Program Files\\Microsoft Tablet PC Platform SDK\\Samples\\FactReg\\wordlist.txt")
//        
//      This application is discussed in the Getting Started guide.
//   
//--------------------------------------------------------------------------

#include <windows.h>
#include "resource.h"   // Microsoft Developer Studio generated include file, that contains 
                        // the list of control identifiers mentioned in the Factoids.reg file

/////////////////////////////////////////////////////////
//                                          
// DlgProc
//
//        The DlgProc function is an application-defined 
//        function that processes messages sent to the dialog.
//        The minimal dialog procedure template is used here.
//
// Parameters:
//        HWND hwnd      : [in] handle to dialog window
//        UINT uMsg      : [in] message identifier
//        WPARAM wParam  : [in] first message parameter
//        LPARAM lParam  : [in] second message parameter
//
// Return Values:
//        The return value is the result of the 
//        message processing and depends on the message sent
//
/////////////////////////////////////////////////////////
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:

            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            { 
                case IDCLOSE:   // User clicked on the "Close" button in the dialog.
                case IDCANCEL:  // User clicked the close button ([X]) in the caption
                                // or pressed Alt+F4.
                    DestroyWindow(hwnd); 
                    return TRUE; 
            } 
            break;
    }

    return FALSE;
}

/////////////////////////////////////////////////////////
//                                          
// WinMain
// 
//      The WinMain function is called by the system as the 
//      initial entry point for a Win32-based application. 
//      It contains typical boilerplate code to create and 
//      show the main window, and pump messages.
//
// Parameters:
//      HINSTANCE hInstance,      : [in] handle to current instance
//      HINSTANCE hPrevInstance,  : [in] handle to previous instance
//      LPSTR lpCmdLine,          : [in] command line
//      int nCmdShow              : [in] show state
//
// Return Values:
//        0, if the function terminated before entering the message loop,
//        or the value of the message's wParam
//
/////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    // Unused parameters, the next line silence the compiler warnings.
    hPrevInstance, lpCmdLine, nCmdShow;      

    // Need to load the library before creating RichEdit controls 
    // (see Q166132 in the Microsoft Knowledge Base).
    HMODULE hRichEdit = LoadLibrary(TEXT("RichEd32.dll"));

    // Create the application window.
    HWND hwndDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    if (!hwndDlg)
    {
        MessageBox(NULL, TEXT("Error creating the dialog box"), 
                   TEXT("Error"), MB_OK | MB_ICONINFORMATION);
        return 0;                                                                                                          
    }

    ShowWindow(hwndDlg, SW_SHOW);
    
    // Start the boilerplate message loop.
    MSG msg; 
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        if (!IsDialogMessage(hwndDlg, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
        
    // Release the RichEdit module.
    FreeLibrary(hRichEdit);
    
    return msg.wParam;
}

                
