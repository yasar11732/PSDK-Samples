VERSION 5.00
Begin VB.Form InkCollection 
   Caption         =   "Ink Collection Sample"
   ClientHeight    =   3810
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   4440
   LinkTopic       =   "InkCollection"
   ScaleHeight     =   254
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   296
   StartUpPosition =   3  'Windows Default
   Begin VB.Menu FileMenu 
      Caption         =   "File"
      Begin VB.Menu FileExitMenu 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu InkMenu 
      Caption         =   "Ink"
      Begin VB.Menu InkEnabledMenu 
         Caption         =   "Enabled"
         Checked         =   -1  'True
      End
      Begin VB.Menu InkColorMenu 
         Caption         =   "Color"
         Begin VB.Menu InkColorRedMenu 
            Caption         =   "Red"
         End
         Begin VB.Menu InkColorGreenMenu 
            Caption         =   "Green"
         End
         Begin VB.Menu InkColorBlueMenu 
            Caption         =   "Blue"
         End
         Begin VB.Menu InkColorBlackMenu 
            Caption         =   "Black"
         End
      End
      Begin VB.Menu WidthMenu 
         Caption         =   "Width"
         Begin VB.Menu InkWidthThinMenu 
            Caption         =   "Thin"
         End
         Begin VB.Menu InkWidthMediumMenu 
            Caption         =   "Medium"
         End
         Begin VB.Menu InkWidthThickMenu 
            Caption         =   "Thick"
         End
      End
   End
End
Attribute VB_Name = "InkCollection"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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
'  File: InkCollection.vb
'  Simple Ink Collection Sample Application
'
'  This sample program is a "Hello World" application, which
'  demonstrates basic functionality of the Tablet PC platform.
'  It is the simplest program that you can build using the
'  Tablet PC Platform APIs. This application uses an ink
'  collector to collect and render pen input.
'
'  The features used are: InkCollector, default tablet, and
'  modifying default drawing attributes.
'
'--------------------------------------------------------------------------

' Declare the Ink Collector object
Dim myInkCollector
Attribute myInkCollector.VB_VarHelpID = -1

' Declare constants for the pen widths used by this application.
' Note that these constants are in high metric units (1 unit = .01mm)
Const ThinInkWidth = 10
Const MediumInkWidth = 100
Const ThickInkWidth = 200

'''''''''''''''''''''''''''''''''''''''''
' Form Load method
'   Setup the ink collector for collection
'''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

            ' Create a new ink collector and assign it to this form's window
            Set myInkCollector = New InkCollector
            myInkCollector.hWnd = Me.hWnd

            ' Set the pen width to be a medium width
            myInkCollector.DefaultDrawingAttributes.Width = MediumInkWidth
        
            ' If you do not modify the default drawing attributes, the default
            ' drawing attributes will use the following properties and values:
            '
            '      Color           = black
            '      Width           = 53 (2 pixels on a 96 dpi screen)
            '      Height          = 1
            '      PenStyle        = solid, geometric
            '      PenTip          = ball
            '      Transparency    = 0
            '      AntiAliased     = true
            '      FitToCurve      = false
            '
            ' For an example of how to modify other drawing attributes, uncomment
            ' the following lines of code:
            ' myInkCollector.DefaultDrawingAttributes.PenTip = IPT_Rectangle
            ' myInkCollector.DefaultDrawingAttributes.Height = (0.5) * MediumInkWidth
            ' myInkCollector.DefaultDrawingAttributes.Transparency = 128

            ' Turn the ink collector on
            myInkCollector.Enabled = True
            
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Color->Red Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkColorRedMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Color = vbRed
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Color->Green Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkColorGreenMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Color = vbGreen
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Color->Blue Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkColorBlueMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Color = vbBlue
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Color->Black Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkColorBlackMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Color = vbBlack
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Width->Thin Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkWidthThinMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Width = ThinInkWidth
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Width->Medium Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkWidthMediumMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Width = MediumInkWidth
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Width->Thick Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkWidthThickMenu_Click()
    myInkCollector.DefaultDrawingAttributes.Width = ThickInkWidth
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from File->Exit Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub FileExitMenu_Click()
    myInkCollector.Enabled = False
    End
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handler from Ink->Enabled Menu Item
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub InkEnabledMenu_Click()
    myInkCollector.Enabled = Not myInkCollector.Enabled
    InkEnabledMenu.Checked = myInkCollector.Enabled
End Sub
