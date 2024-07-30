#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
STRMBASE = strmbase.lib
MSVCRT = msvcrt.lib
ATLS = atls.lib
!else
STRMBASE = strmbasd.lib
MSVCRT = msvcrtd.lib
ATLS = atlsd.lib
cflags=$(cflags) /DDEBUG
!endif

!if "$(CPU)"=="AMD64"
ATLS = 
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\inftee.ax 

$(OUTDIR)\inftee.ax:	$(OUTDIR)\inftee.obj $(OUTDIR)\inftee.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\inftee.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\inftee.pdb /DEF:.\inftee.def /IMPLIB:"$(OUTDIR)\inftee.lib" $(guilflags) /MACHINE:$(CPU) $(OUTDIR)\inftee.obj $(OUTDIR)\inftee.res $(STRMBASE) quartz.lib vfw32.lib winmm.lib $(baselibs) version.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib $(MSVCRT) $(ATLS) /NODEFAULTLIB

$(OUTDIR)\inftee.obj:	inftee.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Oid /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" inftee.cpp

$(OUTDIR)\inftee.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\inftee.res inftee.rc
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
