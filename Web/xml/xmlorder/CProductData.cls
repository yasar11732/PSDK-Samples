VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CProductData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CCProductData
'
'   Description: This class wraps is a simple data store for product data
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------
Private m_str_productID As String
Private m_str_manufacturer As String
Private m_str_partNumber As String
Private m_str_description As String
Private m_sng_price As Single

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get ProductID() As String
    ProductID = m_str_productID
End Property

Property Get Manufacturer() As String
    Manufacturer = m_str_manufacturer
End Property

Property Get PartNumber() As String
    PartNumber = m_str_partNumber
End Property

Property Get Description() As String
    Description = m_str_description
End Property

Property Get Price() As Single
    Price = m_sng_price
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let ProductID(ByVal p_str_data As String)
    m_str_productID = p_str_data
End Property

Property Let Manufacturer(ByVal p_str_data As String)
    m_str_manufacturer = p_str_data
End Property

Property Let PartNumber(ByVal p_str_data As String)
    m_str_partNumber = p_str_data
End Property

Property Let Description(ByVal p_str_data As String)
    m_str_description = p_str_data
End Property

Property Let Price(ByVal p_str_data As Single)
    m_sng_price = p_str_data
End Property
