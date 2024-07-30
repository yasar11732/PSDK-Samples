#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
STRMBASE = strmbase.lib
ATLS = atls.lib
!else
STRMBASE = strmbasd.lib
ATLS = atlsd.lib
cflags=$(cflags) /DDEBUG
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\amcap.exe 

$(OUTDIR)\amcap.exe:	 $(OUTDIR) $(OUTDIR)\amcap.obj $(OUTDIR)\crossbar.obj $(OUTDIR)\samplecgb.obj $(OUTDIR)\status.obj $(OUTDIR)\amcap.res 
		$(link) $(ldebug) /OUT:$(OUTDIR)\amcap.exe $(guilflags) /PDB:$(OUTDIR)\none /MACHINE:$(CPU) $(OUTDIR)\amcap.obj $(OUTDIR)\crossbar.obj $(OUTDIR)\samplecgb.obj $(OUTDIR)\status.obj $(OUTDIR)\amcap.res quartz.lib $(baselibs) user32.lib gdi32.lib comdlg32.lib ole32.lib winmm.lib msacm32.lib oleaut32.lib uuid.lib strmiids.lib $(STRMBASE) 

$(OUTDIR)\amcap.obj:	amcap.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fp$(OUTDIR)\amcap.pch /Yc"streams.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" amcap.cpp

$(OUTDIR)\crossbar.obj:	crossbar.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fp$(OUTDIR)\amcap.pch /Yu"streams.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I..\..\BaseClasses crossbar.cpp

$(OUTDIR)\samplecgb.obj:	samplecgb.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fp$(OUTDIR)\amcap.pch /Yu"streams.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I..\..\BaseClasses samplecgb.cpp

$(OUTDIR)\status.obj:	status.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fp$(OUTDIR)\amcap.pch /Yu"streams.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I..\..\BaseClasses status.cpp

$(OUTDIR)\amcap.res:	
	$(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\\amcap.res amcap.rc
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
