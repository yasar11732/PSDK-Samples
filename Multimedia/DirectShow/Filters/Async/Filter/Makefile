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

all:	$(OUTDIR) $(OUTDIR)\asyncflt.ax 

$(OUTDIR)\asyncflt.ax:	$(OUTDIR)\asyncflt.obj $(OUTDIR)\asyncflt.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\asyncflt.ax $(dlllflags) /DLL /PDB:$(OUTDIR)\asyncflt.pdb /DEF:asyncflt.def /IMPLIB:"$(OUTDIR)\asyncflt.lib" /MACHINE:$(CPU) $(OUTDIR)\asyncflt.obj $(OUTDIR)\asyncflt.res $(STRMBASE) ..\base\$(OUTDIR)\asynbase.lib quartz.lib winmm.lib shell32.lib $(ole2libs) odbc32.lib odbccp32.lib $(MSVCRT) $(ATLS) /NODEFAULTLIB

$(OUTDIR)\asyncflt.obj:	asyncflt.cpp
	$(cc) $(cflags) $(cdebug) /Gz $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /DSTRICT /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\..\BaseClasses /I..\include /I"$(DXSDK_DIR)\Include" asyncflt.cpp

$(OUTDIR)\asyncflt.res:	
	 $(rc) $(rcflags) $(rcvars) /I..\..\..\BaseClasses /Fo$(OUTDIR)\asyncflt.res asyncflt.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
