=================================================
Reusing Browser Technology - Rendering Behaviors
=================================================
Last Updated: January 22, 2001


SUMMARY
========
Rendering behaviors enable you to perform custom drawing on a Web page using the 
Graphics Device Interface (GDI) or a drawing object such as Microsoft® DirectDraw® 
or Microsoft® Direct3D®. You might use rendering behaviors to provide a custom 
background or highlighting for elements, for instance, or to provide guidelines 
for laying out a page in a what you see is what you get (WYSIWYG) editor. 

This sample illustrates how to: 

 - Attach a binary DHTML behavior to an HTML element.  
 - Implement a binary DHTML behavior for Internet Explorer 5.  
 - Access the document object model.
 - Handle events from the document object model.


DETAILS
========
Rendering behaviors are extensions of binary behaviors. To use a rendering 
behavior, you must: 

 - Implement the basic structure of a binary behavior. 
 - Implement the rendering behavior within the binary behavior. 
 - Attach the rendering behavior to an element on a page.
 
A binary behavior has two basic components: the binary behavior itself, and a 
class factory to create the binary behavior. Attach a binary behavior to an element 
by giving MSHTML a reference to the behavior's factory, which is an implementation 
of IElementBehaviorFactory. MSHTML then calls on the factory to create the 
IElementBehavior interface for the behavior itself. From IElementBehavior, 
MSHTML automatically calls QueryInterface , requesting an IHTMLPainter interface 
pointer to determine if the behavior is also a rendering behavior. 

Once MSHTML has a pointer to IHTMLPainter, it calls IHTMLPainter::GetPainterInfo. 
IHTMLPainter::GetPainterInfo provides MSHTML with information about how to draw a 
rendering behavior, including: 

 - How it is to be layered in relation to the element. 
 - Whether it uses the GDI or another object (such as DirectDraw) for drawing. 
 - Whether it is opaque or transparent. 
 - Whether your behavior responds to events. 
 - Whether your behavior draws outside the element. 

After the call to IHTMLPainter::GetPainterInfo, MSHTML is ready to draw the 
behavior. When the system needs to paint or repaint the area of the screen 
occupied by the element to which the behavior is attached, MSHTML calls the 
IHTMLPainter::Draw method of your IHTMLPainter implementation. If your behavior 
responds to events, MSHTML calls IHTMLPainter::HitTestPoint whenever an event 
occurs in the rendering behavior's drawing area. MSHTML also calls 
IHTMLPainter::OnResize whenever the window containing your element is resized. 

The first step in implementing a rendering behavior is to implement, at a minimum, 
the IElementBehavior and IElementBehaviorFactory interfaces needed to get a binary 
behavior up and running. If the behavior is to handle events, it also must implement 
an event sink, derived from IDispatch , to intercept and handle events occurring on 
the element. If a behavior will be used on a Web page, the factory should implement 
IObjectSafety, which defines the behavior's security level. A binary behavior used 
in an application hosting MSHTML would not need to implement IObjectSafety. 

Once the binary behavior framework is complete, implementing a rendering behavior 
involves implementing just one more interface, IHTMLPainter, over those that are 
necessary for a binary behavior. IHTMLPainter must be implemented on the same object 
that implements IElementBehavior, since MSHTML calls QueryInterface from the 
IElementBehavior interface to find it. 


USAGE
======
The sample for this tutorial provides a simple example of a rendering behavior. 
It demonstrates some important features that rendering behaviors provide and 
implementation details to consider: 

 - How you can use the GDI to draw directly on a Web page. 
 - How a behavior can specify the z-order in which it is to be layered with the 
   element. 
 - How a behavior can draw outside the element to which it is attached. 
 - How a rendering behavior can intercept and handle mouse events, including events 
   outside the element itself. 

The specifications of this behavior are as follows: 

 - The rendering behavior initially draws a blue rectangular polygon over an 
   element with black circular handles centered on each corner of the element. 
 - The handles can be dragged to reshape the polygon. The color of a handle 
   changes to yellow while being dragged. 
 - The rendering behavior draws outside the boundaries of the element by a small 
   amount equal to the handle radius. 
 - The rendering behavior restricts mouse movements to the confines of the element 
   whenever a handle is dragged. 

BUILDING THE SAMPLE
--------------------
Note: You must first download the sample to your own computer to run it.

The source code for this sample is included in a Microsoft® Visual C++ 6 workspace.
Note:  You will need to include the Internet Explorer 5.5 header and library files, and the Windows 2000 Header and Library files from the Platform SDK in your development path when building the sample source code.

For the IE 5.5 Headers and Library files and the Win32 Header and Library files for Windows 2000, go to: http://www.microsoft.com/msdownload/platformsdk/setuplauncher.htm. Install over the network and select "Custom Install". To obtain the full set of header and library files necessary to build the C/C++ projects, you will need, at minimum, to install the 'Build Environment' section of the Platform SDK.

The source code development path for Header files will be:
C:\Program Files\Microsoft Platform SDK\Include\prerelease
C:\Program Files\Microsoft Visual Studio\VC98\INCLUDE
C:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE
C:\Program Files\Microsoft Visual Studio\VC98\ATL\INCLUDE

The source code development path for Library files will be:
C:\Program Files\Microsoft Platform SDK\Lib\prerelease
C:\Program Files\Microsoft Visual Studio\VC98\LIB
C:\Program Files\Microsoft Visual Studio\VC98\MFC\LIB

RUNNING THE SAMPLE
-------------------
1.) If you decide to run the sample from Visual C++, make sure that your 
    computer's path settings correspond to the sample project folder. 
    
    - In Visual C++, choose Settings from the Project menu, click the Debug tab, 
      and change the path in the Program Arguments field to match the path 
      location of the Render.htm file in your Renderproject folder 
      (for instance, "C:\Workshop\Downloads\Samples\Internet\ie55\RenderBehave\Renderproject"). 
OR 

2.) Open Render.htm with your Internet Explorer 5.5 browser. 



BROWSER/PLATFORM COMPATIBILITY
===============================
The Rendering Behaviors sample requires Microsoft® Internet Explorer 5.5 or 
later on the Win32 platform. For developers, header and library files for Windows 2000 and
Internet Explorer 5.5 or later are needed for use in your development environment; 
in particular, Mshtml.h and Mshtmdid.h are necessary. 


SOURCE FILES
=============
- FACTORY.CPP,FACTORY.H - IElementBehaviorFactory interface implementation.
- BEHAVIOR.CPP,BEHAVIOR.H - IElementBehavior interface implementation.
- EVENTSINK.CPP,EVENTSINK.H - HTMLElementEvents event sink implementation.
- BEHAVE.HTM - test HTML file which demonstrates the sample behavior.
- BEHAVIOR.RGS
- DLLDATA.C
- EVENTSINK.RGS
- FACTORY.RGS
- RENDER.APS
- RENDER.CLW
- RENDER.CPP
- RENDER.DEF
- RENDER.DSP
- RENDER.DSW
- RENDER.IDL
- RENDER.INF
- RENDER.OPT
- RENDER.RC
- RENDER.TLB
- RENDER_P.C
- RESOURCE.H
- STDAFX.CPP
- STDAFX.H


OTHER FILES
============
RENDER.CAB (render.inf, render.dll)


SEE ALSO
=========
For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on Implementing Rendering Behaviors, go to:
http://msdn.microsoft.com/workshop/browser/editing/impRendBehav.asp

For more information on 'What's New' in IE 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.
