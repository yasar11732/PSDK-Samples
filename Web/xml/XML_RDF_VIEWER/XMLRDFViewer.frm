VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.Form frmXMLRDFViewer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "RDF Viewer"
   ClientHeight    =   8535
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11985
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8535
   ScaleWidth      =   11985
   StartUpPosition =   3  'Windows Default
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   7095
      Left            =   2880
      TabIndex        =   6
      Top             =   1320
      Width           =   9015
      ExtentX         =   15901
      ExtentY         =   12515
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "res://H:\WINNT\system32\shdoclc.dll/navcancl.htm#res://C:\WINNT\System32\shdoclc.dll/dnserror.htm#http:///"
   End
   Begin VB.CommandButton btnSpaceNews 
      Height          =   615
      Left            =   3000
      Picture         =   "XMLRDFViewer.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   600
      Width           =   1695
   End
   Begin VB.CommandButton btnMacWeek 
      Height          =   615
      Left            =   1080
      Picture         =   "XMLRDFViewer.frx":05CE
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   600
      Width           =   1695
   End
   Begin VB.CommandButton btnGo 
      Caption         =   "Go"
      Height          =   375
      Left            =   6600
      TabIndex        =   3
      Top             =   120
      Width           =   735
   End
   Begin VB.ListBox List1 
      Height          =   7080
      Left            =   120
      TabIndex        =   2
      Top             =   1320
      Width           =   2655
   End
   Begin VB.TextBox txtURL 
      Height          =   375
      Left            =   1080
      TabIndex        =   1
      Top             =   120
      Width           =   5415
   End
   Begin VB.Label Label1 
      Caption         =   "Data URL:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   855
   End
End
Attribute VB_Name = "frmXMLRDFViewer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
' Create an array to hold the XML items
Dim URLs() As String

Private Sub btnGo_Click()
  ' Clear the items list and reload it
  List1.Clear
  LoadRDF List1, txtURL
End Sub

Private Sub btnMacWeek_Click()
 txtURL = "http://macweek.zdnet.com/macweek.xml"
 btnGo_Click
End Sub

Private Sub btnSpaceNews_Click()
  txtURL = "http://exosci.com/exosci.rdf"
  btnGo_Click
End Sub

Private Sub Form_Load()
 List1.Clear
 SetEnables
End Sub

Private Sub List1_Click()
    ' Get the URL for the selected item and then load it up in the browser
    WebBrowser1.Navigate2 URLs(List1.ListIndex)
End Sub

Private Sub txtURL_Change()
  SetEnables
End Sub

Private Sub SetEnables()
  btnGo.Enabled = Len(txtURL) <> 0
End Sub

Private Sub LoadRDF(lstList As ListBox, strURL As String)
  Dim xmlDoc As DOMDocument
  Dim xmlRoot As IXMLDOMElement
  Dim xmlItem As IXMLDOMElement
  Dim xmlItemChild As IXMLDOMElement
  Dim i As Integer
  Dim j As Integer
  Dim k As Integer
  Dim bloaded As Boolean
  
  ' Load in the XML data
  Set xmlDoc = New DOMDocument
  xmlDoc.async = False
  bloaded = xmlDoc.Load(strURL)
  
  ' If the data is successfully loaded, populate the list
  If (bloaded) Then
    ' Create an object to represent the root element
    Set xmlRoot = xmlDoc.documentElement
    k = 0
    ' Loop through each child node in the root
    For i = 0 To xmlRoot.childNodes.length - 1
      ' Create an object to represent the current child node
      Set xmlItem = xmlRoot.childNodes.Item(i)
      ' If the node represents an item
      If (xmlItem.tagName = "item") Then
        ' Loop through each child node in this node
        For j = 0 To xmlItem.childNodes.length - 1
          ' Create an object to represent the current child node
          Set xmlItemChild = xmlItem.childNodes.Item(j)
          ' If the node represents a title
          If (xmlItemChild.tagName = "title") Then
            ' Add the title text to the list
            List1.AddItem xmlItemChild.Text
          End If
          ' If the node represents a link
          If (xmlItemChild.tagName = "link") Then
            ' Add a row to the array and add the link
            ReDim Preserve URLs(k + 1) As String
            URLs(k) = xmlItemChild.Text
            k = k + 1
          End If
        Next j
      End If
    Next i
  End If
  
End Sub
