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


all:	$(OUTDIR) $(OUTDIR)\dump.ax 



$(OUTDIR)\dump.ax:	$(OUTDIR)\dump.obj $(OUTDIR)\dump.res
	$(link) $(ldebug) /OUT:$(OUTDIR)\dump.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\dump.pdb /DEF:.\dump.def /IMPLIB:"$(OUTDIR)/dump.lib" /MACHINE:$(CPU) $(OUTDIR)\dump.obj $(OUTDIR)\dump.res $(STRMBASE) quartz.lib winmm.lib $(baselibs) user32.lib gdi32.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib $(MSVCRT) $(ATLS) /NODEFAULTLIB

$(OUTDIR)\dump.obj:	dump.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" dump.cpp

$(OUTDIR)\dump.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\dump.res dump.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
