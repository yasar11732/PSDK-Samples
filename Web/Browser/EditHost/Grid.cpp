/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// Grid.cpp : Implementation of CGrid
#include "stdafx.h"
#include "EdHost.h"
#include "Grid.h"

/////////////////////////////////////////////////////////////////////////////
// CGrid


// IGrid
STDMETHODIMP CGrid::get_GridSize(long *pVal)
{
	pVal = &m_lGridSize;

	return S_OK;
}

STDMETHODIMP CGrid::put_GridSize(long newVal)
{
	m_lGridSize = newVal;
	m_spPaintSite->InvalidateRect(NULL);

	return S_OK;
}

// IElementBehavior
STDMETHODIMP CGrid::Init(IElementBehaviorSite* pBehaviorSite)
{
	HRESULT hr;
	IHTMLElement* pBody;
	IHTMLElement2* pBody2;

	pBehaviorSite->GetElement(&pBody);
	pBody->QueryInterface(IID_IHTMLElement2, (void**)&pBody2);

	pBody2->get_clientTop(&m_lClientTop);
	pBody2->get_clientLeft(&m_lClientLeft);
	m_spSite = pBehaviorSite;

	hr = m_spSite->QueryInterface(IID_IHTMLPaintSite, (void**)&m_spPaintSite);


	return hr;
}
	
STDMETHODIMP CGrid::Notify(LONG lEvent, VARIANT * pVar)
{
	if (pVar == NULL)
		return E_POINTER;

	return E_NOTIMPL;
}
	
STDMETHODIMP CGrid::Detach()
{
	m_spPaintSite->InvalidateRect(NULL);
	return S_OK;
}

// IHTMLPainter
STDMETHODIMP CGrid::Draw(RECT rcBounds, RECT rcUpdate, LONG lDrawFlags, HDC hdc, LPVOID pvDrawObject)
{
	HPEN redPen	= (HPEN)CreatePen(PS_DOT, 0, RGB(0xff, 0x99, 0x99));
	HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

	long lFirstLine = rcBounds.left;

	for (int i = lFirstLine; i <= rcBounds.right; i += m_lGridSize)
	{
		MoveToEx(hdc, i, rcBounds.top, NULL);
		LineTo(hdc, i, rcBounds.bottom);
	}

	lFirstLine = rcBounds.top;

	for (i = lFirstLine ; i <= rcBounds.bottom; i += m_lGridSize)
	{
		MoveToEx(hdc, rcBounds.left, i,  NULL);
		LineTo(hdc, rcBounds.right, i);
	}

	return S_OK;
}
	
STDMETHODIMP CGrid::OnResize(SIZE size) {return S_OK;}
	
STDMETHODIMP CGrid::GetPainterInfo(HTML_PAINTER_INFO * pInfo)
{
	if (pInfo == NULL)
		return E_POINTER;

	pInfo->lFlags = HTMLPAINTER_TRANSPARENT;
	pInfo->lZOrder = HTMLPAINT_ZORDER_BELOW_CONTENT;

	memset(&pInfo->iidDrawObject, 0, sizeof(IID));

	pInfo->rcExpand.left = 0;
	pInfo->rcExpand.right = 0;
	pInfo->rcExpand.top = 0;
	pInfo->rcExpand.bottom = 0;

	return S_OK;
}
	
STDMETHODIMP CGrid::HitTestPoint(POINT pt, BOOL* pbHit, LONG* plPartID)
{
	if (pbHit == NULL)
		return E_POINTER;

	if (plPartID == NULL)
		return E_POINTER;

	return E_NOTIMPL;
}

// IObjectSafety
STDMETHODIMP CGrid::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
{
     // Set the safety options we have been asked to set.
	m_dwCurrentSafety = m_dwCurrentSafety  & ~dwEnabledOptions | dwOptionSetMask;
	return S_OK;
}

// CFactory

STDMETHODIMP
CGrid::FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, IElementBehaviorSite* pSite, IElementBehavior** ppBehavior)
{
	HRESULT hr;

	hr = this->QueryInterface(IID_IElementBehavior, (void**)ppBehavior );

	return hr;
}
