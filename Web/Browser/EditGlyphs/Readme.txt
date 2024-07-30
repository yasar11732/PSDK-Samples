============================================
Reusing Browser Technology - Editing Glyphs
============================================
Last Updated: January 22, 2001


SUMMARY
========
Editing glyphs are images that represent the tags formatting a Web page. Editing 
glyphs give users visual clues about the structure of a page, and enable users 
to do more precise editing than they could without glyphs. The MSHTML Editor enables 
you to represent most tags with your own custom images. However, some tags can't have 
glyph images. For instance, a TABLE tag can be assigned an image to show where the table 
as a whole is anchored in the document, but images cannot be assigned to the tags that 
format within the table, like TD and TH. Custom glyphs can only be used from C++, and 
work only when design mode is "On."   


DETAILS
========
The sample for this tutorial shows how to use custom editing glyphs in an application. 
It demonstrates the most important implementation details to consider: 

 - How to use IOleCommandTarget::Exec to specify images to display for specific tags. 
 - How to format the string data that IOleCommandTarget::Exec needs. 
 - How to use image resources in a dynamic-link library (DLL) or executable program 
   to store the images for the editing glyphs. 

The specifications of this behavior: 

 - This sample is a simple browser implementation with an address bar and three buttons. 
 - The first button turns design mode on and off. 
 - The second button turns the custom editing glyphs on and off. 
 - The third button turns the default editing glyphs on and off. 

Many of the interface pointers in the sample are wrapped by the CComQIPtr class. 
CComQIPtr is a "smart" pointer class. Besides automatic reference counting, it provides 
overloaded operators to make working with COM easier. CComQIPtr includes an overloaded 
assignment operator (operator=) which performs an automatic QueryInterface during 
assignment. For instance, the sample's QueryInterface call to initialize its 
IOleCommandTarget pointer looks like this: 

  // m_spWebBrowser is an already initialized pointer to an IWebBrowser2 interface.
  // m_spOleCmdTarg is a declared but uninitialized CComQIPtr for an IOleCommandTarget interface.

  m_spOleCmdTarg = m_spWebBrowser;


USAGE
======
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
The Editing Glyphs sample requires Microsoft® Internet Explorer 5.5 or later on 
the Win32 platform. For developers, header files for Internet Explorer 5.5 or later 
are needed for use in your development environment; in particular, Mshtml.h and Mshtmcid.h are necessary.   


SOURCE FILES
=============
BrowserHost.cpp
BrowserHost.h
BrowserHost.rgs
dlldata.c
EdCommands.asp
EdCommands.cpp
EdCommands.dsp
EdCommands.dsw
EdCommands.idl
EdCommands.rc
EdCommands.rgs
EdCommands_p.c
EdCommandsps.def
EdCommandsps.mk
resource.h
StdAfx.cpp
StdAfx.h
test.html

OTHER FILES
============
toolbar1.bmp
anchor.gif
br.gif
comment.gif
divbgn.gif
divend.gif
formbgn.gif
formend.gif
h3bgn.gif
h3end.gif
pbgn.gif
pend.gif
script.gif
spanbgn.gif
spanend.gif
style.gif
styleend.gif
table.gif
trans.gif


SEE ALSO
=========
For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on Using Editing Glyphs, go to:
http://msdn.microsoft.com/workshop/browser/editing/usingeditingglyphs.asp

For more information on 'What's New' in IE 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.
