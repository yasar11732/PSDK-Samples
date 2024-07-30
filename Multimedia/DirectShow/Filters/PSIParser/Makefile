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

all:	$(OUTDIR) $(OUTDIR)\psiparser.ax 

$(OUTDIR)\psiparser.ax:	$(OUTDIR)\psiparser.obj $(OUTDIR)\progprop.obj $(OUTDIR)\psiparser.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\psiparser.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\psiparser.pdb /DEF:.\psiparser.def /IMPLIB:"$(OUTDIR)\psiparser.lib" /MACHINE:$(CPU) $(OUTDIR)\psiparser.obj $(OUTDIR)\progprop.obj $(OUTDIR)\psiparser.res $(STRMBASE) quartz.lib winmm.lib $(MSVCRT) $(baselibs) user32.lib gdi32.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib $(ATLS) /NODEFAULTLIB

$(OUTDIR)\PsiParser.obj:	PsiParser.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" PsiParser.cpp

$(OUTDIR)\progprop.obj:	progprop.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" progprop.cpp

$(OUTDIR)\PsiParser.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\PsiParser.res PsiParser.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
