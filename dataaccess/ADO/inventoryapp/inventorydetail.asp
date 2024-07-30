<%@ Language=VBScript %>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<LINK href="main.css" rel=stylesheet type=text/css>

<%

    Dim objInventory
    Dim rs
    Dim varProductID
    Dim varProductName
    Dim varSupplierID
    Dim varCategoryID
    Dim varQuantityPerUnit
    Dim varUnitPrice
    Dim varUnitsInStock
    Dim varUnitsOnOrder
    Dim varReorderLevel
    Dim varDiscontinued
    Set objInventory = Server.CreateObject("InventoryApp.Inventory")

    ' load specific inventory item if supplied
    
    If Trim(Request("ProductID")) <> "" then
        Set rs = objInventory.RetrieveByID(Request("ProductID"),dfRecordset)
        varProductID        =  rs("ProductID")
        varProductName      =  rs("ProductName")
        varSupplierID       =  rs("SupplierID") 
        varCategoryID       =  rs("CategoryID") 
        varQuantityPerUnit  =  rs("QuantityPerUnit") 
        varUnitPrice        =  rs("UnitPrice")
        varUnitsInStock     =  rs("UnitsInStock")
        varUnitsOnOrder     =  rs("UnitsOnOrder") 
        varReorderLevel     =  rs("ReorderLevel") 
        varDiscontinued     =  rs("Discontinued")
        set rs = Nothing
    else 
        varSupplierID = "-1"
        varCategoryID = "-1"
    end if

%>


<FORM action="inventoryaction.asp" id=FORM1 method=post name=FORM1>
<TABLE border=0 cellPadding=1 cellSpacing=1 width="100%">
  
  <TR>
    <TD width="15%" bgColor=#d0e3ff>Product ID:</TD>
    <TD bgColor=#d0e3ff><INPUT id="txtProductID" name="txtProductID" MAXLENGTH="5"
      style="BACKGROUND-COLOR: #cccccc; HEIGHT: 22px; WIDTH: 67px" readOnly value="<%= varProductID %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff>Product Name:</TD>
    <TD bgColor=#d0e3ff><INPUT id="txtProductName" name="txtProductName" MAXLENGTH="40"
      style="HEIGHT: 22px; WIDTH: 423px" value="<%= varProductName  %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff>Unit Price:</TD>
    <TD bgColor=#d0e3ff><INPUT id=txtUnitPrice name=txtUnitPrice MAXLENGTH="6"
      style="HEIGHT: 22px; WIDTH: 260px" value="<%= varUnitPrice   %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff>Supplier:</TD>
    <TD bgColor=#d0e3ff>
<%
    dim RsSuppliers
    set RsSuppliers = objInventory.GetSuppliers
    Response.Write("<SELECT SIZE=""1"" ID=""cboSuppliers"" name=""cboSuppliers"">")
    
    while  RsSuppliers.EOF =false 
        if RsSuppliers.Fields("SupplierID").value = varSupplierID then 
            Response.Write( "<OPTION VALUE=""" & RsSuppliers.Fields("SupplierID").value & """ SELECTED>" & _ 
                RsSuppliers.Fields("CompanyName").value & "</OPTION>")
        else
            Response.Write( "<OPTION VALUE=""" & RsSuppliers.Fields("SupplierID").value & """>" & _ 
                RsSuppliers.Fields("CompanyName").value & "</OPTION>")                
        end if 
                
        RsSuppliers.movenext                
    wend
    Response.Write("</SELECT></TD>")
    set RsSuppliers=nothing         
%>  
    <TR>
    <TD bgColor=#d0e3ff>Category:</TD>
    <TD bgColor=#d0e3ff>
<%

    dim rsCategories
    set rsCategories =  objInventory.GetCategories() 
    Response.Write("<SELECT SIZE=""1"" ID=""cboCategory"" name=""cboCategory"">")
    
    if rsCategories.eof <>  true then 
        while rsCategories.EOF =false 
            if rsCategories.Fields("CategoryID").value  = varCategoryID then
                Response.Write( "<OPTION VALUE=""" & rsCategories.Fields("CategoryID").value & " ""SELECTED>" & _ 
                    rsCategories.Fields("CategoryName").value & "</OPTION>")                                           
                else 
                    Response.Write( "<OPTION VALUE=""" & rsCategories.Fields("CategoryID").value & " "">" & _ 
                        rsCategories.Fields("CategoryName").value & "</OPTION>")
            end if         
            rsCategories.movenext               
        wend
        Response.Write("</SELECT></TD>")
    end if 
    
    set rsCategories=nothing         
     
%>

    </TD>
  </TR>


  <TR>
    <TD bgColor=#d0e3ff>Quantiy Per Unit :</TD>
    <TD bgColor=#d0e3ff><INPUT id=txtQuantityPerUnit name=txtQuantityPerUnit MAXLENGTH="20"
      style="HEIGHT: 22px; WIDTH: 262px" value="<%= varQuantityPerUnit   %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff>Units In Stock:</TD>
    <TD bgColor=#d0e3ff><INPUT id=txtUnitsInStock  MAXLENGTH="5" 
      name=txtUnitsInStock style   ="HEIGHT: 22px;  WIDTH: 260px" 
      value="<%= varUnitsInStock  %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff>Units On Order:</TD>
    <TD bgColor=#d0e3ff><INPUT id=txtUnitsOnOrder  MAXLENGTH="5"
      name=txtUnitsOnOrder style   ="HEIGHT: 22px;   WIDTH: 261px" 
      value="<%= varUnitsOnOrder   %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff noWrap>ReOrder  Level:</TD>
    <TD bgColor=#d0e3ff><INPUT id=txtReorderLevel name=txtReorderLevel MAXLENGTH="5"
      style="HEIGHT: 22px; WIDTH: 260px" value="<%= varReorderLevel %>"></TD>
  </TR>
  <TR>
    <TD bgColor=#d0e3ff noWrap></TD>
    <TD bgColor=#d0e3ff><INPUT id=btnSave name=btnSave type=submit value="Save Changes">
    &nbsp;&nbsp;
    <INPUT id=btnDelete name=btnDelete type=submit value="Delete Item">
    &nbsp;&nbsp;
    <INPUT id=btnIncrement name=btnIncrement type=submit value="Increment 5">
    &nbsp;&nbsp;
    <INPUT id=btnDecrement name=btnDecrement type=submit value="Decrement 5">
    </TD></TR>

</TABLE>
</FORM>
</BODY>
</HTML>
