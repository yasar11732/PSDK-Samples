VERSION 5.00
Begin VB.Form CACApp 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Character Auto Completion Sample Application"
   ClientHeight    =   4350
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5760
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4350
   ScaleWidth      =   5760
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox fraBox 
      Height          =   2055
      Left            =   1560
      ScaleHeight     =   133
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   149
      TabIndex        =   7
      Top             =   480
      Width           =   2295
   End
   Begin VB.PictureBox PctResult 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Index           =   2
      Left            =   1560
      ScaleHeight     =   435
      ScaleWidth      =   3795
      TabIndex        =   6
      Top             =   3720
      Width           =   3855
   End
   Begin VB.PictureBox PctResult 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Index           =   1
      Left            =   1560
      ScaleHeight     =   435
      ScaleWidth      =   3795
      TabIndex        =   5
      Top             =   3240
      Width           =   3855
   End
   Begin VB.PictureBox PctResult 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Index           =   0
      Left            =   1560
      ScaleHeight     =   435
      ScaleWidth      =   3795
      TabIndex        =   4
      Top             =   2760
      Width           =   3855
   End
   Begin VB.CommandButton CmdClear 
      Caption         =   "Clear"
      Height          =   495
      Left            =   4200
      TabIndex        =   3
      Top             =   480
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Random Mode:"
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   2
      Top             =   3840
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Prefix Mode:"
      Height          =   375
      Index           =   1
      Left            =   240
      TabIndex        =   1
      Top             =   3360
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Full Mode:"
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   2880
      Width           =   1215
   End
End
Attribute VB_Name = "CACApp"
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
'  File: CACApp.vb
'      Character Autocompletion sample application
'
'  This sample demonstrates how to perform Character Autocompletion
'  in Japanese using the recognition APIs.  This feature is supported
'  for all East Asian recognizers.   The sample displays the recognition
'  results from each of the three Character Autocompletion modes:
'
'  1.  Full: Recognition occurs as if all strokes that comprise the
'      character have been entered.
'  2.  Prefix: Recognition occurs on partial input. The order of the
'      strokes is assumed to conform to the rules of the language.
'  3.  Random: Recognition occurs on partial input. The order of the
'      strokes is not necessarily assumed to conform to the rules of
'      the language.
'
'  Note that a Japanese Recognizer is required to run this sample.
'  In addition, a Japanese font is required to display the recognition results.
'
'  The features used are:
'  InkCollector, InkRecognizers, RecognizerContext, IInkRecognitionAlternates,
'  background recognition, and Character Autocompletion
'
'--------------------------------------------------------------------------

' Declare the Ink Collector object
Dim WithEvents ic As InkCollector
Attribute ic.VB_VarHelpID = -1

' The recognizer context provides the ability to perform ink recognition,
' retrieve the recognition result, and retrieve alternates.
Dim WithEvents rc As InkRecognizerContext
Attribute rc.VB_VarHelpID = -1

' Declare the strings used to hold the recognition results for
' each of the three Character Autocomplete modes.
Dim FullCACText As String
Dim PrefixCACText As String
Dim RandomCACText As String

' Declare the rectangle specifying the size of the area where recognition
' results will be displayed.
Dim DrawTextRect As RECT


''''''''''''''''''''''''''''''''''''''''''''''''''
' ------------ Form Events ------------
''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''
' Form Load
'   Set up the ink collector and recognizer context
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

    ' Initialize the size of the area where recognition results
    ' will be displayed.  Large values are used to avoid clipping
    ' the recognition results.
    DrawTextRect.Left = 0
    DrawTextRect.Top = 0
    DrawTextRect.Right = 1000
    DrawTextRect.Bottom = 1000

    'Create a new ink collector that uses the Frame's window
    Set ic = New InkCollector
    ic.hWnd = fraBox.hWnd
    ic.Enabled = True
    
    ' Use a helper method to retrieve the default Japanese recognizer
    LoadRecognizer
       
    ' Declare the coordinates of the writing area
    Dim Top As Long
    Dim Bottom As Long
    Dim Left As Long
    Dim Right As Long
    
    ' Set the writing area to the frame's area
    Top = 0
    Left = 0
    Bottom = fraBox.ScaleHeight
    Right = fraBox.ScaleWidth
    
    ' Convert from pixel to ink space (1 ink unit = .01mm)
    ic.Renderer.PixelToInkSpace Me.hdc, Left, Top
    ic.Renderer.PixelToInkSpace Me.hdc, Right, Bottom
    
    ' Create a rectangle with the ink space coordinates of the
    ' writing area
    Dim FrameRectangle As New InkRectangle
    FrameRectangle.SetRectangle Top, Left, Bottom, Right
    
    ' Initialize and configure the recognizer guide, which represents
    ' the area used by the recognizer in which ink can be drawn.
    ' Character Autocompletion requires the recognizer context to have
    ' a guide associated with it.
    Dim Guide As New InkRecognizerGuide
    
    ' Set the number of columns and rows in the recognition guide box
    Guide.Columns = 1
    Guide.Rows = 1
    
    ' Do not use a midline
    Guide.Midline = -1
    
    ' The drawn box is the writing area displayed on the screen
    ' in ink space coordinates.
    Guide.DrawnBox = FrameRectangle
    
    ' The writing box is the invisible box in which writing can actually
    ' take place.  It can be used to provide a margin of error to users
    ' if they draw ink outside the lines of the drawn box.  The writing
    ' box should also be specified in ink space coordinates.
    Guide.WritingBox = FrameRectangle
    
    ' Set the recognition guide on the recognizer context.  It is
    ' necessary to set the guide before attaching the Strokes
    ' collection to the recognizer context, or set the Strokes
    ' collection to Null and then set the Guide.
    Set rc.Guide = Guide
    
    ' Set the strokes collection on the recognizer context
    Set rc.Strokes = ic.Ink.Strokes
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Form Paint Event
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Paint()
    
    ' Draw each string in its box
    PctResult(0).Cls
    DrawText PctResult(0).hdc, StrPtr(FullCACText), Len(FullCACText), DrawTextRect, 0
    PctResult(1).Cls
    DrawText PctResult(1).hdc, StrPtr(PrefixCACText), Len(PrefixCACText), DrawTextRect, 0
    PctResult(2).Cls
    DrawText PctResult(2).hdc, StrPtr(RandomCACText), Len(RandomCACText), DrawTextRect, 0
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Clear button Click Event
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub CmdClear_Click()
    
    Dim strokesToDelete As InkStrokes
    Set strokesToDelete = ic.Ink.Strokes
    
    ' Check to ensure that the ink collector isn't currently
    ' in the middle of a stroke before clearing the ink.
    ' Deleting a stroke that is currently being collected
    ' will result in an error condition.
    If Not (ic.CollectingInk) Then
    
        ' Stop the unfinished recognition processes
        rc.StopBackgroundRecognition
        
        ' Set the strokes collection on the recognizer context to nothing.
        ' We do not want results we could get between the next statement and
        ' the reinitialization of the rc.Strokes to have invalid strokes
        ' collection
        Set rc.Strokes = Nothing
        
        ' Delete all the strokes from the ink object
        ic.Ink.DeleteStrokes strokesToDelete
        
        ' Refresh the window
        fraBox.Refresh
        
        ' refresh the recognizer context
        Set rc.Strokes = ic.Ink.Strokes
        
        ' Clear the result strings
        FullCACText = ""
        PrefixCACText = ""
        RandomCACText = ""
        
        ' Clear the result windows
        PctResult(0).Cls
        PctResult(1).Cls
        PctResult(2).Cls
        
    Else
        MsgBox "Cannot clear ink while the ink collector is busy."
    End If
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' ------------ Ink Collector Events ------------
''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from the ink collector's stroke event
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub ic_Stroke(ByVal Cursor As MSINKAUTLib.IInkCursor, ByVal Stroke As MSINKAUTLib.IInkStrokeDisp, Cancel As Boolean)
    
    ' Stop the unfinished recognition processes
    rc.StopBackgroundRecognition
    
    ' Add the new stroke
    rc.Strokes.Add Stroke
    
    ' Request background recognition for all three CAC modes
    ' Note that the parameter passed to the background recognize method
    ' is application-defined data;  in this case, we use the parameter to
    ' store the index of the picture box corresponding to the Character
    ' Autocompletion mode.  After the background recognition has occurred,
    ' we will use this value to determine which picture box should
    ' be used to display the results and to determine which autocompletion
    ' mode was used for the recognition.
    rc.CharacterAutoCompletionMode = IRCACM_Full
    rc.BackgroundRecognizeWithAlternates 0
    rc.CharacterAutoCompletionMode = IRCACM_Prefix
    rc.BackgroundRecognizeWithAlternates 1
    rc.CharacterAutoCompletionMode = IRCACM_Random
    rc.BackgroundRecognizeWithAlternates 2
    
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' ------------ Recognition Context Events ------------
''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from the recognition context's
' RecognitionWithAlternates Event
'
' This event occurs when the RecognizerContext has generated
' results after calling the BackgroundRecognizeWithAlternates.
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub rc_RecognitionWithAlternates(ByVal RecognitionResult As MSINKAUTLib.IInkRecognitionResult, ByVal vCustomParam As Variant, ByVal RecognitionStatus As MSINKAUTLib.InkRecognitionStatus)
    
    ' Declare the string containing the recognition result
    Dim ResultString As String
    
    ' Declare variable containing the RecognitionAlternate objects that
    ' represent possible word matches for segments of ink.
    Dim alts As IInkRecognitionAlternates
    Dim alt As IInkRecognitionAlternate
        
    On Error GoTo EndFunc

    ' Check the recognition status event parameter to ensure that
    ' the recognition succeeded...
    If RecognitionStatus = IRS_NoError Then
    
        
        ' Retrieve the collection of alternates from a selection within
        ' the best result string of the recognition result.
        Set alts = RecognitionResult.AlternatesFromSelection
        
        ' Fill a string with all the characters for this CAC mode
        ' by concatenating all the recognition alternates together.
        For Each alt In alts
            ResultString = ResultString + alt.String
        Next alt
        
        ' Display the string.  Recall that the Stroke event passed a custom
        ' parameter to BackgroundRecognizeWithAlternates, which specified
        ' the index of the picture box corresponding to the Character
        ' Autocompletion mode.  As a result, we can now pass this custom
        ' parameter to the PictureBox control array to retrieve the
        ' PictureBox for displaying the recognition result.
        PctResult(vCustomParam).Cls
        DrawText PctResult(vCustomParam).hdc, StrPtr(ResultString), Len(ResultString), DrawTextRect, 0
        
        ' Use the custom parameter passed to the background recognize method to
        ' determine which type of character autocompletion was used
        Select Case vCustomParam
        Case 0:
            FullCACText = ResultString
        Case 1:
            PrefixCACText = ResultString
        Case 2:
            RandomCACText = ResultString
        End Select
        
    End If
    Exit Sub
EndFunc:
    MsgBox Err.Description
End Sub

''''''''''''''''''''''''''''''''''''''''''''''''''
' ------------ Helper Methods ------------
''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''
' Helper method to load the default Japanese recognizer
''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub LoadRecognizer()

    On Error GoTo NoRecognizer
    
    ' Declare the collection of all ink recognizers installed on this system.
    ' Ink recognizers provide the ability to create a recognition context,
    ' retrieve its attributes and properties, and determine which packet properties
    ' the recognizer needs to perform recognition.
    Dim recos As New InkRecognizers
    Dim JapaneseReco As IInkRecognizer
    
    ' Retrieve the default recognizer for the Japanese language, specified
    ' by the NLS locale identifier LCID.
    Set JapaneseReco = recos.GetDefaultRecognizer(&H411)
    If JapaneseReco Is Nothing Then
        MsgBox "Japanese Recognizers are not installed on this system. Exiting."
        End
    End If
    
    ' Perform an extra check to ensure that we retrieved a Japanese recognizer.
    Dim IsJapanese As Boolean
    Dim lan As Integer
    IsJapanese = False
    For lan = LBound(JapaneseReco.Languages) To UBound(JapaneseReco.Languages)
        If JapaneseReco.Languages(lan) = &H411 Then
            IsJapanese = True
        End If
    Next lan
    
    If Not IsJapanese Then
        MsgBox "Japanese Recognizers are not installed on this system. Exiting."
        End
    End If
    
    ' Use the japanese ink recognizer to create a recognizer context.
    ' The recognizer context provides the ability to perform ink recognition,
    ' retrieve the recognition result, and retrieve alternates.
    Set rc = JapaneseReco.CreateRecognizerContext
    
    Exit Sub
NoRecognizer:
    MsgBox "Japanese Recognizers are not installed on this system. Exiting."
    End
End Sub

