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

all:	$(OUTDIR) $(OUTDIR)\scope.ax 

$(OUTDIR)\scope.ax:	$(OUTDIR)\scope.obj $(OUTDIR)\scope.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\scope.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\scope.pdb /DEF:.\scope.def /IMPLIB:"$(OUTDIR)\scope.lib" $(guilflags) /MACHINE:$(CPU) $(OUTDIR)\scope.obj $(OUTDIR)\scope.res $(STRMBASE) quartz.lib vfw32.lib winmm.lib $(baselibs) version.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib $(MSVCRT) $(ATLS) /NODEFAULTLIB

$(OUTDIR)\scope.obj:	scope.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" scope.cpp

$(OUTDIR)\scope.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\scope.res scope.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
