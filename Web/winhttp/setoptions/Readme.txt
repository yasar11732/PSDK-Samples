===============================================================================
WINHTTP SERVICES - SetOptions
===============================================================================
Last Updated: October 18, 2001

DESCRIPTION
============
This sample demonstrates the process for setting Microsoft® Windows® HTTP 
Services (WinHTTP) options programmatically from a C/C++ application. 
WinHTTP application programming interface (API) functions are used to 
change the connect time-out value.

MORE DETAILS
============
WinHTTP provides developers with a server-supported, high-level interface 
to the HTTP Internet protocol. WinHTTP is designed to be used primarily in 
server-based applications, such as IIS-based middle-tier servers, to send 
requests through the HTTP protocol to other servers. WinHTTP offers both a 
Microsoft Win32® C/C++ API, as well as a Component Object Model (COM) 
Automation component suitable for use in Active Server Pages (ASP)-based 
applications. 

BROWSER/PLATFORM COMPATIBILITY
===============================
WinHTTP 5.1 runs on Windows 2000 Service Pack 3, Windows XP Service Pack 1, 
and Windows Server 2003 RC1 or later. It requires Unicode support, and is not 
supported on Windows NT 4.

For Windows Server 2003, WinHTTP is a system side-by-side assembly. See the "Side-
by-side Assemblies Reference" topic for further information.

WinHTTP 5.0 runs on Windows 2000 or later, or Microsoft Windows NT® 4.0 
with Internet Explorer 5.01 or later. Determine the version of Internet 
Explorer by clicking "About Internet Explorer" on the Help menu. The 
version number reported in this dialog box should be 5.00.2900.6300 or 
higher.


USAGE
=====
To use the SetOptions sample, complete the following steps:

  1. Download and install the Win 32 Headers and Libraries files for 
     Windows XP SP1 or later.

  2. Place the WinHTTP header file (Winhttp.h) and library file 
     (Winhttp.lib) in your development environment.

  3. Open the SetOptions workspace in Microsoft Visual C++®.
     Build and run the application.


SOURCE FILES
=============
SetOptions.cpp

OTHER FILES
============
Readme.txt


RELATED INFORMATIONAL SOURCES
=============================
  "Setting Internet Options With WinHTTP"
  "WinHTTP Option Flags Constants"

=================================
Copyright © Microsoft Corporation






