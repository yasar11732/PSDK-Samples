# Microsoft Developer Studio Generated NMAKE File, Based on Help.dsp
!IF "$(CFG)" == ""
CFG=Help - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to Help - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "Help - Win32 Release" && "$(CFG)" != "Help - Win32 Debug" && "$(CFG)" != "Help - Win32 Ansi Debug" && "$(CFG)" != "Help - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Help.mak" CFG="Help - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Help - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Help - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "Help_EXPORTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x14000000" /dll /incremental:no /pdb:"$(OUTDIR)\Help.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\Help.dll
InputPath=.\Release\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" "$(OUTDIR)\Help.bsc" ".\Debug\regsvr32.trg"


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
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\MMCCrack.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\StatNode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Help.bsc"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.ilk"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase "$(OUTDIR)\Help.pdb"
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\Comp.sbr" \
	"$(INTDIR)\CompData.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\DeleBase.sbr" \
	"$(INTDIR)\MMCCrack.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\StatNode.sbr"

"$(OUTDIR)\Help.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x14000000" /dll /incremental:yes /pdb:"$(OUTDIR)\Help.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Help.dll
InputPath=.\Debug\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" "$(OUTDIR)\Help.bsc" ".\Ansi_debug\regsvr32.trg"


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
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\MMCCrack.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\StatNode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Help.bsc"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.ilk"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase "$(OUTDIR)\Help.pdb"
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\Comp.sbr" \
	"$(INTDIR)\CompData.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\DeleBase.sbr" \
	"$(INTDIR)\MMCCrack.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\StatNode.sbr"

"$(OUTDIR)\Help.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x14000000" /dll /incremental:yes /pdb:"$(OUTDIR)\Help.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\Help.dll
InputPath=.\Ansi_debug\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\CompData.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DeleBase.obj"
	-@erase "$(INTDIR)\MMCCrack.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StatNode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "Help_EXPORTS" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x14000000" /dll /incremental:no /pdb:"$(OUTDIR)\Help.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\CompData.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\DeleBase.obj" \
	"$(INTDIR)\MMCCrack.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StatNode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\Help.dll
InputPath=.\Ansi_release\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Help.dep")
!INCLUDE "Help.dep"
!ELSE 
!MESSAGE Warning: cannot find "Help.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Help - Win32 Release" || "$(CFG)" == "Help - Win32 Debug" || "$(CFG)" == "Help - Win32 Ansi Debug" || "$(CFG)" == "Help - Win32 Ansi Release"
SOURCE=.\About.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseSnap.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Comp.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CompData.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\CompData.obj"	"$(INTDIR)\CompData.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\CompData.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DataObj.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeleBase.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\DeleBase.obj"	"$(INTDIR)\DeleBase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\DeleBase.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MMCCrack.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\MMCCrack.obj"	"$(INTDIR)\MMCCrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\MMCCrack.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StatNode.cpp

!IF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\StatNode.obj"	"$(INTDIR)\StatNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\StatNode.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Resource.rc

"$(INTDIR)\Resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

