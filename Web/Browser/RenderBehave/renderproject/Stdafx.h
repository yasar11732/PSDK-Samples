/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently.

#if !defined(AFX_STDAFX_H__140D5503_2290_11D2_AF61_00A0C9C9E6C5__INCLUDED_)
#define AFX_STDAFX_H__140D5503_2290_11D2_AF61_00A0C9C9E6C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>		// IObjectSafetyImpl

#include <mshtmdid.h>	// DHTML Behavior identifiers
#include <mshtmhst.h>	// DHTML Behavior interfaces
#include <mshtml.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__140D5503_2290_11D2_AF61_00A0C9C9E6C5__INCLUDED)
