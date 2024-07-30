VERSION 5.00
Begin VB.Form frmDbLogIn 
   Caption         =   "ADO Simple Database Sample"
   ClientHeight    =   3840
   ClientLeft      =   6135
   ClientTop       =   4965
   ClientWidth     =   7080
   LinkTopic       =   "Form2"
   ScaleHeight     =   3840
   ScaleWidth      =   7080
   Begin VB.TextBox Text1 
      BackColor       =   &H00800080&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   705
      Left            =   -30
      MultiLine       =   -1  'True
      TabIndex        =   7
      Text            =   "frmDbLogIn.frx":0000
      Top             =   3120
      Width           =   7230
   End
   Begin VB.CommandButton cmdConnectToDb 
      Caption         =   "Log-on to Server"
      Default         =   -1  'True
      Height          =   585
      Left            =   2700
      TabIndex        =   6
      Top             =   2370
      Width           =   1815
   End
   Begin VB.TextBox txtPwd 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   2460
      MaxLength       =   15
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   1860
      Width           =   4005
   End
   Begin VB.TextBox txtUid 
      Height          =   315
      Left            =   2460
      MaxLength       =   15
      TabIndex        =   3
      Top             =   1080
      Width           =   4005
   End
   Begin VB.TextBox txtServer 
      Height          =   315
      Left            =   2460
      TabIndex        =   1
      Top             =   300
      Width           =   4005
   End
   Begin VB.Label Label3 
      Caption         =   "User ID"
      Height          =   315
      Left            =   330
      TabIndex        =   2
      Top             =   1080
      Width           =   1725
   End
   Begin VB.Label Label2 
      Caption         =   "Server"
      Height          =   315
      Left            =   330
      TabIndex        =   0
      Top             =   330
      Width           =   1725
   End
   Begin VB.Label Label1 
      Caption         =   "Password"
      Height          =   315
      Left            =   330
      TabIndex        =   4
      Top             =   1830
      Width           =   1725
   End
End
Attribute VB_Name = "frmDbLogIn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdConnectToDb_Click()
    Set gCn = New ADODB.Connection
    gCn.ConnectionString = "Provider=SQLOLEDB;uid=" & Trim(txtUid) & ";pwd=" & Trim(txtPwd) & ";Data Source=" & Trim(txtServer) & ";" & "Initial Catalog=Northwind;"
    Set gCn = OpenSql(txtServer, "Northwind", adUseClient, adModeReadWrite, txtUid, txtPwd)
    Me.Hide
    Unload Me
End Sub

Private Sub Form_Load()
    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)
End Sub

