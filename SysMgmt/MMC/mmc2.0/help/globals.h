/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//

#ifndef _MMC_GLOBALS_H
#define _MMC_GLOBALS_H

#include <TChar.h>
#include <Mmc.h>
#include <CrtDbg.h>                    // Support for _ASSERT
#include <shlwapi.h>                   // Support for path functions
#include "Guids.h"

#pragma warning(4:4267)   // convertion from size_t to smaller type
#pragma warning(3:4244)   // sizeof returns to INT

class CBaseNode;                       // References
class CDataObject;


//---------------------------------------------------------------------------
extern HINSTANCE g_hInst;              // Global instance handle
extern ULONG     g_uObjectCount;       // Instance count for this object 
extern ULONG     g_uServerLocks;       // Server lock count for this object

//---------------------------------------------------------------------------
// Clipformats requiered by MMC

extern CLIPFORMAT g_cfDisplayName;      // DisplayName for our SnapIn node
extern CLIPFORMAT g_cfNodeType;         // GUID of the selected node
extern CLIPFORMAT g_cfSnapinClsid;      // Class ID of this SnapIn
extern CLIPFORMAT g_cfszNodeType;       // String version of namespace GUID

extern CLIPFORMAT g_cfBaseNodePtr;      // Retrieves BaseNode pointer 
extern CLIPFORMAT g_cfDataObjPtr;       // Retrieves pointer to CDataObject

//---------------------------------------------------------------------------
//  Global function prototypes

void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );
void _fastcall Ansi2Unicode( CHAR* pszAnsi, WCHAR** ppszWide );
void _fastcall CopyBuffer( WCHAR* pszAnsiPtr, WCHAR** ppszWide );
void _fastcall CopyT2W( LPWSTR strDest, LPCTSTR strSource, size_t count);

void InitClipboardFormats();

HRESULT ExtractFromDataObject( LPDATAOBJECT ipDataObject,CLIPFORMAT cf,ULONG cb,HGLOBAL *phGlobal );

CBaseNode* ExtractBaseNodePtr( LPDATAOBJECT ipDataObject );
CDataObject* ExtractDataObjPtr( LPDATAOBJECT ipDataObject );

LPOLESTR GetHelpFilePath();

//---------------------------------------------------------------------------
//  Global Strings


static TCHAR*  gtszSNAPIN_NAME       = _T("Sample H (MMC 2.0) - MMC Help");
static TCHAR*  gtszABOUT_NAME        = _T("Sample H (MMC 2.0) - ISnapinAbout");


static WCHAR*  gwszROOT_NODE_NAME    = L"MMC Help Sample";
static WCHAR*  gwszABOUT_DESCRIPTION = L"MMC SDK MMC Help Sample";
static WCHAR*  gwszABOUT_PROVIDER    = L"Copyright � 1999 - 2001 Microsoft Corporation";
static WCHAR*  gwszABOUT_VERSION     = L"2.0";

// We need to do this to get around MMC.IDL - it explicitly defines
// the clipboard formats as WCHAR types...
#define T_CCF_DISPLAY_NAME    _T("CCF_DISPLAY_NAME")
#define T_CCF_NODETYPE        _T("CCF_NODETYPE")
#define T_CCF_SZNODETYPE      _T("CCF_SZNODETYPE")
#define T_CCF_SNAPIN_CLASSID  _T("CCF_SNAPIN_CLASSID")

#define T_CCF_BASENODE_PTR    _T("CCF_BASENODE_PTR")
#define T_CCF_DATAOBJ_PTR     _T("CCF_DATAOBJ_PTR")

//---------------------------------------------------------------------------
// Constants

#define NODETYPE_STATIC                100   // Node Types
#define NODETYPE_DEVICE                200 
#define NODETYPE_FOLDER                300   
#define NODETYPE_VFILE                 400    


#define ATTRIBUTE_DATA_ARCHIVE         2     // Node Attributes
#define ATTRIBUTE_DATA_HIDDEN          4
#define ATTRIBUTE_DATA_LOCKED          8
#define ATTRIBUTE_DATA_READONLY        16
#define ATTRIBUTE_BACKUP_DEVICE        2048  


#define IMG_DEVICE_DEFAULT             0     // Image Indexes 
#define IMG_DEVICE_OFFLINE             1
#define IMG_DATA_FILE                  2
#define IMG_DRIVE_DEFAULT              3
#define IMG_DRIVE_OFFLINE              4
#define IMG_FOLDER_DEFAULT             5
#define IMG_CDROM_DEFAULT              6
#define IMG_REMOVABLE_MEDIA            7

#define IDM_NEW_DEVICE                 100   
#define IDM_NEW_FOLDER                 200
#define IDM_TOGGLE_STATUS              300
#define IDM_NEW_VIRTFILE               400   

#define STATUS_ONLINE                  1
#define STATUS_OFFLINE                 0

// Define some custom window messages so that objects running in
// different threads can send us commands.
//
#define WM_DEL_DEVICENODES             (WM_USER + 100)
#define WM_ADD_DEVICENODE              (WM_USER + 101)
#define WM_DEVICENODE_CLOSED           (WM_USER + 102)
#define WM_ADD_VIRTUALFILE             (WM_USER + 103)
#define WM_VIRTUALFILE_CLOSED          (WM_USER + 104)


// Defines interfaces which can be requested from IComponentData
// or IComponet's ::GetInterface method
//
#define REQUEST_ICONSOLENAMESPACE2     1000
#define REQUEST_ICONSOLE               1001
#define REQUEST_ICONSOLEVERB           1002
#define REQUEST_IRESULTDATA            1003
#define REQUEST_IHEADERCTRL2           1004
#define REQUEST_IDISPLAYHELP           1005

/////////////////////////////////////////////////////////////////////////////
// Helper classes and macros

#define BYTE_SIZE(string)          ((_tcslen(string)+1) * sizeof(TCHAR))

#define BREAK_ON_ERROR( hResult )  if( S_OK != hResult ) continue

// Useful only for debugging.  Never use modal dialogs in release builds!!
#define MsgBox(wszMsg, wszTitle) ::MessageBox(NULL, wszMsg, wszTitle, MB_OK)


//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_RELEASE( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    pObj->Release(); 
    pObj = NULL; 
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to release NULL Com pointer.\n")); 
  }
} 

//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_FREE_BITMAP( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    BOOL bStatus = DeleteObject( pObj );
    pObj = NULL;
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to delete NULL Bitmap handle.\n")); 
  }
} 

//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_FREE_ICON( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    BOOL bStatus = DestroyIcon( pObj );
    pObj = NULL;
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to delete NULL Icon handle.\n")); 
  }
} 



//---------------------------------------------------------------------------
//  W2T converts a wide character string to unicode if _UNICODE is not
//  defined.  If it is defined then the sting is copied to another buffer.
//  
#ifndef _UNICODE
#define W2T( szAnsiPtr, szWide )   Unicode2Ansi( szAnsiPtr, szWide )
#else
#define W2T( szAnsiPtr, szWidePtr )                                 \
        *szAnsiPtr = (WCHAR*)CoTaskMemAlloc(BYTE_SIZE(szWidePtr) ); \
        CopyMemory( *szAnsiPtr, szWidePtr, BYTE_SIZE(szWidePtr) )

#endif //_UNICODE

//---------------------------------------------------------------------------
//  T2W

#ifndef _UNICODE
#define T2W( szAnsi, szWidePtr )   Ansi2Unicode( szAnsi, szWidePtr ) 
#else
#define T2W( szAnsi, szWidePtr )   CopyBuffer( szAnsi, szWidePtr )  
#endif //_UNICODE

#endif //_MMC_GLOBALS_H
