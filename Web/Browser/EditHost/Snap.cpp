/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// Snap.cpp : Implementation of CSnap
#include "stdafx.h"
#include "EdHost.h"
#include "Snap.h"

/////////////////////////////////////////////////////////////////////////////
// CSnap

// IHTMLEditHost
STDMETHODIMP
CSnap::SnapRect(IHTMLElement *pIElement, 
				RECT *prcNew, 
				ELEMENT_CORNER eHandle)
{
	if (!m_bSnapOn) return S_OK; // Disables snap to grid when m_bSnapOn is FALSE

	LONG lWidth = prcNew->right - prcNew->left;
	LONG lHeight = prcNew->bottom - prcNew->top;

	switch (eHandle)
	{
	case ELEMENT_CORNER_NONE:
		prcNew->top = ((prcNew->top + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		prcNew->left = ((prcNew->left + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		prcNew->bottom = prcNew->top + lHeight;
		prcNew->right = prcNew->left + lWidth;
		break;

	case ELEMENT_CORNER_TOP:
		prcNew->top = ((prcNew->top + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		break;

	case ELEMENT_CORNER_LEFT:
		prcNew->left = ((prcNew->left + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		break;

	case ELEMENT_CORNER_BOTTOM:
		prcNew->bottom = ((prcNew->bottom + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		break;

	case ELEMENT_CORNER_RIGHT:
		prcNew->right = ((prcNew->right + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		break;

	case ELEMENT_CORNER_TOPLEFT:
		prcNew->top = ((prcNew->top + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		prcNew->left = ((prcNew->left + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		break;

	case ELEMENT_CORNER_TOPRIGHT:
		prcNew->top = ((prcNew->top + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		prcNew->right = ((prcNew->right + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		break;

	case ELEMENT_CORNER_BOTTOMLEFT:
		prcNew->bottom = ((prcNew->bottom + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		prcNew->left = ((prcNew->left + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement - 2;
		break;

	case ELEMENT_CORNER_BOTTOMRIGHT:
		prcNew->bottom = ((prcNew->bottom + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		prcNew->right = ((prcNew->right + (m_lSnapIncrement/2))/m_lSnapIncrement) * m_lSnapIncrement + 1;
		break;
	}

	return S_OK;

}

// ISnap
STDMETHODIMP CSnap::get_SnapIncrement(long *pVal)
{
	pVal = &m_lSnapIncrement;

	return S_OK;
}

STDMETHODIMP CSnap::put_SnapIncrement(long newVal)
{
	m_lSnapIncrement = newVal;

	return S_OK;
}

STDMETHODIMP CSnap::get_SnapOn(BOOL *pVal)
{
	pVal = &m_bSnapOn;

	return S_OK;
}

STDMETHODIMP CSnap::put_SnapOn(BOOL newVal)
{
	m_bSnapOn = newVal;

	return S_OK;
}


