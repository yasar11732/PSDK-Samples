// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__AB8FEB9C_3841_11D2_8512_00C04FA34A14__INCLUDED_)
#define AFX_STDAFX_H__AB8FEB9C_3841_11D2_8512_00C04FA34A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#if _MSC_VER >= 1200
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#include <malloc.h>

// Agent Control Wrapper Headers generated by Class Wizard

#include "ACEx.h"
#include "ACChars.h"
#include "ACChar.h"
#include "ACBall.h"
#include "ACAnim.h"
#include "ACComms.h"
#include "ACUser.h"
#include "ACReq.h"
#include "ACProp.h"
#include "ACAudio.h"

// Agent Control Header

#include "AgtCtl.h"

// Agent Server Header (need only for visibility causes)

#include "AgtSvr.h"

#endif // !defined(AFX_STDAFX_H__AB8FEB9C_3841_11D2_8512_00C04FA34A14__INCLUDED_)
