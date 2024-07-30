#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifndef NODEBUG
cflags=$(cflags) /DDEBUG
!endif

all:	$(OUTDIR) $(OUTDIR)\dvdsample.exe 

DXDIR="%DXSDK_DIR%\Include"

$(OUTDIR)\dvdsample.exe:	 $(OUTDIR) $(OUTDIR)\Dialogs.obj $(OUTDIR)\DvdCore.obj $(OUTDIR)\DVDSample.obj $(OUTDIR)\StringUtil.obj $(OUTDIR)\DVDSample.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\dvdsample.exe $(guilflags) /PDB:$(OUTDIR)\dvdsample.pdb /MACHINE:$(CPU) $(OUTDIR)\Dialogs.obj $(OUTDIR)\DvdCore.obj $(OUTDIR)\DVDSample.obj $(OUTDIR)\StringUtil.obj $(OUTDIR)\DVDSample.res shell32.lib $(ole2libs) comctl32.lib quartz.lib strmiids.lib winmm.lib 

$(OUTDIR)\DVDSample.obj:	DVDSample.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" DVDSample.cpp

$(OUTDIR)\Dialogs.obj:	Dialogs.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" Dialogs.cpp

$(OUTDIR)\DvdCore.obj:	DvdCore.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_MBCS" /U"_STRSAFE_H_INCLUDED_" /I..\..\BaseClasses /I$(DXDIR) DvdCore.cpp

$(OUTDIR)\StringUtil.obj:	StringUtil.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" StringUtil.cpp

$(OUTDIR)\DVDSample.res:	
	$(rc) $(rcflags) $(rcvars) /I..\..\BaseClasses /Fo$(OUTDIR)\dvdsample.res dvdsample.rc  

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
