=============================
DX Surface Example - DXSurf3
=============================
Last Updated: OCT. 18,  2001              

DESCRIPTION
============
DXSurf3 blends one image surface with surfaces with pixel RBG color 
and alpha values defined dynamically called procedural surfaces.  
Only the procedure used to compute the surface is stored in memory.  
Examples of procedural surfaces are lines, dots, including surfaces 
resulting from AlphaImageLoader and Gradient filters.  In this sample 
the procedural surface is a fractal.

DETAILED DESCRIPTION
====================
More Details
This sample shows a fractal being rendered translucently over a parrot. 
This sample demonstrates: 

-+- Using a DXSurface in full-screen and windowed mode. 
-+- Loading an image onto a DXSurface. 
-+- Directly manipulating the alpha, red, green, and blue components of pixels. 
-+- Using graphics device interface (GDI) objects on DXSurfaces. 
-+- Using a DXTransform function to scale a DXSurface to fit the window. 


BROWSER/PLATFORM COMPATIBILITY
===============================
DXSurf3.exe operates with Microsoft® Internet Explorer 5.5 and greater 
on the Microsoft Win32® platforms.

USAGE
=====
To build DXSurf3.exe, the following is required. 

1) Platform Software Development Kit (PSDK) (the latest version). 
2) If using If using Internet Explorer 6 Public Preview, the Internet 
   Explorer 6 Public Preview header and library files that contains the 
    DXTransform header and library files. 
3) If using Internet Explorer 5.5, the Internet Explorer 5.5 header
   and library files that contains the DXTransform header and library files. 
4) Microsoft® Visual C++® 6.0 or later

To run the demo, go to the Demo folder, insure that DXSurf3.exe and 
Parrot.png are in the same folder, and then click DXSurf3.exe. 


SOURCE FILES
=============
DXSurf3.cpp
Resource.h

OTHER FILES
============
Readme.txt

RELATED INFORMATIONAL SOURCES
=============================
Building DirectX Transform Samples and Applications:
http://msdn.microsoft.com/Workshop/browser/filter/OVERVIEW
/BuildingDirectXTransformSamplesandApplications.asp

DirectX Transform Author's Guide:
http://www.microsoft.com/directx/dxm/help/dxt/overview/DXTAuthorGuide.htm#meshpick

=======================
© Microsoft Corporation





 







