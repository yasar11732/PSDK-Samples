==============================================
Reusing Browser Technology - Editing Commands
==============================================
Last Updated: January 22, 2000


SUMMARY
========
The MSHTML Editor provides a full complement of commands that enable you to modify 
a document. The commands to edit a document operate on the current selection. They 
enable you to perform many tasks, including: 

 - Cutting, copying, pasting or deleting the selection. 
 - Changing font size or color. 
 - Inserting new elements. 
 - Finding text. 
 - Changing between overwriting and insertion mode. 
 - Creating or removing hyperlinks. 
 - Indenting and negative-indenting blocks. 

You can find a list of the available commands in MSHTML Command Identifiers. 

The commands can be used from C++, Visual Basic, and script. The commands also work 
in browse mode, though you can't edit the text in browse mode. When you execute a 
command, it becomes a part of the Editor's undo list, if applicable. The MSHTML Editor 
provides some keyboard shortcuts to execute commands: the most important of these commands are copy, cut, paste, bold, and italic. 

Caution: If you change a property on any element in a page, the undo list is cleared. 


DETAILS
========
The samples for this tutorial demonstrate the selection editing commands controlled 
through IOleCommandTarget::Exec and execCommand. They show: 

 - How each of the features behaves. 
 - How to use IOleCommandTarget::Exec and execCommand to execute editing commands. 

There are two samples for this tutorial. One is an executable application developed 
in C++; the other is a simple Web page. Their specifications are similar: 

 - The samples are simple editor implementations with buttons and input boxes to 
   execute commands. 
 - The first button turns the MSHTML Editor on and off. 
 - Each of the other buttons executes one of the selection editing commands. 
   Some commands have edit boxes for input. 


USAGE
======
Note: You must download the sample to your own computer to run it. The source code 
for this sample is included in a Microsoft® Visual C++ 6 workspace. The C++ sample 
uses ATL to provide COM support, standard implementations of some of the standard 
interfaces, and "smart" interface pointers that handle their own reference counting. 

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


BROWSER/PLATFORM COMPATIBILITY
===============================
The Editing Commands sample requires Microsoft® Internet Explorer 5.5 or later on 
the Win32 platform. For developers, header files for Internet Explorer 5.5 or later 
are needed for use in your development environment; in particular, Mshtml.h 
and Mshtmcid.h are necessary.  


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
cone.jpg


SEE ALSO
=========
For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on Modifying Documents in Edit Mode, go to:
http://msdn.microsoft.com/workshop/browser/editing/modifyingdoc.asp

For more information on 'What's New' in IE 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.
