
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996 - 2000 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// XMLTree.h : main header file for the XMLTREE application
//

#if !defined(AFX_XMLTREE_H__3C9F0B05_FD51_11D2_AC35_00600812D7F9__INCLUDED_)
#define AFX_XMLTREE_H__3C9F0B05_FD51_11D2_AC35_00600812D7F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMLTreeApp:
// See XMLTree.cpp for the implementation of this class
//

class CXMLTreeApp : public CWinApp
{
public:
	CXMLTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMLTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLTREE_H__3C9F0B05_FD51_11D2_AC35_00600812D7F9__INCLUDED_)
