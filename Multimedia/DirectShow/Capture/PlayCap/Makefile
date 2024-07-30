!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"


#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>



all:	$(OUTDIR) $(OUTDIR)\PlayCap.exe 

$(OUTDIR)\PlayCap.exe:	 $(OUTDIR) $(OUTDIR)\playcap.obj $(OUTDIR)\playcap.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\PlayCap.exe $(guilflags) /PDB:$(OUTDIR)\PlayCap.pdb /MACHINE:$(CPU) $(OUTDIR)\playcap.obj $(OUTDIR)\playcap.res $(STRMBASE) quartz.lib shell32.lib $(ole2libs) odbc32.lib odbccp32.lib 

$(OUTDIR)\playcap.obj:	playcap.cpp
	$(cc) $(cflags) $(cdebug) $(cvars) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" playcap.cpp

$(OUTDIR)\playcap.res:	
	$(rc) $(rcflags) /Fo$(OUTDIR)\\PlayCap.res PlayCap.rc 

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
