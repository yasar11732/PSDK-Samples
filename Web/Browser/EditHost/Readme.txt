=======================================
Reusing Browser Technology - Edit Host
=======================================
Last Updated: January 22, 2001


SUMMARY
========
IHTMLEdit Host provides a way to control how elements are resized and moved when 
the user grabs and drags the handles on a control element. For instance, you could 
cause an element to resize or move by specific increments (a snap-to-grid feature), 
limit resizing to a minimum or maximum size, or constrain the area to which an element 
can be moved. The use of IHTMLEditHost is limited to applications hosting MSHTML or 
the WebBrowser control. IHTMLEditHost cannot be used with binary behaviors or rendering 
behaviors. 


DETAILS
========
Whenever the MSHTML Editor is activated, it looks to see if an IHTMLEditHost is 
available. The Editor first asks the host application for an IServiceProvider interface. 
If it finds IServiceProvider, it will query for an IHTMLEditHost interface pointer. 

IHTMLEditHost acts like a callback routine. The MSHTML Editor holds a pointer to an 
IHTMLEditHost interface (with which you provide it) and calls IHTMLEditHost's one method,
IHTMLEditHost::SnapRect, whenever the user resizes or moves a resizable/moveable element 
in the editing environment. When the MSHTML Editor calls IHTMLEditHost::SnapRect, the 
method's arguments will tell you which element is being resized, the original size and 
position of the element, and which handle the user has grabbed. You have the ability to 
control the size and position of the element when the user releases the handle. 

The IHTMLEditHost interface will remain active until the Editor is turned off or the 
WebBrowser navigates to a new page. At this point, the Editor releases its pointer to 
any IHTMLEditHost interface it holds. 

The sample for this tutorial implements a snap-to-grid feature using IHTMLEditHost. It 
demonstrates the important features that IHTMLEditHost provides, and offers implementation
details to consider: 

 - How you can tell which element is being resized and moved, determine the selected 
   element's current position and size, and know which handle the user has grabbed. 
 - How you can change the element's current position and size. 
 - How and when MSHTML calls IHTMLEditHost's SnapRect method. 
 - How to implement the IServiceProvider interface needed to give the MSHTML Editor 
   a pointer to your IHTMLEditHost interface implementaton. 
 - How you can deactivate and reactivate the IHTMLEditHost interface. 

This sample is a simple browser implementation with an address bar, five buttons, and 
a combo box. The specifications are as follows: 

 - The first button turns the MSHTML Editor on and off. 
 - The second button turns the snap-to-grid feature on and off. 
 - The third button turns a red dashed grid on and off, so you can see how element 
   resizing and movement is constrained to a specific increment when the snap-to-grid 
   feature is turned on. 
 - The right-hand combo box holds the snap and grid increment, which can be changed. 
 - The fourth button turns two-dimensional positioning on and off. 
 - The fifth button turns live resizing on and off. 



USAGE
======
Note: You must download the sample to your own computer to run it. 

The source code for this sample is included in a Microsoft® Visual C++ 6 workspace. 
It uses ATL to provide COM support, standard implementations of some of the standard 
interfaces, and "smart" interface pointers that handle their own reference counting. 
You can use this sample as a structure for building your own implementations of 
IHTMLEditHost. 

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


BROWSER/PLATFORM COMPATIBILITY
===============================
The EditHost sample requires Microsoft® Internet Explorer 5.5 or later on the 
Win32 platform. For developers, Header files for Internet Explorer 5.5 or later 
are needed for use in your development environment; in particular, Mshtml.h is necessary. 



SOURCE FILES
=============
BrowserHost.cpp
BrowserHost.h
BrowserHost.rgs
dlldata.c
EdHost.asp
EdHost.cpp
EdHost.dsp
EdHost.dsw
EdHost.idl
EdHost.plg
EdHost.rc
EdHost.rgs
EdHost_p.c
EdHostps.def
EdHostps.mk
Grid.cpp
Grid.h
grid.rgs
resource.h
Snap.cpp
Snap.h
snap.rgs
StdAfx.cpp
StdAfx.h
test.html

OTHER FILES
============
toolbar1.bmp
cone.jpg


SEE ALSO
=========
For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on Implementing IHTMLEditHost, go to:
http://msdn.microsoft.com/workshop/browser/editing/impedithost.asp

For more information on 'What's New' in IE 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.
