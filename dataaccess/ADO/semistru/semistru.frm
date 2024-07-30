VERSION 5.00
Begin VB.Form Form1 
   ClientHeight    =   8205
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   14940
   LinkTopic       =   "Form1"
   ScaleHeight     =   8205
   ScaleWidth      =   14940
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox Members 
      Height          =   7080
      Left            =   10800
      TabIndex        =   10
      Top             =   600
      Width           =   4095
   End
   Begin VB.TextBox URL 
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Text            =   "http://localhost/adosamp"
      Top             =   720
      Width           =   2655
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Search "
      Height          =   735
      Left            =   240
      TabIndex        =   6
      Top             =   3000
      Width           =   1695
   End
   Begin VB.TextBox FileContents 
      Height          =   1815
      Left            =   600
      MultiLine       =   -1  'True
      TabIndex        =   4
      Text            =   "SemiStru.frx":0000
      Top             =   5760
      Width           =   9855
   End
   Begin VB.ListBox FileProps 
      Height          =   4740
      Left            =   3240
      TabIndex        =   3
      Top             =   600
      Width           =   7215
   End
   Begin VB.TextBox FileName 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Text            =   "ADOSamp.xml"
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label FileMembers 
      Caption         =   "File Members"
      Height          =   375
      Left            =   10800
      TabIndex        =   9
      Top             =   120
      Width           =   1695
   End
   Begin VB.Label Label4 
      Caption         =   "URL to search"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   240
      Width           =   1695
   End
   Begin VB.Label Label3 
      Caption         =   "File Contents"
      Height          =   255
      Left            =   600
      TabIndex        =   5
      Top             =   5280
      Width           =   2295
   End
   Begin VB.Label Label2 
      Caption         =   "File Properties"
      Height          =   255
      Left            =   3240
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "File to search for"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   1560
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim rsMembers As New ADODB.Recordset

Private Sub Form_Load()

'default URL
URL.Text = "http://localhost"
'default file to search for. "" means display the file in the URL
FileName.Text = ""

Search

End Sub

Private Sub Command1_Click()

Search

End Sub

Private Sub Search()

'Search uses the findfile method to search the directory specified in the URL and
'if necessary any subordinate directories for the file specified in the FileName
'text box. The file may be a directory or it may be a regular file.
'If the file is found then search fills the FileProps, FileMembers and FileContents
'controls as appropriate for the type of file found.

'ADO and the Microsoft OLE DB Provider for Internet Publishing are used to search
'the contents of the file system identified by the URL. The file system is searchable
'only if the administrator of the web site has explicitly elected to publish the URL.

Dim root                As New ADODB.Record
Dim file                As New ADODB.Record
Dim contents            As New Stream
Dim str                 As String
Dim strURL              As String
Dim fEmptyCollection    As Boolean

strURL = "URL=" & URL.Text
On Error GoTo ErrorExit

If FileName.Text <> "" Then
    'open the requested URL as the starting point of the search
    root.Open "", strURL, adModeRead
    'search the root file and any subordinate directories for the requested file
    FindFile root, file
Else
    'since no search file was specified just display the file in the URL
    file.Open "", strURL, adModeRead
End If

'if the requested file was found display it
If (file.State = adStateOpen) Then
    'first populate the fileprops list box with the fields in the ADO record
    'for the requested file
    FileProps.Clear
    For indx = 0 To file.Fields.Count - 1
        FileProps.AddItem file.Fields(indx).Name & "=" & file.Fields(indx).Value
    Next
    
    'if the file has displayable (i.e. text) contents open a stream from the ADO
    'record and use the stream to fill the FileContents text box
    str = file.Fields("resource_contentclass").Value
    If (str = "text/plain") Or (str = "text/xml") Or (str = "text/html") Then
        contents.Open file, adModeRead, adOpenStreamFromRecord
        
        'verify that the file actualy has contents
        If (contents.Size > 0) Then
            str = contents.ReadText(1)
            contents.Position = 0
            If Asc(Mid(str, 1, 1)) = 63 Then
                contents.Charset = "ascii"
                contents.Type = adTypeText
            End If
            FileContents.Text = contents.ReadText(adReadAll)
        Else
            FileContents.Text = "The file is empty"
        End If
    Else
        FileContents.Text = "Can not display file contents"
    End If
    
    'If the record is a collection (i.e. it is a directory)
    'use the GetChildren method to populate an ADO recordset with the members of
    'the collection. Then insert the names of the members in the members list box.
    'Put the appropriate message in the list box if the file is not a collection or
    'the collection is empty.
    Members.Clear
    If file.Fields("RESOURCE_ISCOLLECTION").Value = True Then
        If rsMembers.State <> adStateClosed Then rsMembers.Close
        Set rsMembers = file.GetChildren()
        fEmptyCollection = True
        While rsMembers.EOF = False
            Members.AddItem rsMembers.Fields("RESOURCE_PARSENAME").Value
            rsMembers.MoveNext
            fEmptyCollection = False
        Wend
        If fEmptyCollection = True Then
            Members.AddItem "The collection is empty"
        End If
        
    Else
        Members.AddItem "File is not a collection"
        If rsMembers.State <> adStateClosed Then rsMembers.Close
    End If
    
Else
    'if the requested file could not be found say so.
    FileContents.Text = "File Not Found"
    FileProps.Clear
    FileProps.AddItem "File Not Found"
    Members.Clear
    Members.AddItem "File Not Found"
End If

GoTo endsub

ErrorExit:

FileContents.Text = "Unable to perform requested operation"
FileProps.Clear
FileProps.AddItem "Unable to perform requested operation"
FileProps.AddItem "Err.description = " & Err.Description
FileProps.AddItem "Err.Source = " & Err.Source
Members.Clear
Members.AddItem "Unable to perform requested operation"

endsub:

End Sub

Private Sub FindFile(directory As ADODB.Record, file As ADODB.Record)

Dim dir As ADODB.Recordset
Dim subdir As New ADODB.Record
Dim stopwhile As Boolean

'GetChildren returns a recordset containg the members of the directory
Set dir = directory.GetChildren()

'The if checks to see of the recordset contains any rows. If the recordset is empty
'the MoveFirst method will cause an error.
If dir.EOF = False Then dir.MoveFirst

'Search the recordset for the record for the requested file.
'The stopwhile flag is used to control the loop since
'while ((dir.EOF = FALSE) and (dir.Fields("RESOURCE_PARSENAME").Value = FileName.Text))
'will produce an error if the requested file is not found.
'The error will occur because when dir.eof = true the dir.fields... will error. The
'error is because the recordset is not positioned on a row so there is no value to
'return.
stopwhile = False
While (stopwhile = False)
    If (dir.EOF = True) Then
        stopwhile = True
    Else
        If (dir.Fields("RESOURCE_PARSENAME").Value = FileName.Text) Then
            stopwhile = True
        Else
            dir.MoveNext
        End If
    End If
Wend

'if the requested file was found open the row as an ADO record
If (dir.EOF = False) Then
    file.Open dir
    
'if the requested file was not found in this directory search any subordinate to the
' directories for the requested file.

Else
    'The if checks to see of the recordset contains any rows. If the recordset is empty
    'the MoveFirst method will cause an error.
    If dir.BOF = False Then dir.MoveFirst
    
    'look in any subordinate directories for the requested file.
    While ((dir.EOF <> True) And (file.State = adStateClosed))
        If dir.Fields("resource_iscollection") = True Then
            subdir.Open dir
            FindFile subdir, file
            subdir.Close
        End If
        dir.MoveNext
    Wend

End If

End Sub

Private Sub Members_Click()

'If rsMembers is closed then the current file is not a collection
If rsMembers.State = adStateOpen Then
    'if both eof and bof are true the recordset is empty.
    If ((rsMembers.BOF = False) Or (rsMembers.EOF = False)) Then
        'repositon the recordset on the forst row and then move forward
        'the appropriate number of rows to position on the selected file.
        rsMembers.MoveFirst
        rsMembers.Move Members.ListIndex
        'use the PARENT name and parse name to request a search of the appropriate
        'directory for the selected file
        URL.Text = rsMembers.Fields("RESOURCE_PARENTNAME").Value
        FileName.Text = rsMembers.Fields("resource_ParseName").Value
        Search
    End If
End If

End Sub
