/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// BrowserHost.h : Declaration of the CBrowserHost

#ifndef __BROWSERHOST_H_
#define __BROWSERHOST_H_

#include "resource.h"		 // main symbols
#include <commctrl.h>
#include <atlwin.h>
#include <exdisp.h>
#include <mshtml.h>
//#include <mshtmhst.h>
//#include <mshtmdid.h>
//#include <mshtmcid.h>

/////////////////////////////////////////////////////////////////////////////
// CBrowserHost
class ATL_NO_VTABLE CBrowserHost : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBrowserHost, &CLSID_BrowserHost>,
	public IDispatchImpl<IBrowserHost, &IID_IBrowserHost, &LIBID_EDCOMMANDSLib>,
	public CWindowImpl<CBrowserHost>,
	public IOleClientSite,
	public IOleInPlaceSite
{
public:
	CBrowserHost();

DECLARE_REGISTRY_RESOURCEID(IDR_BROWSERHOST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBrowserHost)
	COM_INTERFACE_ENTRY(IBrowserHost)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
	COM_INTERFACE_ENTRY2(DWebBrowserEvents2, IDispatch)
END_COM_MAP()

BEGIN_MSG_MAP(CAtlBrCon)
	MESSAGE_HANDLER(WM_CREATE,	  OnCreate)
	MESSAGE_HANDLER(WM_NCDESTROY, OnNCDestroy)
	MESSAGE_HANDLER(WM_SIZE,      OnSize)
	MESSAGE_HANDLER(WM_KEYDOWN,   OnKeydown)

	// Button Commands
	COMMAND_ID_HANDLER(ID_BUTTON1, OnButton1)
	COMMAND_ID_HANDLER(ID_BUTTON2, OnButton2)
	COMMAND_ID_HANDLER(ID_BUTTON3, OnButton3)
	COMMAND_ID_HANDLER(ID_BUTTON4, OnButton4)
	COMMAND_ID_HANDLER(ID_BUTTON5, OnButton5)
	COMMAND_ID_HANDLER(ID_BUTTON6, OnButton6)
	COMMAND_ID_HANDLER(ID_BUTTON7, OnButton7)
	COMMAND_ID_HANDLER(ID_BUTTON8, OnButton8)
	COMMAND_ID_HANDLER(ID_BUTTON9, OnButton9)
	COMMAND_ID_HANDLER(ID_BUTTON10, OnButton10)

	ALT_MSG_MAP(1) // For subclassed window - m_wndUrlCombo
END_MSG_MAP()

// IBrowserHost
public:
	STDMETHOD(GetHwnd)(long* phwnd);
	STDMETHOD(Run)();

protected:
	BOOL  m_bEnableCtxMenus;
	DWORD m_dwDLControl;
	DWORD m_dwCookie;
	DWORD m_dwDocHostUIFlags;
	DWORD m_dwDocHostUIDblClk;
	BOOL  m_bInPlaceActive;
	BOOL  m_bAtlBrowserHelp;
	BOOL  m_bButton2Down;
	BOOL  m_bButton3Down;
	BOOL  m_bButton4Down;
	BOOL  m_bButton5Down;
	BOOL  m_bButton6Down;
	BOOL  m_bButton7Down;
	BOOL  m_bButton8Down;
	BOOL  m_bButton9Down;
	BOOL  m_bButton10Down;
	LONG  m_lCSSlevel;
	CContainedWindow m_wndUrlCombo;
	CWindow m_wndStatusBar;
	CWindow m_wndToolBar;


	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
	CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> m_spDoc;
	CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject> m_spInPlaceObject;
	CComQIPtr<IOleCommandTarget, &IID_IOleCommandTarget> m_spOleCmdTarg;

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnNCDestroy(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnKeydown(UINT, WPARAM wParam, LPARAM lParam, BOOL&);

	LRESULT OnButton1(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton2(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton3(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton4(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton5(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton6(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton7(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton8(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton9(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton10(WORD, WORD, HWND, BOOL&);

	STDMETHOD(Stop)();

private:
	void CreateToolbar();
public:

// IDispatch Methods
private:
	STDMETHOD(Invoke)(DISPID dispidMember,
					  REFIID riid,
					  LCID lcid,
					  WORD wFlags,
					  DISPPARAMS* pdispparams,
					  VARIANT * pvarResult,
					  EXCEPINFO* pexcepinfo,
					  UINT* puArgErr);

// IOleWindow
private:
	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		 *phwnd = m_hWnd;
		return S_OK;
	}

   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode) {return E_NOTIMPL;}

// IOleInPlaceSite
private:
	STDMETHOD(CanInPlaceActivate)() {return S_OK;}

	STDMETHOD(OnInPlaceActivate)()
	{
		  m_bInPlaceActive = TRUE;
		  return S_OK;
	}

	STDMETHOD(GetWindowContext)(IOleInPlaceFrame** ppFrame,
								IOleInPlaceUIWindow** ppDoc,
								LPRECT lprcPosRect,
								LPRECT lprcClipRect,
								LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		GetClientRect(lprcPosRect);
		GetClientRect(lprcClipRect);
		return S_OK;
	}

	STDMETHOD(OnInPlaceDeactivate)()
	{
		m_bInPlaceActive = FALSE;
		return S_OK;
	}

	STDMETHOD(OnUIActivate)() {return E_NOTIMPL;}
	STDMETHOD(Scroll)(SIZE scrollExtant) {return E_NOTIMPL;}
	STDMETHOD(OnUIDeactivate)(BOOL fUndoable) {return E_NOTIMPL;}
	STDMETHOD(DiscardUndoState)() {return E_NOTIMPL;}
	STDMETHOD(DeactivateAndUndo)( void) {return E_NOTIMPL;}
	STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect) {return E_NOTIMPL;}

// IOleClientSite Methods
private:
	STDMETHOD(SaveObject)(void) {return E_NOTIMPL;}
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {return E_NOTIMPL;}
	STDMETHOD(GetContainer)(IOleContainer **ppContainer) {return E_NOTIMPL;}
	STDMETHOD(ShowObject)(void) {return E_NOTIMPL;}
	STDMETHOD(OnShowWindow)(BOOL fShow) {return E_NOTIMPL;}
	STDMETHOD(RequestNewObjectLayout)(void) {return E_NOTIMPL;}
};

#endif //__BROWSERHOST_H_