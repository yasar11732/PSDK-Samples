// ADVCGENDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADVCGEN.h"
#include "ADVCGENDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADVCGENDlg dialog

CADVCGENDlg::CADVCGENDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CADVCGENDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADVCGENDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	schemaRs = NULL; // Schema Recordset Object
    dataRs = NULL;  // Data Recordset Object
	conn = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CADVCGENDlg::~CADVCGENDlg() 
{
	//{{AFX_DATA_INIT(CADVCGENDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	if (schemaRs != NULL) // Schema Recordset Object
	{
		if(schemaRs->State != ado20::adStateOpen)
			schemaRs->Close();
		schemaRs.Release();
		schemaRs=NULL;
	}
    if (dataRs != NULL)  // Data Recordset Object
	{
		if(dataRs->State != ado20::adStateOpen)
			dataRs->Close();
		dataRs.Release();
		dataRs = NULL;
	}
	if(conn != NULL)
	{
		if(conn->State != ado20::adStateOpen)
			conn->Close();
		conn.Release();
		conn = NULL;
	}
}


void CADVCGENDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADVCGENDlg)
	DDX_Control(pDX, IDC_DATAGRID1, m_DataGridDisplay);
	DDX_Control(pDX, IDC_TABLELIST, m_TableListBox);
	DDX_Control(pDX, IDC_CHECK1, m_SchemaInfo);
	DDX_Control(pDX, IDC_EDIT1, m_SQLEditBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CADVCGENDlg, CDialog)
	//{{AFX_MSG_MAP(CADVCGENDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnXecute)
	ON_BN_CLICKED(IDC_BUTTON1, OnBuild)
	ON_BN_CLICKED(IDCANCEL, OnExit)
	ON_LBN_SELCHANGE(IDC_TABLELIST, OnChangeTableList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADVCGENDlg message handlers

BOOL CADVCGENDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CADVCGENDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CADVCGENDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CADVCGENDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CADVCGENDlg::OnXecute() 
{
	char buffer[MAX_COUNT];
	CString buff1;
	// Get the SQL Statement
	TRYDB
	m_SQLEditBox.GetWindowText(buffer,MAX_COUNT);
	if(strlen(buffer) > 0)
		OutputIntoDataGrid(buffer);
	CATCHDB
}

void CADVCGENDlg::OnBuild() 
{

	TRYDB;
	try
	{			
		// The the Smart Pointer
		msdasc::IDataSourceLocatorPtr pOledb;  // Interface to show
		//Get the m_pInterface pointer to the DataLinks COM Object
		pOledb.CreateInstance(__uuidof(msdasc::DataLinks));  // coclass of IDataSourceLocatorPtr
		// Get the Connection 
//		if (conn != NULL)  // It contains data release it first
//			conn->Close();
		conn = (ado20::_ConnectionPtr) pOledb->PromptNew();

		connStr = (char*) conn->ConnectionString;
		TRACE("ADO Connection string is %s\n",(char*) conn->ConnectionString);
		TRACE("ADO Version is %s\n",(char*) conn->Version);
		SetDlgItemText(IDC_CONNECTSTRING,(LPCTSTR) conn->ConnectionString);
		UpdateData();
		// Set The cursor before the Open !!!
		//conn->CursorLocation = ado20::adUseClient;  
		if(conn->State != ado20::adStateOpen)
			conn->Open(L"",L"",L"",-1);

//////////////////////////////////////////////////////////////////////////////
		// How to create restrictions
		// Pass it the right info
		// rs now contains all the data...
		// To selectively get Table data only...
		///////////////////////////////////////////////////////////////
		_variant_t restrictions;
		// For adSchemaTable
		int lenCtr=4;
		_variant_t criteriaValues[4];
		criteriaValues[0].vt = VT_EMPTY;
		criteriaValues[1].vt = VT_EMPTY;
		criteriaValues[2].vt = VT_EMPTY;
		criteriaValues[3].vt = VT_BSTR;
		criteriaValues[3].bstrVal = (BSTR)_bstr_t("TABLE");
		RestrictionsOnOpenSchema(restrictions,lenCtr, criteriaValues);
		// If it contained previous data
		if (schemaRs != NULL)
		{
			schemaRs->putref_ActiveConnection(NULL);
			schemaRs->Close();
		}

		schemaRs = conn->OpenSchema(ado20::adSchemaTables,&restrictions);
		if(schemaRs->State == ado20::adStateOpen)
		{
			schemaRs->MoveFirst();
			m_TableListBox.ResetContent();
			while(!schemaRs->EOF)
			{
			if(m_SchemaInfo.GetCheck() == TRUE)
				{
					m_TableListBox.AddString(VarToBstr(schemaRs->Fields->Item[1L]->Value)+  // The Schema Name
						_bstr_t(".")+												// "."
						VarToBstr(schemaRs->Fields->Item[2L]->Value));					// The Table Name
				}
				else
					m_TableListBox.AddString(VarToBstr(schemaRs->Fields->Item[2L]->Value));
				hr = schemaRs->MoveNext();
			}
			TRACE( "Found %lu records.\n", schemaRs->RecordCount );
			m_DataGridDisplay.SetRefDataSource( NULL);
			m_DataGridDisplay.ClearFields();
			m_DataGridDisplay.Refresh();
			////////////////////////////////////////////////////
			// Enable Disabled Controls...
			SetDlgItemText(IDC_CONNECTSTRING,(LPCTSTR) conn->ConnectionString);
			DataRefresh(TRUE);
		}
		else
			MessageBox("Could not open the Schema Information", "Error",MB_OK);
	}
	catch (_com_error &ce)
	{
		CString adoStr,msgStr,tempStr;
		//
		// Trace COM error information.
		//
		adoStr=_T("");
		TRACE( "\nCom Exception Information\n-----------------------------------------------\n" );
		TRACE( "Description : %s\n",   (char*) ce.Description()  );
		TRACE( "Message     : %s\n",   (char*) ce.ErrorMessage() );
		TRACE( "HResult     : 0x%08x\n", ce.Error() );
		//
		// Trace ADO exception information only if connection is not null.
		//
		if ( NULL != conn )
		{
			TRACE( "\nADO Exception Information\n-----------------------------------------------\n" );
 			ado20::ErrorPtr err;
			for ( long i=0; i<conn->Errors->Count; i++ ) 
			{
				tempStr=_T("");
				err = conn->Errors->Item[i];
				TRACE( "Number      : 0x%08x\n", err->Number );
				TRACE( "Description : %s\n",	  (char*) err->Description );
				TRACE( "SQLState    : %s\n",     (char*) err->SQLState );
				TRACE( "Source      : %s\n\n",   (char*) err->Source );
				tempStr.Format("Ado Exception :\n===============\nDescription : %s\nSource : %s\n",(char*) err->Description,(char*) err->Source);  
				adoStr += tempStr;
			} 
		}
		msgStr.Format("\tCom Exception :\n===============\nDescription : %s\nMessage     : %s\n\t%s",(char*) ce.Description(),(char*) ce.ErrorMessage(), (LPCTSTR) adoStr);  
		this->MessageBox(msgStr,"Error Message", MB_OK);
	}
	CATCHDB;
}

_bstr_t CADVCGENDlg::VarToBstr(_variant_t varT)
{
	TRYDB
	switch(varT.vt)
	{
	case VT_EMPTY: return _bstr_t("Empty");
	case VT_NULL: return _bstr_t("<NULL>");
	case VT_ERROR: return _bstr_t("Error");
	case VT_BSTR: return _bstr_t(varT.bstrVal);
	default: return _bstr_t("Unknown");
	}
	CATCHDB
	return _bstr_t("Wrong Data Type");
}

void CADVCGENDlg::RestrictionsOnOpenSchema(_variant_t &restrictions, int lenCtr, _variant_t *criteriaValues)
{
   HRESULT hr = 0;
   SAFEARRAY FAR* psa;
   SAFEARRAYBOUND rgsabound[1];
   rgsabound[0].lLbound = 0;
   rgsabound[0].cElements = lenCtr;

   TRYDB
   psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
   // Fill the safe array.
   for( long lIndex = 0 ; lIndex < lenCtr ;lIndex++)
   {
     hr  = SafeArrayPutElement(psa, &lIndex,&criteriaValues[lIndex]);
   }
   // Initialize the safearray.
   restrictions.vt = VT_VARIANT | VT_ARRAY;
   V_ARRAY(&restrictions) = psa;
   CATCHDB
}

void CADVCGENDlg::OnExit() 
{
	TRYDB
	if (MessageBox("Thanx for using ADVCGEN...","Exit",MB_OK) == IDOK)
		DestroyWindow();
	CATCHDB	
}

void CADVCGENDlg::OnChangeTableList() 
{
	CString buff1,buffer;
	// Get the table name
	TRYDB
	m_TableListBox.GetText(m_TableListBox.GetCurSel(), buffer);
	// Create connection object.
	if (buffer.Find(" ") == -1)
		buff1.Format("SELECT * FROM %s",buffer,buffer);
	else
		buff1.Format("SELECT * FROM [%s]",buffer,buffer);
	OutputIntoDataGrid((char *) _bstr_t(buff1));
	m_SQLEditBox.SetWindowText(buff1);
	CATCHDB
}

void CADVCGENDlg::OutputIntoDataGrid(char *buffer)
{
	_variant_t vra; // Dummy Rows affected variant

	TRYDB
	try
	{			
		TRACE( "Instantiating ado connection object...\n" );
		// Remember INSERT, Update, Delete commands do not return recordsets
		if(dataRs == NULL) // Create it only for the 1st time
			hr = dataRs.CreateInstance(__uuidof(ado20::Recordset));
		else
		{
			dataRs->putref_ActiveConnection(NULL);
			if(dataRs->State == ado20::adStateOpen)
				dataRs->Close();
			m_DataGridDisplay.ClearFields();
			m_DataGridDisplay.SetRefDataSource(NULL);
		}
		dataRs->putref_ActiveConnection(conn);
		hr = dataRs->Open(_bstr_t(buffer),_variant_t((IDispatch*) conn), ado20::adOpenStatic,ado20::adLockOptimistic,ado20::adCmdText);
		if (SUCCEEDED(hr))
		{
			// Only for select statements do the following
			if(dataRs->State == ado20::adStateOpen)
			{
				TRACE( "Found %lu records.\n", dataRs->RecordCount );
				if(dataRs->RecordCount > 0 )
				{
					m_DataGridDisplay.ClearFields();
					m_DataGridDisplay.SetRefDataSource( (IUnknownPtr) dataRs);
				}
				else
					MessageBox("No Records found !!", "Error", MB_OK);
				UpdateData();
			}
		}
		else
			MessageBox("Could not Open the Query !!", "Error", MB_OK);
	}
	catch (_com_error &ce)
	{
		CString adoStr,msgStr,tempStr;
		//
		// Trace COM error information.
		//
		adoStr=_T("");
		TRACE( "\nCom Exception Information\n-----------------------------------------------\n" );
		TRACE( "Description : %s\n",   (char*) ce.Description()  );
		TRACE( "Message     : %s\n",   (char*) ce.ErrorMessage() );
		TRACE( "HResult     : 0x%08x\n", ce.Error() );
		//
		// Trace ADO exception information only if connection is not null.
		//
		if ( NULL != conn )
		{
			TRACE( "\nADO Exception Information\n-----------------------------------------------\n" );
 			ado20::ErrorPtr err;
			for ( long i=0; i<conn->Errors->Count; i++ ) 
			{
				tempStr=_T("");
				err = conn->Errors->Item[i];
				TRACE( "Number      : 0x%08x\n", err->Number );
				TRACE( "Description : %s\n",	  (char*) err->Description );
				TRACE( "SQLState    : %s\n",     (char*) err->SQLState );
				TRACE( "Source      : %s\n\n",   (char*) err->Source );
				tempStr.Format("Ado Exception :\n===============\nDescription : %s\nSource : %s\n",(char*) err->Description,(char*) err->Source);  
				adoStr += tempStr;
			} 
		}
		msgStr.Format("Com Exception :\n===============\nDescription : %s\nMessage     : %s\n%s",(char*) ce.Description(),(char*) ce.ErrorMessage(), (LPCTSTR) adoStr);  
		MessageBox(msgStr,"Error Message", MB_OK);
	}
	CATCHDB

}

void CADVCGENDlg::DataRefresh(BOOL bflag)
{
	m_SQLEditBox.EnableWindow(bflag); // enable the SQL statement Edit Box
	m_TableListBox.EnableWindow(bflag); // The Select Table ListBox...
	(GetDlgItem(IDC_DATAGRID1))->EnableWindow(bflag); // The Datagrid
	(GetDlgItem(IDC_BUTTON2))->EnableWindow(bflag); // The Xeceute Button
	(GetDlgItem(ID_REFRESH))->EnableWindow(bflag); // The Refresh Button
	UpdateData();
}
