=====================================================
Reusing Browser Technology - Edit Designer Annotator
=====================================================
Last Updated: Jul 05,2000


SUMMARY
========
The Edit Designer Annotator sample implements an IHTMLEditDesigner interface 
that enables the user to read, modify, and add comments in a document. It 
demonstrates important features of edit designer implementation:  

 - How to implement IHTMLEditDesigner using Microsoft® Visual C++® 6. 
 - How to script component implementation-specifically, the calls to 
   IHTMLEditServices::AddDesigner and IHTMLEditServices::RemoveDesigner that 
   attach and detach an edit designer to and from the MSHTML Editor. 
 - How to add an edit designer component to a Web page and call the component's 
   methods from script.  
 - How to use the IMarkupServices, IMarkupPointer, IMarkupPointer2, 
   IDisplayServices, ILineInfo, and IHTMLCaret interfaces to locate the onscreen 
   position of comments, or the insertion point, and translate that position to 
   the corresponding location in the page's markup. 


DETAILS
========
If you've read through the Edit Designers Overview and first tutorial concerning 
edit designers - Implementing Edit Designers: The Basics, you already know quite 
a bit about edit designers and how to implement them. You know that they are COM 
components that you implement to customize the MSHTML Editor's behavior. You know 
that the main interface for edit designers is IHTMLEditDesigner, and that 
IHTMLEditDesigner consists of four methods:  

 - IHTMLEditDesigner::PreHandleEvent 
 - IHTMLEditDesigner::PostHandleEvent 
 - IHTMLEditDesigner::TranslateAccelerator 
 - IHTMLEditDesigner::PostEditorEventNotify 

These methods act as callback routines for the MSHTML Editor; that is, the Editor 
calls these methods at different points during the handling of events. 

Now, take the knowledge you've acquired so far and put it to work building an 
annotation system for use with the MSHTML Editor. The Annotator is simple in 
principle. It gives the user access to the comments in a document, allowing the 
user to edit the comments or add new ones as desired. To build the Annotator, 
you'll use a few customization tools available for the MSHTML Editor. You'll use 
custom glyphs to show the location of comments in a document, and markup pointers, 
display pointers, and the IHTMLCaret interface to determine a comment's location on 
the screen so you can open a comment edit box next to it or add new comments.


USAGE
======
To make best use of this sample, you need: 

 - An understanding of edit designers and their capabilities. See Edit Designers 
   Overview and Implementing Edit Designers: The Basics. 
 - A good understanding of C++, the Component Object Model (COM), and the Active 
   Template Library (ATL). 

The source code for this sample is included in a Visual C++ 6 workspace. It uses 
ATL to provide COM support, standard implementations of some common interfaces, 
and "smart" interface pointers that handle their own reference counting. You can 
use this sample as a structure for building your own implementations of 
IHTMLEditDesigner. 

Structurally, the sample consists of one class, CAnnotator, implementing two 
interfaces. The interfaces are: 

 - IHTMLEditDesigner: Only one method of this interface, 
   IHTMLEditDesigner::PreHandleEvent, is implemented for the Annotator designer. 
 - IAnnotator: This interface supports the Annotator designer. Its primary methods 
   allow a designer to be attached to, or detached from, a document through script. 
   IAnnotator also has a method to control the display of glyphs showing the 
   location of comments in a document, and another that lets the user add comments. 

The sample has been kept simple in order to focus on the implementation structure 
of edit designers. For this reason, the sample performs minimal error checking and 
no exception handling. A *"real-world" application generally provides more robust 
error checking and exception handling. 

Designer Considerations
-----------------------
Here's a strategy for implementing the Annotator and making it work on a Web 
page: 

 - The Annotator must provide a visual marker to show the locations of comments 
   in a document. You can use a custom editing glyph for this purpose. The glyph 
   is activated using the IOleCommandTarget::Exec method with the MSHTML Command 
   Identifiers for controlling custom editing glyphs. 
 - The Annotator must open a particular comment to give the user access to the 
   element. There are a variety of ways to do this - the comments could be opened 
   in a separate window or a separate area of the document, for instance. In this 
   sample, the comments open in a pop-up box. The Annotator inserts a temporary, 
   absolutely positioned, content-editable element into the document at the end 
   of the body section, and positions it next to the comment glyph. 
 - In order to place the popup window near the comment, the Annotator must 
   determine the on-screen coordinates of the comment. You can use a display 
   pointer, a markup pointer, and the ILineInfo interface for this. 
 - The Annotator must provide a way to attach itself to a Web page through script. 
   IHTMLEditServices::AddDesigner and IHTMLEditServices::RemoveDesigner are C++ 
   methods, and are not ordinarily accessible through script. The Annotator 
   therefore must include some scriptable methods that will make the calls to 
   IHTMLEditServices::AddDesigner and IHTMLEditServices::RemoveDesigner on behalf 
   of a client using the Annotator. You can include these methods by implementing 
   IDispatch . This is relatively easy with ATL's implementation IDispatchImpl. 
   You can make turning the glyphs on and off accessible through script also. 
 - For completeness, the Annotator should add a scriptable method that will allow 
   the user to add new comments to a document. To accomplish this, you can use 
   the IHTMLCaret interface, a display pointer, and a markup pointer. 

Opening the Project
-------------------
Let's begin with the steps needed to start a project in Visual C++ 6. 

 1.) First, open Visual C++ 6. 
 2.) Choose New from the File menu. 
 3.) Click the Projects tab and choose "ATL COM AppWizard." Give your project a 
     name and choose a directory in which to put it. This tutorial will call the 
     project "EDAnnotator" and put the project directory in the root directory, 
     C:\EDAnnotator. Click OK. 
 4.) In Step 1 of the Wizard, accept all defaults (Server Type = DLL; all 
     checkboxes unchecked). 
 5.) Click Finish.
 6.) Click OK at the New Project Information box.

These steps create a bare-bones project with enough support to build a 
dynamic-link library (DLL). At this point, it's a good idea to build the 
project to make sure the project settings are all correct. 

Preparing the Project Environment
---------------------------------
This project will use interface definitions from Mshtml.idl in its project 
Interface Definition Language (IDL) file, EDAnnotator.idl. In order to import 
Mshtml.idl into EDAnnotator.idl, there are some special modifications to be made 
to Mshtml.idl. Instructions for these modifications are located in the MIDL and 
Mshtml.idl (http://msdn.microsoft.com/workshop/browser/editing/editdesignerimp1.asp#MIDL_and_MSHTMLIDL)
section of Implementing Edit Designers: The Basics. If you haven't already done 
so, make the modifications described there.

There's one other modification to make to the Annotator project. Later, you'll 
be adding code that uses C run-time string comparison functions. By default, ATL 
projects don't link to the C run-time startup code. To enable the use of the 
string comparison functions, you must remove the _ATL_MIN_CRT preprocessor 
definition from the project settings. Follow these steps: 

 1.) From the Project menu, choose Settings... 
 2.) In the "Settings For:" drop-down list, select "Multiple Configurations." 
 3.) In the "Select project configuration(s) to modify" dialog box, select the 
     check boxes for all release versions, then click OK. 
 4.) Click the C/C++ tab in the Project Settings dialog box, and then choose the 
     General category. 
 5.) There will be a number of preprocessor definitions in the "Preprocessor 
     definitions" edit box, separated by commas. Remove the "_ATL_MIN_CRT" 
     preprocessor definition.

Note:  You may have to "clean" the project before this setting change will take 
effect. From the Build menu, choose Clean; alternatively, you can choose Batch 
Build and then click the Clean button from the Batch Build dialog box.

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
This sample requires Internet Explorer 5.5 or greater installed on Microsoft Win32®. 
Also, header files and libraries for Win32 and Internet Explorer 5.5 or later are 
necessary for use in your development environment. 

Note:  Microsoft Visual Studio 6.0 Service Pack 3 or greater will also be necessary 
to build and run the sample successfully in your development environment. 
(http://msdn.microsoft.com/vstudio/sp/vs6sp4/default.asp)


SOURCE FILES
=============
Annotator.cpp
Annotator.h
Annotator.htm
Annotator.rgs
Dlldata.c
EdAnnotator.aps
EdAnnotator.cpp
EdAnnotator.def
EdAnnotator.dsp
EdAnnotator.dsw
EdAnnotator.idl
EdAnnotator.inf
EdAnnotator.opt
EdAnnotator.plg
EdAnnotator.rc
EdAnnotator_p.c
EdAnnotatorps.def
Resource.h
StdAfx.cpp
StdAfx.h

OTHER FILES
============
Annotato.bmp
Comment.gif
EdAnnotator.CAB

SEE ALSO
=========
For information on Implementing Edit Designers: Advanced, go to:
http://msdn.microsoft.com/workshop/browser/editing/editdesignerimp2.asp

For more information on Reusing Browser Technology, go to:
http://msdn.microsoft.com/workshop/browser/default.asp

For more information on 'What's New' in Internet Explorer 5.5, go to:
http://msdn.microsoft.com/workshop/essentials/whatsnew/whatsnew.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.
