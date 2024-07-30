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
LIBC=libcmt
MSVCRT=msvcrt.lib
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
LIBC=libcmtd
MSVCRT=msvcrtd.lib
!endif

!if "$(CPU)"=="AMD64"
DXLIB="$(DXSDK_DIR)\Lib\x64"
!else
DXLIB="$(DXSDK_DIR)\Lib\x32"
!endif


STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"


all:    $(OUTDIR) $(OUTDIR)\ticker.exe 

$(OUTDIR)\ticker.exe:   $(OUTDIR)\ticker.obj $(OUTDIR)\bitmap.obj $(OUTDIR)\ticker.res 
    $(link) $(ldebug) /OUT:$(OUTDIR)\ticker.exe $(guilflags) /PDB:$(OUTDIR)\ticker.pdb /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(OUTDIR)\ticker.obj $(OUTDIR)\bitmap.obj  $(OUTDIR)\ticker.res shell32.lib $(ole2libs) strmiids.lib quartz.lib comctl32.lib winmm.lib dxguid.lib ddraw.lib $(STRMBASE) $(MSVCRT) /NODEFAULTLIB:$(LIBC)

$(OUTDIR)\ticker.obj:    ticker.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses /I..\inc  /I"$(DXSDK_DIR)\Include" ticker.CPP

$(OUTDIR)\bitmap.obj:  bitmap.CPP
    $(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I..\..\BaseClasses  /I"$(DXSDK_DIR)\Include" bitmap.CPP

$(OUTDIR)\ticker.res:   
     $(rc) $(rcflags) /Fo$(OUTDIR)\ticker.res ticker.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)

!else
!MESSAGE This sample builds only for Windows XP (or greater) platforms.
!endif
!endif
