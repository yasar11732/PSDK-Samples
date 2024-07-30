/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// BrowserHost.cpp : Implementation of CBrowserHost
#include "stdafx.h"
#include "EdHost.h"
#include "BrowserHost.h"
#include "exdispid.h"
#include "mshtmdid.h"
#include "mshtmhst.h"
#include "mshtmcid.h"
#include "Snap.h"

/////////////////////////////////////////////////////////////////////////////
// BrowserHost

CBrowserHost::CBrowserHost() :
	m_bEnableCtxMenus(TRUE),
	m_dwDLControl(DLCTL_DLIMAGES|DLCTL_VIDEOS|DLCTL_BGSOUNDS),
	m_dwCookie((DWORD)0),
	m_dwDocHostUIFlags((DWORD)0),
	m_dwDocHostUIDblClk((DWORD)0),
	m_bInPlaceActive(FALSE),
	m_bAtlBrowserHelp(TRUE),
	m_wndUrlCombo(_T("ComboBox"), this, 1),
	m_wndIncrementCombo(_T("ComboBox"), this, 1),
	m_bButton2Down(FALSE),
	m_bButton3Down(FALSE),
	m_bButton4Down(FALSE),
	m_bButton5Down(FALSE),
	m_lGridCookie(NULL),
	m_lSnapIncrement(50)
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
	USES_CONVERSION;

	// Deal with return key events
	if (wParam == VK_RETURN)
	{
		// Stop any previous navigations
		m_spWebBrowser->Stop();

		CComBSTR bstrURL, bstrOldURL, bstrIncrement;
		CComVariant vtEmpty;

    // CODE REVIEW: Add following security comment.
    /* The following use of GetWindowText is simplified for illustrative
    purposes. This simplified use in production code can expose a
    security risk in some situations. In production code you might want
    to ensure that the receiving buffer size isn't exceeded by the size
    of the source string. */
		// Get text in Url address box and the
		// URL of current page for comparison
		m_wndUrlCombo.GetWindowText(bstrURL.m_str);
		m_spWebBrowser->get_LocationURL(&bstrOldURL);

		// Convert to char string for comparison
		LPSTR tURL = OLE2A(bstrURL);
		LPSTR tOldURL = OLE2A(bstrOldURL);

		if (strcmp(tURL,tOldURL)) // strcmp returns 0 if they're the same
		{
			// string in URL box is new, so navigate to new page and return
			
			// First remove grid behavior if there is one
			if (m_lGridCookie)
			{
				IHTMLElement* pBody = NULL;
				IHTMLElement2* pBody2;
				VARIANT_BOOL dummy;

				// Get IHTMLElement and IHTMLElement2 interfaces for the body
				m_spDoc->get_body(&pBody);
				pBody->QueryInterface(IID_IHTMLElement2, (void**)&pBody2);
				pBody2->removeBehavior(m_lGridCookie, &dummy);
				m_lGridCookie = NULL;
				m_spGrid = (IGrid*)NULL;

				pBody->Release();
				pBody2->Release();
			}

			m_spWebBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);

			// Turn off snap and grid buttons because IHTMLEditHost and the
			// rendering behavior are re-initialized when a navigation happens
			m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
			m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));
			m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
			m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));
			m_bButton2Down = FALSE;
			m_bButton4Down = FALSE;
			m_bButton5Down = FALSE;

			bHandled = TRUE;
			return 0;
		}

    // CODE REVIEW: Add following security comment.
    /* The following use of GetWindowText is simplified for illustrative
    purposes. This simplified use in production code can expose a
    security risk in some situations. In production code you might want
    to ensure that the receiving buffer size isn't exceeded by the size
    of the source string. */
		// Get text in increment box and convert to char string
		m_wndIncrementCombo.GetWindowText((BSTR&)bstrIncrement);
		LPSTR tIncrement = OLE2A(bstrIncrement);

		// convert new increment to number and
		// compare to current increment
		long lNewInc = _wtol(bstrIncrement);
		if (lNewInc != m_lSnapIncrement && lNewInc > 0)
		{
			// increment is new, so change to it and return
			m_lSnapIncrement = lNewInc;

			if (m_spGrid)
				m_spGrid->put_GridSize(m_lSnapIncrement);

			if (m_spSnap)
				m_spSnap->put_SnapIncrement(m_lSnapIncrement);

			bHandled = TRUE;
			return S_OK;
		}
		else
		{
			// increment is either the same as old one or invalid,
			// so change increment box value back to old one
			TCHAR oldInc;
			// convert number to string
			_ltot(m_lSnapIncrement, &oldInc, 10);
			m_wndIncrementCombo.SetWindowText(&oldInc);
		}
	}

	// Deal with tab and delete key events
	// Check for doc first
	if (m_spDoc)
	{
		// Determine current designMode
		CComBSTR bstrMode;
		m_spDoc->get_designMode(&bstrMode);
		char* cMode = OLE2A(bstrMode);

		// Handle tab when design mode is off
		if ((strcmp(cMode, "On") && wParam == VK_TAB) || wParam == VK_RETURN)
		{
			// Pass user interface control to the WebBrowser when
			// the tab key is pressed (that is, UIActivate it)
			// This lets the WebBrowser change focus between the
			// various controls on the page when the tab key is pressed
			CComQIPtr<IOleObject, &IID_IOleObject> spOleObject(m_spWebBrowser);

			RECT rect;
			GetClientRect(&rect);
			spOleObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, this, 0, m_hWnd, &rect);
		}

		// When designMode is on, disable tab and handle delete
		// (it requires special handling to work correctly)
		if ((!strcmp(cMode, "On") && wParam == VK_DELETE) ||
			(strcmp(cMode, "On") && wParam == VK_TAB) ||
			(wParam == VK_RETURN))
		{
			// Call TranslateAccelerator on the in-place active
			// object for the delete key so that the accelerator will be passed to the
			// hosted WebBrowser control.  This forces the delete key to
			// work correctly in design mode.
			CComQIPtr<IOleInPlaceActiveObject,
					&IID_IOleInPlaceActiveObject> spInPlaceActiveObject(m_spWebBrowser);
	
			MSG msg;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;

			spInPlaceActiveObject->TranslateAccelerator(&msg);
		}
		
	}

	bHandled = FALSE;

	return 0;
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
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(TRUE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(TRUE, 0));

	}
	else
	{
		m_spDoc->put_designMode(L"Off");
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON1, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
		m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));
		m_bButton2Down = FALSE;
		m_bButton4Down = FALSE;
		m_bButton5Down = FALSE;

	}

	return 1;
}

LRESULT CBrowserHost::OnButton2(WORD, WORD, HWND, BOOL&)
{
	if (!m_spSnap) return 0;

	m_bButton2Down = !m_bButton2Down;

	m_spSnap->put_SnapOn(m_bButton2Down);
	m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON2, MAKELONG(m_bButton2Down, 0));

	return 0;
}

LRESULT CBrowserHost::OnButton3(WORD, WORD, HWND, BOOL&)
{
	HRESULT hr;

	IHTMLElement* pBody = NULL;
	IHTMLElement2* pBody2;
	IElementBehaviorFactory* pGridFactory;
    VARIANT vFactory;

	// Get IHTMLElement and IHTMLElement2 interfaces for the body
	hr = m_spDoc->get_body(&pBody);
	hr = pBody->QueryInterface(IID_IHTMLElement2, (void**)&pBody2);

	if (m_lGridCookie)
	{
		VARIANT_BOOL dummy;
		hr = pBody2->removeBehavior(m_lGridCookie, &dummy);
		m_lGridCookie = NULL;
		m_spGrid = (IGrid*)NULL;
		LRESULT lr = m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(FALSE, 0));

		return 1;
	}

	// Get the behavior factory interface for
	// the grid rendering behavior
	hr = CoCreateInstance(CLSID_Grid, NULL, CLSCTX_INPROC_SERVER, IID_IElementBehaviorFactory, (void**)&pGridFactory);

	// Convert pGridFactory to the proper VARIANT data type
	// for IHTMLElement2::AddBehavior
	V_VT(&vFactory) = VT_UNKNOWN;
    V_UNKNOWN(&vFactory) = pGridFactory;

	// AddRef because we've copied the pGridFactory pointer
    V_UNKNOWN(&vFactory)->AddRef();

	// Add Grid behavior
	hr = pBody2->addBehavior(NULL, &vFactory, &m_lGridCookie);
	m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON3, MAKELONG(TRUE, 0));

	// cache a pointer the the IGrid interface and set the gridsize
	hr = pGridFactory->QueryInterface(IID_IGrid, (void**)&m_spGrid);
	hr = m_spGrid->put_GridSize(m_lSnapIncrement);

	// Release resources
	hr = pBody->Release();
	hr = pBody2->Release();
	hr = pGridFactory->Release();

	return 0;
}

LRESULT CBrowserHost::OnButton4(WORD, WORD, HWND, BOOL&)
{
	m_bButton4Down = !m_bButton4Down;

	VARIANT var;
	V_VT(&var) = VT_BOOL;

	if (m_bButton4Down)
	    V_BOOL(&var) = VARIANT_TRUE;
	else
		V_BOOL(&var) = VARIANT_FALSE;
	
	// Turn on 2D positioning
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_2D_POSITION,
						 MSOCMDEXECOPT_DODEFAULT,
						 &var,
						 NULL);

	m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON4, MAKELONG(m_bButton4Down, 0));

	return 0;
}

LRESULT CBrowserHost::OnButton5(WORD, WORD, HWND, BOOL&)
{
	m_bButton5Down = !m_bButton5Down;

	VARIANT var;
	V_VT(&var) = VT_BOOL;

	if (m_bButton5Down)
	    V_BOOL(&var) = VARIANT_TRUE;
	else
		V_BOOL(&var) = VARIANT_FALSE;

	// Turn on LiveResizing	
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_LIVERESIZE,
						 MSOCMDEXECOPT_DODEFAULT,
						 &var,
						 NULL);

	m_wndToolBar.SendMessage(TB_PRESSBUTTON, ID_BUTTON5, MAKELONG(m_bButton5Down, 0));

	return 0;
}

STDMETHODIMP CBrowserHost::Run()
{
	// Create and show the window
	RECT rcClient = { CW_USEDEFAULT, 0, 0, 0 };

	Create(GetDesktopWindow(), rcClient, _T("IHTMLEditHost Sample App"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
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
	m_spWebBrowser->Navigate(L"res://edhost.exe/test.html", NULL, NULL, NULL, NULL);

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
		
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
		0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,

		3, ID_BUTTON4, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
		4, ID_BUTTON5, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
	};

	HWND toolbar = CreateToolbarEx(m_hWnd,
								   WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
								   ID_TOOLBARWND,
								   4,
								   _Module.GetResourceInstance(),
								   IDR_TOOLBAR1,
								   tbb, 55,
								   0, 0,
								   55, 30,
								   sizeof(TBBUTTON));

	m_wndToolBar.Attach(toolbar);
	_ASSERT(m_wndToolBar);

	// Tell the toolbar to resize itself
	m_wndToolBar.SendMessage(TB_AUTOSIZE, 0, 0L);

	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON2, MAKELONG(FALSE, 0));
	//m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON3, MAKELONG(TRUE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON4, MAKELONG(FALSE, 0));
	m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_BUTTON5, MAKELONG(FALSE, 0));

	// Create the combo box on the toolbar
	RECT rc, rc2, rc3, rc4;

	// Calculate the coordinates for the combo box.
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)0, (LPARAM)(LPRECT)&rc);
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)38, (LPARAM)(LPRECT)&rc2);
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)45, (LPARAM)(LPRECT)&rc3);
	m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)48, (LPARAM)(LPRECT)&rc4);

	rc.right = rc2.right;
	rc3.right = rc4.right;
	rc.top = rc.top + 5;
	rc3.top = rc3.top + 5;
	rc.bottom = rc.top + 20;
	rc3.bottom = rc3.top + 20;

	m_wndUrlCombo.Create(m_wndToolBar, rc, NULL, WS_CHILD|WS_VISIBLE,
								0, ID_URLBOX);
	m_wndIncrementCombo.Create(m_wndToolBar, rc3, NULL, WS_CHILD|WS_VISIBLE,
								0, ID_SNAPINCBOX);

	TCHAR tcharInc;
	_ltot(m_lSnapIncrement, &tcharInc, 10);
	m_wndIncrementCombo.SetWindowText(&tcharInc);



}


STDMETHODIMP CBrowserHost::GetHwnd(long* phwnd)
{
	*phwnd = (long)m_hWnd;
	 return S_OK;
}

// IServiceProvider
STDMETHODIMP CBrowserHost::QueryService(REFGUID guidService,
									  REFIID riid,
									  void **ppv)
{
    HRESULT hr = E_NOINTERFACE;

    if (guidService == SID_SHTMLEditHost && riid == IID_IHTMLEditHost)
    {
		// Create new CSnap object
        CComObject<CSnap>* pSnap;
        hr = CComObject<CSnap>::CreateInstance(&pSnap);
		
		// Query the new CSnap object for IHTMLEditHost interface
        hr = pSnap->QueryInterface(IID_IHTMLEditHost, ppv);

        // Cache a pointer to ISnap so we can tell the Snap behavior
        // when to snap
        m_spSnap = (ISnap*)NULL; // Clear any previous pointers
        hr = pSnap->QueryInterface(IID_ISnap, (void**)&m_spSnap);
		
		// Set the snap increment
        hr = pSnap->put_SnapIncrement(m_lSnapIncrement);
    }

    return hr;
}

