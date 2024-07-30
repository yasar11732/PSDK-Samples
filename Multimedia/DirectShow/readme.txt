=============================================================================
DirectShow SDK Samples README
=============================================================================

The DirectShow SDK samples are subdivided into directories according to 
their major function:

    BaseClasses
    Capture
    Common (shared source files)
    DMO
    DVD
    Filters
    Misc
    Players
    VMR
    VMR9


Building the Samples
--------------------

In addition to the standard requirements for building Platform SDK samples, the 
DirectShow samples require the DirectX SDK 9.0 Update (February 2005) or later. 

After you install the DirectX SDK, make sure the %DXSDK_DIR% environment variable 
points to the DirectX SDK install path.

You should build the BaseClasses sample first, because many of the other 
DirectShow samples require this library.

For additional DirectShow build information, see "Setting Up The Build 
Environment" in the DirectShow SDK documentation.


Windows Media support in SDK samples
------------------------------------

Because of the Windows Media Format SDK (and WMStub.lib) dependency, along with
the extra filter connection and key provider code required, most of the DirectShow 
SDK samples do not fully support rendering and playback of Windows Media content by 
default. If you attempt to open a Windows Media file using one of these samples, 
you will be presented with a message box indicating the lack of Windows Media 
support.

The Jukebox sample provides the necessary extra code and project settings to enable 
proper Windows Media support (including unlocking of "keyed" files).

Many of the other samples allow you to render Windows Media files with the legacy
DirectShow ASF Reader filter, which is adequate for simple playback.  This method,
however, does not offer the benefits of the newer Windows Media ASF Reader filter
and does not support "dekeying" of keyed Windows Media content.

For more detailed information, see "Windows Media Applications" in the DirectShow
SDK documentation.


Using Windows Media 9 Series
----------------------------

Beginning with Windows Media 9 Series and the Windows Media Format 9 SDK, the 
WMStub.lib and key provider implementation code are no longer necessary.  This
simplifies the sample code and removes the need to download and link with a WMStub 
library.

The Jukebox sample demonstrates some of the implementation differences. The 
preprocessor constant (TARGET_WMF9) disables the key-providing code. For more details,
see the Windows Media Format 9 SDK documentation.



VMR9 Hardware requirements
--------------------------

The VMR9 samples require a video card with a minimum of 16MB of video RAM. If your card has 
less than the minimum RAM, you may see failures when building filter graphs.  If that occurs, 
try lowering your display resolution.


GraphEdit
---------

The GraphEdit utility is located in the Microsoft Platform SDK\Bin directory. Before running 
GraphEdit, regsvr the file Proppage.dll. This DLL contains property pages for various filters, 
which are intended for debugging purposes only.

The x64 setup installs two versions of GraphEdit:

    x86 version: GraphEdt.exe, Proppage.dll
    x64 version: GraphEdt_64.exe, Proppage_64.dll

DirectShow does not provide an IA64 version of GraphEdit.


Known Issues
----------------------------------

The DSNetwork and VideoControl samples are listed in the DirectShow SDK documentation, but
these samples have been removed from the SDK. 

The following samples do not build on x64 platforms:
	VMR\VMRMulti
	VMR\VMRXcl
	VMR9\MultiVMR9

None of the DirectShow samples is supported for IA64.


