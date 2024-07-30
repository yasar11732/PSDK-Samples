<%@ Language=VBScript %>
<%

Dim objInventory
Dim rs
Dim ID

Set objInventory = Server.CreateObject("InventoryApp.Inventory")

' determine which action to perform

If Request.Form("btnDelete") <> "" then
    ' delete item
    objInventory.Delete Request.Form("txtID")
    ID=""
end if

If Request.Form("btnSave")<>"" and Request.Form("txtProductID") = "" then
    ' create new inventory item
    ID = objInventory.Create(Request.Form("txtTitle"),_
                             Request.Form("txtPrice"),_
                             Request.Form("txtQuantity"),_
                             Request.Form("txtRestockLevel"),_
                             Request.Form("txtRestockQuantity"))
end if

if Request.Form("btnSave") <> "" and Request.Form("txtID") <> "" then
    ' update existing inventory item
    objInventory.Update Request.Form("txtID"),_
                        Request.Form("txtTitle"),_
                        Request.Form("txtPrice"),_
                        Request.Form("txtQuantity"),_
                        Request.Form("txtRestockLevel"),_
                        Request.Form("txtRestockQuantity")
    ID = Request.Form("txtID")

end if

if Request.Form("btnIncrement") <> "" then
    ' increment inventory item
    objInventory.IncrementQuantity Request.Form("txtID"),5
    ID = Request.Form("txtID")
end if  

if Request.Form("btnDecrement") <> "" then
    ' increment inventory item
    objInventory.DecrementQuantity Request.Form("txtID"),5
    ID = Request.Form("txtID")
end if  

Set objInventory = nothing

Response.Redirect("inventorylistxml.asp?ID=" & ID)

%>