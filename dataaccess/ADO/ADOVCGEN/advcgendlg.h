// ADVCGENDlg.h : header file
//
//{{AFX_INCLUDES()
#include "ADOHeader.h"
#include "datagrid.h"
//}}AFX_INCLUDES

#if !defined(AFX_ADVCGENDLG_H__202C1C4E_0C5C_4307_8CD3_FDDD43571792__INCLUDED_)
#define AFX_ADVCGENDLG_H__202C1C4E_0C5C_4307_8CD3_FDDD43571792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CADVCGENDlg dialog

class CADVCGENDlg : public CDialog
{
// Construction
public:
	void DataRefresh(BOOL bflag);
	// ADO specific variables
	_bstr_t connStr;
	ado20::_ConnectionPtr conn;
	ado20::_RecordsetPtr    dataRs;  // Data Recordset Object
	ado20::_RecordsetPtr    schemaRs;
	HRESULT hr;

	// ADO specific functions
	void RestrictionsOnOpenSchema(_variant_t &restrictions,int lenCtr, _variant_t *criteriaValues);
	_bstr_t VarToBstr(_variant_t varT);
	void OutputIntoDataGrid(char *buffer);

	CADVCGENDlg(CWnd* pParent = NULL);	// standard constructor
	~CADVCGENDlg();	// standard Destructor
	
// Dialog Data
	//{{AFX_DATA(CADVCGENDlg)
	enum { IDD = IDD_ADVCGEN_DIALOG };
	CDataGrid	m_DataGridDisplay;
	CListBox	m_TableListBox;
	CButton	m_SchemaInfo;
	CEdit  m_SQLEditBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADVCGENDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CADVCGENDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnXecute();
	afx_msg void OnBuild();
	afx_msg void OnExit();
	afx_msg void OnChangeTableList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVCGENDLG_H__202C1C4E_0C5C_4307_8CD3_FDDD43571792__INCLUDED_)
