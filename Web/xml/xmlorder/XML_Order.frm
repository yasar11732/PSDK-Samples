VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "msflxgrd.ocx"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmOrder 
   Caption         =   "XML Order Form"
   ClientHeight    =   8592
   ClientLeft      =   168
   ClientTop       =   456
   ClientWidth     =   11880
   Icon            =   "XML_Order.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   8592
   ScaleWidth      =   11880
   Begin TabDlg.SSTab SSTab1 
      Height          =   5292
      Left            =   120
      TabIndex        =   6
      Top             =   1080
      Width           =   9132
      _ExtentX        =   16108
      _ExtentY        =   9335
      _Version        =   393216
      Style           =   1
      Tabs            =   2
      TabHeight       =   420
      TabCaption(0)   =   "New Order"
      TabPicture(0)   =   "XML_Order.frx":014A
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "frNewOrder"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Order History"
      TabPicture(1)   =   "XML_Order.frx":0166
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "frHistory"
      Tab(1).ControlCount=   1
      Begin VB.Frame frHistory 
         Height          =   4812
         Left            =   -74880
         TabIndex        =   25
         Top             =   360
         Width           =   8895
         Begin VB.CommandButton cmdDeleteOrder 
            Cancel          =   -1  'True
            Caption         =   "&Delete Order"
            Height          =   375
            Left            =   4200
            TabIndex        =   29
            Top             =   720
            Width           =   1455
         End
         Begin VB.CommandButton cmdEdit 
            Caption         =   "Edit &Order"
            Height          =   375
            Left            =   4200
            TabIndex        =   28
            Top             =   240
            Width           =   1455
         End
         Begin VB.ListBox lstOrders 
            Height          =   816
            Left            =   2640
            Sorted          =   -1  'True
            TabIndex        =   27
            Top             =   240
            Width           =   1335
         End
         Begin MSFlexGridLib.MSFlexGrid OrderHistoryGrid 
            Height          =   3252
            Left            =   120
            TabIndex        =   26
            Top             =   1440
            Width           =   8652
            _ExtentX        =   15261
            _ExtentY        =   5736
            _Version        =   393216
            Cols            =   7
            FixedCols       =   0
         End
         Begin VB.Label lblOrder 
            AutoSize        =   -1  'True
            Caption         =   "Select a order number for details:"
            Height          =   195
            Left            =   240
            TabIndex        =   30
            Top             =   240
            Width           =   2325
         End
      End
      Begin VB.Frame frNewOrder 
         Height          =   4815
         Left            =   120
         TabIndex        =   7
         Top             =   360
         Width           =   8895
         Begin VB.TextBox txtPrice 
            Height          =   285
            Left            =   1440
            TabIndex        =   14
            Top             =   1560
            Width           =   1095
         End
         Begin VB.ComboBox cmbProducts 
            Height          =   288
            ItemData        =   "XML_Order.frx":0182
            Left            =   1440
            List            =   "XML_Order.frx":018F
            Sorted          =   -1  'True
            Style           =   2  'Dropdown List
            TabIndex        =   13
            Top             =   600
            Width           =   7215
         End
         Begin VB.TextBox txtDescription 
            Height          =   285
            Left            =   1440
            TabIndex        =   12
            Top             =   1080
            Width           =   7215
         End
         Begin VB.CommandButton cmdAdd 
            Caption         =   "&Add To Order"
            Height          =   375
            Left            =   4560
            TabIndex        =   11
            Top             =   1560
            Width           =   1215
         End
         Begin VB.TextBox txtQty 
            Height          =   285
            Left            =   3480
            TabIndex        =   10
            Text            =   "1"
            Top             =   1560
            Width           =   855
         End
         Begin VB.CommandButton cmdSave 
            Caption         =   "&Save Order"
            Height          =   375
            Left            =   6000
            TabIndex        =   9
            Top             =   1560
            Width           =   1215
         End
         Begin VB.CommandButton cmdCancel 
            Caption         =   "&Cancel"
            Height          =   375
            Left            =   7440
            TabIndex        =   8
            Top             =   1560
            Width           =   1215
         End
         Begin MSFlexGridLib.MSFlexGrid OrderGrid 
            Height          =   2655
            Left            =   120
            TabIndex        =   15
            Top             =   2040
            Width           =   8655
            _ExtentX        =   15261
            _ExtentY        =   4678
            _Version        =   393216
            Cols            =   7
            FixedCols       =   0
            WordWrap        =   -1  'True
            SelectionMode   =   1
            AllowUserResizing=   1
         End
         Begin VB.Label lblOrderNumber 
            AutoSize        =   -1  'True
            Caption         =   "Order Number:"
            Height          =   195
            Left            =   120
            TabIndex        =   24
            Top             =   240
            Width           =   1035
         End
         Begin VB.Label lblActualOrderNumber 
            AutoSize        =   -1  'True
            Caption         =   "1"
            Height          =   192
            Left            =   1440
            TabIndex        =   23
            Top             =   240
            Width           =   336
         End
         Begin VB.Label lblOrderDate 
            AutoSize        =   -1  'True
            Caption         =   "Order Date:"
            Height          =   195
            Left            =   6960
            TabIndex        =   22
            Top             =   240
            Width           =   825
         End
         Begin VB.Label lblActualOrderDate 
            AutoSize        =   -1  'True
            Caption         =   "01/04/99"
            Height          =   195
            Left            =   7920
            TabIndex        =   21
            Top             =   240
            Width           =   690
         End
         Begin VB.Label lblPrice 
            AutoSize        =   -1  'True
            Caption         =   "Price:"
            Height          =   195
            Left            =   720
            TabIndex        =   20
            Top             =   1560
            Width           =   405
         End
         Begin VB.Label lblProducts 
            AutoSize        =   -1  'True
            Caption         =   "Products:"
            Height          =   195
            Left            =   480
            TabIndex        =   19
            Top             =   600
            Width           =   675
         End
         Begin VB.Label lblDescription 
            AutoSize        =   -1  'True
            Caption         =   "Description:"
            Height          =   195
            Left            =   360
            TabIndex        =   18
            Top             =   1080
            Width           =   840
         End
         Begin VB.Label lblQty 
            AutoSize        =   -1  'True
            Caption         =   "Qty:"
            Height          =   195
            Left            =   3000
            TabIndex        =   17
            Top             =   1560
            Width           =   285
         End
         Begin VB.Label lblTotal 
            AutoSize        =   -1  'True
            Caption         =   "Order Total = $0.00"
            Height          =   195
            Left            =   2400
            TabIndex        =   16
            Top             =   240
            Width           =   1380
         End
      End
   End
   Begin VB.CommandButton cmdCust 
      Caption         =   "&View Customer"
      Height          =   375
      Left            =   6480
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   7920
      TabIndex        =   3
      Top             =   120
      Width           =   1335
   End
   Begin VB.ComboBox cmbCustomer 
      Height          =   288
      Left            =   1440
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   120
      Width           =   4935
   End
   Begin VB.Label lblTotalOrders 
      AutoSize        =   -1  'True
      Caption         =   "Total Orders To Date:"
      Height          =   195
      Left            =   4440
      TabIndex        =   5
      Top             =   600
      Width           =   1545
   End
   Begin VB.Label lblCustID 
      AutoSize        =   -1  'True
      Caption         =   "Customer ID:"
      Height          =   195
      Left            =   120
      TabIndex        =   4
      Top             =   600
      Width           =   915
   End
   Begin VB.Label lblCustName 
      AutoSize        =   -1  'True
      Caption         =   "Customer Name:"
      Height          =   195
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1170
   End
End
Attribute VB_Name = "frmOrder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: frmOrder
'
'   Description: This form displays orders based on customers and allows
'                new orders to be entered
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private attributes
'-------------------------------------------------------------------------
Private m_obj_orders As COrdersDB

'item collections
Private m_col_customers As Collection
Private m_col_products As Collection

Private m_bln_inEdit As Boolean
Private m_cur_totalCost As Currency

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Sub ShowOrder()
    Load Me
    
    'do some form setup
    Call Me.ZOrder(0)  ' Place form on top
    Me.WindowState = 0 ' restore window incase it was min.
    Me.Height = 6870
    Me.Width = 9510
    
    'show the form
    Me.Show
End Sub

'-------------------------------------------------------------------------
'   Form Event Handlers
'-------------------------------------------------------------------------
Private Sub Form_Load()
    'create the orders DB object
    Set m_obj_orders = New COrdersDB
    
    ' Setup the Order grid
    OrderGrid.Cols = 6
    OrderGrid.Rows = 1
    OrderGrid.Row = 0
    OrderGrid.Col = 0
    OrderGrid.Text = "ProductID"
    OrderGrid.CellAlignment = 1
    OrderGrid.ColWidth(0) = 0
    OrderGrid.Col = 1
    OrderGrid.Text = "Part Number:"
    OrderGrid.CellAlignment = 1
    OrderGrid.ColWidth(1) = 1200
    OrderGrid.Col = 2
    OrderGrid.Text = "Description:"
    OrderGrid.CellAlignment = 1
    OrderGrid.ColWidth(2) = 4000
    OrderGrid.Col = 3
    OrderGrid.Text = "Price:"
    OrderGrid.ColWidth(3) = 1000
    OrderGrid.CellAlignment = 1
    OrderGrid.Col = 4
    OrderGrid.Text = "Qty:"
    OrderGrid.ColWidth(4) = 900
    OrderGrid.CellAlignment = 1
    OrderGrid.Col = 5
    OrderGrid.Text = "Total Cost:"
    OrderGrid.ColWidth(5) = 1300
    OrderGrid.CellAlignment = 1
    
    ' Setup Order History Grid
    OrderHistoryGrid.Row = 0
    OrderHistoryGrid.Col = 0
    OrderHistoryGrid.Text = "Part Number:"
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.ColWidth(0) = 1200
    OrderHistoryGrid.Col = 1
    OrderHistoryGrid.Text = "Description:"
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.ColWidth(1) = 4000
    OrderHistoryGrid.Col = 2
    OrderHistoryGrid.Text = "Price:"
    OrderHistoryGrid.ColWidth(2) = 1000
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.Col = 3
    OrderHistoryGrid.Text = "Qty:"
    OrderHistoryGrid.ColWidth(3) = 900
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.Col = 4
    OrderHistoryGrid.Text = "Total Cost:"
    OrderHistoryGrid.ColWidth(4) = 1300
    OrderHistoryGrid.CellAlignment = 1
    
    'populate the customers list
    Call PopulateCustomerList
    
    'populate the products list
    Call PopulateProductList
    
    'set the order number to New Order
    lblActualOrderNumber.Caption = "New Order"
    
    'select the first customer and product
    cmbCustomer.ListIndex = 0
    cmbProducts.ListIndex = 0
End Sub

Private Sub cmbCustomer_Click()
    Dim lng_index As Long
    Dim obj_customerData As CCustomerData
    
    'verify that it's a valid index
    If cmbCustomer.ListIndex <> -1 Then
        'update the customer data
        lng_index = cmbCustomer.ItemData(cmbCustomer.ListIndex)
        Set obj_customerData = m_col_customers(lng_index)
        
        'get the company ID and display it
        lblCustID.Caption = "Customer ID: " & obj_customerData.CompanyID
        
        'get the count of orders for this customers
        lblTotalOrders.Caption = "Total Orders To Date: " & m_obj_orders.GetOrderIDs(obj_customerData.CompanyID).Count
        
        'populate the list of order IDs
        Call PopulateOrderList(obj_customerData.CompanyID)
    End If
End Sub

Private Sub cmbProducts_Click()
    Dim lng_index As Long
    Dim obj_productData As CProductData
    
    'get the product data
    lng_index = cmbProducts.ItemData(cmbProducts.ListIndex)
    Set obj_productData = m_col_products(lng_index)
    
    'set the data in the text boxes
    txtDescription.Text = obj_productData.Description
    txtPrice.Text = obj_productData.Price
End Sub

Private Sub cmdCust_Click()
    Dim lng_index As Long
    Dim str_custID As String
    
    'verify that it's a valid index
    If cmbCustomer.ListIndex <> -1 Then
        'get the customer ID
        lng_index = cmbCustomer.ItemData(cmbCustomer.ListIndex)
        str_custID = m_col_customers(lng_index).CompanyID
        
        'create a new instance of the customer form
        Dim frmCustomer As New frmCustomers
        Call frmCustomer.ShowCustomer(str_custID)
    End If
End Sub

Private Sub cmdExit_Click()
    Dim int_result As Integer

    'check if editing
    If SSTab1.TabEnabled(1) = False Then
        'display a prompt to the user
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
'   New Order Tab Event Handlers
'-------------------------------------------------------------------------
Private Sub cmdAdd_Click()
    Dim lng_index As Long
    Dim obj_productData As CProductData
    Dim lng_qty As Long
    
    'disable the tabs
    SSTab1.TabEnabled(1) = False
    
    'get the product data
    lng_index = cmbProducts.ItemData(cmbProducts.ListIndex)
    Set obj_productData = m_col_products(lng_index)
    
    'add the data to the grid
    lng_qty = CLng(txtQty.Text)
    OrderGrid.AddItem (obj_productData.ProductID & vbTab & obj_productData.PartNumber & vbTab & _
                      obj_productData.Description & vbTab & FormatCurrency(obj_productData.Price) & _
                      vbTab & lng_qty & vbTab & FormatCurrency(lng_qty * obj_productData.Price))
    
    'update the total cost
    m_cur_totalCost = m_cur_totalCost + lng_qty * obj_productData.Price
    lblTotal.Caption = "Total Cost = " & FormatCurrency(m_cur_totalCost)
End Sub

Private Sub cmdCancel_Click()
    'enable the tabs
    SSTab1.TabEnabled(1) = True

    'clear the grid
    OrderGrid.Rows = 1
    
    'reset the total cost
    lblTotal.Caption = "Total Cost = " & FormatCurrency(0)
    
    'set the order number to New Order
    lblActualOrderNumber.Caption = "New Order"

    'select the first product
    cmbProducts.ListIndex = 0
End Sub

Private Sub cmdSave_Click()
    If lblActualOrderNumber.Caption = "New Order" Then
        'add the order
        Call AddOrder
    Else
        'update the order
        Call UpdateOrder
        
        'update the history grid
        Call lstOrders_Click
    End If
    
    'enable the tabs
    SSTab1.TabEnabled(1) = True
    
    'clear the grid
    OrderGrid.Rows = 1
    
    'reset the total cost
    lblTotal.Caption = "Total Cost = " & FormatCurrency(0)
    
    'set the order number to New Order
    lblActualOrderNumber.Caption = "New Order"
    
    'force a refresh of the history list
    Call cmbCustomer_Click
    
    'select the first product
    cmbProducts.ListIndex = 0
End Sub

Private Sub OrderGrid_Click()
    Dim int_result As Integer

    If OrderGrid.Row > 0 Then
        'ask the user if they want to remove the item
        int_result = MsgBox("Do you want to delete this line item?", vbYesNo)
        
        'check the result
        If int_result = vbYes Then
            'check if it is the last row
            If OrderGrid.Rows = 2 Then
                OrderGrid.Rows = 1
            Else
                OrderGrid.RemoveItem (OrderGrid.Row)
            End If
        End If
    End If
End Sub

'-------------------------------------------------------------------------
'   History Tab Event Handlers
'-------------------------------------------------------------------------
Private Sub lstOrders_Click()
    Dim obj_items As COrderItemsDB
    Dim obj_products As New CProductsDB
    Dim lng_loop As Long

    'select the order
    Call m_obj_orders.SelectOrder(lstOrders.Text)
    
    'get the item
    Set obj_items = m_obj_orders.OrderItems
    
    'populate the grid
    OrderHistoryGrid.Rows = 1
    For lng_loop = 0 To obj_items.ItemCount - 1
        'select the item
        Call obj_items.SelectItem(lng_loop)
    
        'find the product
        Call obj_products.FindProduct(obj_items.ProductID)
    
        'add the grid item
        OrderHistoryGrid.AddItem (obj_products.PartNumber & vbTab & obj_products.Description & vbTab & _
                                  FormatCurrency(obj_items.Price) & vbTab & obj_items.Qty & vbTab & _
                                  FormatCurrency(obj_items.Price * obj_items.Qty))
    Next lng_loop
End Sub

Private Sub cmdDeleteOrder_Click()
    Dim int_result As Integer

    'prompt the user
    int_result = MsgBox("Are you sure that you want to delete this order?", vbYesNo)
    
    'if yes, remove the order
    If int_result = vbYes Then
        'remove the order from the DOM
        Call m_obj_orders.SelectOrder(lstOrders.Text)
        Call m_obj_orders.DeleteOrder
        
        'remove the order from the listbox
        Call lstOrders.RemoveItem(lstOrders.ListIndex)
        
        'reset the list index
        lstOrders.ListIndex = 0
    End If
End Sub

Private Sub cmdEdit_Click()
    'set focus to the first tab
    SSTab1.Tab = 0
    
    'disable the second tab
    SSTab1.TabEnabled(1) = False
    
    'set the order into the new order tab
    Call DisplayOrder(lstOrders.Text)
End Sub

'-------------------------------------------------------------------------
'   Private Methods
'-------------------------------------------------------------------------
Private Sub PopulateCustomerList()
    Dim obj_customers As CCustomersDB
    Dim obj_data As CCustomerData
    
    'create a customer DB object
    Set obj_customers = New CCustomersDB
    
    'create a new customer list collection
    Set m_col_customers = New Collection
    
    'loop through each element
    Call obj_customers.MoveFirst
    Do
        'create a new customer data object
        Set obj_data = New CCustomerData
        
        'populate the customer data object
        obj_data.CompanyID = obj_customers.CompanyID
        obj_data.CompanyName = obj_customers.CompanyName
        obj_data.OwnerName = obj_customers.LastName & ", " & obj_customers.FirstName & " " & obj_customers.MiddleName
                
        'add it to the collection
        Call m_col_customers.Add(obj_data)
        
        'add it to the drop down list
        cmbCustomer.AddItem (obj_data.CompanyName & " - " & obj_data.OwnerName)
        cmbCustomer.ItemData(cmbCustomer.NewIndex) = m_col_customers.Count
    Loop While (obj_customers.MoveNext = False)
    
    'release the customer DB object
    Set obj_customers = Nothing
End Sub

Private Sub PopulateProductList()
    Dim obj_products As CProductsDB
    Dim obj_data As CProductData
    
    'create a customer DB object
    Set obj_products = New CProductsDB
    
    'create a new customer list collection
    Set m_col_products = New Collection
    
    'loop through each element
    Call obj_products.MoveFirst
    Do
        'create a new customer data object
        Set obj_data = New CProductData
        
        'populate the customer data object
        obj_data.ProductID = obj_products.ProductID
        obj_data.Manufacturer = obj_products.Manufacturer
        obj_data.PartNumber = obj_products.PartNumber
        obj_data.Description = obj_products.Description
        obj_data.Price = obj_products.Price
        
        'add it to the collection
        Call m_col_products.Add(obj_data)
        
        'add it to the drop down list
        cmbProducts.AddItem (obj_data.Description)
        cmbProducts.ItemData(cmbProducts.NewIndex) = m_col_products.Count
    Loop While (obj_products.MoveNext = False)
    
    'release the customer DB object
    Set obj_products = Nothing
End Sub

Private Sub PopulateOrderList(ByVal p_str_custID As String)
    Dim col_orderIDs As Collection
    Dim var_orderID As Variant
    
    'get a list of the orders for the customer
    Set col_orderIDs = m_obj_orders.GetOrderIDs(p_str_custID)
    
    'clear the list
    lstOrders.Clear
    
    'loop through each ID
    For Each var_orderID In col_orderIDs
        'add the item to the list box
        Call lstOrders.AddItem(var_orderID)
    Next var_orderID
End Sub

Private Sub AddOrder()
    Dim lng_index As Long
    Dim str_custID As String
    Dim obj_orderItem As COrderItemsDB
    Dim lng_loop As Long
    
    'get the customer ID
    lng_index = cmbCustomer.ItemData(cmbCustomer.ListIndex)
    str_custID = m_col_customers(lng_index).CompanyID
    
    'add a new order
    Call m_obj_orders.AddOrder(str_custID)
    
    'set the order properties
    m_obj_orders.OrderDate = Date
    m_obj_orders.TotalCost = CCur(Right(lblTotal.Caption, Len(lblTotal.Caption) - 15))
    
    'get a reference to the items
    Set obj_orderItem = m_obj_orders.OrderItems
    
    'copy the data
    For lng_loop = 1 To OrderGrid.Rows - 1
        'create a new item
        Call obj_orderItem.AddItem
        
        'set the item properties
        obj_orderItem.ProductID = OrderGrid.TextMatrix(lng_loop, 0)
        obj_orderItem.Qty = CLng(OrderGrid.TextMatrix(lng_loop, 4))
        obj_orderItem.Price = CCur(OrderGrid.TextMatrix(lng_loop, 3))
    Next lng_loop
End Sub

Private Sub DisplayOrder(ByVal p_str_orderID As String)
    Dim obj_items As COrderItemsDB
    Dim obj_products As New CProductsDB
    Dim lng_loop As Long
    Dim cur_total As Currency
    
    'select the order
    Call m_obj_orders.SelectOrder(p_str_orderID)
    
    'setup the order number and date
    lblActualOrderNumber.Caption = m_obj_orders.OrderID
    lblActualOrderDate.Caption = CStr(m_obj_orders.OrderDate)
    
    'get a reference to the items
    Set obj_items = m_obj_orders.OrderItems
    
    'populate the grid
    OrderGrid.Rows = 1
    For lng_loop = 0 To obj_items.ItemCount - 1
        'select the item
        Call obj_items.SelectItem(lng_loop)
    
        'find the product
        Call obj_products.FindProduct(obj_items.ProductID)
    
        'add the grid item
        Call OrderGrid.AddItem(obj_items.ProductID & vbTab & obj_products.PartNumber & vbTab & _
                               obj_products.Description & vbTab & FormatCurrency(obj_items.Price) & _
                               vbTab & obj_items.Qty & vbTab & FormatCurrency(obj_items.Price * obj_items.Qty))
                                 
        'update the total
        cur_total = cur_total + (obj_items.Price * obj_items.Qty)
    Next lng_loop
    
    'set the new total
    lblTotal.Caption = "Total Cost = " & FormatCurrency(cur_total)
End Sub

Private Sub UpdateOrder()
    Dim obj_items As COrderItemsDB
    Dim obj_products As New CProductsDB
    Dim lng_loop As Long
    Dim cur_total As Currency
    
    'select the order
    Call m_obj_orders.SelectOrder(lblActualOrderNumber.Caption)
        
    'set the new total
    m_obj_orders.TotalCost = CCur(Right(lblTotal.Caption, Len(lblTotal.Caption) - 15))
    
    'get a reference to the items
    Set obj_items = m_obj_orders.OrderItems
    
    'remove all the line items
    Call obj_items.SelectItem(0)
    For lng_loop = 0 To obj_items.ItemCount - 1
        obj_items.DeleteItem
    Next lng_loop
    
    'copy the data
    For lng_loop = 1 To OrderGrid.Rows - 1
        'create a new item
        Call obj_items.AddItem
        
        'set the item properties
        obj_items.ProductID = OrderGrid.TextMatrix(lng_loop, 0)
        obj_items.Qty = CLng(OrderGrid.TextMatrix(lng_loop, 4))
        obj_items.Price = CCur(OrderGrid.TextMatrix(lng_loop, 3))
    Next lng_loop
End Sub

