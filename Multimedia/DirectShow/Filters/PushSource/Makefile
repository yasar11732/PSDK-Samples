#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
STRMBASE = strmbase.lib
ATLS = atls.lib
MSVCRT = msvcrt.lib
!else
STRMBASE = strmbasd.lib
ATLS = atlsd.lib
MSVCRT = msvcrtd.lib
!endif


!if "$(CPU)"=="AMD64"
ATLS = 
!endif


STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\pushsource.ax 

$(OUTDIR)\pushsource.ax:	$(OUTDIR)\dibhelper.obj $(OUTDIR)\pushsourcebitmap.obj $(OUTDIR)\pushsourcebitmapset.obj $(OUTDIR)\PushSourceDesktop.obj $(OUTDIR)\setup.obj $(OUTDIR)\pushsource.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\pushsource.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\pushsource.pdb /DEF:.\pushsource.def /IMPLIB:"$(OUTDIR)\pushsource.lib" /MACHINE:$(CPU) $(OUTDIR)\dibhelper.obj $(OUTDIR)\pushsourcebitmap.obj $(OUTDIR)\pushsourcebitmapset.obj $(OUTDIR)\PushSourceDesktop.obj $(OUTDIR)\setup.obj $(OUTDIR)\pushsource.res $(STRMBASE) quartz.lib winmm.lib $(MSVCRT) $(baselibs) user32.lib gdi32.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib $(ATLS) /NODEFAULTLIB

$(OUTDIR)\dibhelper.obj:	dibhelper.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" dibhelper.cpp

$(OUTDIR)\pushsourcebitmap.obj:	pushsourcebitmap.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" pushsourcebitmap.cpp

$(OUTDIR)\pushsourcebitmapset.obj:	pushsourcebitmapset.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" pushsourcebitmapset.cpp

$(OUTDIR)\PushSourceDesktop.obj:	PushSourceDesktop.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" PushSourceDesktop.cpp

$(OUTDIR)\setup.obj:	setup.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" setup.cpp

$(OUTDIR)\pushsource.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\pushsource.res pushsource.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
