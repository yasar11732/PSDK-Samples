//=--------------------------------------------------------------------------=
//  (C) Copyright 1996 - 2000 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=

// XMLTreeDlg.h : header file
//

#if !defined(AFX_XMLTREEDLG_H__3C9F0B07_FD51_11D2_AC35_00600812D7F9__INCLUDED_)
#define AFX_XMLTREEDLG_H__3C9F0B07_FD51_11D2_AC35_00600812D7F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CXMLTreeDlg dialog

class CXMLTreeDlg : public CDialog
{
// Construction
public:
	CImageList m_imageList;
	int MakeTree(MSXML::IXMLDOMElement *node, HTREEITEM ht);
	int LoadXML(CString filename);
	CXMLTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMLTreeDlg)
	enum { IDD = IDD_XMLTREE_DIALOG };
	CTreeCtrl	m_tree;
	CString	m_filename;
	CString	m_debug;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

    virtual void OnOK();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMLTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoad();
	afx_msg void OnChangeFilename();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLTREEDLG_H__3C9F0B07_FD51_11D2_AC35_00600812D7F9__INCLUDED_)
