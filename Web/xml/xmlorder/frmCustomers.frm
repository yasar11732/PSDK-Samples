VERSION 5.00
Begin VB.Form frmCustomers 
   Caption         =   "Customers"
   ClientHeight    =   5124
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   8124
   Icon            =   "frmCustomers.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   5124
   ScaleWidth      =   8124
   Begin VB.CommandButton cmdSave 
      Caption         =   "&Save"
      Height          =   375
      Left            =   5640
      TabIndex        =   26
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   ">>"
      Height          =   375
      Left            =   1440
      TabIndex        =   22
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   ">"
      Height          =   375
      Left            =   1080
      TabIndex        =   21
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdPrevious 
      Caption         =   "<"
      Height          =   375
      Left            =   600
      TabIndex        =   20
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdFirst 
      Caption         =   "<<"
      Height          =   375
      Left            =   240
      TabIndex        =   19
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "&Delete"
      Height          =   375
      Left            =   3240
      TabIndex        =   24
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   6840
      TabIndex        =   27
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   2040
      TabIndex        =   23
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdEdit 
      Caption         =   "Edi&t"
      Height          =   375
      Left            =   4440
      TabIndex        =   25
      Top             =   4560
      Width           =   1095
   End
   Begin VB.TextBox txtShipZip 
      Height          =   285
      Left            =   3480
      Locked          =   -1  'True
      TabIndex        =   17
      Top             =   3960
      Width           =   855
   End
   Begin VB.TextBox txtShipState 
      Height          =   285
      Left            =   5400
      Locked          =   -1  'True
      TabIndex        =   18
      Top             =   3960
      Width           =   1815
   End
   Begin VB.TextBox txtShipCity 
      Height          =   285
      Left            =   600
      Locked          =   -1  'True
      TabIndex        =   16
      Top             =   3960
      Width           =   2175
   End
   Begin VB.TextBox txtShipAddress2 
      Height          =   285
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   15
      Top             =   3480
      Width           =   6495
   End
   Begin VB.TextBox txtShipAddress1 
      Height          =   285
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   14
      Top             =   3240
      Width           =   6495
   End
   Begin VB.TextBox txtCCNumber 
      Height          =   285
      Left            =   6240
      Locked          =   -1  'True
      TabIndex        =   13
      Top             =   2760
      Width           =   1695
   End
   Begin VB.TextBox txtCCExp 
      Height          =   285
      Left            =   3720
      Locked          =   -1  'True
      TabIndex        =   12
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox txtMethod 
      Height          =   285
      Left            =   1800
      Locked          =   -1  'True
      TabIndex        =   11
      Top             =   2760
      Width           =   1095
   End
   Begin VB.TextBox txtWorkPhone 
      Height          =   285
      Left            =   4920
      Locked          =   -1  'True
      TabIndex        =   10
      Top             =   2280
      Width           =   2295
   End
   Begin VB.TextBox txtHomePhone 
      Height          =   285
      Left            =   1320
      Locked          =   -1  'True
      TabIndex        =   9
      Top             =   2280
      Width           =   2295
   End
   Begin VB.TextBox txtZip 
      Height          =   285
      Left            =   5400
      Locked          =   -1  'True
      TabIndex        =   8
      Top             =   1800
      Width           =   1815
   End
   Begin VB.TextBox txtState 
      Height          =   285
      Left            =   3480
      Locked          =   -1  'True
      TabIndex        =   7
      Top             =   1800
      Width           =   855
   End
   Begin VB.TextBox txtCity 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   600
      Locked          =   -1  'True
      TabIndex        =   6
      Top             =   1800
      Width           =   2175
   End
   Begin VB.TextBox txtAddress2 
      Height          =   285
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   5
      Top             =   1320
      Width           =   6495
   End
   Begin VB.TextBox txtAddress1 
      Height          =   285
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   4
      Top             =   1080
      Width           =   6495
   End
   Begin VB.TextBox txtCompanyName 
      Height          =   285
      Left            =   3960
      Locked          =   -1  'True
      TabIndex        =   0
      Top             =   120
      Width           =   3975
   End
   Begin VB.TextBox txtLastName 
      Height          =   285
      Left            =   6360
      Locked          =   -1  'True
      TabIndex        =   3
      Top             =   600
      Width           =   1575
   End
   Begin VB.TextBox txtMiddleName 
      Height          =   285
      Left            =   3840
      Locked          =   -1  'True
      TabIndex        =   2
      Top             =   600
      Width           =   1575
   End
   Begin VB.TextBox txtFirstName 
      Height          =   285
      Left            =   1080
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   600
      Width           =   1575
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   8160
      Y1              =   4440
      Y2              =   4440
   End
   Begin VB.Label lblCustID 
      AutoSize        =   -1  'True
      Caption         =   "Customer ID:"
      Height          =   195
      Left            =   120
      TabIndex        =   47
      Top             =   120
      Width           =   915
   End
   Begin VB.Label lblShipZip 
      AutoSize        =   -1  'True
      Caption         =   "Zip Code:"
      Height          =   195
      Left            =   4560
      TabIndex        =   46
      Top             =   3960
      Width           =   690
   End
   Begin VB.Label lblShipState 
      AutoSize        =   -1  'True
      Caption         =   "State:"
      Height          =   195
      Left            =   3000
      TabIndex        =   45
      Top             =   3960
      Width           =   420
   End
   Begin VB.Label lblShipCity 
      AutoSize        =   -1  'True
      Caption         =   "City:"
      Height          =   195
      Left            =   240
      TabIndex        =   44
      Top             =   3960
      Width           =   300
   End
   Begin VB.Label lblShipAddress2 
      AutoSize        =   -1  'True
      Caption         =   "Ship Address 2:"
      Height          =   195
      Left            =   240
      TabIndex        =   43
      Top             =   3480
      Width           =   1110
   End
   Begin VB.Label lblShipAddress1 
      AutoSize        =   -1  'True
      Caption         =   "Ship Address 1:"
      Height          =   195
      Left            =   240
      TabIndex        =   42
      Top             =   3240
      Width           =   1110
   End
   Begin VB.Label lblCCExp 
      AutoSize        =   -1  'True
      Caption         =   "CC Exp:"
      Height          =   195
      Left            =   3120
      TabIndex        =   41
      Top             =   2760
      Width           =   570
   End
   Begin VB.Label lblCCNumber 
      AutoSize        =   -1  'True
      Caption         =   "CC Number:"
      Height          =   195
      Left            =   5280
      TabIndex        =   40
      Top             =   2760
      Width           =   855
   End
   Begin VB.Label lblMethod 
      AutoSize        =   -1  'True
      Caption         =   "Method of Payment:"
      Height          =   195
      Left            =   240
      TabIndex        =   39
      Top             =   2760
      Width           =   1425
   End
   Begin VB.Label lblWorkPhone 
      AutoSize        =   -1  'True
      Caption         =   "Work Phone:"
      Height          =   195
      Left            =   3840
      TabIndex        =   38
      Top             =   2280
      Width           =   945
   End
   Begin VB.Label lblHomePhone 
      Caption         =   "Home Phone:"
      Height          =   255
      Left            =   240
      TabIndex        =   37
      Top             =   2280
      Width           =   975
   End
   Begin VB.Label lblZip 
      AutoSize        =   -1  'True
      Caption         =   "Zip Code:"
      Height          =   195
      Left            =   4560
      TabIndex        =   36
      Top             =   1800
      Width           =   690
   End
   Begin VB.Label lblState 
      AutoSize        =   -1  'True
      Caption         =   "State:"
      Height          =   195
      Left            =   3000
      TabIndex        =   35
      Top             =   1800
      Width           =   420
   End
   Begin VB.Label lblCity 
      AutoSize        =   -1  'True
      Caption         =   "City:"
      Height          =   195
      Left            =   240
      TabIndex        =   34
      Top             =   1800
      Width           =   300
   End
   Begin VB.Label lblAddress2 
      AutoSize        =   -1  'True
      Caption         =   "Maill Address 2:"
      Height          =   195
      Left            =   240
      TabIndex        =   33
      Top             =   1320
      Width           =   1110
   End
   Begin VB.Label lblAddress1 
      AutoSize        =   -1  'True
      Caption         =   "Mail Address 1:"
      Height          =   195
      Left            =   240
      TabIndex        =   32
      Top             =   1080
      Width           =   1080
   End
   Begin VB.Label lblCompanyName 
      AutoSize        =   -1  'True
      Caption         =   "Company Name:"
      Height          =   195
      Left            =   2760
      TabIndex        =   31
      Top             =   120
      Width           =   1170
   End
   Begin VB.Label lblLastName 
      AutoSize        =   -1  'True
      Caption         =   "Last Name:"
      Height          =   195
      Left            =   5520
      TabIndex        =   30
      Top             =   600
      Width           =   810
   End
   Begin VB.Label lblMiddleName 
      AutoSize        =   -1  'True
      Caption         =   "Middle Name:"
      Height          =   195
      Left            =   2760
      TabIndex        =   29
      Top             =   600
      Width           =   975
   End
   Begin VB.Label lblFirstName 
      AutoSize        =   -1  'True
      Caption         =   "First Name:"
      Height          =   195
      Left            =   240
      TabIndex        =   28
      Top             =   600
      Width           =   795
   End
End
Attribute VB_Name = "frmCustomers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: frmCustomers
'
'   Description: This form provides an interface to view, add, edit, and
'                remove customers from the system
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private attributes
'-------------------------------------------------------------------------
Private m_obj_customers As CCustomersDB
Private m_bln_inEdit As Boolean

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Sub ShowCustomer(ByVal p_str_custID As String)
    'load the form
    Load Me
    
    'check if an ID was provided
    If p_str_custID <> "" Then
        'find the correct customer
        If m_obj_customers.FindCustomer(p_str_custID) = False Then
            'display an error message
            MsgBox "Customer " & p_str_custID & " not found"
            
            'unload the form
            Unload Me
        End If
    End If
    
    'display the data
    Call DisplayCustomer
    
    'do some form setup
    Me.Height = 5445
    Me.Width = 8220
    Call Me.ZOrder(0)  ' Place form on top
    Me.WindowState = 0 ' restore window incase it was min.
    
    'show the form
    Me.Show
End Sub

'-------------------------------------------------------------------------
'   Form Event Handlers
'-------------------------------------------------------------------------
Private Sub Form_Load()
    'create the DB object
    Set m_obj_customers = New CCustomersDB
    
    'unlock the text boxes
    Call SetLocked(True)
    
    'set enable
    Call SetEnabled(False)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'release the object
    Set m_obj_customers = Nothing
End Sub

Private Sub cmdExit_Click()
    Dim int_result As Integer

    'check if in edit
    If m_bln_inEdit = True Then
        'display the save dialog
        int_result = MsgBox("Do you want to save changes before exit?", vbYesNoCancel)
    Else
        'set the result to no
        int_result = vbNo
    End If

    'deal witht he result
    If int_result = vbNo Then
        'hide and unload the form
        Me.Hide
        Unload Me
    ElseIf int_result = vbYes Then
        'save the changes
        Call cmdSave_Click
        
        'hide and unload the form
        Me.Hide
        Unload Me
    End If
End Sub

'-------------------------------------------------------------------------
'   Navigation Event Handlers
'-------------------------------------------------------------------------
Private Sub cmdFirst_Click()
    'move to the first node
    Call m_obj_customers.MoveFirst
    
    'refresh the display
    Call DisplayCustomer
End Sub

Private Sub cmdEnd_Click()
    'move to the last node
    Call m_obj_customers.MoveLast
    
    'refresh the display
    Call DisplayCustomer
End Sub

Private Sub cmdNext_Click()
    'move to the next node
    Call m_obj_customers.MoveNext
    
    'refresh the display
    Call DisplayCustomer
End Sub

Private Sub cmdPrevious_Click()
    'move to the previous node
    Call m_obj_customers.MovePrev
    
    'refresh the display
    Call DisplayCustomer
End Sub

'-------------------------------------------------------------------------
'   Operation Event Handlers
'-------------------------------------------------------------------------
Private Sub cmdAdd_Click()
    'create the new customer
    Call m_obj_customers.AddCustomer
    
    'refresh the display
    Call DisplayCustomer
    
    'unlock the text boxes
    Call SetLocked(False)
    
    'set enable
    Call SetEnabled(True)
End Sub

Private Sub cmdEdit_Click()
    'set the customer to edit
    Call m_obj_customers.EditCustomer
    
    'unlock the text boxes
    Call SetLocked(False)
    
    'set enable
    Call SetEnabled(True)
End Sub

Private Sub cmdSave_Click()
    'validate the data
    If ValidateEntries = True Then
        'store the form data
        Call StoreCustomer
    
        'save the data in the DB class
        Call m_obj_customers.SaveCustomer
        
        'lock the text boxes
        Call SetLocked(True)
        
        'set enable
        Call SetEnabled(False)
        
        'refresh the display
        Call DisplayCustomer
    End If
End Sub

Private Sub cmdDelete_Click()
    'remove the current node
    Call m_obj_customers.DeleteCustomer
    
    'refresh the display
    Call DisplayCustomer
End Sub

Private Sub SetEnabled(ByVal p_bln_inEdit As Boolean)
    'set navigation enable
    cmdFirst.Enabled = Not p_bln_inEdit
    cmdEnd.Enabled = Not p_bln_inEdit
    cmdNext.Enabled = Not p_bln_inEdit
    cmdPrevious.Enabled = Not p_bln_inEdit

    'set add, edit, and delete enable
    cmdAdd.Enabled = Not p_bln_inEdit
    cmdEdit.Enabled = Not p_bln_inEdit
    cmdDelete.Enabled = Not p_bln_inEdit
    
    'set save endable
    cmdSave.Enabled = p_bln_inEdit
    
    'set the enabled flag
    m_bln_inEdit = p_bln_inEdit
End Sub

'-------------------------------------------------------------------------
'   Private Methods
'-------------------------------------------------------------------------
Private Sub DisplayCustomer()
    'display the data or the selected customer
    lblCustID.Caption = "Customer ID:" & m_obj_customers.CompanyID
    txtCompanyName.Text = m_obj_customers.CompanyName
    txtFirstName.Text = m_obj_customers.FirstName
    txtMiddleName.Text = m_obj_customers.MiddleName
    txtLastName.Text = m_obj_customers.LastName
    txtAddress1.Text = m_obj_customers.Address1
    txtAddress2.Text = m_obj_customers.Address2
    txtCity.Text = m_obj_customers.City
    txtState.Text = m_obj_customers.State
    txtZip.Text = m_obj_customers.Zip
    txtHomePhone.Text = m_obj_customers.HomePhone
    txtWorkPhone.Text = m_obj_customers.WorkPhone
    txtMethod.Text = m_obj_customers.MethodOfPayment
    txtCCExp.Text = m_obj_customers.CCExp
    txtCCNumber.Text = m_obj_customers.CCNum
    txtShipAddress1.Text = m_obj_customers.ShipAddress1
    txtShipAddress2.Text = m_obj_customers.ShipAddress2
    txtShipCity.Text = m_obj_customers.ShipCity
    txtShipState.Text = m_obj_customers.ShipState
    txtShipZip.Text = m_obj_customers.ShipZip
End Sub

Private Sub StoreCustomer()
    'store the values in the form to the DB class
    m_obj_customers.CompanyName = txtCompanyName.Text
    m_obj_customers.FirstName = txtFirstName.Text
    m_obj_customers.MiddleName = txtMiddleName.Text
    m_obj_customers.LastName = txtLastName.Text
    m_obj_customers.Address1 = txtAddress1.Text
    m_obj_customers.Address2 = txtAddress2.Text
    m_obj_customers.City = txtCity.Text
    m_obj_customers.State = txtState.Text
    m_obj_customers.Zip = txtZip.Text
    m_obj_customers.HomePhone = txtHomePhone.Text
    m_obj_customers.WorkPhone = txtWorkPhone.Text
    m_obj_customers.MethodOfPayment = txtMethod.Text
    m_obj_customers.CCExp = txtCCExp.Text
    m_obj_customers.CCNum = txtCCNumber.Text
    m_obj_customers.ShipAddress1 = txtShipAddress1.Text
    m_obj_customers.ShipAddress2 = txtShipAddress2.Text
    m_obj_customers.ShipCity = txtShipCity.Text
    m_obj_customers.ShipState = txtShipState.Text
    m_obj_customers.ShipZip = txtShipZip.Text
End Sub

Private Sub SetLocked(ByVal p_bln_locked As Boolean)
    'set the locked property of the controls
    txtCompanyName.Locked = p_bln_locked
    txtFirstName.Locked = p_bln_locked
    txtMiddleName.Locked = p_bln_locked
    txtLastName.Locked = p_bln_locked
    txtAddress1.Locked = p_bln_locked
    txtAddress2.Locked = p_bln_locked
    txtCity.Locked = p_bln_locked
    txtState.Locked = p_bln_locked
    txtZip.Locked = p_bln_locked
    txtHomePhone.Locked = p_bln_locked
    txtWorkPhone.Locked = p_bln_locked
    txtMethod.Locked = p_bln_locked
    txtCCExp.Locked = p_bln_locked
    txtCCNumber.Locked = p_bln_locked
    txtShipAddress1.Locked = p_bln_locked
    txtShipAddress2.Locked = p_bln_locked
    txtShipCity.Locked = p_bln_locked
    txtShipState.Locked = p_bln_locked
    txtShipZip.Locked = p_bln_locked

    'set the backgroud color property of the controls
    txtCompanyName.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtFirstName.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtMiddleName.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtLastName.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtAddress1.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtAddress2.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtCity.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtState.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtZip.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtHomePhone.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtWorkPhone.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtMethod.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtCCExp.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtCCNumber.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtShipAddress1.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtShipAddress2.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtShipCity.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtShipState.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
    txtShipZip.BackColor = IIf(p_bln_locked, &H8000000F, &H80000005)
End Sub

Private Function ValidateEntries() As Boolean
    'check the first name
    If txtFirstName.Text = "" Then
        MsgBox "Please enter a first name."
        txtFirstName.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the last name
    If txtLastName.Text = "" Then
        MsgBox "Please enter a last name."
        txtLastName.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the address
    If txtAddress1.Text = "" Then
        MsgBox "Please enter a address."
        txtAddress1.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the city
    If txtCity.Text = "" Then
        MsgBox "Please enter a city."
        txtCity.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the state
    If txtState.Text = "" Then
        MsgBox "Please enter a state."
        txtState.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the zip
    If txtZip.Text = "" Then
        MsgBox "Please enter a zip code."
        txtZip.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the phone
    If (txtHomePhone.Text = "" And txtWorkPhone.Text = "") Then
        MsgBox "Please enter a phone number."
        txtHomePhone.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the method
    If txtMethod.Text = "" Then
        MsgBox "Please enter a method of payment."
        txtMethod.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the ccexp
    If txtCCExp.Text = "" Then
        MsgBox "Please enter a credit card exper date."
        txtCCExp.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the ccnum
    If txtCCNumber.Text = "" Then
        MsgBox "Please enter a credit card number."
        txtCCNumber.SetFocus
        ValidateEntries = False
        Exit Function
    End If
    
    'check the shipping address
    If txtShipAddress1.Text = "" Then
        If (MsgBox("Do you want to ship to the billing address?", vbYesNo) = vbYes) Then
            txtShipAddress1.Text = txtAddress1.Text
            txtShipAddress2.Text = txtAddress2.Text
            txtShipCity.Text = txtCity.Text
            txtShipState.Text = txtState.Text
            txtShipZip.Text = txtZip.Text
        Else
            txtShipAddress1.SetFocus
            ValidateEntries = False
            Exit Function
        End If
    End If
    
    'return true
    ValidateEntries = True
End Function
