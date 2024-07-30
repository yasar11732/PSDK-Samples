# Microsoft Developer Studio Project File - Name="sampprov" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sampprov - Win32 x86 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sampprov.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sampprov.mak" CFG="sampprov - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sampprov - Win32 x86 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 x86 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampprov"
# PROP BASE Intermediate_Dir ".\sampprov"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\Debug"
# PROP Intermediate_Dir "x86\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"headers.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msad.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /profile /map

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\samppro0"
# PROP BASE Intermediate_Dir ".\samppro0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\Release"
# PROP Intermediate_Dir "x86\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"headers.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msad.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map /machine:I386
# SUBTRACT BASE LINK32 /profile /incremental:yes /debug
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /map /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /profile /incremental:yes /debug

!ENDIF 

# Begin Target

# Name "sampprov - Win32 x86 Debug"
# Name "sampprov - Win32 x86 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\accessor.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# ADD CPP /Yu"headers.h"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asserts.cpp
# End Source File
# Begin Source File

SOURCE=.\baseobj.cpp
# End Source File
# Begin Source File

SOURCE=.\binder.cpp
# End Source File
# Begin Source File

SOURCE=.\bitarray.cpp
# End Source File
# Begin Source File

SOURCE=.\classfac.cpp
# End Source File
# Begin Source File

SOURCE=.\colinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\command.cpp
# End Source File
# Begin Source File

SOURCE=.\common.cpp
# End Source File
# Begin Source File

SOURCE=.\crtsess.cpp
# End Source File
# Begin Source File

SOURCE=.\cvttype.cpp
# End Source File
# Begin Source File

SOURCE=.\datasrc.cpp
# End Source File
# Begin Source File

SOURCE=.\dbinit.cpp
# End Source File
# Begin Source File

SOURCE=.\dbprop.cpp
# End Source File
# Begin Source File

SOURCE=.\dbsess.cpp
# End Source File
# Begin Source File

SOURCE=.\extbuff.cpp
# End Source File
# Begin Source File

SOURCE=.\fileidx.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\fileio.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\hashtbl.cpp
# End Source File
# Begin Source File

SOURCE=.\headers.cpp
# ADD CPP /Yc"headers.h"
# End Source File
# Begin Source File

SOURCE=.\igetrow.cpp
# End Source File
# Begin Source File

SOURCE=.\irowiden.cpp
# End Source File
# Begin Source File

SOURCE=.\irowset.cpp
# End Source File
# Begin Source File

SOURCE=.\opnrowst.cpp
# End Source File
# Begin Source File

SOURCE=.\persist.cpp
# End Source File
# Begin Source File

SOURCE=.\row.cpp
# End Source File
# Begin Source File

SOURCE=.\rowchng.cpp
# End Source File
# Begin Source File

SOURCE=.\rowinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\rowset.cpp
# End Source File
# Begin Source File

SOURCE=.\sampprov.def
# End Source File
# Begin Source File

SOURCE=.\sampprov.rc
# End Source File
# Begin Source File

SOURCE=.\stream.cpp
# End Source File
# Begin Source File

SOURCE=.\utilprop.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\accessor.h
# End Source File
# Begin Source File

SOURCE=.\asserts.h
# End Source File
# Begin Source File

SOURCE=.\baseobj.h
# End Source File
# Begin Source File

SOURCE=.\binder.h
# End Source File
# Begin Source File

SOURCE=.\bitarray.h
# End Source File
# Begin Source File

SOURCE=.\classfac.h
# End Source File
# Begin Source File

SOURCE=.\command.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\datasrc.h
# End Source File
# Begin Source File

SOURCE=.\dbsess.h
# End Source File
# Begin Source File

SOURCE=.\extbuff.h
# End Source File
# Begin Source File

SOURCE=.\fileidx.h
# End Source File
# Begin Source File

SOURCE=.\fileio.h
# End Source File
# Begin Source File

SOURCE=.\guids.h
# End Source File
# Begin Source File

SOURCE=.\hashtbl.h
# End Source File
# Begin Source File

SOURCE=.\headers.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\row.h
# End Source File
# Begin Source File

SOURCE=.\rowset.h
# End Source File
# Begin Source File

SOURCE=.\sampprov.h
# End Source File
# Begin Source File

SOURCE=.\sampver.h
# End Source File
# Begin Source File

SOURCE=.\stream.h
# End Source File
# Begin Source File

SOURCE=.\utilprop.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
