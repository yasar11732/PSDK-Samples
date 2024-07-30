VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form frmParser 
   Caption         =   "XML Tree View"
   ClientHeight    =   4884
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   6516
   Icon            =   "frmParser.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4884
   ScaleWidth      =   6516
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdFont 
      Caption         =   "Font..."
      Height          =   255
      Left            =   5760
      TabIndex        =   5
      Top             =   240
      Width           =   735
   End
   Begin ComctlLib.TreeView tvwXMLData 
      Height          =   3735
      Left            =   0
      TabIndex        =   4
      Top             =   720
      Width           =   6495
      _ExtentX        =   11451
      _ExtentY        =   6583
      _Version        =   327682
      Style           =   7
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton cmdParse 
      Caption         =   "Load"
      Height          =   255
      Left            =   4920
      TabIndex        =   3
      Top             =   240
      Width           =   735
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   255
      Left            =   4440
      TabIndex        =   2
      Top             =   240
      Width           =   375
   End
   Begin VB.TextBox txtFileName 
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Text            =   "sample.xml"
      Top             =   240
      Width           =   3855
   End
   Begin MSComDlg.CommonDialog cmnd 
      Left            =   5040
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Status 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   4560
      Width           =   6375
   End
   Begin VB.Label Label1 
      Caption         =   "URL:"
      Height          =   255
      Left            =   60
      TabIndex        =   1
      Top             =   270
      Width           =   375
   End
End
Attribute VB_Name = "frmParser"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: frmParser
'
'   Description: This form displays the data from the XML file in a
'                tree view control
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   DOM Constants
'-------------------------------------------------------------------------
Const READYSTATE_COMPLETE = 4

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------
Dim WithEvents xml_document As DOMDocument
Attribute xml_document.VB_VarHelpID = -1

'-------------------------------------------------------------------------
'   Public Methods
'-------------------------------------------------------------------------
Public Sub DisplayDomNode(ByVal int_ancestor As Integer, ByRef xml_node As MSXML.IXMLDOMNode, ByVal int_level As Integer)
    On Error Resume Next
    
    Dim str_line As String
    Dim int_index
    Dim obj_treeNode As Node
    Dim lng_loop As Long
    
    'check if the provided node is nothing
    If xml_node Is Nothing Then
        Exit Sub
    End If
    
    'determine the type of node to get the correct formatting
    str_line = FormatNodeString(xml_node)
    
    'don't display anything if the line is NULL
    If str_line = "" Then
        Exit Sub
    End If
    
    'handle any attributes in the node
    If (xml_node.nodeType = NODE_ELEMENT) Then
        str_line = str_line & FormatAttributes(xml_node.Attributes)
    End If
    
    'check if the node is the root
    If int_ancestor = 0 Then
        Set obj_treeNode = tvwXMLData.Nodes.Add(, , , str_line)
    Else
        Set obj_treeNode = tvwXMLData.Nodes.Add(int_ancestor, tvwChild, , str_line)
    End If
    int_index = obj_treeNode.index
    
    'call this function recursively to display the child nodes
    If Not (xml_node.childNodes Is Nothing) Then
        For lng_loop = 0 To xml_node.childNodes.length - 1
            Call DisplayDomNode(int_index, xml_node.childNodes.Item(lng_loop), int_level & 1)
        Next lng_loop
    End If
End Sub

'-------------------------------------------------------------------------
'   Private Methods
'-------------------------------------------------------------------------
Private Function FormatNodeString(ByRef xml_node As IXMLDOMNode) As String
    Dim xml_entity As IXMLDOMEntity
    Dim xml_notation As IXMLDOMNotation
    Dim str_line As String

    If xml_node.nodeType = NODE_COMMENT Then
        'format the code comment line
        str_line = "<!--" & xml_node.nodeValue & "-->"
    ElseIf xml_node.nodeType = NODE_CDATA_SECTION Or xml_node.nodeType = NODE_TEXT Then
        'format the node value
        str_line = xml_node.nodeValue
    ElseIf xml_node.nodeType = NODE_DOCUMENT_TYPE Then
        'format the doc type line
        str_line = "DOCTYPE " & xml_node.nodeName
    ElseIf xml_node.nodeType = NODE_PROCESSING_INSTRUCTION Then
        'format the processing instruction
        str_line = "<?" & xml_node.nodeName & " " & xml_node.nodeValue & "?>"
    ElseIf xml_node.nodeType = NODE_ENTITY Then
        'get the entity reference
        Set xml_entity = xml_node
        
        'format the beginning of the entity line
        str_line = "<!ENTITY " & xml_node.nodeName
        
        'check if public and system IDs exist
        If (xml_entity.publicId <> "") Then
            'format the public ID part of the line
            str_line = str_line & " PUBLIC '" & xml_entity.publicId & "' '" & xml_entity.systemId & "'"
        ElseIf (xml_entity.systemId <> "") Then
            'format the system ID part of the line
            str_line = str_line & " SYSTEM '" & xml_entity.systemId & "'"
        End If
        
        'check if a notation name exists
        If (xml_entity.notationName <> "") Then
            'format the notation name part of the line
            str_line = str_line & " NDATA " & xml_entity.notationName
        End If
        
        'append the closing string
        str_line = str_line & ">"
    ElseIf xml_node.nodeType = NODE_NOTATION Then
        'get the notation reference
        Set xml_notation = xml_node
        
        'format the beginning of the notation line
        str_line = "<!NOTATION " & xml_node.nodeName
        
        'check if public and system IDs exist
        If (xml_notation.publicId <> "") Then
            'format the public ID part of the line
            str_line = str_line & " PUBLIC '" & xml_notation.publicId & "' '" & xml_notation.systemId & "'"
        ElseIf (xml_notation.systemId <> "") Then
            'format the system ID part of the line
            str_line = str_line & " SYSTEM '" & xml_notation.systemId & "'"
        End If
        
        'append the closing string
        str_line = str_line & ">"
    ElseIf xml_node.nodeType = NODE_ENTITY_REFERENCE Then
        'format the entity reference line
        str_line = "&" & xml_node.nodeName & ";"
    ElseIf xml_node.nodeType = NODE_DOCUMENT Then
        'format the document line
        str_line = txtFileName
    Else
        'format the line for all the rest of the node types
        str_line = xml_node.nodeName
    End If
    
    'return the string
    FormatNodeString = str_line
End Function

Private Function FormatAttributes(ByRef xml_namedNodeMap As IXMLDOMNamedNodeMap) As String
    Dim xml_attribute As IXMLDOMAttribute
    Dim str_line As String
    Dim lng_loop As Long
    
    'iterate through the attributes
    For lng_loop = 0 To xml_namedNodeMap.length - 1
        'get a reference to the attribute
        Set xml_attribute = xml_namedNodeMap.Item(lng_loop)
        
        'format the return string
        str_line = " " & xml_attribute.Name & "='" & xml_attribute.Value & "'"
    Next lng_loop
    
    'return the string
    FormatAttributes = str_line
End Function

'-------------------------------------------------------------------------
'   Button Event Handlers
'-------------------------------------------------------------------------
Private Sub cmdBrowse_Click()
    'use the common open dialog to get a filename
    cmnd.Filter = "XML (*.xml)|*.xml|All (*.*)|*.*"
    cmnd.ShowOpen
    
    'set the URL line
    txtFileName = cmnd.FileName
End Sub

Private Sub cmdFont_Click()
    'populate the common font dialog with the current fonts
    cmnd.FontName = tvwXMLData.Font.Name
    cmnd.FontItalic = tvwXMLData.Font.Italic
    cmnd.FontSize = tvwXMLData.Font.Size
    cmnd.FontBold = tvwXMLData.Font.Bold
    cmnd.Flags = cdlCFScreenFonts
    
    'display the common font dialog
    cmnd.ShowFont
    
    'set the treeview with the new fonts
    tvwXMLData.Font.Name = cmnd.FontName
    tvwXMLData.Font.Italic = cmnd.FontItalic
    tvwXMLData.Font.Size = cmnd.FontSize
    tvwXMLData.Font.Bold = cmnd.FontBold
End Sub

Private Sub cmdParse_Click()
    'clear the tree view
    tvwXMLData.Nodes.Clear
    
    'load the DOM document from the provided URL
    On Error Resume Next
    xml_document.async = True
    xml_document.Load txtFileName.Text
End Sub

'-------------------------------------------------------------------------
'   DOM Event Handlers
'-------------------------------------------------------------------------
Private Sub xml_document_ondataavailable()
    Dim xml_node As IXMLDOMNode
    Dim int_count As Integer
    
    'get a reference to an XML node
    Set xml_node = xml_document.documentElement
    
    'get the count of nodes loaded
    int_count = xml_document.childNodes.length
    If (TypeName(xml_node) <> "Nothing") Then
        int_count = int_count + xml_node.childNodes.length
    End If
    
    'display the count in the status bar
    Status.Caption = "Loaded " & int_count & " nodes..."
End Sub

Private Sub xml_document_onreadystatechange()
    Dim xml_parseError As MSXML.IXMLDOMParseError
    Dim xml_node As MSXML.IXMLDOMNode
    
    'check if the document reference's status is complete
    If (xml_document.readyState = READYSTATE_COMPLETE) Then
    
        'get a reference to the parseerror object
        Set xml_parseError = xml_document.parseError
        
        'check if an error occured
        If TypeName(xml_document.documentElement) = "Nothing" Then
            'display the error
            MsgBox xml_parseError.reason, vbOKOnly
        Else
            'get a reference to the document
            Set xml_node = xml_document
            
            'display the nodes
            Call DisplayDomNode(0, xml_node, 0)
            
            'expand the first node in the tree
            tvwXMLData.Nodes.Item(1).Expanded = True
        End If
    End If
End Sub

'-------------------------------------------------------------------------
'   Form Event Handlers
'-------------------------------------------------------------------------
Private Sub Form_Load()
    'create the DOM document
    Set xml_document = CreateObject("Microsoft.XMLDOM")
End Sub

Private Sub Form_Resize()
    On Error Resume Next
    
    'set the width of the tree view based on the form size
    tvwXMLData.Width = Me.ScaleWidth - tvwXMLData.Left - 60
    tvwXMLData.Height = Me.ScaleHeight - tvwXMLData.Top - 60 - Status.Height
End Sub


