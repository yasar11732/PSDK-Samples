// ADVCGEN.h : main header file for the ADVCGEN application
//

#if !defined(AFX_ADVCGEN_H__745DF779_D2F6_4E0E_97A8_EE39AF8C2117__INCLUDED_)
#define AFX_ADVCGEN_H__745DF779_D2F6_4E0E_97A8_EE39AF8C2117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CADVCGENApp:
// See ADVCGEN.cpp for the implementation of this class
//

class CADVCGENApp : public CWinApp
{
public:
	CADVCGENApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADVCGENApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CADVCGENApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVCGEN_H__745DF779_D2F6_4E0E_97A8_EE39AF8C2117__INCLUDED_)
