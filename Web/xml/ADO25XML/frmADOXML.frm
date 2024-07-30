VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmADOXML 
   Caption         =   "ADO 2.5 XML Support"
   ClientHeight    =   6990
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10140
   LinkTopic       =   "Form1"
   ScaleHeight     =   6990
   ScaleWidth      =   10140
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnClearRecordset 
      Caption         =   "Clear"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8760
      TabIndex        =   9
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton btnClear 
      Caption         =   "Clear"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   8760
      TabIndex        =   8
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton btnFilter 
      Caption         =   "Apply"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   7440
      TabIndex        =   7
      Top             =   2880
      Width           =   1215
   End
   Begin VB.TextBox txtFilter 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   840
      TabIndex        =   5
      Top             =   2880
      Width           =   6495
   End
   Begin VB.TextBox txtXML 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   11.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2895
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   4
      Top             =   3960
      Width           =   9855
   End
   Begin VB.CommandButton btnXMLToADO 
      Caption         =   "XML --> ADO"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1800
      TabIndex        =   3
      Top             =   3360
      Width           =   1575
   End
   Begin VB.CommandButton btnADOToXML 
      Caption         =   "ADO --> XML"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   3360
      Width           =   1575
   End
   Begin VB.CommandButton btnRetrieve 
      Caption         =   "Retrieve"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7440
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin MSDataGridLib.DataGrid grdRecordset 
      Bindings        =   "frmADOXML.frx":0000
      Height          =   2055
      Left            =   120
      TabIndex        =   0
      Top             =   720
      Width           =   9855
      _ExtentX        =   17383
      _ExtentY        =   3625
      _Version        =   393216
      HeadLines       =   1
      RowHeight       =   19
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1033
            SubFormatType   =   0
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1033
            SubFormatType   =   0
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin MSAdodcLib.Adodc dsoRecordset 
      Height          =   330
      Left            =   120
      Top             =   240
      Width           =   7215
      _ExtentX        =   12726
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   8
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   1
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   ""
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   ""
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   ""
      Caption         =   "ADO Recordset"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin VB.Label Label1 
      Caption         =   "Filter:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   2880
      Width           =   735
   End
End
Attribute VB_Name = "frmADOXML"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub btnADOToXML_Click()
    ' Build an XML string from an ADO recordset
    
    ' Create an stream object and a recordset object
    ' A Stream object provides the means to read, write, and manage the
    ' binary stream of bytes or text that comprise a file or message stream.
    Dim st As New ADODB.Stream
    Dim rs As ADODB.Recordset
    
    ' Point rs to the recordset belonging to the ADODC control on the form.
    Set rs = dsoRecordset.Recordset
    
    ' Save the contents of this recordset into the stream as XML.
    rs.Save st, adPersistXML
    
    ' Display the text in the stream in a textbox on the form.
    txtXML = st.ReadText
   

End Sub

Private Sub btnClear_Click()
    On Error Resume Next

    ' Clear the filter in the data control's recordset.
    dsoRecordset.Recordset.Filter = "productid <> 0"
    
    If Err.Number <> 0 Then
        MsgBox Err.Description
    End If

End Sub

Private Sub btnClearRecordset_Click()
    On Error Resume Next

    ' Close the recordset that belongs to the data control.
    dsoRecordset.Recordset.Close
    ' Empty the filter text box and disable the buttons.
    txtFilter.Text = ""
    btnADOToXML.Enabled = False
    If txtXML = "" Then
        btnXMLToADO.Enabled = False
    End If

End Sub

Private Sub btnFilter_Click()
    On Error Resume Next

    ' Apply the specified filter to the data control's recordset.
    dsoRecordset.Recordset.Filter = txtFilter.Text
    
    If Err.Number <> 0 Then
        MsgBox Err.Description
    End If

End Sub

Private Sub btnRetrieve_Click()
    ' Create ADO objects.
    Dim conn As New ADODB.Connection
    Dim rs As New ADODB.Recordset
    Dim cmd As New ADODB.Command

    ' Open a connection using a client cursor.
    conn.CursorLocation = adUseClient
    conn.ConnectionString = "Provider=SQLOLEDB;Database=Northwind;uid=sa;pwd=;"
    conn.Open
    
    ' Set options on the Command object.
    cmd.CommandText = "Select * from Products"
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = conn

    ' Open a recordset and then disconnect.
    rs.CursorType = adOpenStatic
    rs.LockType = adLockReadOnly
    rs.Open cmd
    Set rs.ActiveConnection = Nothing
       
    ' Close the connection and release 2 of the ADO objects.
    conn.Close
    Set conn = Nothing
    Set cmd = Nothing
    
    ' Assign the recordset to the ADO data control on the form.
    Set dsoRecordset.Recordset = rs

    ' Enable buttons
    btnADOToXML.Enabled = True
    btnXMLToADO.Enabled = True

End Sub

Private Sub btnXMLToADO_Click()
    ' Build an ADO recordset from an XML string
    
    On Error Resume Next
    
    ' Create an stream object and a recordset object
    ' A Stream object provides the means to read, write, and manage the
    ' binary stream of bytes or text that comprise a file or message stream.
    Dim rs As New ADODB.Recordset
    Dim st As New ADODB.Stream
    
    ' Open the Stream object.
    st.Open
    ' Write the contents of the textbox into the Stream.
    st.WriteText txtXML.Text
    ' Return to the beginning of the Stream.
    st.Position = 0
    ' Open the recordset based on the XML in the Stream.
    ' In ADO 2.1 you can open a recordset based on XML that is
    ' persisted to disk using rs.Save adPersistXML. In ADO 2.5 you
    ' can use the Stream object to work with XML without having to
    ' write it to disk first.
    rs.Open st

    If Err.Number <> 0 Then
        MsgBox Err.Description
        Exit Sub
    End If

    ' Assign the recordset to the ADO data control on the form.
    Set dsoRecordset.Recordset = rs
    
    btnADOToXML.Enabled = True

End Sub
