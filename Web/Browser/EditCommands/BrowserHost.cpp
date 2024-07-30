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

LRESULT CBrowserHost::OnButton1(WORD, WORD, HWND, BOOL& bHandled)
{
	_ASSERT(m_spWebBrowser);

	if (!m_spDoc)
	{
		 MessageBox(_T("Document object no available."));
		 return 0;
	}

	USES_CONVERSION; // Needed for the OLE2A conversion macro
	BSTR bstrMode;
	HRESULT hr;

	hr = AtlUnadvise(m_spDoc,
					 DIID_HTMLDocumentEvents2,
					 m_dwCookie2);
		
	m_dwCookie2 = NULL;

	m_spDoc->get_designMode(&bstrMode);
	char* cMode = OLE2A(bstrMode);

	if (strcmp(cMode, "On"))
	{
		m_spDoc->put_designMode(L"On");
		m_wndButton1.SendMessage(BM_SETCHECK, BST_CHECKED, NULL);
	}
	else
	{
		m_spDoc->put_designMode(L"Off");
		m_wndButton1.SendMessage(BM_SETCHECK, BST_UNCHECKED, NULL);
	}

	if (m_bIsChecked)
	{
		m_wndBox1.SetWindowText(_T(""));
		m_wndBox2.SetWindowText(_T(""));
		m_wndBox3.SetWindowText(_T(""));
	}


	hr = AtlAdvise(m_spDoc,
				   GetUnknown(),
				   DIID_HTMLDocumentEvents2,
				   &m_dwCookie2);

	m_spOleCmdTarg = m_spWebBrowser;
	
	bHandled = TRUE;

	return 0;
}

LRESULT CBrowserHost::OnButton2(WORD, WORD, HWND, BOOL& bHandled)
{
	// Bold Selection
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_BOLD,
						 MSOCMDEXECOPT_DODEFAULT,
						 NULL,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton3(WORD, WORD, HWND, BOOL& bHandled)
{
	// Italicize Selection
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_ITALIC,
						 MSOCMDEXECOPT_DODEFAULT,
						 NULL,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton4(WORD, WORD, HWND, BOOL& bHandled)
{
	// Font Color
	USES_CONVERSION;

	CComBSTR bstrColor;

  // CODE REVIEW: Add this security comment.
  /* The following use of GetWindowText is simplified for illustrative
  purposes. This simplified use in production code can expose a
  security risk in some situations. In production code you might want
  to ensure that the receiving buffer size isn't exceeded by the size
  of the source string. */
	m_wndBox1.GetWindowText(bstrColor.m_str);

	VARIANT vColor;
	vColor.vt = VT_BSTR;
	vColor.bstrVal = bstrColor;
	
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_FORECOLOR,
						 MSOCMDEXECOPT_DODEFAULT,
						 &vColor,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton5(WORD, WORD, HWND, BOOL& bHandled)
{
	// FontSize
	USES_CONVERSION;

	CComBSTR bstrSize;

  // CODE REVIEW: Add this security comment.
  /* The following use of GetWindowText is simplified for illustrative
  purposes. This simplified use in production code can expose a
  security risk in some situations. In production code you might want
  to ensure that the receiving buffer size isn't exceeded by the size
  of the source string. */
	m_wndBox2.GetWindowText(bstrSize.m_str);

	LPSTR szSize = OLE2A(bstrSize);

	LONG lSize = atoi(szSize);

	VARIANT vSize;
	vSize.vt = VT_I4;
	vSize.lVal = lSize;
	
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_FONTSIZE,
						 MSOCMDEXECOPT_DODEFAULT,
						 &vSize,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton6(WORD, WORD, HWND, BOOL& bHandled)
{
	// FontName
	USES_CONVERSION;

	CComBSTR bstrName;

  // CODE REVIEW: Add this security comment.
  /* The following use of GetWindowText is simplified for illustrative
  purposes. This simplified use in production code can expose a
  security risk in some situations. In production code you might want
  to ensure that the receiving buffer size isn't exceeded by the size
  of the source string. */
	m_wndBox3.GetWindowText(bstrName.m_str);

	VARIANT vName;
	vName.vt = VT_BSTR;
	vName.bstrVal = bstrName;
	
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_FONTNAME,
						 MSOCMDEXECOPT_DODEFAULT,
						 &vName,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnButton7(WORD, WORD, HWND, BOOL& bHandled)
{
	//InsertImage
	USES_CONVERSION;

	CComBSTR bstrImage;

  // CODE REVIEW: Add this security comment.
  /* The following use of GetWindowText is simplified for illustrative
  purposes. This simplified use in production code can expose a
  security risk in some situations. In production code you might want
  to ensure that the receiving buffer size isn't exceeded by the size
  of the source string. */
	m_wndBox4.GetWindowText(bstrImage.m_str);

	VARIANT vImage;
	vImage.vt = VT_BSTR;
	vImage.bstrVal = bstrImage;
	
	m_spOleCmdTarg->Exec(&CGID_MSHTML,
						 IDM_IMAGE,
						 MSOCMDEXECOPT_DONTPROMPTUSER,
						 &vImage,
						 NULL);

	return 0;
}

LRESULT CBrowserHost::OnCheckBox(WORD, WORD, HWND, BOOL& bHandled)
{
	m_bIsChecked = !m_bIsChecked;

	return 0;
}

LRESULT CBrowserHost::OnAddressBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	USES_CONVERSION;

	if (wParam == VK_RETURN)
	{
		CComBSTR bstrURL;

    // CODE REVIEW: Add this security comment.
    /* The following use of GetWindowText is simplified for illustrative
    purposes. This simplified use in production code can expose a
    security risk in some situations. In production code you might want
    to ensure that the receiving buffer size isn't exceeded by the size
    of the source string. */
		m_wndAddressBox.GetWindowText(bstrURL.m_str);
		m_spWebBrowser->Navigate(bstrURL, NULL, NULL, NULL, NULL);
	}

	return 0;
}

LRESULT CBrowserHost::OnBox1(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_RETURN)
		OnButton4(NULL, NULL, NULL, bHandled);

	return 0;
}

LRESULT CBrowserHost::OnBox2(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_RETURN)
		OnButton5(uMsg, wParam, NULL, bHandled);

	return 0;
}

LRESULT CBrowserHost::OnBox3(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_RETURN)
		OnButton6(uMsg, wParam, NULL, bHandled);

	return 0;
}

LRESULT CBrowserHost::OnBox4(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == VK_RETURN)
		OnButton7(uMsg, wParam, NULL, bHandled);

	return 0;
}

STDMETHODIMP CBrowserHost::Run()
{
	// Create and show the window
	RECT rcClient = { CW_USEDEFAULT, 0, 0, 0 };

	Create(GetDesktopWindow(),
		   rcClient,
		   _T("Editing Command Sample App"),
		   WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		   0,
		   NULL);

	ShowWindow(SW_SHOWNORMAL);

	// Add status bar
	m_wndStatusBar.Attach(CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE,
										     _T("Ready"),
											 m_hWnd,
											 2));

	// CreateWebBrowser Control
	CComQIPtr<IOleObject> spOleObject;
	HRESULT hr = CoCreateInstance(CLSID_WebBrowser,
								  NULL,
								  CLSCTX_INPROC,
								  IID_IWebBrowser,
								  (void**)&m_spWebBrowser);

	m_spInPlaceObject = m_spWebBrowser;
	spOleObject = m_spWebBrowser;

	hr = spOleObject->SetClientSite(this);
	if (FAILED(hr))
	{
		MessageBox(_T("SetClientSite failed"));
		return E_FAIL;
	}


	// In-place activate the WebBrower control
	MSG msg;
	GetClientRect(&rcClient);

	hr = spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, &msg, this, 0, m_hWnd, &rcClient);

	// Set up event notification to browser
	hr = AtlAdvise(m_spWebBrowser,
				   GetUnknown(),
				   DIID_DWebBrowserEvents2,
				   &m_dwCookie);

	// Create Top Band Window
	RECT rc;

	GetClientRect(&rc);
	rc.bottom = rc.top + m_lTopBandHeight;

	m_wndTopBand.Create(m_hWnd,
						 rc,
						 NULL,
						 WS_CHILD|WS_VISIBLE|SS_BLACKRECT,
						 0,
						 ID_TOPBAND);

	// Create Left Band Window
	GetClientRect(&rc);
	rc.right = rc.left + m_lLeftBandWidth;
	rc.top = rc.top + m_lTopBandHeight;

	RECT rcStatus;
	m_wndStatusBar.GetWindowRect(&rcStatus);

	rc.bottom = rc.bottom - (rcStatus.bottom - rcStatus.top);

	m_wndLeftBand.Create(m_hWnd,
						 rc,
						 NULL,
						 WS_CHILD|WS_VISIBLE|SS_BLACKRECT,
						 0,
						 ID_LEFTBAND);

	// Add buttons
	LONG lheight = 25;
	LONG lwidth = 80;
	LONG lYOffset = 35;
	LONG lTopMargin = 10;
	LONG lLeftMargin = 10;
	
	GetClientRect(&rc);

	rc.top = rc.top + lTopMargin;
	rc.left = rc.left + lLeftMargin;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + 110;

	m_wndButton1.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("DesignModeOn"),
						WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_PUSHLIKE,
						0,
						ID_BUTTON1);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth;

	m_wndButton2.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("Bold"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON2);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth;

	m_wndButton3.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("Italic"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON3);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth;

	m_wndButton4.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("FontColor"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON4);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth;

	m_wndButton5.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("FontSize"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON5);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth;

	m_wndButton6.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("FontName"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON6);

	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;
	rc.right = rc.left + lwidth + 10;

	m_wndButton7.Create(m_wndLeftBand.m_hWnd,
						rc,
						_T("InsertImage"),
						WS_CHILD|WS_VISIBLE| BS_PUSHBUTTON,
						0,
						ID_BUTTON7);

	// Add edit boxes
	lwidth = 65;
	lheight = 25;

	rc.left = rc.left + 90;
	rc.right = rc.left + lwidth;
	rc.top = rc.top - 3 *lYOffset;
	rc.bottom = rc.top + lheight;

	m_wndBox1.Create(m_wndLeftBand.m_hWnd,
					 rc,
					 NULL,
					 WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,
					 0,
					 ID_BOX1);

	rc.right = rc.left + lwidth;
	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;

	m_wndBox2.Create(m_wndLeftBand.m_hWnd,
					 rc,
					 NULL,
					 WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL,
					 0,
					 ID_BOX2);

	rc.right = rc.left + lwidth;
	rc.top = rc.top + lYOffset;
	rc.bottom = rc.top + lheight;

	m_wndBox3.Create(m_wndLeftBand.m_hWnd,
					 rc,
					 NULL,
					 WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL,
					 0,
					 ID_BOX3);

	rc.left = rc.left - 80;
	rc.right = rc.left + lwidth + 80;
	rc.top = rc.top + 2 *lYOffset;
	rc.bottom = rc.top + lheight;

	m_wndBox4.Create(m_wndLeftBand.m_hWnd,
					 rc,
					 NULL,
					 WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL,
					 0,
					 ID_BOX4);

	m_wndBox1.SetWindowText(_T("red"));
	m_wndBox2.SetWindowText(_T("7"));
	m_wndBox3.SetWindowText(_T("comic sans ms"));
	m_wndBox4.SetWindowText(_T("res://edcommands.exe/cone.jpg"));

	rc.top = rc.top + 2*lYOffset;
	rc.bottom = rc.top + 3*lheight/2;
	rc.left = rc.left - 10;
	rc.right = rc.left + 130;
	
	m_wndCheckBox.Create(m_wndLeftBand.m_hWnd,
					 rc,
					 _T("Track Selection Properties"),
					 WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|BS_MULTILINE,
					 0,
					 ID_CHECKBOX);

	// Add addressbox
	GetClientRect(&rc);
	rc.top += 5;
	rc.bottom = rc.top + 25;
	rc.left += lLeftMargin;
	rc.right = rc.left + 450;

	m_wndAddressBox.Create(m_wndTopBand.m_hWnd,
					 rc,
					 NULL,
					 WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL,
					 0,
					 ID_ADDRESSBOX);


	m_wndStatusBar.GetWindowRect(&rc);

	// resize webbrowser to account for status bar, top and left band
	GetClientRect(&rcClient);
	rcClient.top = rcClient.top + m_lTopBandHeight;
	rcClient.left = rcClient.left + m_lLeftBandWidth;
	rcClient.bottom = rcClient.bottom - (rc.bottom - rc.top);
	
	m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);

	// Navigate to home page
	m_spWebBrowser->Navigate(L"res://edcommands.exe/test.html", NULL, NULL, NULL, NULL);
	m_wndAddressBox.SetWindowText(_T("res://edcommands.exe/test.html"));

	m_spOleCmdTarg = m_spWebBrowser;

	return S_OK;
}

STDMETHODIMP CBrowserHost::Stop()
{
	HRESULT hr = AtlUnadvise(m_spWebBrowser,
							 DIID_DWebBrowserEvents2,
							 m_dwCookie);

	m_dwCookie = NULL;

	PostQuitMessage(0);

	return S_OK;
}

LRESULT CBrowserHost::OnCreate(UINT, WPARAM, LPARAM, BOOL&) {return 0;}
	
LRESULT CBrowserHost::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Stop();
	return 0;
}


LRESULT CBrowserHost::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rcStatus;
	RECT rc;

	// Resize the status bar
	if (m_wndStatusBar.m_hWnd)
	{
		GetClientRect(&rc);

		// Keep the status bar height the same.
		m_wndStatusBar.GetWindowRect(&rcStatus);
		rc.top = rc.bottom - (rcStatus.bottom - rcStatus.top);
	
		m_wndStatusBar.MoveWindow(&rc, TRUE);
	}

	// Resize Top Band
	if (m_wndTopBand.m_hWnd)
	{
		GetClientRect(&rc);
		rc.bottom = rc.top + m_lTopBandHeight;
		m_wndTopBand.MoveWindow(&rc, TRUE);
	}

	// Resize Left Band
	if (m_wndLeftBand.m_hWnd)
	{
		GetClientRect(&rc);
		rc.right = rc.left + m_lLeftBandWidth;
		rc.top = rc.top + m_lTopBandHeight;
		rc.bottom = rc.bottom - (rcStatus.bottom - rcStatus.top);
		m_wndLeftBand.MoveWindow(&rc, TRUE);
	}

	// Resize the WebBrowser
	if (m_spWebBrowser && m_bInPlaceActive)
	{
		GetClientRect(&rc);

		// Resize the control to accomodate the status bar and toolbar
		rc.bottom -= (rcStatus.bottom - rcStatus.top);

		//m_wndToolBar.GetWindowRect(&rcWindow);
		rc.left += m_lLeftBandWidth;
		rc.top += m_lTopBandHeight;

		if (m_spInPlaceObject)
			m_spInPlaceObject->SetObjectRects(&rc, &rc);
	}

	return 0;
}

LRESULT CBrowserHost::OnKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Deal with tab and delete key events
	// Check for doc first
	if (!m_spDoc) return 0;

	USES_CONVERSION;
	// Determine current designMode
	CComBSTR bstrMode;
	m_spDoc->get_designMode(&bstrMode);
	char* cMode = OLE2A(bstrMode);

	// Handle tab when design mode is off
	// Handle return regardless of designMode
	if ((strcmp(cMode, "On") && wParam == VK_TAB) || wParam == VK_RETURN)
	{
		// Pass user interface control to the WebBrowser when
		// the tab or return keys are pressed (that is, UIActivate it)
		// This lets the WebBrowser change focus between the
		// various controls on the page when the tab key is pressed
		CComQIPtr<IOleObject, &IID_IOleObject> spOleObject(m_spWebBrowser);

		RECT rect;
		GetClientRect(&rect);
		spOleObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, this, 0, m_hWnd, &rect);
	}

	// When designMode is on, tab, backspace, right arrow,
	// left arrow, up arrow, down arrow, and end key events
	// shouldn't be passed to the WebBrowser
	// (They require special handling to work correctly)
	// Also, pass VK_TAB to WebBrowser control when designMode is off
	// Pass return key events regardless of designMode
	if ((!strcmp(cMode, "On") && wParam != VK_TAB &&
								 wParam != VK_BACK &&
								 wParam != VK_RIGHT &&
								 wParam != VK_LEFT &&
								 wParam != VK_UP &&
								 wParam != VK_DOWN &&
								 wParam != VK_END) ||
		(strcmp(cMode, "On") && wParam == VK_TAB) ||
		(wParam == VK_RETURN))
	{
		// Call TranslateAccelerator on the in-place active
		// object to pass events to the WebBrowser control
		CComQIPtr<IOleInPlaceActiveObject,
				&IID_IOleInPlaceActiveObject> spInPlaceActiveObject(m_spWebBrowser);
	
		MSG msg;
		msg.message = uMsg;
		msg.wParam = wParam;
		msg.lParam = lParam;

		spInPlaceActiveObject->TranslateAccelerator(&msg);
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
	HRESULT hr;
	CComBSTR bstrString;
	CComVariant var;
	TCHAR szRed[3];
	TCHAR szGreen[3];
	TCHAR szBlue[3];
	TCHAR szColor[8];
	TCHAR szString[25];
	int i = 0;
	int j = 0;
	int hex = 1;
	LONG lColor, lRed, lGreen, lBlue;

	switch (dispidMember)
	{
		case DISPID_DOCUMENTCOMPLETE:
		{
			IDispatch* pDisp;
			m_spDoc = (IHTMLDocument2*)NULL;
			m_spWebBrowser->get_Document(&pDisp);
			pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&m_spDoc);

			// Set up event notification to document
			if (!m_dwCookie2) // Check m_dwCookie because Invoke is called
							  // w/DISPID_DOCUMENTCOMPLETE more than once
							  // and we don't want to set more than one
							  // connection point to document
				hr = AtlAdvise(m_spDoc,
							   GetUnknown(),
							   DIID_HTMLDocumentEvents2,
							   &m_dwCookie2);

			pDisp->Release();
			break;
		}

		case DISPID_BEFORENAVIGATE:
		case DISPID_BEFORENAVIGATE2:
		case DISPID_ONQUIT:
		{
			if (!m_dwCookie2 || !m_spDoc) break;
			hr = AtlUnadvise(m_spDoc,
							 DIID_HTMLDocumentEvents2,
							 m_dwCookie2);

			m_dwCookie2 = NULL;

			break;
		}

		case DISPID_HTMLDOCUMENTEVENTS2_ONSELECTIONCHANGE:
		{
			if (!m_bIsChecked) break;

			// Get font color
			hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
								 IDM_FORECOLOR, // To compile with IE 5.0 Headers and Libs use:  IDM_DISABLE_EDITFOCUS_UI
								 MSOCMDEXECOPT_DODEFAULT,
								 NULL,
								 &var);
			
			// Convert long returned in var to hash-prefixed
			// hexidecimal string
			lColor = var.lVal;
			lBlue = lColor/(256*256);
			lColor = lColor - lBlue*256*256;
			lGreen = lColor/256;
			lRed = lColor - lGreen*256;

			_itot(lRed, szRed, 16);
			_itot(lGreen, szGreen, 16);
			_itot(lBlue, szBlue, 16);

			szColor[0] = '#';
			if (lRed < 16)
			{
				szColor[1] = '0';
				szColor[2] = szRed[0];
			}
			else
			{
				szColor[1] = szRed[0];
				szColor[2] = szRed[1];
			}
			if (lGreen < 16)
			{
				szColor[3] = '0';
				szColor[4] = szGreen[0];
			}
			else
			{
				szColor[3] = szGreen[0];
				szColor[4] = szGreen[1];
			}
			if (lBlue < 16)
			{
				szColor[5] = '0';
				szColor[6] = szBlue[0];
			}
			else
			{
				szColor[5] = szBlue[0];
				szColor[6] = szBlue[1];
			}

			szColor[7] = NULL;
			
			if (var.vt != VT_EMPTY)
				m_wndBox1.SetWindowText(szColor);
			else
				m_wndBox1.SetWindowText(_T(""));

			// Get font size
			hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
								 IDM_FONTSIZE,
								 MSOCMDEXECOPT_DODEFAULT,
								 NULL,
								 &var);

			_itot(var.lVal, szString, 10);

			if (var.vt != VT_EMPTY)
				m_wndBox2.SetWindowText(szString);
			else
				m_wndBox2.SetWindowText(_T(""));

			// Get font name
			hr = m_spOleCmdTarg->Exec(&CGID_MSHTML,
								 IDM_FONTNAME,
								 MSOCMDEXECOPT_DODEFAULT,
								 NULL,
								 &var);
			
			if (var.vt != VT_EMPTY)
				m_wndBox3.SetWindowText(OLE2T(var.bstrVal));
			else
				m_wndBox3.SetWindowText(_T(""));

			break;
		}

		case DISPID_STATUSTEXTCHANGE:
			m_wndStatusBar.SetWindowText(OLE2T(pDispParams->rgvarg[0].bstrVal));
			break;

		default:
			return DISP_E_MEMBERNOTFOUND;
	}

	return S_OK;
}
