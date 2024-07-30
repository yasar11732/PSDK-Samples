VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CLogDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CLogDB
'
'   Description: This class wraps the Log DB file to provide a simple
'                interface
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Function AddLogEntry(ByVal p_str_userName As String, ByVal p_dat_date As Date) As Boolean
    Dim xml_document As IXMLDOMDocument
    Dim str_password As String
    
    'create the xml dom document
    Set xml_document = CreateObject("Microsoft.XMLDOM")

    'load the document
    Call xml_document.loadXML(ReadXMLFromFile(c_str_logDB))
    
    'check if xml exists in the file
    If xml_document.xml = "" Then
        Call xml_document.loadXML("<root></root>")
    End If
    
    'create the entry into the log
    Call CreateLogEntry(p_str_userName, p_dat_date, xml_document)
    
    'save the log data
    Call WriteXMLToFile(c_str_logDB, xml_document.xml)
    
    'release the DOM document
    Set xml_document = Nothing
End Function

Private Sub CreateLogEntry(ByVal p_str_userName As String, ByVal p_dat_date As Date, ByRef p_xml_document As IXMLDOMDocument)
    Dim xml_node As IXMLDOMNode
    
    'create the new log node
    Set xml_node = p_xml_document.createElement("log")
    
    'add the node to the document
    Set xml_node = p_xml_document.documentElement.appendChild(xml_node)
    
    'add the date and user to the new node
    Call AddAttributes(p_str_userName, p_dat_date, p_xml_document)
End Sub

Private Sub AddAttributes(ByVal p_str_userName As String, ByVal p_dat_date As Date, ByRef p_xml_document As IXMLDOMDocument)
    Dim xml_logNode As IXMLDOMNode
    Dim xml_node As IXMLDOMNode
            
    'get the new node
    Set xml_logNode = p_xml_document.documentElement.lastChild
            
    'create the new date atribute
    Set xml_node = p_xml_document.createAttribute("User")
    xml_node.Text = p_str_userName
        
    'add the attribute to the list
    Call xml_logNode.Attributes.setNamedItem(xml_node)
            
    'create the new user atribute
    Set xml_node = p_xml_document.createAttribute("Date")
    xml_node.Text = CStr(p_dat_date)
        
    'add the attribute to the list
    Call xml_logNode.Attributes.setNamedItem(xml_node)
End Sub






