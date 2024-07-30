/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// BrowserHost.cpp : Implementation of CBrowserHost
#include "stdafx.h"
#include "EdCommands.h"
#include "BrowserHost.h"
#include "exdispid.h"
#include "mshtmdid.h"
#include "mshtmhst.h"
#include "mshtmcid.h"

/////////////////////////////////////////////////////////////////////////////
// CBrowserHost

CBrowserHost::CBrowserHost() :
	m_bEnableCtxMenus(TRUE),
	m_dwDLControl(DLCTL_DLIMAGES|DLCTL_VIDEOS|DLCTL_BGSOUNDS),
	m_dwCookie((DWORD)0),
	m_dwDocHostUIFlags((DWORD)0),
	m_dwDocHostUIDblClk((DWORD)0),
	m_bInPlaceActive(FALSE),
	m_bAtlBrowserHelp(TRUE),
	m_wndUrlCombo(_T("ComboBox"), this, 1),
	m_bButton2Down(FALSE),
	m_bButton3Down(FALSE),
	m_bButton4Down(FALSE),
	m_bButton5Down(FALSE),
	m_bButton6Down(FALSE),
	m_bButton7Down(TRUE),
	m_bButton8Down(FALSE),
	m_bButton9Down(FALSE),
	m_bButton10Down(FALSE),
	m_lCSSlevel(0)
{
}

LRESULT CBrowserHost::OnCreate(UINT, WPARAM, LPARAM, BOOL&) {return 0;}

LRESULT CBrowserHost::OnNCDestroy(UINT, WPARAM, LPARAM, BOOL&)
{
	Stop();
	return 0;
}

LRESULT CBrowserHost::OnKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_RETURN)
	{
		// Stop any previous navigations
		m_spWebBrowser->Stop();

		USES_CONVERSION;
		CComBSTR bstrURL;
		CComVariant vtEmpty;

    // CODE REVIEW: Add following security comment.
    /* The following use of GetWindowText is simplified for illustrative
    purposes. This simplified use in production code can expose a
    security risk in some situations. In production code you might want
    to ensure that the receiving buffer size isn't exceeded by the size
    of the source string. */
		m_wndUrlCombo.GetWindowText((BSTR&)bstrURL);

		if (bstrURL)
			m_spWebBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);

		bHandled = TRUE;
		return S_OK;
	}

	MSG msg;
	msg.message = uMsg;
	msg.wParam = wParam;
	msg.lParam = lParam;


	// UIActivate the WebBrowser control when the tab key
	// is pressed so that focus will be changed to the next
	// control in the tabbing order.  If this is not done,
	// the WebBrowser control never gets the focus.
	if ((uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) && wParam == VK_TAB)
	{
		CComQIPtr<IOleObject, &IID_IOleObject> spOleObject(m_spWebBrowser);

		RECT rect;
		GetClientRect(&rect);
		spOleObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, this, 0, m_hWnd, &rect);
	}

	// Call TranslateAccelerator on the in-place active
	// object for the delete key so that the accelerator will be passed to the
	// hosted WebBrowser control.  This forces the delete key to
	// work correctly in design mode.
	if (wParam == VK_DELETE)
	{
		CComQIPtr<IOleInPlaceActiveObject,
				 &IID_IOleInPlaceActiveObject> spInPlaceActiveObject(m_spWebBrowser);
	
		spInPlaceActiveObject->TranslateAccelerator(&msg);
	}

	bHandled = TRUE;

	return S_FALSE;
}

LRESULT CBrowserHost::OnButton1(WORD, WORD, HWND, BOOL&)
{
	_ASSERT(m_spWebBrowser);

	if (!m_spDoc)
	{
		 MessageBox(_T("Document object no available."));
		 return 0;
	}

	USES_CONVERSION; // Needed for the OLE2A conversion macro
	BSTR bstrMode;

	m_spDoc->get_designMode(&bstrMode);
	char* cMode = OLE2A(bstrMode);

	if (strcmp(cMode, "On"))
	{
		m_spDoc->put_designMode(L"On");

		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON1, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON7, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON3, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(TRUE, 0));

		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON7, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON8, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON9, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON10, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON6, MAKELONG(FALSE, 0));
		m_bButton6Down = FALSE;
	}
	else
	{
		m_spDoc->put_designMode(L"Off");
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON1, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON6, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON7, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON8, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON9, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON10, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));

		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON7, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON8, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON9, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON10, MAKELONG(FALSE, 0));
		m_bButton2Down = FALSE;
		m_bButton3Down = FALSE;
		m_bButton4Down = FALSE;
		m_bButton5Down = FALSE;
		m_bButton6Down = FALSE;
		m_bButton7Down = TRUE;
		m_bButton8Down = FALSE;
		m_bButton9Down = FALSE;
		m_bButton10Down = FALSE;
	}

	return 1;
}

LRESULT CBrowserHost::OnButton2(WORD, WORD, HWND, BOOL&)
{
	USES_CONVERSION;

	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton2Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(TRUE, 0));

	m_bButton2Down = !m_bButton2Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = VARIANT_TRUE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_MULTIPLESELECTION,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);
	
	return 0;
}

LRESULT CBrowserHost::OnButton3(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton3Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(TRUE, 0));

	m_bButton3Down = !m_bButton3Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton3Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_2D_POSITION,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton4(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton4Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(TRUE, 0));

	m_bButton4Down = !m_bButton4Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton4Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_LIVERESIZE,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton5(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton5Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(TRUE, 0));

	m_bButton5Down = !m_bButton5Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton5Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_DISABLE_EDITFOCUS_UI,
							  // Note: IDM_DISABLE_EDITFOCUS_UI will change
							  // after Beta 3 to IDM_DISABLE_EDITFOCUSHANDLES
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton6(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton6Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON6, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON6, MAKELONG(TRUE, 0));

	m_bButton6Down = !m_bButton6Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton6Down ? VARIANT_TRUE : VARIANT_FALSE;

	//m_spDoc->put_designMode(L"Off");

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_ATOMICSELECTION,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);
	//m_spDoc->put_designMode(L"On");

	return 0;
}

LRESULT CBrowserHost::OnButton7(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton7Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON7, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON7, MAKELONG(TRUE, 0));

	m_bButton7Down = !m_bButton7Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton7Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_AUTOURLDETECT_MODE,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton8(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton8Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON8, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON8, MAKELONG(TRUE, 0));

	m_bButton8Down = !m_bButton8Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton8Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_RESPECTVISIBILITY_INDESIGN,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton9(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	// Turn button on or off
	if (m_bButton9Down)
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON9, MAKELONG(FALSE, 0));
	else
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON9, MAKELONG(TRUE, 0));

	m_bButton9Down = !m_bButton9Down;

	V_VT(&var) = VT_BOOL;
	V_BOOL(&var) = m_bButton9Down ? VARIANT_TRUE : VARIANT_FALSE;

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_OVERRIDE_CURSOR,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton10(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr ;
    VARIANT var;

	V_VT(&var) = VT_I4;

	TCHAR textLevel = NULL;

	_itot(m_lCSSlevel, &textLevel, 10);

	V_I4(&var) = m_lCSSlevel++;

	if (m_lCSSlevel > 2) m_lCSSlevel = 0;

	MessageBox(&textLevel, _T("CSS Level"), NULL);

	hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
							  IDM_CSSEDITING_LEVEL,
							  MSOCMDEXECOPT_DODEFAULT,
							  &var,
							  NULL);



	return 0;
}

STDMETHODIMP CBrowserHost::Run()
{
	// Create and show the window
	RECT rcClient = { CW_USEDEFAULT, 0, 0, 0 };

	Create(GetDesktopWindow(), rcClient, _T("Editing Glyph Sample App"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
			 0, NULL);
	ShowWindow(SW_SHOWNORMAL);

	// Create the toolbar
	CreateToolbar();
	
	// Create the status bar
	m_wndStatusBar.Attach(CreateStatusWindow(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_BOTTOM,
														  _T("Ready"), m_hWnd, 2));
	_ASSERT(m_wndStatusBar);
	
	// Create the WebBrowser control
	CComPtr<IOleObject> spOleObject;
	HRESULT hr = CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC, IID_IOleObject,
											(void**)&spOleObject);
	if (hr != S_OK)
	{
		MessageBox(_T("CoCreateInstance failed"));
		return E_FAIL;
	}

	if (spOleObject->SetClientSite(this) != S_OK)
	{
		MessageBox(_T("SetClientSite failed"));
		return E_FAIL;
	}

	// In-place activate the WebBrower control
	MSG msg;
	GetClientRect(&rcClient);

	hr = spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, &msg, this, 0, m_hWnd, &rcClient);
	if (hr != S_OK)
	{
		MessageBox(_T("DoVerb failed"));
		return E_FAIL;
	}

	// Get the pointer to the WebBrowser control.  Note that setting a CComQIPtr
	// equal to a pointer of another type causes CComQIPtr to call QueryInterface.
	m_spWebBrowser = spOleObject;
	_ASSERT(m_spWebBrowser);

	if (!m_spWebBrowser)
		return E_FAIL;

	// Set up the connection to the WebBrowser control to receive events
	hr = AtlAdvise(m_spWebBrowser, GetUnknown(), DIID_DWebBrowserEvents2, &m_dwCookie);
	if (FAILED(hr))
		ATLTRACE(_T("Failed to Advise\n"));

	// Get the size of the status bar
	RECT rcWindow;
	m_wndStatusBar.GetWindowRect(&rcWindow);

	// Resize the control to accomodate the status bar and toolbar
	rcClient.bottom -= (rcWindow.bottom - rcWindow.top);

	m_wndToolBar.GetWindowRect(&rcWindow);
	rcClient.top += (rcWindow.bottom - rcWindow.top);

	// QI for the in-place object to set the size
	m_spInPlaceObject = m_spWebBrowser;
	_ASSERT(m_spInPlaceObject);

	if (m_spInPlaceObject)
		m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);

	// QI for the IOleCommandTarget interface that will be used later
	m_spOleCmdTarg = m_spWebBrowser;
	_ASSERT(m_spOleCmdTarg);

	// Load Test Page
	m_spWebBrowser->Navigate(L"res://edcommands.exe/test", NULL, NULL, NULL, NULL);

	return S_OK;
}

STDMETHODIMP CBrowserHost::Stop()
{
	_ASSERT(m_spWebBrowser);

	HRESULT hr = AtlUnadvise(m_spWebBrowser, DIID_DWebBrowserEvents2, m_dwCookie);

	if (FAILED(hr))
		ATLTRACE("Failed to Unadvise\n");

	PostQuitMessage(0);

	return S_OK;
}

LRESULT CBrowserHost::OnSize(UINT, WPARAM, LPARAM lParam, BOOL&)
{
	RECT rcWindow;

	// Resize the status bar
	if (m_wndStatusBar)
	{
		int cxParent = LOWORD(lParam);
		int cyParent = HIWORD(lParam);
		int x = 0, y, cx, cy;

		// Keep the status bar height the same.
		m_wndStatusBar.GetWindowRect(&rcWindow);
		cy = rcWindow.bottom - rcWindow.top;

		y = cyParent - cy;
		cx = cxParent;
		m_wndStatusBar.MoveWindow(x, y, cx, cy, TRUE);
	}

	// Tell the toolbar to resize itself
	if (m_wndToolBar)
		m_wndToolBar.SendMessage(TB_AUTOSIZE, 0, 0L);

	// Resize the control
	if (m_spWebBrowser && m_bInPlaceActive)
	{
		RECT rcClient;
		GetClientRect(&rcClient);

		// Resize the control to accomodate the status bar and toolbar
		rcClient.bottom -= (rcWindow.bottom - rcWindow.top);

		m_wndToolBar.GetWindowRect(&rcWindow);
		rcClient.top += (rcWindow.bottom - rcWindow.top);

		if (m_spInPlaceObject)
			m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);
	}

	return 0;
}

// IDispatch Methods
STDMETHODIMP CBrowserHost::Invoke(DISPID dispidMember, REFIID riid,
										 LCID lcid, WORD wFlags,
										 DISPPARAMS* pDispParams,
										 VARIANT* pvarResult, EXCEPINFO*  pExcepInfo,
										 UINT* puArgErr)
{
	USES_CONVERSION;

	switch (dispidMember)
	{
		case DISPID_DOCUMENTCOMPLETE:
			{
			IDispatch* pDisp;
			m_spDoc = (IHTMLDocument2*)NULL;
			m_spWebBrowser->get_Document(&pDisp);
			pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&m_spDoc);

			pDisp->Release();
			break;
			}

		case DISPID_DOWNLOADCOMPLETE:
			// Set the text of the combobox to the current URL
			BSTR bstrURL;

			m_spWebBrowser->get_LocationURL(&bstrURL);
			m_wndUrlCombo.SetWindowText(OLE2T(bstrURL));

			break;

		// The parameters for this DISPID:
		// [0]: New status bar text - VT_BSTR
		case DISPID_STATUSTEXTCHANGE:
			m_wndStatusBar.SetWindowText(OLE2T(pDispParams->rgvarg[0].bstrVal));
			break;

		default:
			return DISP_E_MEMBERNOTFOUND;
	}

	return S_OK;
}

void CBrowserHost::CreateToolbar()
{
	TBBUTTON tbb[] =
	{
		// Add separators to make room for the combo box.
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,

		0, ID_BUTTON1, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		1, ID_BUTTON2, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		2, ID_BUTTON3, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		3, ID_BUTTON4, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		4, ID_BUTTON5, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		5, ID_BUTTON6, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		6, ID_BUTTON7, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		7, ID_BUTTON8, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		8, ID_BUTTON9, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		9, ID_BUTTON10, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
	};

	HWND toolbar = CreateToolbarEx(m_hWnd,
								   WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_WRAPABLE | TBSTYLE_TOOLTIPS,
								   ID_TOOLBARWND,
								   4,
								   _Module.GetResourceInstance(),
								   IDR_TOOLBAR1,
								   tbb, 51,
								   0, 0,
								   55, 30,
								   sizeof(TBBUTTON));

	m_wndToolBar.Attach(toolbar);
	_ASSERT(m_wndToolBar);

	// Tell the toolbar to resize itself
	m_wndToolBar.SendMessage(TB_AUTOSIZE, 0, 0L);
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));

	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON7, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON8, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON9, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON10, MAKELONG(FALSE, 0));

	// Create the combo box on the toolbar
	RECT rc, rc2;

	// Calculate the coordinates for the combo box.
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)0, (LPARAM)(LPRECT)&rc);
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)38, (LPARAM)(LPRECT)&rc2);

	rc.right = rc2.right;
	rc.bottom = 100;
	m_wndUrlCombo.Create(m_wndToolBar, rc, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|CBS_AUTOHSCROLL,
								0, ID_URLBOX);
}


STDMETHODIMP CBrowserHost::GetHwnd(long* phwnd)
{
	*phwnd = (long)m_hWnd;
	 return S_OK;
}
