VERSION 5.00
Begin VB.Form frmAddEmployee 
   Caption         =   "Add Employee"
   ClientHeight    =   4890
   ClientLeft      =   5025
   ClientTop       =   2685
   ClientWidth     =   8010
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   4890
   ScaleWidth      =   8010
   Begin VB.TextBox txtPostalCode 
      Height          =   315
      Left            =   3113
      MaxLength       =   10
      TabIndex        =   13
      Top             =   3518
      Width           =   3885
   End
   Begin VB.TextBox txtRegion 
      Height          =   315
      Left            =   3113
      MaxLength       =   15
      TabIndex        =   11
      Top             =   2958
      Width           =   3885
   End
   Begin VB.TextBox txtCity 
      Height          =   315
      Left            =   3113
      MaxLength       =   15
      TabIndex        =   9
      Top             =   2398
      Width           =   3885
   End
   Begin VB.TextBox txtAddress 
      Height          =   315
      Left            =   3113
      MaxLength       =   60
      TabIndex        =   7
      Top             =   1838
      Width           =   3885
   End
   Begin VB.TextBox txtTitle 
      Height          =   315
      Left            =   3113
      MaxLength       =   30
      TabIndex        =   5
      Top             =   1278
      Width           =   3885
   End
   Begin VB.TextBox txtLastName 
      Height          =   315
      Left            =   3113
      MaxLength       =   20
      TabIndex        =   3
      Top             =   718
      Width           =   3885
   End
   Begin VB.TextBox txtFirstName 
      Height          =   315
      Left            =   3113
      MaxLength       =   10
      TabIndex        =   1
      Top             =   158
      Width           =   3885
   End
   Begin VB.CommandButton cmdSaveRecord 
      Caption         =   "&Save Record"
      Default         =   -1  'True
      Height          =   525
      Left            =   1013
      TabIndex        =   14
      Top             =   4208
      Width           =   1845
   End
   Begin VB.CommandButton cmdExitProgram 
      Caption         =   "&Close "
      Height          =   525
      Left            =   5153
      TabIndex        =   15
      Top             =   4208
      Width           =   1845
   End
   Begin VB.Label Label7 
      Caption         =   "Postal Code"
      Height          =   315
      Left            =   1013
      TabIndex        =   12
      Top             =   3518
      Width           =   1845
   End
   Begin VB.Label Label6 
      Caption         =   "Region"
      Height          =   315
      Left            =   1013
      TabIndex        =   10
      Top             =   2958
      Width           =   1845
   End
   Begin VB.Label Label5 
      Caption         =   "City"
      Height          =   315
      Left            =   1013
      TabIndex        =   8
      Top             =   2398
      Width           =   1845
   End
   Begin VB.Label Label4 
      Caption         =   "Address"
      Height          =   315
      Left            =   1013
      TabIndex        =   6
      Top             =   1838
      Width           =   1845
   End
   Begin VB.Label Label3 
      Caption         =   "Title"
      Height          =   315
      Left            =   1013
      TabIndex        =   4
      Top             =   1278
      Width           =   1845
   End
   Begin VB.Label Label2 
      Caption         =   "Last Name"
      Height          =   315
      Left            =   1013
      TabIndex        =   2
      Top             =   718
      Width           =   1845
   End
   Begin VB.Label Label1 
      Caption         =   "First Name"
      Height          =   315
      Left            =   1013
      TabIndex        =   0
      Top             =   158
      Width           =   1845
   End
End
Attribute VB_Name = "frmAddEmployee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' declare a form global variable for the recordset.
Dim gRS As ADODB.Recordset


Private Sub cmdExitProgram_Click()
    Me.Hide
    Unload Me
End Sub

Private Sub cmdSaveRecord_Click()
    
    gRS.AddNew
    
    gRS.Fields("FirstName") = Trim(txtFirstName) & ""
    gRS.Fields("LastName") = Trim(txtLastName) & ""
    gRS.Fields("Title") = Trim(txtTitle) & ""
    gRS.Fields("Address") = Trim(txtAddress) & ""
    gRS.Fields("City") = Trim(txtCity) & ""
    gRS.Fields("Region") = Trim(txtRegion) & ""
    gRS.Fields("PostalCode") = Trim(txtPostalCode) & ""
    
    gRS.Update
    ' Show the user the value for the new Employee's ID...
    MsgBox "New Employee's ID = " & gRS.Fields("EmployeeID").Value
    Me.Hide
    Unload Me
    
End Sub


 
Private Sub Form_Initialize()
    txtFirstName = ""
    txtLastName = ""
    txtTitle = ""
    txtAddress = ""
    txtCity = ""
    txtRegion = ""
    txtPostalCode = ""

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
    Exit Sub
    
trap:
    MsgBox "Error creating recordset for employee record"
     
    
    
End Sub
