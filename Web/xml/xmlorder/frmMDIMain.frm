VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.MDIForm frmMDIMain 
   BackColor       =   &H8000000C&
   Caption         =   "Main Menu - XML Order Application"
   ClientHeight    =   6210
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8835
   Icon            =   "frmMDIMain.frx":0000
   LinkTopic       =   "MDIForm1"
   WindowState     =   2  'Maximized
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   1
      Top             =   5904
      Width           =   8832
      _ExtentX        =   15584
      _ExtentY        =   529
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   15081
            Text            =   "User:"
            TextSave        =   "User:"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   480
      Top             =   1200
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDIMain.frx":0442
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDIMain.frx":0F0E
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDIMain.frx":122A
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDIMain.frx":167E
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   915
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   8835
      _ExtentX        =   15584
      _ExtentY        =   1614
      ButtonWidth     =   1799
      ButtonHeight    =   1455
      Appearance      =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   3
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Orders"
            Description     =   "Create/Edit/View Orders"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Customers"
            Description     =   "View/Edit/Add Customers"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Exit"
            Description     =   "Exit"
            ImageIndex      =   4
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmMDIMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: frmMDIMain
'
'   Description: This is the main for used to launch the child forms
'
'-------------------------------------------------------------------------

Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
    'change the mouse pointer to an hourglass
    MousePointer = 11

    If Button = "Orders" Then ' load order form
        'create and show an orders form
        Dim frmOrder As New frmOrder
        Call frmOrder.ShowOrder
    ElseIf Button = "Customers" Then ' load customer form
        'create and show a customer form
        Dim frmCust As New frmCustomers
        Call frmCust.ShowCustomer("")
    ElseIf Button = "Exit" Then
        'unload the forms
        Unload frmOrder
        Unload frmCustomers
        Unload frmMDIMain
        End
    End If

    'change the mouse pointer to the default
    MousePointer = 0 ' restore mousepointer
End Sub

