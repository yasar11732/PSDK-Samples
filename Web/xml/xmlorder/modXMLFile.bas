Attribute VB_Name = "modXMLFile"
'-------------------------------------------------------------------------
'
'   Module Name: modXMLFile
'
'   Description: This module contains functions for reading and writing
'                XML strings to a file
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   XML To/From File Functions
'-------------------------------------------------------------------------
Public Function ReadXMLFromFile(ByVal p_str_filename As String) As String
    Dim int_filenumber As Integer
    Dim str_buffer As String
        
    On Error GoTo FileNotFound
        
    'open the XML File
    int_filenumber = FreeFile
    Open p_str_filename For Input As int_filenumber
    
    'keep reading till the end of the file is reached
    Do While Not EOF(int_filenumber)
    
        'read a line
        Line Input #int_filenumber, str_buffer
        
        'append that line to the string
        ReadXMLFromFile = ReadXMLFromFile & str_buffer
    Loop
    
    'close the file
    Close int_filenumber
    
    'exit function
    Exit Function
    
FileNotFound:
    If Err.Number = 53 Then 'file not found
        'create an emprty file
        Open p_str_filename For Output As int_filenumber
        Close int_filenumber
    
        'resume where the error occured
        Resume
    Else
        're-raise the error
        Call Err.Raise(Err.Number, Err.Source, Err.Description, Err.HelpFile, Err.HelpContext)
    End If
End Function

Public Sub WriteXMLToFile(ByVal p_str_filename As String, ByVal p_str_xml As String)
    Dim int_filenumber As Integer
        
    'open the XML File
    int_filenumber = FreeFile
    Open p_str_filename For Output As int_filenumber
    
    'write the string to the file
    Print #int_filenumber, p_str_xml
    
    'close the file
    Close int_filenumber
End Sub

