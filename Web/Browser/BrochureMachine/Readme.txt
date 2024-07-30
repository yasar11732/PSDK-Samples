=============================================
Reusing Browser Technology - Brochure Machine
=============================================
Last Updated: Jan. 22, 2001


SUMMARY
========
The Brochure Machine sample demonstrates a simple Web-based application that edits 
and prints brochures. The Web page shows two pages of a two-fold brochure. Each page 
has three editable columns and includes an option to add a watermark image. Most 
important to this sample, the page provides a button to preview the brochure before 
printing. The user interface also provides toolbars that enable the user to format 
the text and images. The user can: 

 - Apply bold or italic formatting to text. 
 - Change the font, font size, and font color. 
 - Add, change, reposition, and resize images. 
 - Change the column margins. 
  

DETAILS
========
Most important to this sample, the page provides a button to preview the brochure 
before printing. 

The Web page does a pretty good job of representing how the brochure will look, but 
it's not perfect-that's the reason for print preview, after all. The page displays 
scroll bars on a column to indicate when that column contains too much content. When 
you view the brochure in print preview mode, you get an accurate image of how the 
brochure will print. The template checks each column to make sure that the content 
doesn't overflow. It also checks to make sure that the printer is in landscape mode 
and prompts the reader to switch to landscape mode if necessary. 

There are three files in this sample: 

 - BrochureMachine.htm: the Web page with the editable brochure. 
 - BrochureMachine.cab: a cabinet file containing BrochureMachine.dll, which is 
   the control that opens the print preview window. 
 - PT.htm: the print template for viewing and printing the brochure. This file 
   is a resource contained in BrochureMachine.dll. 

The ActiveX control, BrochureMachine.dll
----------------------------------------
Because this sample is Web-based, the binary code to print and preview with the 
custom template is loaded as a COM component and included as an object in the HEAD 
section of the page. The control was developed with Microsoft® Visual C++® 6.0 and 
the ATL Component Wizard. Most of the code just provides support for the COM control. 
The working part, from our point of view, consists of a single method named LaunchPT 
on a single interface, IPTLauncher. The code for LaunchPT is pretty simple. It obtains 
an IOleCommandTarget interface for the document object from the IOleClientSite 
interface in the control by way of IOleContainer, IServiceProvider, IWebBrowser2, 
IDispatch, and IHTMLDocument2. It then calls IOleCommandTarget::Exec to issue the 
IDM_PRINTPREVIEW command with the pvaIn parameter specifying the address of the custom 
template resource, PT.htm, contained in the DLL. 

Note: For clarity, this function contains no error handling.

  STDMETHODIMP CPTLauncher::LaunchPT()
  {
  CComPtr spContainer;
      CComPtr spSP;
      CComPtr spWB;
      CComPtr spDisp;
      CComPtr spDoc;
      CComPtr spCT;
      CComVariant vPTPath = "res:/BrochureMachine.dll/PT.htm";

      m_spClientSite->GetContainer(&spContainer);
      spContainer->QueryInterface(IID_IServiceProvider, (void**)&spSP);
      spSP->QueryService(SID_SWebBrowserApp, IID_IWebBrowser, (void**)&spWB);
      spWB->get_Document(&spDisp);
      spDisp->QueryInterface(IID_IHTMLDocument2, (void**)&spDoc);
      spDoc->QueryInterface(IID_IOleCommandTarget, (void**)&spCT);
      spCT->Exec(&CGID_MSHTML, IDM_PRINTPREVIEW, NULL, &vPTPath, NULL);

      return S_OK;
  }

The Main Page, BrochureMachine.htm
----------------------------------
TThe Web page for the Brochure Machine shows the user the front and back page of the 
brochure and provides toolbars for various editing tasks. The pages have editable 
columns for each section of the brochure. The section styles and the page width and height 
are specified in inches to correspond with letter-size paper.

There's a fair amount of code to this sample to provide a meaningful editing environment. 
For this description, there are two relevant code sections: the ShowPrintPreview function 
and one line in the Init function to add an expando object to the document object. The 
expando object will pass information to the print template. ShowPrintPreview initializes 
the object and calls LaunchPT to open the print preview window.

The Template, PT.htm
--------------------
For the most part, PT.htm uses printing code you’ve already seen in other print templates. 
In addition, it provides error checking to make sure the LAYOUTRECT elements haven't 
overflowed, as well as prompting for the user to switch to landscape orientation and a 
technique for sourcing in content from the Web page.

Building a Document on the Fly for a LAYOUTRECT:
-----------------------------------------------
In the last article, it was demonstrated how to use the dialogArguments.__IE_ContentSelectionUrl 
property to print only the current selection in Internet Explorer. This is a useful feature, 
but suppose you want to print a section that’s not the current selection, or print multiple 
noncontiguous sections? 

Because the template has a reference to the document object for the currently displayed 
page, __IE_BrowseDocument, you can use that reference to extract the portions you want 
from the original and build documents on the fly for the LAYOUTRECT elements you want to 
print. Create a new BODY element using document.createElement, extract the innerHTML from 
the elements you want through __IE_BrowseDocument, and insert that innerHTML in the new 
BODY element you've created. The template does this six times using a for loop in the Init 
function to obtain the content for the columns.

  for (i = 1; i <= 6; i++)
  {
    document.all("layoutrect" + i).onlayoutcomplete = OverflowChecker;
    theBody = document.createElement("BODY");
    theBody.innerHTML = 
        dialogArguments.__IE_BrowseDocument.all("layoutrect" + i).innerHTML;
    
    FixImageURLs(theBody, 
                 dialogArguments.__IE_BrowseDocument.all("layoutrect" + i));    

    document.all("layoutrect" + i).contentSrc = theBody.document;
  }

The template also extracts the images for the watermarks and places them in two additional 
DEVICERECT elements, one for each page. The template doesn’t have to extract the brochure 
information in eight sections; the brochure can extract it in just two operations, acquiring 
the content from the front DIV as a whole and the back DIV as a whole. It was done this way 
so the print template can be "aware" of content overflow in any of the brochure columns and 
to warn the user visually when overflow occurs. 

Notice the function FixImageURLs. The document created with the document.createElement("BODY") 
call does not use the correct URL root to resolve relative links or paths specified in the 
source document. It uses the path to the DLL when it attempts to resolve relative links and 
paths. For instance, the path to an image with a relative source path of graphics/globe1.gif 
in theBody might be res://brochuremachine/graphics/globe1.gif. This makes sense because the 
new element has been created by the DLL. FixImageURLs corrects this problem by grabbing the 
correct paths from the source. 

  function FixImageURLs(oBody, oSourceDiv)
  {
    oBodyImgColl = oBody.document.all.tags("IMG");
    oSourceDivImgColl = oSourceDiv.all.tags("IMG");
    
    for (j = 0; j < oBodyImgColl.length; j++)
        oBodyImgColl.item(j).src = oSourceDivImgColl.item(j).src;
  }

You can use this technique to create dynamic changes in LAYOUTRECT content while in 
print preview mode. All you have to do is create a new BODY element with the content 
you want and substitute it for the contentSrc in a LAYOUTRECT. The change will take 
effect immediately in the print preview window.

Passing Information to a Print Template:
---------------------------------------
The print template needs information from the Web page to determine margin settings and 
watermark placement. The template could drill into __IE_BrowseDocument to obtain this 
information, but it was decided to make it a little simpler for the template to obtain the 
information it needs. This way, it can illustrate a technique to pass information between 
a Web page and a print template. BrochureMachine.htm creates an expando object on the 
document object called brochureInfo. Immediately before the print preview window opens 
(in other words, just before the call to LaunchPT), the Web page initializes this expando 
object with a variety of properties for the margin settings and the watermark placement. 
The print template can read these properties from __IE_BrowseDocument. 

Although the Brochure Machine sample uses this technique only to read properties from 
__IE_BrowseDocument, there is a lot more potential here if you want to use it. 

 - Objects attached as expandos to the Web page document object are full-fledged objects. 
   They can contain functions, arrays, and other kinds of data and nested objects. 
 - A print template can make changes to __IE_BrowseDocument. These changes directly 
   affect the document rendered by the browser. 
 - You can also attach new expando properties to __IE_BrowseDocument from the print 
   template code. These properties will be available to the Web page when the print 
   preview window closes. There is one limitation, though: if you attach an expando 
   object to __IE_BrowseDocument, it will be available only while the print template 
   is active. The print template owns all objects it creates. After the print preview 
   window closes or printing is completed, any objects created by the template are 
   deleted when the template destroys itself.

Checking Page Orientation:
-------------------------
There is no page orientation setting with the print architecture. When a page switches 
from portrait mode to landscape mode or back, the page width and height properties merely 
exchange places. The print template checks the page orientation and paper size by verifying 
that the pageWidth property of the TemplatePrinter behavior is 1100 (remember, page 
measurement is in hundredths of an inch) and that the pageHeight is 850. If the property 
settings are otherwise, the template displays an appropriate alert and opens the Page 
Setup dialog box so the user can correct the settings.

Content Overflow Alert:
----------------------
The onlayoutcomplete event handler for each of the six LAYOUTRECT elements is a function 
called CheckOverflow. It simply checks the contentOverflow property of the event object. 
If the property is true, the function alerts the user that a column contains too much 
stuff and adds a blinking border to that LAYOUTRECT.

USAGE
===============================
Note: You must first download the sample to your own computer to run it.

The source code for this sample is included in a Microsoft® Visual C++ 6 workspace.
Note:  You will need to include the Internet Explorer 5.5 header and library files, and the 

Windows 2000 Header and Library files from the Platform SDK in your development path when 
building the sample source code.

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
This sample requires Microsoft® Internet Explorer 5.5 or later installed on Microsoft 
Win32®. Header files and libraries for Win32 and Internet Explorer 5.5 or later are 
also necessary for use in your development environment. 


SOURCE FILES
=============
BrochureMachine.aps
BrochureMachine.cpp
BrochureMachine.def
BrochureMachine.dsp
BrochureMachine.dsw
BrochureMachine.htm
BrochureMachine.idl
BrochureMachine.inf
BrochureMachine.ncb
BrochureMachine.opt
BrochureMachine.plg
BrochureMachine.rc
BrochureMachine_p.c
BrochureMachineps.def
BrochureMachineps.mk
Dlldata.c
PT.htm
PTLauncher.cpp
PTLauncher.h
PTLauncher.rgs
Resource.h
StdAfx.cpp
StdAfx.h

SUPPORT FILES
==============
BrochureMachine.CAB

GRAPHICS FILES
===============
Bold.gif
Books1.gif
Books2.gif
Bulletlist.gif
Centeralign.gif
Clock1.gif
Clock2.gif
Divider.gif
Form-strike.gif
Globe1.gif
Globe1a.gif
Globe2.gif
Globe2n.gif
Indent.gif
Italic.gif
Leftalign.gif
Movedwn.gif
Movedwn2.gif
Movelft.gif
Movert.gif
Movert2.gif
Moveup.gif
Moveup2.gif
Narrower.gif
Narrower2.gif
Numberlist.gif
Outdent.gif
Rightalign.gif
Shorter.gif
Shorter2.gif
Subscript.gif
Superscript.gif
Taller.gif
Taller2.gif
Tool_vertical.gif
Trans1x1.gif
Underline.gif
Wider.gif


SEE ALSO
=========
For more information on Beyond Print Preview: Print Customization for Internet 
Explorer 5.5, go to:
http://msdn.microsoft.com/workshop/browser/hosting/printpreview/printtemplate2.asp


==================================
Copyright (c) Microsoft Corporation. All rights reserved.

