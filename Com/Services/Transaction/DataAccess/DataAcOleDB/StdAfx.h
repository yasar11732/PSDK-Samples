// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1A34A4C5_1C2D_11D1_98C4_00C04FC2C8D5__INCLUDED_)
#define AFX_STDAFX_H__1A34A4C5_1C2D_11D1_98C4_00C04FC2C8D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0500
#endif // !defined(_WIN32_WINNT)

#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1A34A4C5_1C2D_11D1_98C4_00C04FC2C8D5__INCLUDED)