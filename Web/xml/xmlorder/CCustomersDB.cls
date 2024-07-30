VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CCustomersDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CCustomersDB
'
'   Description: This class wraps the Customers DB file to provide a DB
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
Private m_xml_editNode As IXMLDOMNode
Private m_bln_inEdit As Boolean

'-------------------------------------------------------------------------
'   Class Methods
'-------------------------------------------------------------------------
Private Sub Class_Initialize()
    'create the xml dom document
    Set m_xml_document = CreateObject("Microsoft.XMLDOM")
    
    'load the document
    Call m_xml_document.loadXML(ReadXMLFromFile(c_str_customersDB))
    
    'check if xml exists in the file
    If m_xml_document.xml = "" Then
        Call m_xml_document.loadXML("<root></root>")
    End If
        
    'load the first node
    Set m_xml_currentNode = m_xml_document.documentElement.childNodes(0).firstChild
End Sub

Private Sub Class_Terminate()
    'save the log data
    Call WriteXMLToFile(c_str_customersDB, m_xml_document.xml)
    
    'release the DOM document
    Set m_xml_document = Nothing
End Sub

'-------------------------------------------------------------------------
'   Data Manipulation Methods
'-------------------------------------------------------------------------
Public Sub AddCustomer()
    'create a new node
    Set m_xml_editNode = CreateNewCustomer
    Set m_xml_currentNode = m_xml_editNode
End Sub

Public Sub DeleteCustomer()
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
End Sub

Public Sub EditCustomer()
    'set the edit node to the current node
    Set m_xml_editNode = m_xml_currentNode.cloneNode(True)
    Set m_xml_currentNode = m_xml_editNode
End Sub

Public Sub SaveCustomer()
    Dim xml_selectedNode As IXMLDOMNode
    Dim lng_nodeIndex As Long
    Dim str_query As String

    'generate the ID it doesn't exist
    If m_xml_editNode.Attributes.getNamedItem("ID").Text = "" Then
        m_xml_editNode.Attributes.getNamedItem("ID").Text = GenerateIDNumber(m_xml_editNode)
    End If

    'check if the node already exists
    str_query = "//customer[@ID = '" + m_xml_editNode.Attributes.getNamedItem("ID").Text + "']"
    Set xml_selectedNode = m_xml_document.selectSingleNode(str_query)
    
    If xml_selectedNode Is Nothing Then
        'add the node to the node list
        Call m_xml_document.documentElement.childNodes(0).appendChild(m_xml_editNode)
    Else
        'copy the edit node to the existing node
        Call xml_selectedNode.parentNode.replaceChild(m_xml_editNode, xml_selectedNode)
        
        'set the new current node
        Set m_xml_editNode = Nothing
    End If
    
    'clear the edit node reference
    Set m_xml_editNode = Nothing
End Sub

Public Function FindCustomer(ByVal p_str_custID As String) As Boolean
    Dim xml_selectedNode As IXMLDOMNode
    Dim str_query As String

    'check if the node already exists
    str_query = "//customer[@ID = '" + p_str_custID + "']"
    Set xml_selectedNode = m_xml_document.selectSingleNode(str_query)
    
    If xml_selectedNode Is Nothing Then
        'no node found, return false
        FindCustomer = False
    Else
        'set the current node to the selected node
        Set m_xml_currentNode = xml_selectedNode
        
        'return true
        FindCustomer = True
    End If
End Function

'-------------------------------------------------------------------------
'   Location Manipulation Methods
'-------------------------------------------------------------------------
Public Sub MoveFirst()
    'set the current cell to the first one
    Set m_xml_currentNode = m_xml_document.documentElement.childNodes(0).firstChild
End Sub

Public Sub MoveLast()
    'set the current cell to the first one
    Set m_xml_currentNode = m_xml_document.documentElement.childNodes(0).lastChild
End Sub

Public Function MoveNext() As Boolean
    'check if it's too big
    If Not (m_xml_currentNode.nextSibling Is Nothing) Then
        'get the new element reference
        Set m_xml_currentNode = m_xml_currentNode.nextSibling
    End If
    
    'return true or false indicating the end of the list
    MoveNext = IIf(m_xml_currentNode.nextSibling Is Nothing, True, False)
End Function

Public Function MovePrev() As Boolean
    'check if it's too big
    If Not (m_xml_currentNode.previousSibling Is Nothing) Then
        'get the new element reference
        Set m_xml_currentNode = m_xml_currentNode.previousSibling
    End If
    
    'return true or false indicating the beginning of the list
    MovePrev = IIf(m_xml_currentNode.previousSibling Is Nothing, True, False)
End Function

Private Function CreateNewCustomer() As IXMLDOMNode
    Dim xml_node As IXMLDOMNode
    
    'create the new node
    Set xml_node = m_xml_document.createElement("customer")
    
    'create the attributes
    Call xml_node.Attributes.setNamedItem(m_xml_document.createAttribute("ID"))
        
    'create the sub nodes
    Call xml_node.appendChild(m_xml_document.createElement("company_name"))
    Call xml_node.appendChild(m_xml_document.createElement("first-name"))
    Call xml_node.appendChild(m_xml_document.createElement("middle-name"))
    Call xml_node.appendChild(m_xml_document.createElement("last-name"))
    Call xml_node.appendChild(m_xml_document.createElement("address_1"))
    Call xml_node.appendChild(m_xml_document.createElement("address_2"))
    Call xml_node.appendChild(m_xml_document.createElement("city"))
    Call xml_node.appendChild(m_xml_document.createElement("state"))
    Call xml_node.appendChild(m_xml_document.createElement("zip"))
    Call xml_node.appendChild(m_xml_document.createElement("home_phone"))
    Call xml_node.appendChild(m_xml_document.createElement("work_phone"))
    Call xml_node.appendChild(m_xml_document.createElement("method_of_payment"))
    Call xml_node.appendChild(m_xml_document.createElement("cc_exp"))
    Call xml_node.appendChild(m_xml_document.createElement("cc_num"))
    Call xml_node.appendChild(m_xml_document.createElement("ship_address_1"))
    Call xml_node.appendChild(m_xml_document.createElement("ship_address_2"))
    Call xml_node.appendChild(m_xml_document.createElement("ship_city"))
    Call xml_node.appendChild(m_xml_document.createElement("ship_state"))
    Call xml_node.appendChild(m_xml_document.createElement("ship_zip"))
    
    'return the new node
    Set CreateNewCustomer = xml_node
End Function

Private Function GenerateIDNumber(ByRef p_xml_node As IXMLDOMNode) As String
    Dim str_lastName As String
    Dim str_firstName As String
    Dim str_code As String
    
    Dim xml_nodeList As IXMLDOMNodeList
    Dim str_query As String
    
    Dim lng_loop As Long
    Dim lng_value As Long
    Dim lng_max As Long
    
    'generate the 2 letter code
    str_firstName = p_xml_node.selectSingleNode("first-name").Text
    str_lastName = p_xml_node.selectSingleNode("last-name").Text
    str_code = Left(str_firstName, 1) & Left(str_lastName, 1)

    'get all the nodes using the same first 2 letters
    str_query = "//@ID[value() $ige$ '" & str_code & "' $and$ value() $ile$ '" & str_code & "A']" 'the last restricts codes that do not begin with the same 2 digits
    Set xml_nodeList = m_xml_document.selectNodes(str_query)

    'find the maximum number used
    For lng_loop = 0 To xml_nodeList.length - 1
        'check the value of the addition
        lng_value = Val(Right(xml_nodeList(lng_loop).Text, Len(xml_nodeList(lng_loop).Text) - 2))
        
        'check if we have a new max
        lng_max = IIf(lng_value > lng_max, lng_value, lng_max)
    Next lng_loop
    
    'add max and return the new ID number
    GenerateIDNumber = str_code & CStr(lng_max + 1)
End Function

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get CompanyID() As String
    If m_xml_currentNode Is Nothing Then
        CompanyID = ""
    Else
        CompanyID = m_xml_currentNode.Attributes.getNamedItem("ID").Text
    End If
End Property

Property Get CompanyName() As String
    If m_xml_currentNode Is Nothing Then
        CompanyName = ""
    Else
        CompanyName = m_xml_currentNode.selectSingleNode("company_name").Text
    End If
End Property

Property Get FirstName() As String
    If m_xml_currentNode Is Nothing Then
        FirstName = ""
    Else
        FirstName = m_xml_currentNode.selectSingleNode("first-name").Text
    End If
End Property

Property Get MiddleName() As String
    If m_xml_currentNode Is Nothing Then
        MiddleName = ""
    Else
        MiddleName = m_xml_currentNode.selectSingleNode("middle-name").Text
    End If
End Property

Property Get LastName() As String
    If m_xml_currentNode Is Nothing Then
        LastName = ""
    Else
        LastName = m_xml_currentNode.selectSingleNode("last-name").Text
    End If
End Property

Property Get Address1() As String
    If m_xml_currentNode Is Nothing Then
        Address1 = ""
    Else
        Address1 = m_xml_currentNode.selectSingleNode("address_1").Text
    End If
End Property

Property Get Address2() As String
    If m_xml_currentNode Is Nothing Then
        Address2 = ""
    Else
        Address2 = m_xml_currentNode.selectSingleNode("address_2").Text
    End If
End Property

Property Get City() As String
    If m_xml_currentNode Is Nothing Then
        City = ""
    Else
        City = m_xml_currentNode.selectSingleNode("city").Text
    End If
End Property

Property Get State() As String
    If m_xml_currentNode Is Nothing Then
        State = ""
    Else
        State = m_xml_currentNode.selectSingleNode("state").Text
    End If
End Property

Property Get Zip() As String
    If m_xml_currentNode Is Nothing Then
        Zip = ""
    Else
        Zip = m_xml_currentNode.selectSingleNode("zip").Text
    End If
End Property

Property Get HomePhone() As String
    If m_xml_currentNode Is Nothing Then
        HomePhone = ""
    Else
        HomePhone = m_xml_currentNode.selectSingleNode("home_phone").Text
    End If
End Property

Property Get WorkPhone() As String
    If m_xml_currentNode Is Nothing Then
        WorkPhone = ""
    Else
        WorkPhone = m_xml_currentNode.selectSingleNode("work_phone").Text
    End If
End Property

Property Get MethodOfPayment() As String
    If m_xml_currentNode Is Nothing Then
        MethodOfPayment = ""
    Else
        MethodOfPayment = m_xml_currentNode.selectSingleNode("method_of_payment").Text
    End If
End Property

Property Get CCExp() As String
    If m_xml_currentNode Is Nothing Then
        CCExp = ""
    Else
        CCExp = m_xml_currentNode.selectSingleNode("cc_exp").Text
    End If
End Property

Property Get CCNum() As String
    If m_xml_currentNode Is Nothing Then
        CCNum = ""
    Else
        CCNum = m_xml_currentNode.selectSingleNode("cc_num").Text
    End If
End Property

Property Get ShipAddress1() As String
    If m_xml_currentNode Is Nothing Then
        ShipAddress1 = ""
    Else
        ShipAddress1 = m_xml_currentNode.selectSingleNode("ship_address_1").Text
    End If
End Property

Property Get ShipAddress2() As String
    If m_xml_currentNode Is Nothing Then
        ShipAddress2 = ""
    Else
        ShipAddress2 = m_xml_currentNode.selectSingleNode("ship_address_2").Text
    End If
End Property

Property Get ShipCity() As String
    If m_xml_currentNode Is Nothing Then
        ShipCity = ""
    Else
        ShipCity = m_xml_currentNode.selectSingleNode("ship_city").Text
    End If
End Property

Property Get ShipState() As String
    If m_xml_currentNode Is Nothing Then
        ShipState = ""
    Else
        ShipState = m_xml_currentNode.selectSingleNode("ship_state").Text
    End If
End Property

Property Get ShipZip() As String
    If m_xml_currentNode Is Nothing Then
        ShipZip = ""
    Else
        ShipZip = m_xml_currentNode.selectSingleNode("ship_zip").Text
    End If
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let CompanyID(ByRef p_str_data As String)
    m_xml_currentNode.Attributes.getNamedItem("ID").Text = p_str_data
End Property

Property Let CompanyName(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("company_name").Text = p_str_data
End Property

Property Let FirstName(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("first-name").Text = p_str_data
End Property

Property Let MiddleName(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("middle-name").Text = p_str_data
End Property

Property Let LastName(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("last-name").Text = p_str_data
End Property

Property Let Address1(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("address_1").Text = p_str_data
End Property

Property Let Address2(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("address_2").Text = p_str_data
End Property

Property Let City(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("city").Text = p_str_data
End Property

Property Let State(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("state").Text = p_str_data
End Property

Property Let Zip(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("zip").Text = p_str_data
End Property

Property Let HomePhone(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("home_phone").Text = p_str_data
End Property

Property Let WorkPhone(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("work_phone").Text = p_str_data
End Property

Property Let MethodOfPayment(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("method_of_payment").Text = p_str_data
End Property

Property Let CCExp(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("cc_exp").Text = p_str_data
End Property

Property Let CCNum(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("cc_num").Text = p_str_data
End Property

Property Let ShipAddress1(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("ship_address_1").Text = p_str_data
End Property

Property Let ShipAddress2(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("ship_address_2").Text = p_str_data
End Property

Property Let ShipCity(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("ship_zip").Text = p_str_data
End Property

Property Let ShipState(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("ship_state").Text = p_str_data
End Property

Property Let ShipZip(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("ship_zip").Text = p_str_data
End Property

