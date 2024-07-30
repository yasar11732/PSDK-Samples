VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CCustomerData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'-------------------------------------------------------------------------
'
'   Module Name: CCustomersData
'
'   Description: This class wraps is a simple data store for customer data
'
'-------------------------------------------------------------------------
Option Explicit

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------
Private m_str_companyID As String
Private m_str_companyName As String
Private m_str_ownerName As String

'-------------------------------------------------------------------------
'   Get Properties
'-------------------------------------------------------------------------
Property Get CompanyID() As String
    CompanyID = m_str_companyID
End Property

Property Get CompanyName() As String
    CompanyName = m_str_companyName
End Property

Property Get OwnerName() As String
    OwnerName = m_str_ownerName
End Property

'-------------------------------------------------------------------------
'   Let Properties
'-------------------------------------------------------------------------
Property Let CompanyID(ByVal p_str_data As String)
    m_str_companyID = p_str_data
End Property

Property Let CompanyName(ByVal p_str_data As String)
    m_str_companyName = p_str_data
End Property

Property Let OwnerName(ByVal p_str_data As String)
    m_str_ownerName = p_str_data
End Property


