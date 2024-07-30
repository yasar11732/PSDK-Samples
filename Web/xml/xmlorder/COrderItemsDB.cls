VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "COrderItemsDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False

'-------------------------------------------------------------------------
'
'   Module Name: COrdersDB
'
'   Description: This class wraps the Orders DB file to provide an
'                interface to the items in the order
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------
Private m_xml_document As IXMLDOMDocument
Private m_xml_orderNode As IXMLDOMNode
Private m_xml_currentItem As IXMLDOMNode

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Sub LoadOrder(ByRef p_xml_document As IXMLDOMDocument, ByRef p_xml_orderNode As IXMLDOMNode)
    'save a reference to the node and the document
    Set m_xml_document = p_xml_document
    Set m_xml_orderNode = p_xml_orderNode
End Sub

'returns the index of the new item
Public Function AddItem() As Long
    Dim xml_node As IXMLDOMNode
    
    'create a new node
    Set m_xml_currentItem = m_xml_document.createElement("Item")
    
    'add it to the list
    Call m_xml_orderNode.appendChild(m_xml_currentItem)
    
    'create the sub nodes
    Set xml_node = m_xml_document.createElement("ProductID")
    Call m_xml_currentItem.appendChild(xml_node)
    Set xml_node = m_xml_document.createElement("Qty")
    Call m_xml_currentItem.appendChild(xml_node)
    Set xml_node = m_xml_document.createElement("Price")
    Call m_xml_currentItem.appendChild(xml_node)
    
    'return the index
    AddItem = m_xml_orderNode.childNodes.length
End Function

Public Sub SelectItem(ByVal p_lng_index As Long)
    'set the current item to the selected index
    Set m_xml_currentItem = m_xml_orderNode.childNodes(p_lng_index + 2)
End Sub

'returns the count of items
Public Function ItemCount() As Long
    'return the count
    ItemCount = m_xml_orderNode.childNodes.length - 2
End Function

'returns the new index
Public Function DeleteItem() As Long
    Dim xml_node As IXMLDOMNode
    
    'cache the current node
    Set xml_node = m_xml_currentItem
            
    'set to the next node (or previous if no next is available)
    If m_xml_currentItem.nextSibling Is Nothing Then
        Set m_xml_currentItem = xml_node.previousSibling
    Else
        Set m_xml_currentItem = xml_node.nextSibling
    End If
    
    'remove the node
    Call xml_node.parentNode.removeChild(xml_node)
End Function

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get ProductID() As String
    If m_xml_currentItem Is Nothing Then
        ProductID = ""
    Else
        ProductID = m_xml_currentItem.selectSingleNode("ProductID").Text
    End If
End Property

Property Get Qty() As String
    If m_xml_currentItem Is Nothing Then
        Qty = ""
    Else
        Qty = m_xml_currentItem.selectSingleNode("Qty").Text
    End If
End Property

Property Get Price() As Currency
    If m_xml_currentItem Is Nothing Then
        Price = 0
    Else
        Price = CCur(m_xml_currentItem.selectSingleNode("Price").Text)
    End If
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let ProductID(ByVal p_str_data As String)
    m_xml_currentItem.selectSingleNode("ProductID").Text = p_str_data
End Property

Property Let Qty(ByVal p_str_data As String)
    m_xml_currentItem.selectSingleNode("Qty").Text = p_str_data
End Property

Property Let Price(ByVal p_cur_data As Currency)
    m_xml_currentItem.selectSingleNode("Price").Text = CStr(p_cur_data)
End Property
