VERSION 5.00
Begin VB.Form InkRecognition 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Ink Recognition Sample"
   ClientHeight    =   3930
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7080
   LinkTopic       =   "InkRecognition"
   MaxButton       =   0   'False
   ScaleHeight     =   3930
   ScaleWidth      =   7080
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdRecognize 
      Caption         =   "Recognize Ink"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   2520
      Width           =   6855
   End
   Begin VB.Frame fraInkArea 
      Caption         =   "Ink Here"
      Height          =   2295
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6855
   End
   Begin VB.TextBox txtResults 
      Height          =   735
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   3120
      Width           =   6855
   End
End
Attribute VB_Name = "InkRecognition"
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
'  File: InkRecognition.frm
'  Simple Ink Recognition Sample Application
'
'  This program demonstrates how one can build a basic handwriting
'  recognition application using Microsoft Tablet PC Automation API.
'  It first creates an InkCollector object to enable inking
'  in the window. Upon receiving the "Recognize!" command, fired
'  from the application's button, ToString() is invoked on the
'  collected ink strokes to retrieve the best match using the
'  default recognizer.  The results are presented in a message box.
'
'  The features used are: InkCollector, Ink, Strokes,
'  RecognizerContext, and RecognizerResult
'
'--------------------------------------------------------------------------

' Declare the Ink Collector object
Dim myInkCollector As InkCollector

' Declare the recognition context
Dim myRecognizers As InkRecognizers

''''''''''''''''''''''''''''''''''''''''''''''''''
' Form Load
'   Set up the ink collector
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

    ' Create the recognizers collection
    Set myRecognizers = New InkRecognizers
    
    'Create a new ink collector that uses the Frame's window
    Set myInkCollector = New InkCollector
    myInkCollector.hWnd = fraInkArea.hWnd
    
    ' Turn the ink collector on
    myInkCollector.Enabled = True
    
End Sub


''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Recognize Button Click Event
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub cmdRecognize_Click()
    
    ' Check to ensure that the user has at least one recognizer installed
    ' Note that this is a preventive check - otherwise, an exception will
    ' occur during recognition
    If 0 = myRecognizers.Count Then
        MsgBox "There are no handwriting recognizers installed.  You need to have at least one in order to run this sample."
    Else
    
        ' Note that the Strokes' ToString() method is a
        ' shortcut  for retrieving the best match using the
        ' default recognizer.  The same result can also be
        ' obtained using the RecognizerContext.  For an
        ' example, uncomment the following lines of code:
        '
        ' Dim myRecoContext As New InkRecognizerContext
        ' Dim status As InkRecognitionStatus
        ' Dim recoResult As IInkRecognitionResult
        '
        ' Set myRecoContext.Strokes = myInkCollector.Ink.Strokes
        ' Set recoResult = myRecoContext.Recognize(status)
        ' txtResults.SelText = recoResult.TopString
        '
        txtResults.SelText = myInkCollector.Ink.Strokes.ToString
        
        ' If the mouse is pressed, do not perform the recognition -
        ' this prevents deleting a stroke that is still being drawn
        If Not myInkCollector.CollectingInk Then
                    
            ' Delete the ink from the ink collector
            myInkCollector.Ink.DeleteStrokes myInkCollector.Ink.Strokes
            
            ' Force the Frame to redraw (so the deleted ink will go away)
            fraInkArea.Refresh
            
        End If
    End If
    
End Sub

