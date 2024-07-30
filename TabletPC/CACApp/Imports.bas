'-------------------------------------------------------------------------
'
'  This is part of the Microsoft Tablet PC Platform SDK
'  Copyright (C) 2002 Microsoft Corporation
'  All rights reserved.
'
'  This source code is only intended as a supplement to the
'  Microsoft Tablet PC Platform SDK Reference and related electronic
'  documentation provided with the Software Development Kit.
'  See these sources for more detailed information.
'
'  File: Imports.bas
'      Declarations of the imports for the
'      Character Auto Completion sample application
'
'--------------------------------------------------------------------------

Attribute VB_Name = "Imports"
Public Type RECT
        Left As Long
        Top As Long
        Right As Long
        Bottom As Long
End Type
Public Declare Function DrawText Lib "user32" Alias "DrawTextW" (ByVal hdc As Long, ByVal lpStr As Long, ByVal nCount As Long, lpRect As RECT, ByVal wFormat As Long) As Long
 

