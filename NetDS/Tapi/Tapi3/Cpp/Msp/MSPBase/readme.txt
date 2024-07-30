______________________________________________________________________________

  Copyright (C) 2001 Microsoft Corporation. All rights reserved.

______________________________________________________________________________



Media Streaming Provider Base Classes



Overview:


These are the sources for Media Streaming Provider Base Classes.

See Platform SDK and SampleMSP sample for more information on using MSP Base
Classes for writing Media Streaming Providers.





How to build MSP Base Classes:

To build the sample:

- install the DirectX9 SDK

- set the SDK build environment by running setenv.bat in the Platform SDK root directory

- set the DXSDKROOT enviroment variablet to point to the DirectX9 SDK root directory.
	for example:

	set DXSDKROOT=C:\DXSDK

  You might want to add this line to setenv.bat so it will be set whenever you run setenv.bat

- type "nmake" in MSPBase directory. This will build MSP Base classes and 
produce MSPBaseSample.lib


Note that MSPBase' headers can be found in Platform SDK's include directory.







Building Your MSP with MSP Base Classes


Your MSP should link with the lib file produced from building MSP Base Classes.
SampleMSP is an example of an MSP that uses a custom-built msp.

