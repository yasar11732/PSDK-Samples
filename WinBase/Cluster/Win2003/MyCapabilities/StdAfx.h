//
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
//

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// Categories and ClusCfg GUIDS
#include <ClusCfgGuids.h>

// Interface definitions for IClusCfgCapabilities
#include <ClusCfgServer.h>

// Safe string functions
#include <strsafe.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
