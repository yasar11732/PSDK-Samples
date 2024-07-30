!include <disable.mak>

#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

# -------------------------------------------------------------------
# --- This sample builds ONLY for Windows XP
# -------------------------------------------------------------------
!if "$(TARGETOS)" == "WINNT"
!if "$(APPVER)" == "5.01" || "$(APPVER)" == "5.02"

!ifdef NODEBUG
STRMBASE = strmbase.lib
LIBC = libcmt
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
LIBC = libcmtd
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"


all:	$(OUTDIR) $(OUTDIR)\cube.exe 

$(OUTDIR)\cube.exe:	$(OUTDIR)\app.obj $(OUTDIR)\commands.obj $(OUTDIR)\compositor.obj $(OUTDIR)\vcdplyer.obj $(OUTDIR)\cube.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\cube.exe $(guilflags) /PDB:$(OUTDIR)\cube.pdb /MACHINE:$(CPU) $(OUTDIR)\app.obj $(OUTDIR)\commands.obj $(OUTDIR)\compositor.obj $(OUTDIR)\vcdplyer.obj $(OUTDIR)\cube.res shell32.lib $(ole2libs) strmiids.lib quartz.lib comctl32.lib winmm.lib msvcrtd.lib $(STRMBASE) /NODEFAULTLIB:$(LIBC)

$(OUTDIR)\app.obj:	app.CPP
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I..\inc  /I"$(DXSDK_DIR)\Include" app.CPP

$(OUTDIR)\compositor.obj: compositor.CPP
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses  /I"$(DXSDK_DIR)\Include" compositor.CPP

$(OUTDIR)\commands.obj:	commands.CPP
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses  /I"$(DXSDK_DIR)\Include" commands.CPP

$(OUTDIR)\vcdplyer.obj:	vcdplyer.CPP
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses  /I"$(DXSDK_DIR)\Include" vcdplyer.CPP

$(OUTDIR)\cube.res:	
	 $(rc) $(rcflags) /Fo$(OUTDIR)\cube.res cube.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)

!else
!MESSAGE This sample builds only for Windows XP (or greater) platforms.
!endif
!endif
