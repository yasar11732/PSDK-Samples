VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUsersDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CUserDB
'
'   Description: This class wraps the Users DB file to provide a simple
'                interface
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Constants
'-------------------------------------------------------------------------
Public Enum UDB_Results
    udb_Success = 0
    udb_BadUsername = 1
    udb_BadPassword = 2
End Enum

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Function VerifyLogin(ByVal p_str_username As String, ByVal p_str_password As String) As UDB_Results
    Dim xml_document As IXMLDOMDocument
    Dim str_password As String
    
    'create the xml dom document
    Set xml_document = CreateObject("Microsoft.XMLDOM")
    
    'load the document
    Call xml_document.loadXML(ReadXMLFromFile(c_str_usersDB))
    
    'get the user's real password
    If GetPassword(p_str_username, str_password, xml_document.documentElement) = False Then
        'user name was not found
        VerifyLogin = udb_BadUsername
    Else
        'compare the passwords
        If str_password = p_str_password Then
            VerifyLogin = udb_Success
        Else
            VerifyLogin = udb_BadPassword
        End If
    End If
    
    'release the DOM document
    Set xml_document = Nothing
End Function

Private Function GetPassword(ByVal p_str_username As String, ByRef p_str_password As String, ByRef p_xml_node As IXMLDOMNode) As Boolean
    Dim str_query As String
    Dim xml_node As IXMLDOMNode
    Dim str_password As String
    
    'format the query
    str_query = "users/user[name='" & p_str_username & "']/password"
    
    'search for the username
    Set xml_node = p_xml_node.selectSingleNode(str_query)
    
    'read the password
    If xml_node Is Nothing Then
        'set the password to a null string
        p_str_password = ""
        
        'show that the user wasn't found
        GetPassword = False
    Else
        'set the password
        p_str_password = xml_node.Text
    
        'show that the user was found
        GetPassword = True
    End If
    
    'release the node
    Set xml_node = Nothing
End Function






