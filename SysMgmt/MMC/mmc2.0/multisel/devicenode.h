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
//  Abstract:     Defines the CDeviceNode class.  This node is a child of
//                CStaticNode.  It represents a Virtual Storage device
//                
//


#ifndef _CLASS_CDEVICENODE_
#define _CLASS_CDEVICENODE_

#include "Globals.h"
#include "FolderNode.h"      // Folders are children of this node
#include "LListImpl.h"


class CComponentData;        // References

//---------------------------------------------------------------------------
class CDeviceNode : public CBaseNode  
{
  public:
    CDeviceNode();
    virtual ~CDeviceNode();
    
    HRESULT Initialize( NODE_PROPERTIES* pNodeProps );
    VOID    ToggleStatus();

  // Virtual methods
  public:
    ULONG   GetNodeType() { return NODETYPE_DEVICE; } 
    GUID&   GetNodeGUID() { return m_thisGUID; }

    HRESULT GetResultViewType2( MMC_COOKIE nCookie, PRESULT_VIEW_TYPE_INFO pRVTinfo );
    HRESULT GetDisplayInfo( SCOPEDATAITEM* pSDI );
    HRESULT GetDisplayInfo( RESULTDATAITEM* pRDI );

  ///////////////////////////////////////////////////////////////////////////
  // Notification handlers   
  //
  public:
    HRESULT OnSelect( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnShow( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );
    HRESULT OnExpand( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnRemoveChildren( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pCompData );            
    HRESULT OnRename( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent );

    HRESULT OnViewChange( LPDATAOBJECT ipDataObject, LPARAM nArg, LPARAM nParam, LONG_PTR pComponent )
            { return E_NOTIMPL; }

  ///////////////////////////////////////////////////////////////////////////
  //  Context Menu methods
  //
  public:
    HRESULT AddMenuItems( LPCONTEXTMENUCALLBACK ipCallback, long __RPC_FAR* pInsertionAllowed );
    HRESULT Command( long lCommandID );

  /////////////////////////////////////////////////////////////////////////
  //  IExtendControlbar
  //
  public:
    HRESULT ControlbarNotify( LPARAM nArg, LPARAM lParam, LONG_PTR pComp );

  ///////////////////////////////////////////////////////////////////////////
  // Private helpers
  //
  private:
    HRESULT  DeleteChildItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  InsertChildItems( LPCONSOLENAMESPACE2 ipCNS );
    HRESULT  RefreshNodeList();
    VOID     RemoveNodes();
 
  private:
    static GUID  m_thisGUID;
    DWORD        m_dwAttributes;
    HSCOPEITEM   m_hParentNode;  
    LPWSTR       m_wzStatus;
    BOOL         m_bOnlineStatus;
    HWND         m_hMessageWnd;        // Our message handler 


    CLListImpl<CBaseNode*,CBaseNode*>  m_NodeList;
    CComponentData*                    m_pCompData;

  public:
    HWND         m_hAddFolderDlg;      // Instance of AddDeviceDlg


    HRESULT  AddFolderNode( NODE_PROPERTIES* pProperties );

    static LRESULT CALLBACK DeviceNodeWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

};

#endif //_CLASS_CDEVICENODE_
