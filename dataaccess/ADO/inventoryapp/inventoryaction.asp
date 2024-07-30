<%@ Language=VBScript %>
<%

    Dim objInventory
    Dim rs
    Dim ProductID

    Set objInventory = Server.CreateObject("InventoryApp.Inventory")

    ' this page inserts, updates, deletes, increments or decrements
    ' a specific inventory item

    ' determine which action to perform

    If Request.Form("btnDelete") <> "" then
        ' delete item
        objInventory.Delete Request.Form("txtProductID")
    end if

    If Request.Form("btnSave") <> "" then
        if Request.Form("txtProductID") = "" then
        ' create new inventory item

        ProductID = objInventory.Create( Request.Form("txtProductName")  , _
                                         Request.Form("cboSuppliers")  , _
                                         Request.Form("cboCategory")  , _
                                         Request.Form("txtQuantityPerUnit") , _
                                         Request.Form("txtUnitPrice") , _
                                         Request.Form("txtUnitsInStock") , _
                                         Request.Form("txtUnitsOnOrder") , _
                                         Request.Form("txtReorderLevel") , _
                                         Request.Form("txtDiscontinued") )
        else
            if Request.Form("txtProductID") <> "" then
                ' update existing inventory item
                dim ret
                ret = objInventory.Update( Request.Form("txtProductID")    , _
                                           Request.Form("txtProductName") , _
                                           Request.Form("cboSuppliers") , _
                                           Request.Form("cboCategory") , _
                                           Request.Form("txtQuantityPerUnit") , _
                                           Request.Form("txtUnitPrice") , _
                                           Request.Form("txtUnitsInStock") , _
                                           Request.Form("txtUnitsOnOrder") , _
                                           Request.Form("txtReorderLevel"), "1" )
                if ret = 0 then
                    response.write( "Error Updateing Item... ret == " & ret)
                    response.end
                end if
            end if
        end if
    end if

    if Request.Form("btnIncrement") <> "" then
        ' increment inventory item
        objInventory.IncrementQuantity Request.Form("txtProductID"),5
        ProductID = Request.Form("txtProductID")
    end if

    if Request.Form("btnDecrement") <> "" then
        ' increment inventory item
        objInventory.DecrementQuantity Request.Form("txtProductID"),5
        ProductID = Request.Form("txtProductID")
    end if

    Set objInventory = nothing
    Response.Write( "<br>ProductID == " & ProductID &"<br>")
    Response.Redirect("inventorylist.asp?ID=" & ProductID)
%>
