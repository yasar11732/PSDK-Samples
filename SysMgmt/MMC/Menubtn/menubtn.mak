# Microsoft Developer Studio Generated NMAKE File, Based on MenuBtn.dsp
!IF "$(CFG)" == ""
CFG=MenuBtn - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to MenuBtn - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "MenuBtn - Win32 Release" && "$(CFG)" != "MenuBtn - Win32 Debug" && "$(CFG)" != "MenuBtn - Win32 Ansi Release" && "$(CFG)" != "MenuBtn - Win32 Ansi Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MenuBtn.mak" CFG="MenuBtn - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MenuBtn - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuBtn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuBtn - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MenuBtn - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MenuBtn - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MenuBtn.dll" ".\Release\regsvr32.trg"


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
	-@erase "$(OUTDIR)\MenuBtn.dll"
	-@erase "$(OUTDIR)\MenuBtn.exp"
	-@erase "$(OUTDIR)\MenuBtn.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MenuBtn_EXPORTS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\MenuBtn.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuBtn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x15000000" /dll /incremental:no /pdb:"$(OUTDIR)\MenuBtn.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\MenuBtn.dll" /implib:"$(OUTDIR)\MenuBtn.lib" 
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

"$(OUTDIR)\MenuBtn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\MenuBtn.dll
InputPath=.\Release\MenuBtn.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MenuBtn.dll" "$(OUTDIR)\MenuBtn.bsc" ".\Debug\regsvr32.trg"


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
	-@erase "$(OUTDIR)\MenuBtn.bsc"
	-@erase "$(OUTDIR)\MenuBtn.dll"
	-@erase "$(OUTDIR)\MenuBtn.exp"
	-@erase "$(OUTDIR)\MenuBtn.ilk"
	-@erase "$(OUTDIR)\MenuBtn.lib"
	-@erase "$(OUTDIR)\MenuBtn.pdb"
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuBtn.bsc" 
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

"$(OUTDIR)\MenuBtn.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x15000000" /dll /incremental:yes /pdb:"$(OUTDIR)\MenuBtn.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\MenuBtn.dll" /implib:"$(OUTDIR)\MenuBtn.lib" /pdbtype:sept 
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

"$(OUTDIR)\MenuBtn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\MenuBtn.dll
InputPath=.\Debug\MenuBtn.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\MenuBtn.dll" ".\Ansi_release\regsvr32.trg"


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
	-@erase "$(OUTDIR)\MenuBtn.dll"
	-@erase "$(OUTDIR)\MenuBtn.exp"
	-@erase "$(OUTDIR)\MenuBtn.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MenuBtn_EXPORTS" /Fp"$(INTDIR)\MenuBtn.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuBtn.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x15000000" /dll /incremental:no /pdb:"$(OUTDIR)\MenuBtn.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\MenuBtn.dll" /implib:"$(OUTDIR)\MenuBtn.lib" 
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

"$(OUTDIR)\MenuBtn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\MenuBtn.dll
InputPath=.\Ansi_release\MenuBtn.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\MenuBtn.dll" "$(OUTDIR)\MenuBtn.bsc" ".\Ansi_debug\regsvr32.trg"


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
	-@erase "$(OUTDIR)\MenuBtn.bsc"
	-@erase "$(OUTDIR)\MenuBtn.dll"
	-@erase "$(OUTDIR)\MenuBtn.exp"
	-@erase "$(OUTDIR)\MenuBtn.ilk"
	-@erase "$(OUTDIR)\MenuBtn.lib"
	-@erase "$(OUTDIR)\MenuBtn.pdb"
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MenuBtn.bsc" 
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

"$(OUTDIR)\MenuBtn.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x15000000" /dll /incremental:yes /pdb:"$(OUTDIR)\MenuBtn.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\MenuBtn.dll" /implib:"$(OUTDIR)\MenuBtn.lib" /pdbtype:sept 
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

"$(OUTDIR)\MenuBtn.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\MenuBtn.dll
InputPath=.\Ansi_debug\MenuBtn.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MenuBtn.dep")
!INCLUDE "MenuBtn.dep"
!ELSE 
!MESSAGE Warning: cannot find "MenuBtn.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MenuBtn - Win32 Release" || "$(CFG)" == "MenuBtn - Win32 Debug" || "$(CFG)" == "MenuBtn - Win32 Ansi Release" || "$(CFG)" == "MenuBtn - Win32 Ansi Debug"
SOURCE=.\About.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseSnap.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Comp.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompData.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DataObj.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeleBase.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Land.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\Land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\Land.obj"	"$(INTDIR)\Land.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\Land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\Land.obj"	"$(INTDIR)\Land.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MMCCrack.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\People.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\People.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\People.obj"	"$(INTDIR)\People.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\People.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\People.obj"	"$(INTDIR)\People.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Sky.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\Sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\Sky.obj"	"$(INTDIR)\Sky.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\Sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\Sky.obj"	"$(INTDIR)\Sky.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Space.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\Space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\Space.obj"	"$(INTDIR)\Space.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\Space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\Space.obj"	"$(INTDIR)\Space.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StatNode.cpp

!IF  "$(CFG)" == "MenuBtn - Win32 Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MenuBtn - Win32 Ansi Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Resource.rc

"$(INTDIR)\Resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

