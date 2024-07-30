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

#include "Globals.h"
#include "BaseNode.h"

//---------------------------------------------------------------------------
// MMC's requiered clipboard formats

UINT g_cfDisplayName = 0;      // DisplayName for our SnapIn node
UINT g_cfNodeType    = 0;      // GUID of the selected node
UINT g_cfszNodeType  = 0;      // String representation of namespace GUID
UINT g_cfSnapinClsid = 0;      // Class ID of this SnapIn

//---------------------------------------------------------------------------
//  Custom clipboard formats

UINT g_cfBaseNodePtr = 0;
UINT g_cfDataObjPtr  = 0;
UINT g_cfNodePropPtr = 0;      // DRAGDROP: New format for node properties
UINT g_cfNodeTypeFlg = 0;      // DRAGDROP: New format for node type


// Global variables

HINSTANCE g_hInst = NULL;      // Our global instance handle
ULONG g_uObjectCount = 0;      // Global object count
ULONG g_uServerLocks = 0;      // Global lock count

CONSOLE_VERSION  g_CV;         // MMC20: Global Console Version struct is
                               //        defined in Globals.h

//---------------------------------------------------------------------------
//  Returns the version of the console we are attached to
//
HRESULT GetConsoleVersion( CONSOLE_VERSION* pVersion )
{
  _ASSERT( NULL != pVersion );
  HRESULT hResult = S_FALSE;

  pVersion->nMajor = 0;
  pVersion->nMinor = 0;

  IMMCVersionInfo* ipVersionInfo = NULL;
  hResult = CoCreateInstance( CLSID_MMCVersionInfo,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IMMCVersionInfo,
                              (void**)&ipVersionInfo
                            );
  // If the call to CoCreateInstance fails, the return value
  // will be "ClassFactory cannot supply requested class"
  if( S_OK != hResult )
    return S_FALSE;

  hResult = ipVersionInfo->GetMMCVersion( &pVersion->nMajor, &pVersion->nMinor );
  ipVersionInfo->Release();

  return hResult;
}

//---------------------------------------------------------------------------
//  This is the fast, simple way to convert unicode to ansi.  It does NOT
//  handle multibyte ansi strings and is not localized.  But it should be
//  fine for registry entries
//  NOTE:  The caller is responsible for freeing the memory.
//
void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide )
{
  LONG nLen = wcslen( szWide ) +1;
  *pszAnsi = (char*)CoTaskMemAlloc( nLen );   
  char* pCounter = *pszAnsi;

  while( *szWide )
  {
    *pCounter = LOBYTE(*szWide);
    pCounter++; 
    szWide++;   
  }
  *pCounter = NULL;
}

//---------------------------------------------------------------------------
//  copies a string ( like strncpy )
//  in non-unicode version coverts ansi-to-unicode first.
//
void _fastcall CopyT2W( LPWSTR strDest, LPCTSTR strSource, size_t count)
{
#ifndef _UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, strSource, -1, strDest, count );

#else

	wcsncpy( strDest, strSource, count ); 

#endif

	if ( count > 0 )
		strDest[ count - 1 ] = 0;
}

//---------------------------------------------------------------------------
//
void InitClipboardFormats()
{
  g_cfDisplayName  = RegisterClipboardFormat( T_CCF_DISPLAY_NAME );
  g_cfNodeType     = RegisterClipboardFormat( T_CCF_NODETYPE );
  g_cfszNodeType   = RegisterClipboardFormat( T_CCF_SZNODETYPE );
  g_cfSnapinClsid  = RegisterClipboardFormat( T_CCF_SNAPIN_CLASSID );

  g_cfBaseNodePtr  = RegisterClipboardFormat( T_CCF_BASENODE_PTR );
  g_cfDataObjPtr   = RegisterClipboardFormat( T_CCF_DATAOBJ_PTR );

  //DRAGDROP: Register our new clipboard formats
  g_cfNodePropPtr  = RegisterClipboardFormat( T_CCF_NODEPROP_PTR );
  g_cfNodeTypeFlg  = RegisterClipboardFormat( T_CCF_NODETYPE_FLG );

}

//---------------------------------------------------------------------------
//  Extracts data based on the passed-in clipboard format
//
HRESULT ExtractFromDataObject
(
  LPDATAOBJECT ipDataObject,   // [in]  Points to data object
  UINT         cfClipFormat,   // [in]  Clipboard format to use
  ULONG        nByteCount,     // [in]  Number of bytes to allocate
  HGLOBAL      *phGlobal       // [out] Points to the data we want 
)
{
  _ASSERT( NULL != ipDataObject );

            *phGlobal = NULL;
  HRESULT   hResult   = S_FALSE;
  STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL  };
  FORMATETC FormatEtc = { cfClipFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

  do 
	{
    // Allocate memory for the stream           
    StgMedium.hGlobal = ::GlobalAlloc( GMEM_SHARE, nByteCount );

		if( NULL == StgMedium.hGlobal )
    {
      hResult = E_OUTOFMEMORY;
      break;
    }

    // Attempt to get data from the object
    hResult = ipDataObject->GetDataHere( &FormatEtc, &StgMedium );
    if( FAILED(hResult) )
    {
      break;       
    }
    // StgMedium now has the data we need 
    *phGlobal = StgMedium.hGlobal;
    StgMedium.hGlobal = NULL;

  } while (0); 

  if( FAILED(hResult) && StgMedium.hGlobal )
  {
    HGLOBAL hRetVal = ::GlobalFree(StgMedium.hGlobal);   
    _ASSERT( NULL == hRetVal );         // Must return NULL
  }
  return hResult;
} 


//---------------------------------------------------------------------------
//  This helper returns the current BaseNode object on the custom
//  g_cfBaseNodePtr clipboard format
// 
CBaseNode* ExtractBaseNodePtr
(
  LPDATAOBJECT ipDataObject      // [in] IComponent pointer 
)
{
  LPBASENODE  pNode   = NULL;
  HGLOBAL     hGlobal = NULL;
  HRESULT     hResult = S_FALSE;

  hResult = ExtractFromDataObject( ipDataObject,
                                   g_cfBaseNodePtr,
                                   sizeof(LPBASENODE),
                                   &hGlobal
                                 );
  if( SUCCEEDED(hResult) )
  {
    pNode = *(LPBASENODE*)(hGlobal);
    HGLOBAL hRetVal = GlobalFree(hGlobal);   
    _ASSERT( NULL == hRetVal );        // Must return NULL
  }

  return pNode;

} 


//---------------------------------------------------------------------------
//  This helper returns the NodeType Flag.  It uses the g_cfNodeTypeFlg 
//  clipboard format.  This is needed to support interprocess Cut/Paste
//  because we can't pass a pointer to the object itself.
// 
ULONG ExtractNodeTypeFlg
(
  LPDATAOBJECT ipDataObject      //[in] IComponent pointer 
)
{
  _ASSERT( NULL != ipDataObject );

  ULONG    nTypeFlg = 0;
  ULONG*   pTypeFlg = &nTypeFlg;
  HGLOBAL  hRetVal  = NULL;
  BOOL     bStatus  = FALSE;
  HRESULT  hResult  = S_FALSE;

  STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL  };
  FORMATETC FormatEtc = { g_cfNodeTypeFlg, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
  
  hResult = ipDataObject->GetData( &FormatEtc, &StgMedium );
  if( S_OK == hResult )
  {
    pTypeFlg = (ULONG*)::GlobalLock( StgMedium.hGlobal );
    nTypeFlg = *pTypeFlg;
    bStatus  = ::GlobalUnlock( StgMedium.hGlobal );    
    hRetVal  = GlobalFree( StgMedium.hGlobal );   
    _ASSERT( NULL == hRetVal );        // Must return NULL
  }
                                       // Return 0 if the call to
  return nTypeFlg;                     // ::GetData() failed
} 


//---------------------------------------------------------------------------
//  Converts an IDataObject pointer to a CDataObject pointer by 
//  retrieving a "this" pointer using a custom clipboard format.
// 
CDataObject* ExtractDataObjPtr
(
  LPDATAOBJECT ipDataObject      //[in] IDataObject pointer 
)
{
  _ASSERT( 0 != g_cfDataObjPtr );

  HGLOBAL      hGlobal = NULL;
  HRESULT      hResult = S_OK;
  CDataObject* pDO     = NULL;

  hResult = ExtractFromDataObject( ipDataObject,
                                   g_cfDataObjPtr, 
                                   sizeof(CDataObject **),
                                   &hGlobal
                                 );

  if( SUCCEEDED(hResult) )
  {
    pDO = *(CDataObject **)(hGlobal);
    _ASSERT( NULL != pDO );    

    HGLOBAL hRetVal = GlobalFree(hGlobal);   
    _ASSERT( NULL == hRetVal );       // Must return NULL
  }

  return pDO;

} 
