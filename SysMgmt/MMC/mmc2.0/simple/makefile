#--------------------------------------------------------------
# Do i386 in conventional way
#
!if "$(CPU)" == "i386"
samplename=Simple
!include <..\mmcprerelease.mak>
!else

#--------------------------------------------------------------
# Do 64 bit in following way
#
#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\Simple.Dll

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

#------ Compile options ---------
CPP=cl.exe
CPP_PROJ=$(cflags) $(cdebug) /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SIMPLE_EXPORTS" /D "_UNICODE" /D "UNICODE" /FR"$(OUTDIR)\\" /Fp"$(OUTDIR)\Simple.pch" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /c 

.cpp{$(OUTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

#------ Resource compile options ---------

SOURCE=.\Resource.rc
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(OUTDIR)\Resource.res"

"$(OUTDIR)\Resource.res" : $(SOURCE) "$(OUTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)

#------ Link options ---------
LINK32=link.exe
LINK32_FLAGS=mmc.lib shlwapi.lib shell32.lib odbc32.lib odbccp32.lib /MACHINE:$(CPU) /nologo /dll /incremental:yes /def:".\BaseSnap.Def" /out:"$(OUTDIR)\Simple.dll" /implib:"$(OUTDIR)\Simple.lib"

DEF_FILE= \
	".\BaseSnap.Def"

LINK32_OBJS= \
	"$(OUTDIR)\BaseSnap.obj" \
	"$(OUTDIR)\Comp.obj" \
	"$(OUTDIR)\Compdata.obj" \
	"$(OUTDIR)\Dataobj.obj" \
	"$(OUTDIR)\Globals.obj" \
	"$(OUTDIR)\Registry.obj" \
	"$(OUTDIR)\StaticNode.obj" \
	"$(OUTDIR)\TraceMacro.obj" \
	"$(OUTDIR)\Resource.res"

# Build rule for DLL
$(OUTDIR)\Simple.dll: "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
		$(link) $(olelibs) $(LINK32_FLAGS) $(LINK32_OBJS)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)

!endif
