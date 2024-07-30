VERSION 5.00
Begin VB.Form frmEditEmployee 
   Caption         =   "Edit Employee"
   ClientHeight    =   5760
   ClientLeft      =   5400
   ClientTop       =   5925
   ClientWidth     =   8655
   LinkTopic       =   "Form1"
   ScaleHeight     =   5760
   ScaleWidth      =   8655
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   405
      Left            =   4950
      TabIndex        =   18
      Top             =   4890
      Width           =   1365
   End
   Begin VB.CommandButton cmdSaveUpdate 
      Caption         =   "&Save Changes"
      Height          =   405
      Left            =   2340
      TabIndex        =   17
      Top             =   4890
      Width           =   1365
   End
   Begin VB.TextBox txtFirstName 
      Height          =   315
      Left            =   2940
      MaxLength       =   10
      TabIndex        =   4
      Top             =   870
      Width           =   3885
   End
   Begin VB.TextBox txtLastName 
      Height          =   315
      Left            =   2940
      MaxLength       =   20
      TabIndex        =   6
      Top             =   1425
      Width           =   3885
   End
   Begin VB.TextBox txtTitle 
      Height          =   315
      Left            =   2940
      MaxLength       =   30
      TabIndex        =   8
      Top             =   1995
      Width           =   3885
   End
   Begin VB.TextBox txtAddress 
      Height          =   315
      Left            =   2940
      MaxLength       =   60
      TabIndex        =   10
      Top             =   2550
      Width           =   3885
   End
   Begin VB.TextBox txtCity 
      Height          =   315
      Left            =   2940
      MaxLength       =   15
      TabIndex        =   12
      Top             =   3105
      Width           =   3885
   End
   Begin VB.TextBox txtRegion 
      Height          =   315
      Left            =   2940
      MaxLength       =   15
      TabIndex        =   14
      Top             =   3675
      Width           =   3885
   End
   Begin VB.TextBox txtPostalCode 
      Height          =   315
      Left            =   2940
      MaxLength       =   10
      TabIndex        =   16
      Top             =   4230
      Width           =   3885
   End
   Begin VB.CommandButton cmdFindEmployee 
      Caption         =   "&Find Employee"
      Height          =   405
      Left            =   7110
      TabIndex        =   2
      Top             =   270
      Width           =   1365
   End
   Begin VB.TextBox txtEmployeeID 
      Height          =   315
      Left            =   2940
      MaxLength       =   7
      TabIndex        =   1
      Top             =   330
      Width           =   3885
   End
   Begin VB.Label Label8 
      Caption         =   "First Name"
      Height          =   315
      Left            =   840
      TabIndex        =   3
      Top             =   870
      Width           =   1845
   End
   Begin VB.Label Label2 
      Caption         =   "Last Name"
      Height          =   315
      Left            =   840
      TabIndex        =   5
      Top             =   1425
      Width           =   1845
   End
   Begin VB.Label Label3 
      Caption         =   "Title"
      Height          =   315
      Left            =   840
      TabIndex        =   7
      Top             =   1995
      Width           =   1845
   End
   Begin VB.Label Label4 
      Caption         =   "Address"
      Height          =   315
      Left            =   840
      TabIndex        =   9
      Top             =   2550
      Width           =   1845
   End
   Begin VB.Label Label5 
      Caption         =   "City"
      Height          =   315
      Left            =   840
      TabIndex        =   11
      Top             =   3105
      Width           =   1845
   End
   Begin VB.Label Label6 
      Caption         =   "Region"
      Height          =   315
      Left            =   840
      TabIndex        =   13
      Top             =   3675
      Width           =   1845
   End
   Begin VB.Label Label7 
      Caption         =   "Postal Code"
      Height          =   315
      Left            =   840
      TabIndex        =   15
      Top             =   4230
      Width           =   1845
   End
   Begin VB.Label Label1 
      Caption         =   "Employee ID:"
      Height          =   315
      Left            =   840
      TabIndex        =   0
      Top             =   330
      Width           =   1845
   End
End
Attribute VB_Name = "frmEditEmployee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim gRS As ADODB.Recordset


Private Sub cmdClose_Click()
    gRS.Close
    Set gRS = Nothing
    Me.Hide
    Unload Me
End Sub

Private Sub cmdFindEmployee_Click()

    Dim EmpID As Long
    ' verify an enter was added for the EmployeeID
    If Len(Trim(txtEmployeeID)) < 1 Then
        MsgBox "Employee ID must be entered "
        txtEmployeeID.SetFocus
        Exit Sub
    End If
    
    ' now we test the id is numeric and > 0
    EmpID = CLng(Val(txtEmployeeID))
    If EmpID < 1 Then
        MsgBox "Employee ID must be numeric and greater than zero"
        Exit Sub
    End If
        
        
    gRS.Filter = "EmployeeID=" & EmpID
    
    ' in case the user enter "3f" we assume the value for the
    ' EmployeeID is 3, so we set the fix-ed up value back into
    ' the text box for the employee id.
    
    txtEmployeeID = EmpID
    If gRS.RecordCount = 1 Then
        txtFirstName = gRS.Fields("FirstName") & ""
        txtLastName = gRS.Fields("LastName") & ""
        txtTitle = gRS.Fields("Title") & ""
        txtAddress = gRS.Fields("Address") & ""
        txtCity = gRS.Fields("City") & ""
        txtRegion = gRS.Fields("Region") & ""
        txtPostalCode = gRS.Fields("PostalCode") & ""
        txtEmployeeID.Locked = True
        txtFirstName.SetFocus
    Else
        MsgBox "Employee not found, enter another Employee ID"
        Exit Sub
    End If
            
    cmdSaveUpdate.Enabled = True
    
End Sub


Private Sub cmdSaveUpdate_Click()
    
    gRS.Fields("FirstName") = Trim(txtFirstName) & ""
    gRS.Fields("LastName") = Trim(txtLastName) & ""
    gRS.Fields("Title") = Trim(txtTitle) & ""
    gRS.Fields("Address") = Trim(txtAddress) & ""
    gRS.Fields("City") = Trim(txtCity) & ""
    gRS.Fields("Region") = Trim(txtRegion) & ""
    gRS.Fields("PostalCode") = Trim(txtPostalCode) & ""
    
    gRS.Update
    Call Form_Initialize
    txtEmployeeID.SetFocus
        
End Sub

Private Sub Form_Initialize()
    txtEmployeeID = ""
    txtFirstName = ""
    txtLastName = ""
    txtTitle = ""
    txtAddress = ""
    txtCity = ""
    txtRegion = ""
    txtPostalCode = ""
    txtEmployeeID.Locked = False
    cmdSaveUpdate.Enabled = False

End Sub

Private Sub Form_Load()
       
On Error GoTo trap
    ' intantiate the module recrodset
    Set gRS = New ADODB.Recordset
    With gRS
         Set .ActiveConnection = gCn
        .CursorLocation = adUseClient
        .CursorType = adOpenStatic
        .LockType = adLockOptimistic
        .Open "Select * from Employees"
    End With
    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)
    cmdSaveUpdate.Enabled = False
    Exit Sub
    
trap:
    MsgBox "Error creating recordset for employee record"

End Sub

