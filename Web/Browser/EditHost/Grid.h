/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// Grid.h : Declaration of the CGrid

#ifndef __GRID_H_
#define __GRID_H_

#include "resource.h"       // main symbols
#include "mshtml.h"
//#include "objsafe.h"
#include "atlctl.h"	// For IObjectSafety

/////////////////////////////////////////////////////////////////////////////
// CGrid
class ATL_NO_VTABLE CGrid :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGrid, &CLSID_Grid>,
	public IGrid,
	public IElementBehavior,
	public IElementBehaviorFactory,
  // CODE REVIEW: Add following security comment.
  /* The following untrusted use of IObjectSafetyImpl is for simplicity
  in this sample code.  This usage in production code can expose a
  security risk in some situations. */
	public IObjectSafetyImpl<CGrid, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IHTMLPainter
{
public:
	CGrid() : m_lGridSize(50)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GRID)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGrid)
	COM_INTERFACE_ENTRY(IGrid)
	COM_INTERFACE_ENTRY(IElementBehavior)
	COM_INTERFACE_ENTRY(IElementBehaviorFactory)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IHTMLPainter)
END_COM_MAP()

// IGrid
	CComPtr<IElementBehaviorSite>	m_spSite;
	CComPtr<IHTMLPaintSite>			m_spPaintSite;
	long							m_lGridSize;
	long							m_lClientTop;
	long							m_lClientLeft;

public:
	STDMETHOD(get_GridSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_GridSize)(/*[in]*/ long newVal);

public:
// IElementBehavior
	STDMETHOD(Init)(IElementBehaviorSite * pBehaviorSite);
	STDMETHOD(Notify)(LONG lEvent, VARIANT * pVar);
	STDMETHOD(Detach)();

// IFactory
	STDMETHOD(FindBehavior)(BSTR bstrBehavior, BSTR bstrBehaviorUrl, IElementBehaviorSite* pSite, IElementBehavior** ppBehavior);

// IObjectSafety override
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

// IHTMLPainter
	STDMETHOD(Draw)(RECT rcBounds, RECT rcUpdate, LONG lDrawFlags, HDC hdc, LPVOID pvDrawObject);
	STDMETHOD(OnResize)(SIZE size);
	STDMETHOD(GetPainterInfo)(HTML_PAINTER_INFO * pInfo);
	STDMETHOD(HitTestPoint)(POINT pt, BOOL* pbHit, LONG * plPartID);

// Debug
	void Trace(WCHAR* message)
	{
		MessageBoxW(NULL, message, L"Trace", NULL);
	}
};

#endif //__GRID_H_
