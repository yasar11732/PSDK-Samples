VERSION 5.00
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmListEmployees 
   Caption         =   "Employee List"
   ClientHeight    =   5475
   ClientLeft      =   5325
   ClientTop       =   5430
   ClientWidth     =   8445
   LinkTopic       =   "Form1"
   ScaleHeight     =   5475
   ScaleWidth      =   8445
   Begin VB.CommandButton cmdCloseScreen 
      Caption         =   "&Close"
      Height          =   375
      Left            =   5970
      TabIndex        =   4
      Top             =   4830
      Width           =   2055
   End
   Begin VB.CommandButton cmdUpdateSort 
      Caption         =   "&Update Sort"
      Height          =   375
      Left            =   3270
      TabIndex        =   3
      Top             =   4830
      Width           =   2055
   End
   Begin MSDataGridLib.DataGrid grdEmployees 
      Height          =   4185
      Left            =   270
      TabIndex        =   0
      Top             =   150
      Width           =   7995
      _ExtentX        =   14102
      _ExtentY        =   7382
      _Version        =   393216
      HeadLines       =   1
      RowHeight       =   15
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
         Size            =   8.25
         Charset         =   0
         Weight          =   400
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
   Begin VB.ComboBox cboSortField 
      Height          =   315
      ItemData        =   "frmListEmployees.frx":0000
      Left            =   270
      List            =   "frmListEmployees.frx":001C
      TabIndex        =   2
      Top             =   4800
      Width           =   2655
   End
   Begin VB.Label Label1 
      Caption         =   "Available Sort Fields"
      Height          =   225
      Left            =   270
      TabIndex        =   1
      Top             =   4530
      Width           =   2655
   End
End
Attribute VB_Name = "frmListEmployees"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim gRS As ADODB.Recordset

Private Sub cmdCloseScreen_Click()
    If Not gRS Is Nothing Then
        gRS.Close
    End If
    Set gRS = Nothing
    Me.Hide
    Unload Me
End Sub

Private Sub cmdUpdateSort_Click()
    gRS.Sort = cboSortField.Text
    Set grdEmployees.DataSource = gRS
End Sub

Private Sub Form_Load()
    
    Set gRS = New ADODB.Recordset
    Set gRS.ActiveConnection = gCn
    gRS.CursorLocation = adUseClient
    gRS.CursorType = adOpenStatic
    gRS.LockType = adLockReadOnly
    gRS.Open "Select EmployeeID, FirstName, LastName, Title, Address, City, Region, PostalCode from Employees"
    Set grdEmployees.DataSource = gRS
    cboSortField.ListIndex = 0
    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)

End Sub
