#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=Cutscene

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\cutscene.obj \
	$(OUTDIR)\main.obj 

LINK32_LIBS = \
	ole32.lib \
	uuid.lib \
	kernel32.lib \
	strmiids.lib \
	shell32.lib \
	bufferoverflowu.lib \


all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
