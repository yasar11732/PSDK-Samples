# Microsoft Developer Studio Generated NMAKE File, Based on httpauth.dsp
!IF "$(CFG)" == ""
CFG=httpauth - Win32 Debug
!MESSAGE No configuration specified. Defaulting to httpauth - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "httpauth - Win32 Release" && "$(CFG)" != "httpauth - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "httpauth.mak" CFG="httpauth - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "httpauth - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "httpauth - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "httpauth - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\httpauth.exe"


CLEAN :
	-@erase "$(INTDIR)\httpauth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\httpauth.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\httpauth.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpauth.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\httpauth.pdb" /machine:$(CPU) /out:"$(OUTDIR)\httpauth.exe" 
LINK32_OBJS= \
	"$(INTDIR)\httpauth.obj"

"$(OUTDIR)\httpauth.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "httpauth - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\httpauth.exe"


CLEAN :
	-@erase "$(INTDIR)\httpauth.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\httpauth.exe"
	-@erase "$(OUTDIR)\httpauth.ilk"
	-@erase "$(OUTDIR)\httpauth.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\httpauth.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpauth.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\httpauth.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\httpauth.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\httpauth.obj"

"$(OUTDIR)\httpauth.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("httpauth.dep")
!INCLUDE "httpauth.dep"
!ELSE 
!MESSAGE Warning: cannot find "httpauth.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "httpauth - Win32 Release" || "$(CFG)" == "httpauth - Win32 Debug"
SOURCE=.\httpauth.cpp

"$(INTDIR)\httpauth.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

