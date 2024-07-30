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
cflags=$(cflags) /DDEBUG
!endif

!if "$(CPU)"=="AMD64"
ATLS = 
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\synth.ax 

$(OUTDIR)\synth.ax:	$(OUTDIR)\dynsrc.obj $(OUTDIR)\synth.obj $(OUTDIR)\synthprp.obj $(OUTDIR)\synth.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\synth.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\synth.pdb /DEF:.\synth.def /IMPLIB:"$(OUTDIR)\synth.lib" $(guilflags) /MACHINE:$(CPU) $(OUTDIR)\dynsrc.obj $(OUTDIR)\synth.obj $(OUTDIR)\synthprp.obj $(OUTDIR)\synth.res $(STRMBASE) msacm32.lib $(MSVCRT) quartz.lib vfw32.lib winmm.lib $(baselibs) version.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib $(ATLS) /NODEFAULTLIB

$(OUTDIR)\dynsrc.obj:	dynsrc.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" dynsrc.cpp

$(OUTDIR)\synth.obj:	synth.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" synth.cpp

$(OUTDIR)\synthprp.obj:	synthprp.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" synthprp.cpp

$(OUTDIR)\synth.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\synth.res synth.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
