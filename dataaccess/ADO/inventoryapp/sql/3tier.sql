USE NORTHWIND
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_DecrementInventory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_DecrementInventory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_Insert_Product]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_Insert_Product]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_delete_Inventory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_delete_Inventory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_increment_Inventory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_increment_Inventory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_update_Inventory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_update_Inventory]
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE sp_DecrementInventory 
@ProductID int,
@Quantity int
as 
 
    UPDATE Products
       SET UnitsInStock = ((UnitsInStock) - @Quantity)
     WHERE 
            ProductID = @ProductID
 


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE sp_Insert_Product 
@Return_Value int output, 		
@ProductName varchar(255), 
@SupplierID nvarchar(40), 
@CategoryID int, 
@QuantityPerUnit int, 
@UnitPrice money, 
@UnitsInStock smallint, 
@UnitsOnOrder smallint, 
@ReorderLevel smallint, 
@Discontinued bit
AS

    insert into Products (ProductName                                               
                          ,SupplierID                                               
                          ,CategoryID                                               
                          ,QuantityPerUnit                                            
                          ,UnitPrice                                               
                          ,UnitsInStock                                               
                          ,UnitsOnOrder                                               
                          ,ReorderLevel                                               
                          ,Discontinued)
           values ( @ProductName    
                        ,@SupplierID     
                        ,@CategoryID     
                        ,@QuantityPerUnit
                        ,@UnitPrice      
                        ,@UnitsInStock   
                        ,@UnitsOnOrder   
                        ,@ReorderLevel   
                        ,@Discontinued   )
  
     select  @Return_Value = ProductID from Products 
     where  @ProductName   =  ProductName                                               
       and  @SupplierID          =  SupplierID                                               
       and  @CategoryID         =  CategoryID                                               
       and  @QuantityPerUnit  =  QuantityPerUnit                                               
       and  @UnitPrice            =  UnitPrice                                               
       and  @UnitsInStock      =  UnitsInStock                                               
       and  @UnitsOnOrder     =  UnitsOnOrder                                               
       and  @ReorderLevel     =  ReorderLevel                                               
       and  @Discontinued      =  Discontinued
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE sp_delete_Inventory 
    @ProductID int
AS                              

     DELETE  Products
     WHERE  ProductID = @ProductID
           AND @ProductID > 100
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE sp_increment_Inventory  
    @ProductID int,
    @Quantity int
AS                              
    Update  Products
       Set  UnitsInStock    =   @Quantity + UnitsInStock  
     WHERE 
            ProductID = @ProductID  
 
 
 

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

CREATE PROCEDURE sp_Update_Inventory 
    @ProductID int,
    @ProductName nvarchar(255), 
    @SupplierID int, 
    @CategoryID int, 
    @QuantityPerUnit nvarchar(20), 
    @UnitPrice money, 
    @UnitsInStock smallint, 
    @UnitsOnOrder smallint, 
    @ReorderLevel smallint, 
    @Discontinued bit
AS           
    Update  Products
       Set  ProductName     =   @ProductName,
            SupplierID      =   @SupplierID, 
            CategoryID      =   @CategoryID, 
            QuantityPerUnit =   @QuantityPerUnit, 
            UnitPrice       =   @UnitPrice, 
            UnitsInStock    =   @UnitsInStock, 
            UnitsOnOrder    =   @UnitsOnOrder, 
            ReorderLevel    =   @ReorderLevel, 
            Discontinued    =   @Discontinued
     WHERE 
            ProductID = @ProductID 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO



