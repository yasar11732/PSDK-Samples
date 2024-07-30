# Microsoft Developer Studio Generated NMAKE File, Based on prsample.dsp
!IF "$(CFG)" == ""
CFG=prsample - Win32 x86_debu
!MESSAGE No configuration specified. Defaulting to prsample - Win32 x86_debu.
!ENDIF 

!IF "$(CFG)" != "prsample - Win32 x86_debu" && "$(CFG)" != "prsample - Win32 x86_rele" && "$(CFG)" != "prsample - Win32 axp_debu" && "$(CFG)" != "prsample - Win32 axp_rele"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "prsample.mak" CFG="prsample - Win32 x86_debu"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "prsample - Win32 x86_debu" (based on "Win32 (x86) Console Application")
!MESSAGE "prsample - Win32 x86_rele" (based on "Win32 (x86) Console Application")
!MESSAGE "prsample - Win32 axp_debu" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "prsample - Win32 axp_rele" (based on "Win32 (ALPHA) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

OUTDIR=.\x86_debu
INTDIR=.\x86_debu
# Begin Custom Macros
OutDir=.\x86_debu
# End Custom Macros

ALL : "$(OUTDIR)\prsample.exe" "$(OUTDIR)\prsample.bsc"


CLEAN :
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\command.sbr"
	-@erase "$(INTDIR)\datasource.obj"
	-@erase "$(INTDIR)\datasource.sbr"
	-@erase "$(INTDIR)\enum.obj"
	-@erase "$(INTDIR)\enum.sbr"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\error.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\prsample.idb"
	-@erase "$(INTDIR)\PRSample.res"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\rowset.sbr"
	-@erase "$(INTDIR)\session.obj"
	-@erase "$(INTDIR)\session.sbr"
	-@erase "$(OUTDIR)\prsample.bsc"
	-@erase "$(OUTDIR)\prsample.exe"
	-@erase "$(OUTDIR)\prsample.ilk"
	-@erase "$(OUTDIR)\prsample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\prsample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PRSample.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\prsample.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\command.sbr" \
	"$(INTDIR)\datasource.sbr" \
	"$(INTDIR)\enum.sbr" \
	"$(INTDIR)\error.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\rowset.sbr" \
	"$(INTDIR)\session.sbr"

"$(OUTDIR)\prsample.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\prsample.pdb" /debug /machine:I386 /out:"$(OUTDIR)\prsample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\datasource.obj" \
	"$(INTDIR)\enum.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\session.obj" \
	"$(INTDIR)\PRSample.res"

"$(OUTDIR)\prsample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

OUTDIR=.\x86_rele
INTDIR=.\x86_rele
# Begin Custom Macros
OutDir=.\x86_rele
# End Custom Macros

ALL : "$(OUTDIR)\prsample.exe"


CLEAN :
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\datasource.obj"
	-@erase "$(INTDIR)\enum.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\PRSample.res"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\session.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\prsample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\prsample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PRSample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\prsample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\prsample.pdb" /machine:I386 /out:"$(OUTDIR)\prsample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\datasource.obj" \
	"$(INTDIR)\enum.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\session.obj" \
	"$(INTDIR)\PRSample.res"

"$(OUTDIR)\prsample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

OUTDIR=.\axp_debu
INTDIR=.\axp_debu
# Begin Custom Macros
OutDir=.\axp_debu
# End Custom Macros

ALL : "$(OUTDIR)\prsample.exe"


CLEAN :
	-@erase "$(INTDIR)\PRSample.res"
	-@erase "$(OUTDIR)\prsample.exe"
	-@erase "$(OUTDIR)\prsample.ilk"
	-@erase "$(OUTDIR)\prsample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PRSample.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\prsample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\prsample.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)\prsample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PRSample.res"

"$(OUTDIR)\prsample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

OUTDIR=.\axp_rele
INTDIR=.\axp_rele
# Begin Custom Macros
OutDir=.\axp_rele
# End Custom Macros

ALL : "$(OUTDIR)\prsample.exe"


CLEAN :
	-@erase "$(INTDIR)\PRSample.res"
	-@erase "$(OUTDIR)\prsample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PRSample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\prsample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\prsample.pdb" /machine:ALPHA /out:"$(OUTDIR)\prsample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PRSample.res"

"$(OUTDIR)\prsample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("prsample.dep")
!INCLUDE "prsample.dep"
!ELSE 
!MESSAGE Warning: cannot find "prsample.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "prsample - Win32 x86_debu" || "$(CFG)" == "prsample - Win32 x86_rele" || "$(CFG)" == "prsample - Win32 axp_debu" || "$(CFG)" == "prsample - Win32 axp_rele"
SOURCE=.\command.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"


"$(INTDIR)\command.obj"	"$(INTDIR)\command.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"


"$(INTDIR)\command.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\datasource.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\datasource.obj"	"$(INTDIR)\datasource.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\datasource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\enum.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\enum.obj"	"$(INTDIR)\enum.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\enum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\error.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\error.obj"	"$(INTDIR)\error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\rowset.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\rowset.obj"	"$(INTDIR)\rowset.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\rowset.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\session.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\prsample.pdb" /FD /c 

"$(INTDIR)\session.obj"	"$(INTDIR)\session.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\session.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

SOURCE=.\PRSample.rc

"$(INTDIR)\PRSample.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

