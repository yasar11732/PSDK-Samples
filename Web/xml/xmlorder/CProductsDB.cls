VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CProductsDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CProductsDB
'
'   Description: This class wraps the Products DB file to provide a DB
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
    Call m_xml_document.loadXML(ReadXMLFromFile(c_str_productsDB))
    
    'check if xml exists in the file
    If m_xml_document.xml = "" Then
        Call m_xml_document.loadXML("<root></root>")
    End If
        
    'load the first node
    Set m_xml_currentNode = m_xml_document.documentElement.firstChild
End Sub

Private Sub Class_Terminate()
    'save the log data
    Call WriteXMLToFile(c_str_productsDB, m_xml_document.xml)
    
    'release the DOM document
    Set m_xml_document = Nothing
End Sub

'-------------------------------------------------------------------------
'   Data Manipulation Methods
'-------------------------------------------------------------------------
Public Function FindProduct(ByVal p_str_productID As String) As Boolean
    Dim xml_selectedNode As IXMLDOMNode
    Dim str_query As String

    'check if the node already exists
    str_query = "//ID[. $ige$ '" + p_str_productID + "']"
    Set xml_selectedNode = m_xml_document.selectSingleNode(str_query)
    
    If xml_selectedNode Is Nothing Then
        'no node found, return false
        FindProduct = False
    Else
        'set the current node to the selected node
        Set m_xml_currentNode = xml_selectedNode
        
        'return true
        FindProduct = True
    End If
End Function

'-------------------------------------------------------------------------
'   Location Manipulation Methods
'-------------------------------------------------------------------------
Public Sub MoveFirst()
    'set the current cell to the first one
    Set m_xml_currentNode = m_xml_document.documentElement.firstChild
End Sub

Public Sub MoveLast()
    'set the current cell to the first one
    Set m_xml_currentNode = m_xml_document.documentElement.lastChild
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

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get ProductID() As String
    If m_xml_currentNode Is Nothing Then
        ProductID = ""
    Else
        ProductID = m_xml_currentNode.childNodes(0).Text
    End If
End Property

Property Get Manufacturer() As String
    If m_xml_currentNode Is Nothing Then
        Manufacturer = ""
    Else
        Manufacturer = m_xml_currentNode.selectSingleNode("Manufacturer").Text
    End If
End Property

Property Get PartNumber() As String
    If m_xml_currentNode Is Nothing Then
        PartNumber = ""
    Else
        PartNumber = m_xml_currentNode.selectSingleNode("Manuf_Part_Num").Text
    End If
End Property

Property Get Description() As String
    If m_xml_currentNode Is Nothing Then
        Description = ""
    Else
        Description = m_xml_currentNode.selectSingleNode("Description").Text
    End If
End Property

Property Get Price() As Single
    If m_xml_currentNode Is Nothing Then
        Price = 0
    Else
        Price = CSng(m_xml_currentNode.selectSingleNode("Price").Text)
    End If
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let ProductID(ByRef p_str_data As String)
    m_xml_currentNode.Text = p_str_data
End Property

Property Let Manufacturer(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("Manufacturer").Text = p_str_data
End Property

Property Let PartNumber(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("Manuf_part_num").Text = p_str_data
End Property

Property Let Description(ByRef p_str_data As String)
    m_xml_currentNode.selectSingleNode("Description").Text = p_str_data
End Property

Property Let Price(ByRef p_sng_data As Single)
    m_xml_currentNode.selectSingleNode("Price").Text = CStr(p_sng_data)
End Property

