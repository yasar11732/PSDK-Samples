VERSION 5.00
Begin VB.Form frmBrowse 
   Caption         =   "Browse Recordset"
   ClientHeight    =   5730
   ClientLeft      =   5280
   ClientTop       =   4935
   ClientWidth     =   8580
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   5730
   ScaleWidth      =   8580
   Begin VB.TextBox txtEmployeeID 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   7
      TabIndex        =   1
      Text            =   " "
      Top             =   345
      Width           =   3885
   End
   Begin VB.TextBox txtPostalCode 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   10
      TabIndex        =   15
      Top             =   4245
      Width           =   3885
   End
   Begin VB.TextBox txtRegion 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   15
      TabIndex        =   13
      Top             =   3690
      Width           =   3885
   End
   Begin VB.TextBox txtCity 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   15
      TabIndex        =   11
      Top             =   3120
      Width           =   3885
   End
   Begin VB.TextBox txtAddress 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   60
      TabIndex        =   9
      Top             =   2565
      Width           =   3885
   End
   Begin VB.TextBox txtTitle 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   30
      TabIndex        =   7
      Top             =   2010
      Width           =   3885
   End
   Begin VB.TextBox txtLastName 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   20
      TabIndex        =   5
      Top             =   1440
      Width           =   3885
   End
   Begin VB.TextBox txtFirstName 
      Height          =   315
      Left            =   3398
      Locked          =   -1  'True
      MaxLength       =   10
      TabIndex        =   3
      Top             =   885
      Width           =   3885
   End
   Begin VB.CommandButton cmdMoveNext 
      Caption         =   "Move &Next"
      Height          =   405
      Left            =   3607
      TabIndex        =   18
      Top             =   4950
      Width           =   1365
   End
   Begin VB.CommandButton cmdMoveLast 
      Caption         =   "Move &Last"
      Height          =   405
      Left            =   5189
      TabIndex        =   19
      Top             =   4950
      Width           =   1365
   End
   Begin VB.CommandButton cmdMoveFirst 
      Caption         =   "Move &First"
      Height          =   405
      Left            =   443
      TabIndex        =   16
      Top             =   4950
      Width           =   1365
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   405
      Left            =   6773
      TabIndex        =   20
      Top             =   4950
      Width           =   1365
   End
   Begin VB.CommandButton cmdMovePrev 
      Caption         =   "Move &Previous"
      Height          =   405
      Left            =   2025
      TabIndex        =   17
      Top             =   4950
      Width           =   1365
   End
   Begin VB.Label Label1 
      Caption         =   "Employee ID:"
      Height          =   315
      Left            =   1305
      TabIndex        =   0
      Top             =   345
      Width           =   1845
   End
   Begin VB.Label Label7 
      Caption         =   "Postal Code"
      Height          =   315
      Left            =   1305
      TabIndex        =   14
      Top             =   4245
      Width           =   1845
   End
   Begin VB.Label Label6 
      Caption         =   "Region"
      Height          =   315
      Left            =   1305
      TabIndex        =   12
      Top             =   3690
      Width           =   1845
   End
   Begin VB.Label Label5 
      Caption         =   "City"
      Height          =   315
      Left            =   1305
      TabIndex        =   10
      Top             =   3120
      Width           =   1845
   End
   Begin VB.Label Label4 
      Caption         =   "Address"
      Height          =   315
      Left            =   1305
      TabIndex        =   8
      Top             =   2565
      Width           =   1845
   End
   Begin VB.Label Label3 
      Caption         =   "Title"
      Height          =   315
      Left            =   1305
      TabIndex        =   6
      Top             =   2010
      Width           =   1845
   End
   Begin VB.Label Label2 
      Caption         =   "Last Name"
      Height          =   315
      Left            =   1305
      TabIndex        =   4
      Top             =   1440
      Width           =   1845
   End
   Begin VB.Label Label8 
      Caption         =   "First Name"
      Height          =   315
      Left            =   1305
      TabIndex        =   2
      Top             =   885
      Width           =   1845
   End
End
Attribute VB_Name = "frmBrowse"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mRs As ADODB.Recordset

Private Sub cmdClose_Click()
    mRs.Close
    Set mRs = Nothing
    Me.Hide
    Unload Me
End Sub

Private Sub cmdMoveFirst_Click()
    ' this test may seem like it doesn't make sencse but we are testing
    ' for an empty recordset with no records...  If we attempt to move
    ' within the recordset an error would be generated.
    mRs.MoveFirst
    DisplayRecord
End Sub

Private Sub cmdMoveLast_Click()
    ' this test may seem like it doesn't make sencse but we are testing
    ' for an empty recordset with no records...  If we attempt to move
    ' within the recordset an error would be generated.
    If mRs.EOF <> True And mRs.BOF <> True Then
        mRs.MoveLast
    End If
    DisplayRecord
End Sub

Private Sub cmdMoveNext_Click()
       
    ' as we move through the recordset we will test to make sure if we hit EOF
    ' we move to the last record.  thus we should always point to a valid record
    If mRs.EOF <> True Then
        mRs.MoveNext
        If mRs.EOF = True Then
            mRs.MoveLast
        End If
    Else
        mRs.MoveNext
    End If
    
    DisplayRecord
    
End Sub

Private Sub cmdMovePrev_Click()
       
    ' as we move through the recordset we will test to make sure if we hit BOF
    ' we move to the last record.  thus we should always point to a valid record
    If mRs.BOF <> True Then
        mRs.MovePrevious
        If mRs.BOF = True Then
            mRs.MoveFirst
        End If
    Else
        mRs.MoveFirst
    End If
    
    DisplayRecord
    
End Sub

Private Sub Form_Load()

    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)
    Set mRs = New ADODB.Recordset
    mRs.ActiveConnection = gCn
    mRs.CursorLocation = adUseServer
    mRs.CursorType = adOpenStatic
    mRs.LockType = adLockReadOnly
    mRs.Open "Select * from Employees order by EmployeeID"
    
End Sub


Private Sub DisplayRecord()
    ' simple test to make sure the recordset is open and not at eof or bof
    ' so that we know a valid record is pointed to before displaying the values
    If mRs.State <> adStateOpen Or mRs.EOF = True Or mRs.BOF = True Then
        txtEmployeeID = ""
        txtFirstName = ""
        txtLastName = ""
        txtTitle = ""
        txtAddress = ""
        txtCity = ""
        txtRegion = ""
        txtPostalCode = ""
    Else
        ' to avoid the special handling code for null fields we
        ' concatinate a zero length string to the end of each field
        txtEmployeeID = mRs.Fields("EmployeeID").Value & ""
        txtFirstName = mRs.Fields("FirstName").Value & ""
        txtLastName = mRs.Fields("LastName").Value & ""
        txtTitle = mRs.Fields("Title").Value & ""
        txtAddress = mRs.Fields("Address").Value & ""
        txtCity = mRs.Fields("City").Value & ""
        txtRegion = mRs.Fields("Region").Value & ""
        txtPostalCode = mRs.Fields("PostalCode").Value & ""
    End If
End Sub
