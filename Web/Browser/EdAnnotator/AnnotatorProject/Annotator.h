/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// Annotator.h : Declaration of the CAnnotator

#ifndef __ANNOTATOR_H_
#define __ANNOTATOR_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "mshtml.h"


/////////////////////////////////////////////////////////////////////////////
// CAnnotator
class ATL_NO_VTABLE CAnnotator :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IAnnotator, &IID_IAnnotator, &LIBID_EDANNOTATORLib>,
    public CComControl<CAnnotator>,
    public IPersistStreamInitImpl<CAnnotator>,
    public IOleControlImpl<CAnnotator>,
    public IOleObjectImpl<CAnnotator>,
    public IOleInPlaceActiveObjectImpl<CAnnotator>,
    public IViewObjectExImpl<CAnnotator>,
    public IOleInPlaceObjectWindowlessImpl<CAnnotator>,
    public CComCoClass<CAnnotator, &CLSID_Annotator>,
    /* The following untrusted use of IObjectSafetyImpl is for simplicity
    in this sample code.  This usage in production code can expose a
    security risk in some situations. */
    public IObjectSafetyImpl<CAnnotator,
                             INTERFACESAFE_FOR_UNTRUSTED_CALLER |
                             INTERFACESAFE_FOR_UNTRUSTED_DATA>,
    public IHTMLEditDesigner

{
public:
    CAnnotator()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_ANNOTATOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAnnotator)
    COM_INTERFACE_ENTRY(IAnnotator)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IViewObjectEx)
    COM_INTERFACE_ENTRY(IViewObject2)
    COM_INTERFACE_ENTRY(IViewObject)
    COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceObject)
    COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY(IOleControl)
    COM_INTERFACE_ENTRY(IOleObject)
    COM_INTERFACE_ENTRY(IPersistStreamInit)
    COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
    COM_INTERFACE_ENTRY(IObjectSafety)
    COM_INTERFACE_ENTRY(IHTMLEditDesigner)
END_COM_MAP()

BEGIN_PROP_MAP(CAnnotator)
    PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
    PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
    // Example entries
    // PROP_ENTRY("Property Description", dispid, clsid)
    // PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CAnnotator)
    CHAIN_MSG_MAP(CComControl<CAnnotator>)
    DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
    DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IHTMLEditDesigner
STDMETHOD(PostEditorEventNotify)(DISPID inEvtDispId, IHTMLEventObj *pIEventObj);
STDMETHOD(PostHandleEvent)(DISPID inEvtDispId, IHTMLEventObj *pIEventObj);
STDMETHOD(PreHandleEvent)(DISPID inEvtDispId, IHTMLEventObj *pIEventObj);
STDMETHOD(TranslateAccelerator)(DISPID inEvtDispId, IHTMLEventObj *pIEventObj);

// IAnnotator
public:
  STDMETHOD(AddComment)();
    STDMETHOD(ShowCommentGlyphs)(BOOL bShow);
    STDMETHOD(DetachAnnotator)();
    STDMETHOD(AttachAnnotator)(IHTMLDocument2* pDoc);

// Helper Methods
private:
    STDMETHOD(OpenCommentEditBox)(IHTMLElement* pSrcElem);
    STDMETHOD(CloseCommentEditBox)();

    HRESULT OnDraw(ATL_DRAWINFO& di)
    {
        RECT& rc = *(RECT*)di.prcBounds;
        Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

        SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
        LPCTSTR pszText = _T("ATL 3.0 : Annotator");
        TextOut(di.hdcDraw,
            (rc.left + rc.right) / 2,
            (rc.top + rc.bottom) / 2,
            pszText,
            lstrlen(pszText));

        return S_OK;
    }

private:
    CComPtr<IHTMLDocument2> m_spDoc;
    CComPtr<IHTMLEditDesigner> m_spDesigner;
    CComPtr<IHTMLElement> m_spSrcElem;
    CComPtr<IHTMLElement> m_spCommentEditBox;
    HCURSOR m_hOldCursor;
};

#endif //__ANNOTATOR_H_
