# Microsoft Developer Studio Generated NMAKE File, Based on MultiSel.dsp
!IF "$(CFG)" == ""
CFG=MultiSel - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to MultiSel - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "MultiSel - Win32 Debug" && "$(CFG)" != "MultiSel - Win32 Ansi Debug" && "$(CFG)" != "MultiSel - Win32 Release" && "$(CFG)" != "MultiSel - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiSel.mak" CFG="MultiSel - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiSel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiSel - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiSel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiSel - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MultiSel - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MultiSel.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddFolderDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\MultiSel.res"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\MultiSel.dll"
	-@erase "$(OUTDIR)\MultiSel.exp"
	-@erase "$(OUTDIR)\MultiSel.ilk"
	-@erase "$(OUTDIR)\MultiSel.lib"
	-@erase "$(OUTDIR)\MultiSel.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTISEL_EXPORTS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\MultiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MultiSel.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MultiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\MultiSel.pdb" /debug /machine:$(CPU) /def:".\MultiSel.Def" /out:"$(OUTDIR)\MultiSel.dll" /implib:"$(OUTDIR)\MultiSel.lib" /pdbtype:sept 
DEF_FILE= \
	".\MultiSel.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddFolderDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\MultiSel.res"

"$(OUTDIR)\MultiSel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\MultiSel.dll
InputPath=.\Debug\MultiSel.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MultiSel - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\MultiSel.dll" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddFolderDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\MultiSel.res"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\MultiSel.dll"
	-@erase "$(OUTDIR)\MultiSel.exp"
	-@erase "$(OUTDIR)\MultiSel.ilk"
	-@erase "$(OUTDIR)\MultiSel.lib"
	-@erase "$(OUTDIR)\MultiSel.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTISEL_EXPORTS" /Fp"$(INTDIR)\MultiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MultiSel.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MultiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\MultiSel.pdb" /debug /machine:$(CPU) /def:".\MultiSel.Def" /out:"$(OUTDIR)\MultiSel.dll" /implib:"$(OUTDIR)\MultiSel.lib" /pdbtype:sept 
DEF_FILE= \
	".\MultiSel.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddFolderDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\MultiSel.res"

"$(OUTDIR)\MultiSel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\MultiSel.dll
InputPath=.\Ansi_debug\MultiSel.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MultiSel - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MultiSel.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddFolderDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\MultiSel.res"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\MultiSel.dll"
	-@erase "$(OUTDIR)\MultiSel.exp"
	-@erase "$(OUTDIR)\MultiSel.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTISEL_EXPORTS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\MultiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MultiSel.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MultiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MultiSel.pdb" /machine:$(CPU) /def:".\MultiSel.Def" /out:"$(OUTDIR)\MultiSel.dll" /implib:"$(OUTDIR)\MultiSel.lib" 
DEF_FILE= \
	".\MultiSel.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddFolderDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\MultiSel.res"

"$(OUTDIR)\MultiSel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\MultiSel.dll
InputPath=.\Release\MultiSel.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MultiSel - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\MultiSel.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddFolderDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\MultiSel.res"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\MultiSel.dll"
	-@erase "$(OUTDIR)\MultiSel.exp"
	-@erase "$(OUTDIR)\MultiSel.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTISEL_EXPORTS" /Fp"$(INTDIR)\MultiSel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MultiSel.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MultiSel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MultiSel.pdb" /machine:$(CPU) /def:".\MultiSel.Def" /out:"$(OUTDIR)\MultiSel.dll" /implib:"$(OUTDIR)\MultiSel.lib" 
DEF_FILE= \
	".\MultiSel.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddFolderDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\MultiSel.res"

"$(OUTDIR)\MultiSel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\MultiSel.dll
InputPath=.\Ansi_release\MultiSel.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MultiSel.dep")
!INCLUDE "MultiSel.dep"
!ELSE 
!MESSAGE Warning: cannot find "MultiSel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MultiSel - Win32 Debug" || "$(CFG)" == "MultiSel - Win32 Ansi Debug" || "$(CFG)" == "MultiSel - Win32 Release" || "$(CFG)" == "MultiSel - Win32 Ansi Release"
SOURCE=.\About.Cpp

"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AddDeviceDlg.cpp

"$(INTDIR)\AddDeviceDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AddFolderDlg.cpp

"$(INTDIR)\AddFolderDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AddVFileDlg.cpp

"$(INTDIR)\AddVFileDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BaseDialog.cpp

"$(INTDIR)\BaseDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BaseSnap.Cpp

"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Comp.cpp

"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Compdata.cpp

"$(INTDIR)\Compdata.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Dataobj.cpp

"$(INTDIR)\Dataobj.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DeviceNode.cpp

"$(INTDIR)\DeviceNode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FolderNode.cpp

"$(INTDIR)\FolderNode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LListImpl.cpp

"$(INTDIR)\LListImpl.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MultiSel.rc

"$(INTDIR)\MultiSel.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Registry.cpp

"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StaticNode.cpp

"$(INTDIR)\StaticNode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TraceMacro.cpp

"$(INTDIR)\TraceMacro.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VirtualFile.cpp

"$(INTDIR)\VirtualFile.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

