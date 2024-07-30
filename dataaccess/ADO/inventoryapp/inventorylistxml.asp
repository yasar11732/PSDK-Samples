<%@ Language=VBScript %>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>

<LINK href="main.css" rel=stylesheet type=text/css>

<%
    ' just in case you ever need the dialects for sql server...
    ' DBGUID_DEFAULT As String = "{C8B521FB-5CF3-11CE-ADE5-00AA0044773D}"
    ' DBGUID_SQL As String = "{C8B522D7-5CF3-11CE-ADE5-00AA0044773D}"
    ' DBGUID_MSSQLXML As String = "{5D531CB2-E6Ed-11D2-B252-00C04F681B71}"
    ' DBGUID_XPATH As String = "{ec2a4293-e898-11d2-b1b7-00c04f680c56}"
 
    dim objInv
    dim cn
    dim cmd
    
    
    set cn  = server.createobject("adodb.connection")
    set cmd = server.createobject("adodb.command")
    set objInv = Server.CreateObject("InventoryApp.Inventory")
    cn.ConnectionString = objInv.GetCnString()
    response.write cn.connectionstring

    cn.ConnectionString = objInv.GetCnString()
    cn.Open
    Set cmd.ActiveConnection = cn
    cmd.dialect = "{5D531CB2-E6Ed-11D2-B252-00C04F681B71}"
    cmd.commandtext = "<root xmlns:sql='urn:schemas-microsoft-com:xml-sql' sql:xsl='products.xsl'> " & _ 
                      " <sql:query>SELECT * FROM Products ORDER BY ProductName FOR XML AUTO</sql:query>" & _ 
                      " </root>"
    
    
    cmd.Properties("Output Stream") = response
    cmd.Execute , , 1024    '  adExecuteStream
    cn.Close
    Set cmd = Nothing
    Set cn = Nothing

%>


</BODY>
</HTML>
