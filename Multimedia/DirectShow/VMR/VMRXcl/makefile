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
MSVCRT = msvcrt.lib
LIBC=libcmt
!else
STRMBASE = strmbasd.lib
MSVCRT = msvcrtd.lib
cflags=$(cflags) /DDEBUG
LIBC=libcmtd
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"


all:    $(OUTDIR) $(OUTDIR)\vmrxcl.exe 

$(OUTDIR)\vmrxcl.exe:   $(OUTDIR)\allocpresenter.obj $(OUTDIR)\app.obj $(OUTDIR)\commands.obj $(OUTDIR)\d3dfont.obj $(OUTDIR)\d3dtextr.obj $(OUTDIR)\d3dutil.obj $(OUTDIR)\ddrawsupport.obj $(OUTDIR)\utils.obj $(OUTDIR)\vcdplyer.obj   $(OUTDIR)\vmrxcl.res 
    $(link) $(ldebug) /OUT:$(OUTDIR)\vmrxcl.exe $(guilflags) /PDB:$(OUTDIR)\vmrxcl.pdb /MACHINE:$(CPU) $(OUTDIR)\allocpresenter.obj $(OUTDIR)\app.obj $(OUTDIR)\commands.obj $(OUTDIR)\d3dfont.obj $(OUTDIR)\d3dtextr.obj $(OUTDIR)\d3dutil.obj $(OUTDIR)\ddrawsupport.obj $(OUTDIR)\utils.obj $(OUTDIR)\vcdplyer.obj  $(OUTDIR)\vmrxcl.res shell32.lib $(ole2libs) strmiids.lib quartz.lib comctl32.lib winmm.lib dxguid.lib ddraw.lib d3dx.lib $(STRMBASE) $(MSVCRT) /NODEFAULTLIB:$(LIBC)

$(OUTDIR)\allocpresenter.obj:    allocpresenter.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" allocpresenter.CPP

$(OUTDIR)\app.obj:  app.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" app.CPP

$(OUTDIR)\commands.obj:   commands.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" commands.CPP

$(OUTDIR)\d3dfont.obj:   d3dfont.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" d3dfont.CPP

$(OUTDIR)\d3dtextr.obj:    d3dtextr.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" d3dtextr.CPP

$(OUTDIR)\d3dutil.obj:  d3dutil.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" d3dutil.CPP

$(OUTDIR)\ddrawsupport.obj:   ddrawsupport.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" ddrawsupport.CPP

$(OUTDIR)\utils.obj:    utils.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I..\inc /I"$(DXSDK_DIR)\Include" utils.CPP

$(OUTDIR)\vcdplyer.obj:    vcdplyer.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc- /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" vcdplyer.CPP

$(OUTDIR)\vmrxcl.res:   
     $(rc) $(rcflags) /Fo$(OUTDIR)\vmrxcl.res vmrxcl.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)

!else
!MESSAGE This sample builds only for Windows XP (or greater) platforms.
!endif
!endif
