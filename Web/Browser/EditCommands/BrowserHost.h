/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// BrowserHost.h : Declaration of the CBrowserHost

#ifndef __BROWSERHOST_H_
#define __BROWSERHOST_H_

#include "resource.h"       // main symbols
#include <commctrl.h>
#include <atlwin.h>
#include <exdisp.h>
#include <mshtml.h>

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
	CBrowserHost() :
		m_bInPlaceActive(FALSE),
		m_lLeftBandWidth(180),
		m_lTopBandHeight(35),
		m_dwCookie(NULL),
		m_dwCookie2(NULL),
		m_bIsChecked(FALSE), // for check box state
		m_wndTopBand(_T("Static"), this, 0),
		m_wndLeftBand(_T("Static"), this, 0),
		m_wndButton1(_T("Button"), this, 0),
		m_wndButton2(_T("Button"), this, 0),
		m_wndButton3(_T("Button"), this, 0),
		m_wndButton4(_T("Button"), this, 0),
		m_wndButton5(_T("Button"), this, 0),
		m_wndButton6(_T("Button"), this, 0),
		m_wndButton7(_T("Button"), this, 0),
		m_wndCheckBox(_T("Button"), this, 0),
		m_wndAddressBox(_T("ComboBox"), this, 1),
		m_wndBox1(_T("ComboBox"), this, 2),
		m_wndBox2(_T("ComboBox"), this, 3),
		m_wndBox3(_T("ComboBox"), this, 4),
		m_wndBox4(_T("ComboBox"), this, 5)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BROWSERHOST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBrowserHost)
	COM_INTERFACE_ENTRY(IBrowserHost)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
END_COM_MAP()

BEGIN_MSG_MAP(CBrowserHost)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_KEYDOWN,   OnKeydown)

	// Button message handlers
	COMMAND_ID_HANDLER(ID_BUTTON1, OnButton1)
	COMMAND_ID_HANDLER(ID_BUTTON2, OnButton2)
	COMMAND_ID_HANDLER(ID_BUTTON3, OnButton3)
	COMMAND_ID_HANDLER(ID_BUTTON4, OnButton4)
	COMMAND_ID_HANDLER(ID_BUTTON5, OnButton5)
	COMMAND_ID_HANDLER(ID_BUTTON6, OnButton6)
	COMMAND_ID_HANDLER(ID_BUTTON7, OnButton7)
	COMMAND_ID_HANDLER(ID_CHECKBOX, OnCheckBox)

	// Combobox message handlers
	ALT_MSG_MAP(1) // For subclassed window - m_wndAddressBox
	MESSAGE_HANDLER(WM_KEYDOWN, OnAddressBox)

	ALT_MSG_MAP(2) // For subclassed window - m_wndBox1
	MESSAGE_HANDLER(WM_KEYDOWN, OnBox1)

	ALT_MSG_MAP(3) // For subclassed window - m_wndBox2
	MESSAGE_HANDLER(WM_KEYDOWN, OnBox2)

	ALT_MSG_MAP(4) // For subclassed window - m_wndBox3
	MESSAGE_HANDLER(WM_KEYDOWN, OnBox3)
	
	ALT_MSG_MAP(5) // For subclassed window - m_wndBox4
	MESSAGE_HANDLER(WM_KEYDOWN, OnBox4)

END_MSG_MAP()

private:
	BOOL				m_bInPlaceActive;
	LONG				m_lTopBandHeight;
	LONG				m_lLeftBandWidth;
	DWORD				m_dwCookie; // for connection point to WebBrowserEvents2
	DWORD				m_dwCookie2; // for connection point to HTMLDocumentEvents2
	BOOL				m_bIsChecked; // for check box state
	CWindow				m_wndStatusBar;
	CContainedWindow	m_wndTopBand;
	CContainedWindow	m_wndLeftBand;
	CContainedWindow	m_wndButton1;
	CContainedWindow	m_wndButton2;
	CContainedWindow	m_wndButton3;
	CContainedWindow	m_wndButton4;
	CContainedWindow	m_wndButton5;
	CContainedWindow	m_wndButton6;
	CContainedWindow	m_wndButton7;
	CContainedWindow	m_wndAddressBox;
	CContainedWindow	m_wndCheckBox;
	CContainedWindow	m_wndBox1;
	CContainedWindow	m_wndBox2;
	CContainedWindow	m_wndBox3;
	CContainedWindow	m_wndBox4;
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
	CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> m_spDoc;
	CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject> m_spInPlaceObject;
	CComQIPtr<IOleCommandTarget, &IID_IOleCommandTarget> m_spOleCmdTarg;

	// Message handlers
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeydown(UINT, WPARAM wParam, LPARAM lParam, BOOL&);

	LRESULT OnButton1(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton2(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton3(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton4(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton5(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton6(WORD, WORD, HWND, BOOL&);
	LRESULT OnButton7(WORD, WORD, HWND, BOOL&);
	LRESULT OnCheckBox(WORD, WORD, HWND, BOOL&);
	LRESULT OnAddressBox(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnBox1(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnBox2(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnBox3(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnBox4(UINT, WPARAM, LPARAM, BOOL&);

// IBrowserHost
public:
	STDMETHOD(Run)();
	STDMETHOD(Stop)();

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

// IOleClientSite Methods
private:
	STDMETHOD(SaveObject)(void) {return E_NOTIMPL;}
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {return E_NOTIMPL;}
	STDMETHOD(GetContainer)(IOleContainer **ppContainer) {return E_NOTIMPL;}
	STDMETHOD(ShowObject)(void) {return E_NOTIMPL;}
	STDMETHOD(OnShowWindow)(BOOL fShow) {return E_NOTIMPL;}
	STDMETHOD(RequestNewObjectLayout)(void) {return E_NOTIMPL;}

// IOleWindow Methods
private:
	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		 *phwnd = m_hWnd;
		return S_OK;
	}

   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode) {return E_NOTIMPL;}


// IOleInPlaceSite Methods
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

};

#endif //__BROWSERHOST_H_
