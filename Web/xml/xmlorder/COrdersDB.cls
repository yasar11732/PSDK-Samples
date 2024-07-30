VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "COrdersDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: COrdersDB
'
'   Description: This class wraps the Orders DB file to provide a DB
'                like interface.  This includes MoveFirst, MoveLast,
'                MoveNext, MovePrevious, Add, Delete, Edit, and Update.
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------
Private m_xml_document As IXMLDOMDocument
Private m_xml_currentNode As IXMLDOMNode

'-------------------------------------------------------------------------
'   Class Methods
'-------------------------------------------------------------------------
Private Sub Class_Initialize()
    'create the xml dom document
    Set m_xml_document = CreateObject("Microsoft.XMLDOM")
    
    'load the document
    Call m_xml_document.loadXML(ReadXMLFromFile(c_str_ordersDB))
    
    'check if xml exists in the file
    If m_xml_document.xml = "" Then
        Call m_xml_document.loadXML("<root></root>")
    End If
End Sub

Private Sub Class_Terminate()
    'save the log data
    Call WriteXMLToFile(c_str_ordersDB, m_xml_document.xml)
    
    'release the DOM document
    Set m_xml_document = Nothing
End Sub

'-------------------------------------------------------------------------
'   Misc Orders Methods
'-------------------------------------------------------------------------
Public Function GetOrderIDs(ByVal p_str_custID As String) As Collection
    Dim str_query As String
    Dim xml_nodeList As IXMLDOMNodeList
    Dim col_IDs As New Collection
    Dim lng_loop As Long

    'get all orders for the customer
    str_query = "//Orders/Order_Number[../Cust_ID = '" & p_str_custID & "']"
    Set xml_nodeList = m_xml_document.selectNodes(str_query)
    
    'move the IDs to the collection
    For lng_loop = 0 To xml_nodeList.length - 1
        'add the item to the list
        Call col_IDs.Add(xml_nodeList(lng_loop).Text)
    Next lng_loop
    
    'return the count
    Set GetOrderIDs = col_IDs
End Function

'returns the Order ID of the created order
Public Function AddOrder(ByVal p_str_custID As String) As String
    'create the new node
    Set m_xml_currentNode = CreateNewOrder()
    
    'append the order to the document
    Call m_xml_document.documentElement.appendChild(m_xml_currentNode)
    
    'set the customer ID
    m_xml_currentNode.selectSingleNode("Cust_ID").Text = p_str_custID
    
    'return the new ID
    AddOrder = m_xml_currentNode.selectSingleNode("Order_Number").Text
End Function

Public Function SelectOrder(ByVal p_str_orderID As String) As Boolean
    Dim xml_selectedNode As IXMLDOMNode
    Dim str_query As String

    'check if the node is found
    str_query = "//Orders[Order_Number = '" + p_str_orderID + "']"
    Set xml_selectedNode = m_xml_document.selectSingleNode(str_query)
    
    If xml_selectedNode Is Nothing Then
        'no node found, return false
        SelectOrder = False
    Else
        'set the current node to the selected node
        Set m_xml_currentNode = xml_selectedNode
        
        'return true
        SelectOrder = True
    End If
End Function

'returns the Order ID of the selected order
Public Function DeleteOrder() As String
    Dim xml_node As IXMLDOMNode
    
    'cache the current node
    Set xml_node = m_xml_currentNode
            
    'set to the next node (or previous if no next is available)
    If m_xml_currentNode.nextSibling Is Nothing Then
        Set m_xml_currentNode = xml_node.previousSibling
    Else
        Set m_xml_currentNode = xml_node.nextSibling
    End If
    
    'remove the node
    Call xml_node.parentNode.removeChild(xml_node)
End Function

'-------------------------------------------------------------------------
'   Private Methods
'-------------------------------------------------------------------------
Private Function CreateNewOrder() As IXMLDOMNode
    Dim xml_node As IXMLDOMNode
    Dim xml_orderNumber As IXMLDOMNode
    Dim xml_attribute As IXMLDOMNode
    
    'create the new node
    Set xml_node = m_xml_document.createElement("Orders")
    
    'create the sub nodes
    Set xml_orderNumber = xml_node.appendChild(m_xml_document.createElement("Order_Number"))
    Call xml_node.appendChild(m_xml_document.createElement("Cust_ID"))
    
    'create the attributes
    Set xml_attribute = m_xml_document.createAttribute("Date")
    xml_attribute.Text = CStr(Date)
    Call xml_orderNumber.Attributes.setNamedItem(xml_attribute)
    
    Set xml_attribute = m_xml_document.createAttribute("Total_Cost")
    Call xml_orderNumber.Attributes.setNamedItem(xml_attribute)
    
    'set the order number data
    xml_orderNumber.Text = GenerateOrderNumber
    
    'return the new node
    Set CreateNewOrder = xml_node
End Function

Private Function GenerateOrderNumber() As String
    Dim xml_nodeList As IXMLDOMNodeList
    Dim str_query As String
    
    Dim lng_loop As Long
    Dim lng_value As Long
    Dim lng_max As Long
    
    'get all the nodes using the same first 2 letters
    str_query = "//Order_Number"
    Set xml_nodeList = m_xml_document.selectNodes(str_query)

    'find the maximum number used
    For lng_loop = 0 To xml_nodeList.length - 1
        'check the value of the addition
        lng_value = Val(xml_nodeList(lng_loop).Text)
        
        'check if we have a new max
        lng_max = IIf(lng_value > lng_max, lng_value, lng_max)
    Next lng_loop
    
    'add max and return the new ID number
    GenerateOrderNumber = CStr(lng_max + 1)
End Function

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get OrderID() As String
    If m_xml_currentNode Is Nothing Then
        OrderID = ""
    Else
        OrderID = m_xml_currentNode.selectSingleNode("Order_Number").Text
    End If
End Property

Property Get OrderDate() As String
    If m_xml_currentNode Is Nothing Then
        OrderDate = ""
    Else
        OrderDate = m_xml_currentNode.selectSingleNode("Order_Number").Attributes.getNamedItem("Date").Text
    End If
End Property

Property Get TotalCost() As Currency
    If m_xml_currentNode Is Nothing Then
        TotalCost = 0
    Else
        TotalCost = CCur(m_xml_currentNode.selectSingleNode("Order_Number").Attributes.getNamedItem("Total_Cost").Text)
    End If
End Property

Property Get CustID() As String
    If m_xml_currentNode Is Nothing Then
        CustID = ""
    Else
        CustID = m_xml_currentNode.selectSingleNode("Cust_ID").Text
    End If
End Property

Property Get OrderItems() As COrderItemsDB
    If m_xml_currentNode Is Nothing Then
        Set OrderItems = Nothing
    Else
        'create the DB object
        Set OrderItems = New COrderItemsDB
        
        'initialize the DB object with the order node
        Call OrderItems.LoadOrder(m_xml_document, m_xml_currentNode)
    End If
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let OrderID(ByVal p_str_data As String)
    m_xml_currentNode.selectSingleNode("Order_Number").Text = p_str_data
End Property

Property Let OrderDate(ByVal p_str_data As String)
    m_xml_currentNode.selectSingleNode("Order_Number").Attributes.getNamedItem("Date").Text = p_str_data
End Property

Property Let TotalCost(ByVal p_cur_data As Currency)
    m_xml_currentNode.selectSingleNode("Order_Number").Attributes.getNamedItem("Total_Cost").Text = CStr(p_cur_data)
End Property

Property Let CustID(ByVal p_str_data As String)
    m_xml_currentNode.selectSingleNode("Cust_ID").Text = p_str_data
End Property
