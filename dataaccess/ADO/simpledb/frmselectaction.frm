VERSION 5.00
Begin VB.Form frmSelectAction 
   Caption         =   "Select Operation"
   ClientHeight    =   5475
   ClientLeft      =   6990
   ClientTop       =   5910
   ClientWidth     =   4275
   LinkTopic       =   "Form1"
   ScaleHeight     =   5475
   ScaleWidth      =   4275
   Begin VB.CommandButton cmdBrowseRecords 
      Caption         =   "Browse Records"
      Height          =   645
      Left            =   1215
      TabIndex        =   5
      Top             =   2734
      Width           =   1755
   End
   Begin VB.CommandButton cmdListEmployees 
      Caption         =   "List Employees"
      Height          =   645
      Left            =   1215
      TabIndex        =   3
      Top             =   3542
      Width           =   1755
   End
   Begin VB.CommandButton cmdDeleteEmployee 
      Caption         =   "Delete Employee"
      Height          =   645
      Left            =   1215
      TabIndex        =   2
      Top             =   1926
      Width           =   1755
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   645
      Left            =   1215
      TabIndex        =   4
      Top             =   4350
      Width           =   1755
   End
   Begin VB.CommandButton cmdEditEmployee 
      Caption         =   "&Edit Employee"
      Height          =   645
      Left            =   1215
      TabIndex        =   1
      Top             =   1118
      Width           =   1755
   End
   Begin VB.CommandButton cmdAddEmployee 
      Caption         =   "&Add Employee"
      Height          =   645
      Left            =   1215
      TabIndex        =   0
      Top             =   310
      Width           =   1755
   End
End
Attribute VB_Name = "frmSelectAction"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub cmdAddEmployee_Click()
    frmAddEmployee.Show vbModal
End Sub

Private Sub cmdBrowseRecords_Click()
    frmBrowse.Show vbModal
End Sub

Private Sub cmdClose_Click()
    Me.Hide
    Unload Me
End Sub

Private Sub cmdDeleteEmployee_Click()
    frmDeleteEmployee.Show vbModal
End Sub

Private Sub cmdEditEmployee_Click()
    frmEditEmployee.Show vbModal
End Sub

Private Sub cmdListEmployees_Click()
    frmListEmployees.Show vbModal
End Sub


Private Sub Form_Load()
    Me.Top = (Screen.Height \ 2) - (Me.Height \ 2)
    Me.Left = (Screen.Width \ 2) - (Me.Width \ 2)

End Sub
