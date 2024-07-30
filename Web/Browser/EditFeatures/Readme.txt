==============================================
Reusing Browser Technology - Editing Features
==============================================
Last Updated: January 22, 2001


SUMMARY
========
You can activate a number of optional features to enhance the MSHTML Editor's 
default behavior. For a list of these features, see the section entitled "Document Level 
Editing Commands" at the end of "Using the MSHTML Editor's Extra Features," an article in Web Workshop. 


The commands used to modify the Editor's behavior can be used from 
C++. Most of these commands work only when the browser is in design mode. They are turned off when the Editor is deactivated or the WebBrowser navigates to a new page.  


DETAILS
========
The samples for this tutorial demonstrate the selection editing commands controlled 
through IOleCommandTarget::Exec and execCommand. They show: 

 - How each of the features behaves. 
 - How to use IOleCommandTarget::Exec and execCommand to execute editing commands. 

There are two samples for this tutorial. One is an executable application developed 
in C++; one is a simple Web page. The specifications are similar: 

 - The samples are simple editor implementations with buttons and input boxes to 
   execute commands. 
 - The first button turns the MSHTML Editor on and off. 
 - Each of the other buttons executes one of the selection editing commands. 
   Some commands have edit boxes for input. 

The source code for this sample is included in a Microsoft® Visual C++ 6 workspace. 
It uses ATL to provide COM support, standard implementations of some of the standard 
interfaces, and "smart" interface pointers that handle their own reference counting. 

Many of the interface pointers in the sample are wrapped by the CComQIPtr class. 
CComQIPtr is a "smart" pointer class. Besides automatic reference counting, it provides 
overloaded operators to make working with COM easier. CComQIPtr includes an overloaded 
assignment operator (operator=) which performs an automatic QueryInterface during 
assignment. For instance, the sample's QueryInterface call to initialize its 
IOleCommandTarget pointer looks like this: 

  // m_spWebBrowser is an already-initialized pointer to an IWebBrowser2 interface.
  // m_spOleCmdTarg is a declared but uninitialized CComQIPtr for an IOleCommandTarget 
     interface.

  m_spOleCmdTarg = m_spWebBrowser;


USAGE
======
Note: You must download the sample to your own computer to run it. 

The source code for this sample is included in a Microsoft® Visual C++ 6 workspace. 
It uses ATL to provide COM support, standard implementations of some of the standard 
interfaces, and "smart" interface pointers that handle their own reference counting. 
 
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

The editing commands can be executed using the IOleCommandTarget::Exec method with 
command identifiers taken from the CGID_MSHTML command group. These commands are defined 
in Mshtmcid.h. You can obtain an IOleCommandTarget interface by calling QueryInterface 
on either the IWebBrowser2 or IHTMLDocument2 interface. 

  // Assume pWebBrowser is a valid pointer to the IWebBrowser2 interface
  IOleCommandTarget* pCmdTarg;
  pWebBrowser->QueryInterface(IID_IOleCommandTarget, (void**)&pCmdTarg);

Here is how you can turn on 2-D positioning using IOleCommandTarget::Exec: 

  // Declare a VARIANT data type and initialize it
  VARIANT var;
  V_VT(&var) = VT_BOOL; // Set the type to BOOL  
  V_BOOL(&var) = VARIANT_TRUE;

  // Turn on 2-D positioning for absolutely positioned elements
  hr = pCmdTarg->Exec(&CGID_MSHTML, IDM_2D_POSITION, MSOCMDEXECOPT_DODEFAULT, &var, NULL);

V_VT(X) and V_BOOL(X) are macros defined in Oleauto.h. They take a VARIANT pointer 
for their argument. The sample file BrowserHost.cpp includes Oleauto.h indirectly by 
way of Mshtmhst.h. Mshtmhst.h includes Ole2.h, which includes Oleauto.h. These macros 
assign a value to the appropriate member of a VARIANT structure. For instance, 
V_BOOL(&var) = VARIANT_TRUE is equivalent to var.bVal = VARIANT_TRUE. 


BROWSER/PLATFORM COMPATIBILITY
===============================
The Editing Features sample requires Microsoft® Internet Explorer 5.5 or later on 
the Win32 platform. For developers, Header files for Internet Explorer 5.5 or later 
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


SEE ALSO
=========
For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on Using the MSHTML Editor's Extra Features, go to:
http://msdn.microsoft.com/workshop/browser/editing/editingfeatures.asp

For more information on 'What's New' in IE 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp

==================================
Copyright (c) Microsoft Corporation. All rights reserved.
