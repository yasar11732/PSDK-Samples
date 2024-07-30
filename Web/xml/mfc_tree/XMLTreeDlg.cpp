//=--------------------------------------------------------------------------=
//  (C) Copyright 1996 - 2000 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// XMLTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMLTree.h"
#include "XMLTreeDlg.h"

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
// CXMLTreeDlg dialog

CXMLTreeDlg::CXMLTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMLTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMLTreeDlg)
	m_filename = _T("");
	m_debug = _T("Enter a URL to load or click the open button to find an XML file to open.");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_XMLTREE);
}

void CXMLTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMLTreeDlg)
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	DDX_Text(pDX, IDC_DEBUG, m_debug);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMLTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CXMLTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_EN_CHANGE(IDC_FILENAME, OnChangeFilename)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLTreeDlg message handlers

BOOL CXMLTreeDlg::OnInitDialog()
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

	m_imageList.Create(IDB_TREEICON, 16, 4, RGB( 255, 255, 255 ));	
	m_tree.SetImageList( &m_imageList, TVSIL_NORMAL );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMLTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXMLTreeDlg::OnPaint() 
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
HCURSOR CXMLTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXMLTreeDlg::OnLoad() 
{
    GetDlgItemText(IDC_FILENAME, m_filename);
    if (0 == m_filename.GetLength())
    {
        OnOpen();
    }
    else
    {
        LoadXML(m_filename);
    }
}

int CXMLTreeDlg::LoadXML(CString filename)
{
	MSXML::IXMLDOMDocument		*pDoc        = NULL;
	MSXML::IXMLDOMParseError	*pParsingErr = NULL;
	MSXML::IXMLDOMElement		*element     = NULL;
	MSXML::IXMLDOMNodeList		*childs      = NULL; 
	MSXML::IXMLDOMNode			*node        = NULL;
	HTREEITEM ht;
	
	BSTR	bstr = NULL;
	HRESULT hr;
    int     rc = 0;
	char msg[500];

	m_tree.DeleteAllItems();

	m_debug = "Loading " + filename;
	UpdateData(FALSE);
    UpdateWindow();

	hr = CoInitialize(NULL);
	if(!SUCCEEDED(hr))
		return 0;

	hr = CoCreateInstance (MSXML::CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER, 
							MSXML::IID_IXMLDOMDocument, (LPVOID *)&pDoc);
	if(!pDoc)
    {
        m_debug = "Error co-creating IXMLDOMDocument";
        goto cleanup;
    }

    pDoc->put_async(VARIANT_FALSE);
    bstr = filename.AllocSysString();
	hr = pDoc->load (bstr);
    SysFreeString(bstr);
	
	if(!hr)
	{
		long line, linePos;
		BSTR reason = NULL;
		
		pDoc->get_parseError(&pParsingErr);

	    pParsingErr->get_line(&line);
		pParsingErr->get_linepos(&linePos);
		pParsingErr->get_reason(&reason);
		pParsingErr->get_errorCode(&hr);
		
		sprintf(msg, "Error 0x%.8X on line %d, position %d\r\n", hr, line, linePos);

		m_debug = reason;
		m_debug += CString(msg);
				
        SysFreeString(reason);
	}
    else
    {
        m_debug = "Building Tree View...";
	    UpdateData(FALSE);
        UpdateWindow();

	    pDoc->get_documentElement(&element);

	    ht = m_tree.InsertItem("#document",0,0,TVI_ROOT,TVI_LAST);		

	    int count = MakeTree(element,ht);

	    m_tree.Expand(ht,TVE_EXPAND);
	    ht = m_tree.GetChildItem( ht );
	    m_tree.Expand(ht,TVE_EXPAND);
        rc = 1;

		sprintf(msg, "Loaded %d XML nodes.", count);
        m_debug = msg;
	    UpdateData(FALSE);
        UpdateWindow();
    }

cleanup:	
    UpdateData(FALSE);
	return rc;
}


int CXMLTreeDlg::MakeTree(MSXML::IXMLDOMElement *node, HTREEITEM ht)
{
	MSXML::IXMLDOMNodeList	*childs    = NULL; 
	MSXML::IXMLDOMNode		*childnode = NULL;
	
	BSTR        s = NULL;
	long        i;
	HTREEITEM	ht2;

    // Note this builds the entire tree view.  It would
    // be much more efficient to build only the visible
    // part of the tree and expand the child elements on demand.
    // But that is left as an exercise for the reader.

	node->get_nodeTypeString(&s);

    int result = 1;

    if(!wcscmp(s,L"element"))
	{
		node->get_nodeName(&s);
		ht2 = m_tree.InsertItem(CString(s),1,1,ht,TVI_LAST);	
	} else if(!wcscmp(s,L"text")){
		node->get_text(&s);
		ht2 = m_tree.InsertItem(CString(s),2,2,ht,TVI_LAST);	
	} else {
        // Note: There are more node types than this.
        // Correctly displaying all nodes types is left
        // as an exercise for the reader.
		node->get_nodeName(&s);
		ht2 = m_tree.InsertItem(CString(s),3,3,ht,TVI_LAST);	
	}
	
	if(node->hasChildNodes())
	{
		node->get_childNodes(&childs);
		for(i=0;i<childs->Getlength();i++)
		{
			childs->get_item(i,&childnode);
			result += MakeTree((MSXML::IXMLDOMElement *)childnode,ht2);
		}
	}
    return result;
}

void CXMLTreeDlg::OnOK()
{
    OnLoad();
}

void CXMLTreeDlg::OnChangeFilename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CXMLTreeDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog	dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"XML Files (*.xml)|*.xml|All Files (*.*)|*.*||",this);

	if (IDOK == dlg.DoModal())
    {
    	m_filename = dlg.GetPathName();
	    UpdateData(FALSE);
        LoadXML(m_filename);
    }
}
