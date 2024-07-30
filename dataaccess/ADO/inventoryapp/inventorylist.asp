<%@ Language=VBScript %>
<HTML>
<HEAD>
<META name=VI60_DTCScriptingPlatform content="Client (IE 4.0 DHTML)">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<LINK href="main.css" rel=stylesheet type=text/css>
<TABLE border=0 cellPadding=1 cellSpacing=1 width="100%">
    <TR>
        <TD bgColor=#F0F0F0>
          <STRONG><FONT color=white size=2>
            <a href="inventorydetail.asp">[New...]</a>
          </FONT></STRONG>
        </TD>
    </TR>
</TABLE>

<TABLE border=0 cellPadding=1 cellSpacing=1 width="100%">
  
  <TR>
    <TD bgColor=#336699><P align=center><STRONG><FONT color=white size=2>Product ID:</FONT></STRONG></P></TD>
    <TD bgColor=#336699><P align=center><STRONG><FONT color=white size=2>Product Name:</FONT></STRONG></P></TD>
    <TD bgColor=#336699><P align=center><STRONG><FONT color=white size=2>Unit Price:</FONT></STRONG></P></TD>
    <TD bgColor=#336699><P align=center><STRONG><FONT color=white size=2>Units In Stock:</FONT></STRONG></P></TD>
    <TD bgColor=#336699 noWrap><P align=center><STRONG><FONT color=white size=2>Restock Level:</FONT></STRONG></P></TD>
    <TD bgColor=#336699 noWrap><P align=center><FONT color=white size=2><STRONG>Units On Order:</STRONG></FONT></P></TD></TR>

<%

    Dim objInventory
    Dim rs

    Set objInventory = Server.CreateObject("InventoryApp.Inventory")

    If Request.Form("txtSearch") <> "" then
        ' return inventory based on search
        Set rs = objInventory.RetrieveByName(Request.Form("txtSearch"),dfRecordset)
    else
        if Request("ProductID") <> "" then
            ' return a single inventory item
            Set rs = objInventory.RetrieveByID(Request("ProductID"),dfRecordset)
        else
            ' return all inventory items
            Set rs = objInventory.RetrieveAll(dfRecordset)
        end if
    end if 

    while  rs.EOF = false 
%>
        <TR class="TableRow">
            <TD bgColor=#F0F0F0><a href="inventorydetail.asp?ProductID=<%= rs("ProductID") %>" target="main"><%= rs("ProductID") %></a></TD>
            <TD bgColor=#F0F0F0 noWrap><%= rs("ProductName") %></TD>
            <TD bgColor=#F0F0F0><%= rs("UnitPrice") %></TD>
            <TD bgColor=#F0F0F0><%= rs("UnitsInStock") %></TD>
            <TD bgColor=#F0F0F0><%= rs("ReorderLevel") %></TD>
            <TD bgColor=#F0F0F0><%= rs("UnitsOnOrder") %></TD>
        </TR>
<%
        rs.MoveNext
    wend
    rs.Close

%>
</TABLE>

<TABLE border=0 cellPadding=1 cellSpacing=1 width="100%">
    <TR>
        <TD bgColor=#F0F0F0>
          <STRONG><FONT color=white size=2>
            <a href="inventorydetail.asp">[New...]</a>
          </FONT></STRONG>
        </TD>
    </TR>
</TABLE>

</BODY>
</HTML>
