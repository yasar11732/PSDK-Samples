VERSION 5.00
Begin VB.Form frmDeleteEmployee 
   Caption         =   "Delete Employee"
   ClientHeight    =   5730
   ClientLeft      =   4620
   ClientTop       =   7890
   ClientWidth     =   8610
   LinkTopic       =   "Form1"
   ScaleHeight     =   5730
   ScaleWidth      =   8610
   Begin VB.TextBox txtEmployeeID 
      Height          =   315
      Left            =   2865
      MaxLength       =   7
      TabIndex        =   8
      Top             =   383
      Width           =   3885
   End
   Begin VB.CommandButton cmdFindEmployee 
      Caption         =   "&Find Employee"
      Height          =   405
      Left            =   7035
      TabIndex        =   9
      Top             =   383
      Width           =   1365
   End
   Begin VB.CommandButton cmdDeleteEmployee 
      Caption         =   "Delete Employee"
      Height          =   405
      Left            =   2265
      TabIndex        =   10
      Top             =   4943
      Width           =   1365
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   405
      Left            =   4875
      TabIndex        =   11
      Top             =   4943
      Width           =   1365
   End
   Begin VB.Label lblLastName 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   18
      Top             =   1497
      Width           =   3885
   End
   Begin VB.Label lblTitle 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   " "
      Height          =   315
      Left            =   2865
      TabIndex        =   17
      Top             =   2054
      Width           =   3885
   End
   Begin VB.Label lblAddress 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   16
      Top             =   2611
      Width           =   3885
   End
   Begin VB.Label lblCity 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   15
      Top             =   3168
      Width           =   3885
   End
   Begin VB.Label lblRegion 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   14
      Top             =   3725
      Width           =   3885
   End
   Begin VB.Label lblPostalCode 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   13
      Top             =   4283
      Width           =   3885
   End
   Begin VB.Label lblFirstName 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Height          =   315
      Left            =   2865
      TabIndex        =   12
      Top             =   940
      Width           =   3885
   End
   Begin VB.Label Label1 
      Caption         =   "Employee ID"
      Height          =   315
      Left            =   765
      TabIndex        =   7
      Top             =   390
      Width           =   1845
   End
   Begin VB.Label Label7 
      Caption         =   "Postal Code"
      Height          =   315
      Left            =   765
      TabIndex        =   6
      Top             =   4290
      Width           =   1845
   End
   Begin VB.Label Label6 
      Caption         =   "Region"
      Height          =   315
      Left            =   765
      TabIndex        =   5
      Top             =   3735
      Width           =   1845
   End
   Begin VB.Label Label5 
      Caption         =   "City"
      Height          =   315
      Left            =   765
      TabIndex        =   4
      Top             =   3165
      Width           =   1845
   End
   Begin VB.Label Label4 
      Caption         =   "Address"
      Height          =   315
      Left            =   765
      TabIndex        =   3
      Top             =   2610
      Width           =   1845
   End
   Begin VB.Label Label3 
      Caption         =   "Title"
      Height          =   315
      Left            =   765
      TabIndex        =   2
      Top             =   2055
      Width           =   1845
   End
   Begin VB.Label Label2 
      Caption         =   "Last Name"
      Height          =   315
      Left            =   765
      TabIndex        =   1
      Top             =   1485
      Width           =   1845
   End
   Begin VB.Label Label8 
      Caption         =   "First Name"
      Height          =   315
      Left            =   765
      TabIndex        =   0
      Top             =   930
      Width           =   1845
   End
End
Attribute VB_Name = "frmDeleteEmployee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim gRS As ADODB.Recordset


Private Sub cmdClose_Click()
    If Not gRS Is Nothing Then
        Set gRS = Nothing
    End If
    Me.Hide
    Unload Me
End Sub

Private Sub cmdDeleteEmployee_Click()

On Error GoTo trap

    If MsgBox("Delete this Employee", vbYesNo) = vbYes Then
        gRS.Delete
        MsgBox "Record delete."
        Call Form_Initialize
        txtEmployeeID.SetFocus
    End If
    
    Exit Sub
trap:
    If Err.Number = -2147217873 Then
        MsgBox "Delete failed because of a key constraint -- record not deleted."
        Err.Clear
        Exit Sub
    End If
    MsgBox "Error: (" & Err.Number & ") -- " & Err.Description
        
End Sub

Private Sub cmdFindEmployee_Click()

    Dim cmd  As New ADODB.Command
    Dim EmpID As Long
    Set cmd = New ADODB.Command
    Set cmd.ActiveConnection = gCn
    Set gRS = New ADODB.Recordset
    
    If Len(Trim(txtEmployeeID)) < 1 Then
        MsgBox "Must enter a number for the employee to delete"
        txtEmployeeID.SetFocus
        Exit Sub
    End If
    
    EmpID = CLng(Val(txtEmployeeID))
    If EmpID < 1 Then
        MsgBox "EmployeeID must be greater than zero"
        txtEmployeeID.SetFocus
        Exit Sub
    End If
    
    
    cmd.NamedParameters = True
  
    cmd.CommandText = "Select * from Employees where (EmployeeID = ?)"
    cmd.Parameters(0) = EmpID
    
    
    Set gRS.ActiveConnection = gCn
    gRS.CursorLocation = adUseClient
    gRS.CursorType = adOpenStatic
    gRS.LockType = adLockOptimistic
    gRS.Open cmd
    If gRS.RecordCount = 1 Then
        lblFirstName.Caption = gRS.Fields("FirstName") & ""
        lblLastName.Caption = gRS.Fields("LastName") & ""
        lblTitle.Caption = gRS.Fields("Title") & ""
        lblAddress.Caption = gRS.Fields("Address") & ""
        lblCity.Caption = gRS.Fields("City") & ""
        lblRegion.Caption = gRS.Fields("Region") & ""
        lblPostalCode.Caption = gRS.Fields("PostalCode") & ""
        cmdDeleteEmployee.Enabled = True
     Else
        MsgBox "Employee not found, enter another Employee ID"
        Exit Sub
     End If
     
End Sub

Private Sub Form_Initialize()
    txtEmployeeID = ""
    lblFirstName.Caption = ""
    lblLastName.Caption = ""
    lblTitle.Caption = ""
    lblAddress.Caption = ""
    lblCity.Caption = ""
    lblRegion.Caption = ""
    lblPostalCode.Caption = ""
    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)
    cmdDeleteEmployee.Enabled = False
End Sub

Private Sub Form_Load()
    Call Form_Initialize
End Sub
