VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Login - XML Order Application"
   ClientHeight    =   1548
   ClientLeft      =   2832
   ClientTop       =   3480
   ClientWidth     =   3756
   Icon            =   "frmLogin.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   912.837
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtUserName 
      Height          =   345
      Left            =   1290
      TabIndex        =   1
      Text            =   "Guest"
      Top             =   135
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   5
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   3
      Text            =   "password"
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      Caption         =   "&User Name:"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Password:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
 
Option Explicit

Private Sub cmdCancel_Click()
    'hide the form
    Me.Hide
    
    'unload the login form
    Unload frmLogin
End Sub

Private Sub cmdOK_Click()
    Dim obj_usersDB As New CUsersDB
    Dim obj_log As New CLogDB
    Dim udb_result As UDB_Results
    Dim str_username As String
    Dim str_password As String
    
    'get the username and password
    str_username = txtUserName.Text
    str_password = txtPassword.Text
    
    'verify the username and password are valid
    udb_result = obj_usersDB.VerifyLogin(str_username, str_password)
    If udb_result = udb_Success Then
        'add a log entry
        Call obj_log.AddLogEntry(str_username, Date)
    
        'setup the status bar information and show the main form
        frmMDIMain.StatusBar1.Panels.Item(1).Text = "User: " & txtUserName.Text
        frmMDIMain.Show
                    
        'unload the login form
        Unload frmLogin
    ElseIf udb_result = udb_BadPassword Then
        'display an error message box
        MsgBox "Invalid Password, try again!", , "Login"
        
        'set the focus back to login
        txtPassword.SetFocus
    Else
        'display an error message box
        MsgBox "Invalid Username, try again!", , "Login"
        
        'set the focus back to login
        txtUserName.SetFocus
    End If
End Sub

Private Sub txtPassword_GotFocus()
    'select all the text in the textbox
    txtPassword.SelStart = 0
    txtPassword.SelLength = Len(txtPassword.Text)
End Sub

Private Sub txtUserName_gotfocus()
    'select all the text in the textbox
    txtUserName.SelStart = 0
    txtUserName.SelLength = Len(txtUserName.Text)
End Sub
