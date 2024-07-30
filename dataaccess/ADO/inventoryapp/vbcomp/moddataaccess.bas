Attribute VB_Name = "modDataAccess"
Option Explicit

Public Enum EnumSourceType
    stSQL = 0
    stStoredProc = 1
End Enum

Public Function GetConnectionString() As String
    GetConnectionString = "Provider=SQLOLEDB;Data Source=dand1;Initial Catalog=Northwind;Uid= YOUR USER ID;pwd=YOUR USER PASSWORD;"
End Function

Public Function PrepareCommand(ByVal Source As String, ByVal SourceType As EnumSourceType) As Command

    Dim conn As New ADODB.Connection
    Dim cmd As New ADODB.Command

    ' open connection
    conn.CursorLocation = adUseClient
    conn.Open GetConnectionString
    
    ' set command properties
    Set cmd.ActiveConnection = conn
    cmd.CommandText = Source
    
    ' determine if this is a SQL statement
    ' or stored procedure
    If SourceType = stSQL Then
        cmd.CommandType = adCmdText
    Else
        cmd.CommandType = adCmdStoredProc
        ' get stored procedure parameters from database
        cmd.Parameters.Refresh
    End If
   
    Set PrepareCommand = cmd


End Function

Public Function GetADOXML(rs As ADODB.Recordset) As String

    Dim st As New ADODB.Stream
    st.Open
    rs.Save st, adPersistXML
    GetADOXML = st.ReadText(adReadAll)


End Function

