# Microsoft Developer Studio Generated NMAKE File, Based on OpenServ.dsp
!IF "$(CFG)" == ""
CFG=OpenServ - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to OpenServ - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "OpenServ - Win32 Release" && "$(CFG)" != "OpenServ - Win32 Debug" && "$(CFG)" != "OpenServ - Win32 Ansi Release" && "$(CFG)" != "OpenServ - Win32 Ansi Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenServ.mak" CFG="OpenServ - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenServ - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenServ - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenServ - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenServ - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OpenServ - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\OpenServ.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\Land.obj"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\People.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\Sky.obj"
	-@erase "$(INTDIR)\Space.obj"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OpenServ.dll"
	-@erase "$(OUTDIR)\OpenServ.exp"
	-@erase "$(OUTDIR)\OpenServ.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OpenServ_EXPORTS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\OpenServ.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x11000000" /dll /incremental:no /pdb:"$(OUTDIR)\OpenServ.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\OpenServ.dll" /implib:"$(OUTDIR)\OpenServ.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\Land.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\People.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Sky.obj" \
	"$(INTDIR)\Space.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\OpenServ.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\OpenServ.dll
InputPath=.\Release\OpenServ.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OpenServ.dll" "$(OUTDIR)\OpenServ.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\BaseSnap.sbr"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Comp.sbr"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\CompData.sbr"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DataObj.sbr"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\DeleBase.sbr"
	-@erase "$(INTDIR)\Land.obj"
	-@erase "$(INTDIR)\Land.sbr"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\MMCCrack.sbr"
	-@erase "$(INTDIR)\People.obj"
	-@erase "$(INTDIR)\People.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\Sky.obj"
	-@erase "$(INTDIR)\Sky.sbr"
	-@erase "$(INTDIR)\Space.obj"
	-@erase "$(INTDIR)\Space.sbr"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\StatNode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OpenServ.bsc"
	-@erase "$(OUTDIR)\OpenServ.dll"
	-@erase "$(OUTDIR)\OpenServ.exp"
	-@erase "$(OUTDIR)\OpenServ.ilk"
	-@erase "$(OUTDIR)\OpenServ.lib"
	-@erase "$(OUTDIR)\OpenServ.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenServ.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\Comp.sbr" \
	"$(INTDIR)\CompData.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\DeleBase.sbr" \
	"$(INTDIR)\Land.sbr" \
	"$(INTDIR)\MMCCrack.sbr" \
	"$(INTDIR)\People.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\Sky.sbr" \
	"$(INTDIR)\Space.sbr" \
	"$(INTDIR)\StatNode.sbr"

"$(OUTDIR)\OpenServ.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x11000000" /dll /incremental:yes /pdb:"$(OUTDIR)\OpenServ.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\OpenServ.dll" /implib:"$(OUTDIR)\OpenServ.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\Land.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\People.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Sky.obj" \
	"$(INTDIR)\Space.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\OpenServ.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\OpenServ.dll
InputPath=.\Debug\OpenServ.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\OpenServ.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\Land.obj"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\People.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\Sky.obj"
	-@erase "$(INTDIR)\Space.obj"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OpenServ.dll"
	-@erase "$(OUTDIR)\OpenServ.exp"
	-@erase "$(OUTDIR)\OpenServ.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OpenServ_EXPORTS" /Fp"$(INTDIR)\OpenServ.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenServ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x11000000" /dll /incremental:no /pdb:"$(OUTDIR)\OpenServ.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\OpenServ.dll" /implib:"$(OUTDIR)\OpenServ.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\Land.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\People.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Sky.obj" \
	"$(INTDIR)\Space.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\OpenServ.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\OpenServ.dll
InputPath=.\Ansi_release\OpenServ.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\OpenServ.dll" "$(OUTDIR)\OpenServ.bsc" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\BaseSnap.sbr"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Comp.sbr"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\CompData.sbr"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DataObj.sbr"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\DeleBase.sbr"
	-@erase "$(INTDIR)\Land.obj"
	-@erase "$(INTDIR)\Land.sbr"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\MMCCrack.sbr"
	-@erase "$(INTDIR)\People.obj"
	-@erase "$(INTDIR)\People.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\Sky.obj"
	-@erase "$(INTDIR)\Sky.sbr"
	-@erase "$(INTDIR)\Space.obj"
	-@erase "$(INTDIR)\Space.sbr"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\StatNode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OpenServ.bsc"
	-@erase "$(OUTDIR)\OpenServ.dll"
	-@erase "$(OUTDIR)\OpenServ.exp"
	-@erase "$(OUTDIR)\OpenServ.ilk"
	-@erase "$(OUTDIR)\OpenServ.lib"
	-@erase "$(OUTDIR)\OpenServ.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenServ.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\Comp.sbr" \
	"$(INTDIR)\CompData.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\DeleBase.sbr" \
	"$(INTDIR)\Land.sbr" \
	"$(INTDIR)\MMCCrack.sbr" \
	"$(INTDIR)\People.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\Sky.sbr" \
	"$(INTDIR)\Space.sbr" \
	"$(INTDIR)\StatNode.sbr"

"$(OUTDIR)\OpenServ.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x11000000" /dll /incremental:yes /pdb:"$(OUTDIR)\OpenServ.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\OpenServ.dll" /implib:"$(OUTDIR)\OpenServ.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\Land.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\People.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Sky.obj" \
	"$(INTDIR)\Space.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\OpenServ.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\OpenServ.dll
InputPath=.\Ansi_debug\OpenServ.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OpenServ.dep")
!INCLUDE "OpenServ.dep"
!ELSE 
!MESSAGE Warning: cannot find "OpenServ.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OpenServ - Win32 Release" || "$(CFG)" == "OpenServ - Win32 Debug" || "$(CFG)" == "OpenServ - Win32 Ansi Release" || "$(CFG)" == "OpenServ - Win32 Ansi Debug"
SOURCE=.\About.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseSnap.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Comp.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompData.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DataObj.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeleBase.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Land.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\Land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\Land.obj"	"$(INTDIR)\Land.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\Land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\Land.obj"	"$(INTDIR)\Land.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MMCCrack.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\People.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\People.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\People.obj"	"$(INTDIR)\People.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\People.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\People.obj"	"$(INTDIR)\People.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Sky.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\Sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\Sky.obj"	"$(INTDIR)\Sky.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\Sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\Sky.obj"	"$(INTDIR)\Sky.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Space.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\Space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\Space.obj"	"$(INTDIR)\Space.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\Space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\Space.obj"	"$(INTDIR)\Space.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StatNode.cpp

!IF  "$(CFG)" == "OpenServ - Win32 Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "OpenServ - Win32 Ansi Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Resource.rc

"$(INTDIR)\Resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

