/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// Snap.h : Declaration of the CSnap

#ifndef __SNAP_H_
#define __SNAP_H_

#include "resource.h"       // main symbols
#include "mshtml.h"

/////////////////////////////////////////////////////////////////////////////
// CSnap
class ATL_NO_VTABLE CSnap : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSnap, &CLSID_Snap>,
	public IDispatchImpl<ISnap, &IID_ISnap, &LIBID_EDHOSTLib>,
	public IHTMLEditHost
{
public:
	CSnap() : m_lSnapIncrement(40), m_bSnapOn(FALSE)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SNAP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSnap)
	COM_INTERFACE_ENTRY(ISnap)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IHTMLEditHost)
END_COM_MAP()

long m_lSnapIncrement;
BOOL m_bSnapOn;

// ISnap

public:
	STDMETHOD(get_SnapOn)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_SnapOn)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_SnapIncrement)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SnapIncrement)(/*[in]*/ long newVal);
	STDMETHOD(SnapRect)(IHTMLElement *pIElement, 
						RECT *prcNew, 
						ELEMENT_CORNER eHandle);
};

#endif //__SNAP_H_
