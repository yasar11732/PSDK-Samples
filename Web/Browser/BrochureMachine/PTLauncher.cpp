/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// PTLauncher.cpp : Implementation of CPTLauncher
#include "stdafx.h"
#include "BrochureMachine.h"
#include "PTLauncher.h"
#include "ExDisp.h"
#include "shlguid.h"
#include "mshtml.h"
#include "mshtmcid.h"
#include "mshtmhst.h"
#include "mshtmdid.h"
/////////////////////////////////////////////////////////////////////////////
// CPTLauncher

STDMETHODIMP CPTLauncher::LaunchPT()
{
	CComPtr<IOleContainer> spContainer;
	CComPtr<IServiceProvider> spSP;
	CComPtr<IWebBrowser2> spWB;
	CComPtr<IDispatch> spDisp;
	CComPtr<IHTMLDocument2> spDoc;
	CComPtr<IOleCommandTarget> spCT;
	CComVariant vPTPath = "res://BrochureMachine.dll/PT.htm";

	m_spClientSite->GetContainer(&spContainer);
	spContainer->QueryInterface(IID_IServiceProvider, (void**)&spSP);
	spSP->QueryService(SID_SWebBrowserApp, IID_IWebBrowser, (void**)&spWB);
	spWB->get_Document(&spDisp);
	spDisp->QueryInterface(IID_IHTMLDocument2, (void**)&spDoc);
	spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&spCT);
	spCT->Exec(&CGID_MSHTML, IDM_PRINTPREVIEW, NULL, &vPTPath, NULL);

	return S_OK;
}