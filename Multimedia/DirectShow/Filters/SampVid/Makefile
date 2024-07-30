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

all:	$(OUTDIR) $(OUTDIR)\sampvid.ax 

$(OUTDIR)\sampvid.ax:	$(OUTDIR)\sampvid.obj $(OUTDIR)\videotxt.obj $(OUTDIR)\vidprop.obj $(OUTDIR)\sampvid.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\sampvid.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\sampvid.pdb /DEF:.\sampvid.def /IMPLIB:"$(OUTDIR)\sampvid.lib" /MACHINE:$(CPU) $(OUTDIR)\sampvid.obj $(OUTDIR)\videotxt.obj $(OUTDIR)\vidprop.obj $(OUTDIR)\sampvid.res $(STRMBASE) quartz.lib winmm.lib $(MSVCRT) $(baselibs) user32.lib gdi32.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib $(ATLS) /NODEFAULTLIB

$(OUTDIR)\sampvid.obj:	sampvid.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" sampvid.cpp

$(OUTDIR)\videotxt.obj:	videotxt.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" videotxt.cpp

$(OUTDIR)\vidprop.obj:	vidprop.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" vidprop.cpp

$(OUTDIR)\sampvid.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\sampvid.res sampvid.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
