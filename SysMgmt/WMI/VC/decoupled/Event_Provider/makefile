!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!ifndef NODEBUG
CPP_PROJ=	/nologo \
			/ML /W3 /Od \
			/D "WIN32" /D "DDEBUG" /D "_WINDOWS" /D "UNICODE" \
			/Fp"$(INTDIR)\SdkSample.pch" /EHsc \
			/Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c \
			/I . /I include

OUTDIR=.\Debug
INTDIR=.\Debug
!else
CPP_PROJ=	/nologo \
			/ML /W3 /O2 \
			/D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" \
			/Fp"$(INTDIR)\SdkSample.pch" /EHsc \
			/Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c \
			/I . /I include
OUTDIR=.\Release
INTDIR=.\Release

!endif #NODEBUG


ALL : "$(OUTDIR)\SdkSample.exe"

CLEAN :
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SdkSample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe


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
	
LINK=link.exe

LINK_FLAGS=	wbemuuid.lib \
			kernel32.lib \
			user32.lib \
			gdi32.lib \
			winspool.lib \
			comdlg32.lib \
			advapi32.lib \
			shell32.lib \
			ole32.lib \
			oleaut32.lib \
			uuid.lib \
			bufferoverflowu.lib \
			$(LIBPATHS) \
			/nologo \
			/subsystem:windows \
			/incremental:no \
			/pdb:"$(OUTDIR)\SdkSample.pdb" \
			/out:"$(OUTDIR)\SdkSample.exe" 

LINK_OBJS= \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Main.obj"

"$(OUTDIR)\SdkSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK_OBJS)
    $(LINK) @<<
  $(LINK_FLAGS) $(LINK_OBJS)
<<


SOURCE=.\Globals.cpp
"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"

SOURCE=.\Main.cpp
"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
