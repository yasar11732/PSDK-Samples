Attribute VB_Name = "basSimpleDb"
Option Explicit

' Global connection for the database, open one connection and use it for everything.
Global gCn As ADODB.Connection

Sub main()

On Error GoTo trap
    
    frmDbLogIn.Show vbModal  '  As frmDbLogIn
    'Set frmLogin = New frmDbLogIn
    
    ' get the connection creditials for the database and establish connection
    'frmLogin.Show vbModal
    
    ' either an error will occur or the connection will not be open if an error
    ' occured, thus if the connection is still nothing then the log-in failed.
    If gCn Is Nothing Then
        MsgBox "Failed to log-in to database"
        End
    End If
    
    If gCn.State <> adStateOpen Then
        MsgBox "Failed to log-in to database"
        End
    End If
    
    frmSelectAction.Show vbModal
    
    ' avoid the error handler code and jump to the clean-up code.
    GoTo cleanup
    
trap:
    MsgBox "Error (" & Err.Number & "): " & Err.Description

cleanup:
    

    Set gCn = Nothing
    ' terminate the program
    End
End Sub
 
' a good general purpose routine for opening the database, may be used for other database,
' while for this sample we pass in the database name

Public Function OpenSql(ByVal txtServerName, _
                        ByVal txtDatabaseName As String, _
                        ByVal CursorType As ADODB.CursorLocationEnum, _
                        ByVal ConnectionMode As ADODB.ConnectModeEnum, _
                        ByVal txtUid As String, _
                        ByVal txtPwrd As String) As ADODB.Connection
    
On Error GoTo trap
    
    Set OpenSql = New ADODB.Connection
    
    With OpenSql
        .ConnectionString = "Provider=SQLOLEDB;pwd=" & txtPwrd & ";uid=" & txtUid & ";Data Source=" & txtServerName & ";Initial Catalog=" & txtDatabaseName & ";"
        .Mode = ConnectionMode
        .Open
    End With

    Exit Function
    
trap:
    Set OpenSql = Nothing
    Exit Function

End Function


