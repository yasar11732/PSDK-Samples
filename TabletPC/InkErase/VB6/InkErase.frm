VERSION 5.00
Begin VB.Form InkErase 
   Caption         =   "Ink Erase Sample"
   ClientHeight    =   7875
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   10635
   LinkTopic       =   "InkEditing"
   ScaleHeight     =   525
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   709
   StartUpPosition =   3  'Windows Default
   Begin VB.Menu miAction 
      Caption         =   "&Action"
      Begin VB.Menu miClear 
         Caption         =   "&Clear"
      End
      Begin VB.Menu miActionSeparator 
         Caption         =   "-"
      End
      Begin VB.Menu miExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu InkMode 
      Caption         =   "&Mode"
      Begin VB.Menu miInk 
         Caption         =   "&Ink"
         Checked         =   -1  'True
         Shortcut        =   ^I
      End
      Begin VB.Menu miCuspErase 
         Caption         =   "Erase at &Cusps"
         Shortcut        =   ^C
      End
      Begin VB.Menu miIntersectionErase 
         Caption         =   "Erase at I&ntersections"
         Shortcut        =   ^N
      End
      Begin VB.Menu miStrokeErase 
         Caption         =   "Erase &Strokes"
         Shortcut        =   ^S
      End
   End
End
Attribute VB_Name = "InkErase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'+-------------------------------------------------------------------------
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
'  File: InkEditing.frm
'  Simple Ink Erasing Sample Application
'
'  This sample program demonstrates how to erase ink using hit
'  testing.  It has the following modes:
'
'  1.  Ink:  Allows the user to ink strokes.
'  2.  Erase at Cusps:  Displays the cusps as red points drawn over the
'      strokes.  The application reports a hit when the mouse is pressed
'      and a circular region around the cursor intersects the stroke.
'      When a hit occurs, the application splits the stroke at the
'      cusps on either side of the hit and erases the corresponding stroke
'      segment.
'  3.  Erase at Intersections:  Same as 2, except stroke intersections
'      are used.
'  4.  Erase Strokes:  Uses hit testing to determine which strokes to delete.
'
'  This sample application supports the inverted pen - if the
'  pen is inverted in Ink mode, stroke erasing is performed.
'
'  The features used are:  InkCollector, Ink hit testing,
'  deleting and splitting strokes, finding cusps and intersections,
'  and using the inverted pen.
'
'--------------------------------------------------------------------------

' Declare the Ink Collector object
Dim WithEvents myInkCollector As InkCollector
Attribute myInkCollector.VB_VarHelpID = -1

' Declare constant for the pen width used by this application.
' Note that this constant is in high metric units (1 unit = .01mm)
Const MediumInkWidth = 100

' Declare constant for the size of the hit test circle radius.
' Note that this constant is in high metric units (1 unit = .01mm)
Const HitTestRadius = 30

' Delcare constant for the radius of the painted cusp/intersection points
Const StrokePointRadius = 3

' Declare constant for the color of the painted cusp/intersection points
Const StrokePointColor = vbRed

' Declare constants for the application modes
Const MODE_INK = 1
Const MODE_CUSPERASE = 2
Const MODE_INTERSECTIONERASE = 3
Const MODE_STROKEERASE = 4

' The index of the x and y packet properties in the packet description
Const XPacketIndex = 0
Const YPacketIndex = 1

' The current application mode:  inking, cusp erasing,
' intersection erasing, or stroke erasing
Dim mode As Integer

'''''''''''''''''''''''''''''''''''''''''''''''
' Form Load Method
'   Setup the ink collector for collection
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()

    ' Start the application in inking mode
    mode = MODE_INK

    ' Create a new ink collector
    Set myInkCollector = New InkCollector
    
    ' Assign the ink collector to collect on the form's window
    myInkCollector.hWnd = Me.hWnd
    
    ' Turn off auto-redrawing since this sample application
    ' needs to display the stroke cusps as red points over the strokes.
    ' If autoredraw is enabled, the strokes will be drawn over
    ' the red points, which will make the cusps hard to see.
    myInkCollector.AutoRedraw = False
    
    ' Set the pen width to be a medium width
    myInkCollector.DefaultDrawingAttributes.Width = MediumInkWidth
    
    ' Turn on event interest for Cursor down event.
    ' This is necessary since the application needs to check if the cursor
    ' is inverted and use the result to determine the visibility of the ink.
    myInkCollector.SetEventInterest ICEI_CursorDown, True
    
    ' Turn on event interest for NewPackets event.
    ' This is necessary since the application needs to examine new packets
    ' when the cursor is inverted and use them to determine whether
    ' any strokes should be erased.
    myInkCollector.SetEventInterest ICEI_NewPackets, True
    
    ' Turn the ink collector on
    myInkCollector.Enabled = True
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Mouse Move
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    ' If the application is in erase mode and a mouse button is
    ' pressed, perform a hit test to determine which stroke segments
    ' to erase (if any).
    If (Not (MODE_INK = mode) And (Button > 0)) Then
    
        Dim ix As Long
        Dim iy As Long
        
        ix = X
        iy = Y
        
        ' Convert the specified point from pixel to ink space coordinates
        myInkCollector.Renderer.PixelToInkSpace Me.hDC, ix, iy
        
        Select Case mode
            Case MODE_CUSPERASE:
                EraseAtCusps ix, iy
            Case MODE_INTERSECTIONERASE:
                EraseAtIntersections ix, iy
            Case MODE_STROKEERASE:
                EraseStrokes ix, iy, Nothing
        End Select
    
    End If
    
 End Sub
 

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Paint Event
'   It is necessary to handle the paint event since
'   this sample needs to draw red points to indicate
'   the strokes' cusps.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Paint()
    
    ' Get the strokes to paint from the ink
    Dim strokesToPaint As InkStrokes
    Set strokesToPaint = myInkCollector.Ink.Strokes

    ' Draw the strokes - note that it is necessary to manually
    ' paint the strokes since auto-redrawing is set to false.
    myInkCollector.Renderer.Draw Me.hDC, strokesToPaint
    

    Select Case mode
        Case MODE_CUSPERASE:
            PaintCusps strokesToPaint
    
        Case MODE_INTERSECTIONERASE:
            PaintIntersections strokesToPaint
            
    End Select
     
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Action->Clear menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miClear_Click()

    Dim strokesToDelete As InkStrokes
    Set strokesToDelete = myInkCollector.Ink.Strokes
    
    ' Check to ensure that the ink collector isn't currently
    ' in the middle of a stroke before clearing the ink.
    ' Deleting a stroke that is currently being collected
    ' will result in an error condition.
    If Not myInkCollector.CollectingInk Then

        myInkCollector.Ink.DeleteStrokes strokesToDelete
        miInk_Click
    
    Else
    
        MsgBox "Cannot clear ink while the ink collector is busy."
    
    End If
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Action->Exit menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miExit_Click()

    myInkCollector.Enabled = False
    End
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Ink Collector Cursor Down Event Handler
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub myInkCollector_CursorDown(ByVal Cursor As MSINKAUTLib.IInkCursor, ByVal Stroke As MSINKAUTLib.IInkStrokeDisp)
   
    ' If the pen is inverted, this application will perform stroke
    ' erasing; since we do not want to show the pen while the user
    ' is erasing, make this stroke transparent.
    If (Cursor.Inverted) Then
        Stroke.DrawingAttributes.Transparency = 255
    End If
   
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Ink Collector New Packets Event Handler
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub myInkCollector_NewPackets(ByVal Cursor As MSINKAUTLib.IInkCursor, ByVal Stroke As MSINKAUTLib.IInkStrokeDisp, ByVal PacketCount As Long, PacketData As Variant)
    If (Cursor.Inverted) Then
    
        Dim i As Integer
        Dim X As Long
        Dim Y As Long
        Dim packetSize As Integer
        Dim packetLength As Integer
        
        packetSize = Stroke.packetSize
        packetLength = (UBound(PacketData) - LBound(PacketData)) + 1
        
        '  For each new packet...
        For i = LBound(PacketData) To i = UBound(PacketData) Step 1
                   
            ' retrieve the x and y packet values
            X = PacketData(i * packetSize + XPacketIndex)
            Y = PacketData(i * packetSize + YPacketIndex)
        
            ' Use helper method to erase all strokes hit by
            ' the current point
            EraseStrokes X, Y, Stroke
        Next
    End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Ink Collector Stroke Event Handler
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub myInkCollector_Stroke(ByVal Cursor As MSINKAUTLib.IInkCursor, ByVal Stroke As MSINKAUTLib.IInkStrokeDisp, Cancel As Boolean)
    
    '  Cancel the stroke if the cursor is inverted (since
    '  it is being used to erase strokes).
    If (Cursor.Inverted) Then
        Cancel = True
    End If
    
End Sub


'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Mode->Ink menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miInk_Click()

    UpdateApplicationMode MODE_INK
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Mode->Cusp Erase menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miCuspErase_Click()

    UpdateApplicationMode MODE_CUSPERASE

End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Mode->Intersection Erase menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miIntersectionErase_Click()

    UpdateApplicationMode MODE_INTERSECTIONERASE
    
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Event Handle from Mode->Stroke Erase menu.
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub miStrokeErase_Click()

    UpdateApplicationMode MODE_STROKEERASE

End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method to update the application mode
'
' Parameters:
' newMode:  The new application mode
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub UpdateApplicationMode(ByVal newMode As Integer)

    ' Turn on/off the ink collector
    myInkCollector.Enabled = (MODE_INK = newMode)

    ' Update the state of the Ink and Erase menu items
    miInk.Checked = (MODE_INK = newMode)
    miCuspErase.Checked = (MODE_CUSPERASE = newMode)
    miIntersectionErase.Checked = (MODE_INTERSECTIONERASE = newMode)
    miStrokeErase.Checked = (MODE_STROKEERASE = newMode)

    mode = newMode

    Refresh
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method to paint the stroke collection's cusps
'
' Parameters:
' strokesToPaint:  The collection of strokes to paint
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub PaintCusps(strokesToPaint As InkStrokes)

    'for each stroke, get its polyline cusps and draw them
    Dim currentStroke As IInkStrokeDisp
    Dim cusps As Variant
    Dim i As Integer
    Dim X As Long
    Dim Y As Long
    
    ' Draw the cusps of each stroke as little red circles
    For Each currentStroke In strokesToPaint
    
        ' Get the cusps of the stroke
        cusps = currentStroke.PolylineCusps
        
        ' Loop through each cusp
        For i = LBound(cusps) To UBound(cusps)
        
            ' Get the X, Y position of the cusp
            Dim pt As Variant
            pt = currentStroke.GetPoints(cusps(i), 1)
            
            X = pt(0)
            Y = pt(1)

            ' Convert the X, Y position to Window based pixel coordinates
            myInkCollector.Renderer.InkSpaceToPixel Me.hDC, X, Y
            
            ' Draw a red circle as the cusp position
            Circle (X, Y), StrokePointRadius, StrokePointColor
        Next i
    Next
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method to paint the stroke collection's intersections
'
' Parameters:
' strokesToPaint:  The collection of strokes to paint
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub PaintIntersections(strokesToPaint As InkStrokes)

    'for each stroke, get its intersections and draw them
    Dim currentStroke As IInkStrokeDisp
    Dim intersections As Variant
    Dim points As Variant
    Dim i As Integer
    
    ' Draw the intersections of each stroke as little red circles
    For Each currentStroke In strokesToPaint
    
        ' Get the intersections of the stroke
        intersections = currentStroke.FindIntersections(strokesToPaint)
        
        points = currentStroke.GetPoints()
        
        ' Draw each intersection in the stroke
        For i = LBound(intersections) To UBound(intersections)
        
            Dim fi As Double
            Dim fiFraction As Double
        
            fi = intersections(i)
            
            ' Find the fractional part of the FINDEX
            fiFraction = fi - Int(fi)
            
            ' Get the point before the FINDEX
            Dim ptIntersect As Variant
            ptIntersect = currentStroke.GetPoints(Int(fi), 1)

            ' if the fi does not have a fractional part, we have already
            ' found the intersection point.  Otherwise, use the FINDEX to
            ' calculate the interpolated intersection point on the stroke
            If (fiFraction > 0) Then
            
                Dim ptNextIntersect  As Variant
                ptNextIntersect = currentStroke.GetPoints(Int(fi) + 1, 1)
                ptIntersect(0) = ptIntersect(0) + Int(((ptNextIntersect(0) - ptIntersect(0)) * fiFraction))
                ptIntersect(1) = ptIntersect(1) + Int(((ptNextIntersect(1) - ptIntersect(1)) * fiFraction))

            End If

            Dim X As Long
            Dim Y As Long
            X = ptIntersect(0)
            Y = ptIntersect(1)

            ' Convert the X, Y position to Window based pixel coordinates
            myInkCollector.Renderer.InkSpaceToPixel Me.hDC, X, Y
                
            ' Draw a red circle as the intersection position
            Circle (X, Y), StrokePointRadius, StrokePointColor
        Next i
    Next
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method that performs a hit test using the specified point.
' When a hit occurs, the application splits the stroke at the cusps
' on either side of the hit and erases the corresponding stroke segment.
'
' Parameters:
' x:  The x coordinate of the point used for hit testing
' y:  The y coordinate of the point used for hit testing
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub EraseAtCusps(ByVal X As Long, ByVal Y As Long)
            
    ' Declare the collection of strokes returned from HitTest
    Dim strokesHit As InkStrokes

    ' Use HitTest to find the collection of strokes that are intersected
    ' by the point.  The HitTestRadius constant is used to specify the
    ' radius of the hit test circle in ink space coordinates (1 unit = .01mm).
    Set strokesHit = myInkCollector.Ink.HitTestCircle(X, Y, HitTestRadius)

    Dim cusps As Variant

    ' Loop over each stroke returned from the hit test to determine
    ' which portion to erase...
    For Each currentStroke In strokesHit

        ' Retrieve the cusps of the stroke.  The cusps mark the points where
        ' the stroke changes direction abruptly.  A segment is defined as the
        ' points between two cusps.
        cusps = currentStroke.PolylineCusps

        ' If there are 1 or two cusps, it's a single stroke - delete the
        ' entire stroke.
        If (UBound(cusps) - LBound(cusps) <= 1) Then
            myInkCollector.Ink.DeleteStroke currentStroke

        ' If there are more than 2 cusps, determine which cusps bound the
        ' hit-tested portion of the stroke, split the stroke at these cusps,
        ' and delete the stroke that defines the segment we hit-tested.
        Else
            ' Get the FINDEX of the nearest point on the stroke.  An FINDEX
            ' is a float value representing a location somewhere between two
            ' points in the stroke.  For instance, 0.0 is the first point in
            ' the stroke. 1.0 is the second point in the stroke. 0.5 is halfway
            ' between the first and second points.
            Dim findex As Single
            findex = currentStroke.NearestPoint(X, Y)

            ' Declare the stroke segment to delete
            Dim strokeToDelete As IInkStrokeDisp

            ' Cycle through each cusp of the stroke to determine
            ' which cusps bound the hit-tested portion of the stroke...
            For i = UBound(cusps) - 1 To LBound(cusps) Step -1
            
                ' If this cusp is less than the findex, then split
                ' the stroke at this cusp and the cusp immediately
                ' after it
                If (cusps(i) <= findex) Then
                
                    ' Provided we aren't at the end of the stroke, split at
                    ' cusp i+1.
                    If (i < UBound(cusps) - 1) Then
                        Set strokeToDelete = currentStroke.Split(cusps(i + 1))
                    End If
                    
                    ' If the hit occurred between the first and second cusp,
                    ' delete the stroke.  Keep in mind that the stroke has
                    ' already been split at index 1, so the delete will only
                    ' remove the beginning portion of the stroke (as desired).
                    If (i = LBound(cusps)) Then
                        myInkCollector.Ink.DeleteStroke (currentStroke)

                    ' Otherwise, split the stroke at the current cusp and
                    ' delete the result.  Keep in mind that the stroke has
                    ' already been split at index i+1, so the delete will
                    ' remove the segment from cusp i to i+1.
                    Else
                        Set strokeToDelete = currentStroke.Split(cusps(i))
                        myInkCollector.Ink.DeleteStroke strokeToDelete
                    End If
        
                    Exit For
                End If
            Next
        End If
    Next
    
    If (strokesHit.Count > 0) Then
        ' Repaint the screen to reflect the change
        Me.Refresh
    End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method that performs a hit test using the specified point.
' When a hit occurs, the application splits the stroke at the intersections
' on either side of the hit and erases the corresponding stroke segment.
'
' Parameters:
' x:  The x coordinate of the point used for hit testing
' y:  The y coordinate of the point used for hit testing
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub EraseAtIntersections(ByVal X As Long, ByVal Y As Long)
            
    ' Declare the collection of strokes returned from HitTest
    Dim strokesHit As InkStrokes

    ' Use HitTest to find the collection of strokes that are intersected
    ' by the point.  The HitTestRadius constant is used to specify the
    ' radius of the hit test circle in ink space coordinates (1 unit = .01mm).
    Set strokesHit = myInkCollector.Ink.HitTestCircle(X, Y, HitTestRadius)

    Dim intersections As Variant

    ' Loop over each stroke returned from the hit test to determine
    ' which portion to erase...
    For Each currentStroke In strokesHit

        ' Retrieve the intersecitons of the stroke.
        intersections = currentStroke.FindIntersections(myInkCollector.Ink.Strokes)

        ' If there aren't any intersections, delete the entire stroke.
        If (UBound(intersections) - LBound(intersections) < 0) Then
            myInkCollector.Ink.DeleteStroke currentStroke

        ' If there is at least one intersection, determine which
        ' intersections bound the hit-tested portion of the stroke,
        ' split the stroke at these intersections, and delete the stroke
        ' that defines the segment we hit-tested.
        Else
            ' Get the FINDEX of the nearest point on the stroke.  An FINDEX
            ' is a float value representing a location somewhere between two
            ' points in the stroke.  For instance, 0.0 is the first point in
            ' the stroke. 1.0 is the second point in the stroke. 0.5 is halfway
            ' between the first and second points.
            Dim findex As Single
            findex = currentStroke.NearestPoint(X, Y)
            
            ' If the hit occured before the first intersection, split the stroke
            ' at the current intersection and delete the beginning of the
            ' stroke
            If (findex < intersections(0)) Then
                currentStroke.Split (intersections(0))
                myInkCollector.Ink.DeleteStroke currentStroke
            Else
            
                ' Declare the stroke segment to delete
                Dim strokeToDelete As IInkStrokeDisp

                ' Cycle through each intersection of the stroke to determine
                ' which intersections bound the hit-tested portion of the stroke...
                For i = UBound(intersections) To LBound(intersections) Step -1
                
                    ' If this intersection is less than the findex, the intersection
                    ' occurs between this intersection and the one after it
                    If (intersections(i) <= findex) Then
                    
                        ' Provided we aren't at the end of the stroke and that
                        ' the hit occured after this intersection, split at
                        ' intersection i+1.
                        If (i < UBound(intersections)) Then
                            Set strokeToDelete = currentStroke.Split(intersections(i + 1))
                        End If
    
                        ' Split the stroke at the current intersection.  Keep in
                        ' mind that the stroke has already been split at index i+1,
                        ' so the delete will remove the segment from intersection i
                        ' to i+1.
                        Set strokeToDelete = currentStroke.Split(intersections(i))
                        myInkCollector.Ink.DeleteStroke strokeToDelete
                        
                        Exit For
                    End If
                Next
            End If
        End If
    Next
    
    If (strokesHit.Count > 0) Then
        ' Repaint the screen to reflect the change
        Me.Refresh
    End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''
' Helper method that performs a hit test using the specified point.
' It deletes all strokes that were hit by the point.
'
' Parameters:
' x:  The x coordinate of the point used for hit testing
' y:  The y coordinate of the point used for hit testing
'''''''''''''''''''''''''''''''''''''''''''''''
Private Sub EraseStrokes(ByVal X As Long, ByVal Y As Long, currentStroke As IInkStrokeDisp)
            
    ' Declare the collection of strokes returned from HitTest
    Dim strokesHit As InkStrokes

    ' Use HitTest to find the collection of strokes that are intersected
    ' by the point.  The HitTestRadius constant is used to specify the
    ' radius of the hit test circle in ink space coordinates (1 unit = .01mm).
    Set strokesHit = myInkCollector.Ink.HitTestCircle(X, Y, HitTestRadius)

    If Not (currentStroke Is Nothing) Then
        strokesHit.Remove currentStroke
    End If

    ' Delete all strokes that were hit by the point
    myInkCollector.Ink.DeleteStrokes strokesHit
    
    If (strokesHit.Count > 0) Then
    
        ' Repaint the screen to reflect the change
        Me.Refresh
    End If
End Sub

