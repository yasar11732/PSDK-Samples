VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Inventory"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum EnumDataFormat
    dfRecordset = 0
    dfXML = 1
End Enum

Public Function Create(ByVal ProductName As String, _
                       ByVal SupplierID As Integer, _
                       ByVal CategoryID As Integer, _
                       ByVal QuantityPerUnit As String, _
                       ByVal UnitPrice As Double, _
                       ByVal UnitsInStock As Integer, _
                       ByVal UnitsOnOrder As Integer, _
                       ByVal ReorderLevel As Integer, _
                       ByVal Discontinued As Boolean) As Long
                          
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    
On Error GoTo trap
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    cn.ConnectionString = GetCnString
    cn.Open
    Set cmd.ActiveConnection = cn
    cmd.CommandText = "sp_insert_Product"
    cmd.CommandType = adCmdStoredProc
    cmd.Parameters.Append cmd.CreateParameter("@Return_Value", adInteger, adParamOutput)
    cmd.Parameters.Append cmd.CreateParameter("@ProductName", adVarWChar, adParamInput, 40, ProductName)
    cmd.Parameters.Append cmd.CreateParameter("@SupplierID", adInteger, adParamInput, , SupplierID)
    cmd.Parameters.Append cmd.CreateParameter("@CategoryID", adInteger, adParamInput, , CategoryID)
    cmd.Parameters.Append cmd.CreateParameter("@QuantityPerUnit", adVarWChar, adParamInput, 20, QuantityPerUnit)
    cmd.Parameters.Append cmd.CreateParameter("@UnitPrice", adDouble, adParamInput, , UnitPrice)
    cmd.Parameters.Append cmd.CreateParameter("@UnitsInStock", adInteger, adParamInput, , UnitsInStock)
    cmd.Parameters.Append cmd.CreateParameter("@UnitsOnOrder", adInteger, adParamInput, , UnitsOnOrder)
    cmd.Parameters.Append cmd.CreateParameter("@ReOrderLevel", adInteger, adParamInput, , ReorderLevel)
    cmd.Parameters.Append cmd.CreateParameter("@Discontinued", adBoolean, adParamInput, , False)
    cmd.Execute
    ' return ID of newly inserted Productsrecord
    Create = cmd.Parameters("@Return_Value").Value
        
    ' close connection
    cn.Close
    Set cmd = Nothing
    Set cn = Nothing
    Exit Function
    
trap:

    Err.Raise vbUser + 5000, "InventoryApp.Create", "Error adding new item"
    Set cmd = Nothing
    Set cn = Nothing
    Create = 0
    
End Function

Public Function Update(ByVal ProductID As Integer, _
                       ByVal ProductName As String, _
                       ByVal SupplierID As Integer, _
                       ByVal CategoryID As Integer, _
                       ByVal QuantityPerUnit As String, _
                       ByVal UnitPrice As Double, _
                       ByVal UnitsInStock As Integer, _
                       ByVal UnitsOnOrder As Integer, _
                       ByVal ReorderLevel As Integer, _
                       ByVal Discontinued As Boolean) As Long

    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    
On Error GoTo trap

    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    cn.ConnectionString = GetCnString
    cn.Open
    Set cmd.ActiveConnection = cn
    cmd.CommandText = "sp_update_Inventory"
    cmd.CommandType = adCmdStoredProc
    
    cmd.Parameters.Append cmd.CreateParameter("@ProductID", adInteger, adParamInput, , ProductID)
    cmd.Parameters.Append cmd.CreateParameter("@ProductName", adVarWChar, adParamInput, 40, ProductName)
    cmd.Parameters.Append cmd.CreateParameter("@SupplierID", adInteger, adParamInput, , SupplierID)
    cmd.Parameters.Append cmd.CreateParameter("@CategoryID", adInteger, adParamInput, , CategoryID)
    cmd.Parameters.Append cmd.CreateParameter("@QuantityPerUnit", adVarWChar, adParamInput, 20, QuantityPerUnit)
    cmd.Parameters.Append cmd.CreateParameter("@UnitPrice", adDouble, adParamInput, , UnitPrice)
    cmd.Parameters.Append cmd.CreateParameter("@UnitsInStock", adInteger, adParamInput, , UnitsInStock)
    cmd.Parameters.Append cmd.CreateParameter("@UnitsOnOrder", adInteger, adParamInput, , UnitsOnOrder)
    cmd.Parameters.Append cmd.CreateParameter("@ReOrderLevel", adInteger, adParamInput, , ReorderLevel)
    cmd.Parameters.Append cmd.CreateParameter("@Discontinued", adBoolean, adParamInput, , False)
    cmd.Execute
    ' return ID for the update Product record
    Update = True
        
    ' close connection
    cn.Close
    Set cmd = Nothing
    Set cn = Nothing
    Exit Function
    
trap:
    Dim errstr As String
    Dim er As Error
    
    For Each er In cn.Errors
        errstr = errstr & vbCrLf & er.NativeError & " " & er.Description
    Next
    
    Err.Raise vbUser + 5000, "InventoryApp.Update", errstr & vbCrLf & " Error uppdate product id [" & ProductID & "]"
    Set cmd = Nothing
    Set cn = Nothing
    Update = 0

End Function

Public Function Delete(ByVal ID As Long)

    Dim cmd As ADODB.Command

    ' open connection and return command
    Set cmd = PrepareCommand("sp_delete_Inventory", stStoredProc)
    
    ' set ID of Productsto delete
    cmd.Parameters("@ProductID").Value = ID
    
    ' now execute stored procedure
    cmd.Execute
        
    ' close connection
    cmd.ActiveConnection.Close

End Function

Public Function IncrementQuantity(ByVal ID As Long, ByVal Quantity As Long) As Boolean

    Dim cmd As ADODB.Command

    ' open connection and return command
    Set cmd = PrepareCommand("sp_increment_Inventory", stStoredProc)
    
    ' set ID and quantity to increment
    cmd.Parameters("@ProductID").Value = ID
    cmd.Parameters("@Quantity").Value = Quantity
    
    ' now execute stored procedure
    cmd.Execute
        
    ' close connection
    cmd.ActiveConnection.Close

End Function

Public Function DecrementQuantity(ByVal ID As Long, ByVal Quantity As Long) As Boolean

    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    
    ' Supplier stuff was MSMQ and should be removed
    'Dim objSupplier As SupplierApp.Supplier

    ' open connection and return command
    Set cmd = PrepareCommand("sp_DecrementInventory", stStoredProc)
    
    ' set ID and quantity to decrement
    cmd.Parameters("@ProductID").Value = ID
    cmd.Parameters("@Quantity").Value = Quantity
    
    ' now execute stored procedure and return recordset
    Set rs = cmd.Execute

    ' close connection
    cmd.ActiveConnection.Close
   
End Function

Public Function RetrieveByID(ByVal ID As Long, ByVal DataFormat As EnumDataFormat) As Variant
    
    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    Dim strCommand As String

    ' Set SQL statement
    strCommand = "SELECT * FROM Products WHERE ProductID=" & ID & _
             " ORDER BY ProductName"

    ' open connection and return command
    Set cmd = PrepareCommand(strCommand, stSQL)
    
    ' open recordset by executing command
    Set rs = cmd.Execute
        
    ' disconnect recordset from database
    Set rs.ActiveConnection = Nothing
    
    ' close connection
    cmd.ActiveConnection.Close
        
    ' Return results to caller
    Select Case DataFormat
        ' return a disconnected recordset
        Case dfRecordset
            Set RetrieveByID = rs
        ' return an XML string
        Case dfXML
            RetrieveByID = GetADOXML(rs)
        Case Else
            Set RetrieveByID = Nothing
    End Select

End Function

Public Function RetrieveByName(ByVal TitleSearch As String, ByVal DataFormat As EnumDataFormat) As Variant

    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    Dim strCommand As String

    ' Set SQL statement
    strCommand = "SELECT * FROM Products WHERE " & _
             "ProductName LIKE '%" & TitleSearch & "%' " & _
             "ORDER BY ProductName"

    ' open connection and return command
    Set cmd = PrepareCommand(strCommand, stSQL)
    
    ' open recordset by executing command
    Set rs = cmd.Execute
        
    ' disconnect recordset from database
    Set rs.ActiveConnection = Nothing
    
    ' close connection
    cmd.ActiveConnection.Close
        
    ' Return results to caller
    Select Case DataFormat
        ' return a disconnected recordset
        Case dfRecordset
            Set RetrieveByName = rs
        ' return an XML string
        Case dfXML
            RetrieveByName = GetADOXML(rs)
        Case Else
            Set RetrieveByName = Nothing
    End Select

'    GetObjectContext.SetComplete

End Function

Public Function RetrieveAll(ByVal DataFormat As EnumDataFormat) As Variant

    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    Dim strCommand As String

    ' Set SQL statement
    strCommand = "SELECT * FROM Products ORDER BY ProductName"

    ' open connection and return command
    Set cmd = PrepareCommand(strCommand, stSQL)
    
    ' open recordset by executing command
    Set rs = cmd.Execute
        
    ' disconnect recordset from database
    Set rs.ActiveConnection = Nothing
    
    ' close connection
    cmd.ActiveConnection.Close
        
    ' Return results to caller
    Select Case DataFormat

        ' return a disconnected recordset
        Case dfRecordset
            Set RetrieveAll = rs

        ' return an XML string
        Case dfXML
            RetrieveAll = GetADOXML(rs)
            
        Case Else
            Set RetrieveAll = Nothing
    End Select

End Function

Public Function GetCategories() As ADODB.Recordset

    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    
On Error GoTo trap
    
    Set cmd = PrepareCommand("SELECT CategoryID, CategoryName From Categories Order By CategoryName", stSQL)
   
    Set GetCategories = cmd.Execute
    Set cmd = Nothing
    
    Exit Function

trap:
    Set GetCategories = Nothing
    
End Function


Public Function GetSuppliers() As ADODB.Recordset

    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    
On Error GoTo trap
    
    Set cmd = PrepareCommand("SELECT SupplierID, CompanyName FROM Suppliers ORDER BY CompanyName ", stSQL)
   
    Set GetSuppliers = cmd.Execute
    Set cmd = Nothing
    Exit Function

trap:
    Set GetSuppliers = Nothing

End Function

Public Function GetCnString() As String
    GetCnString = GetConnectionString
End Function
