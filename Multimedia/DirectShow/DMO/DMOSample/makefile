#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=DMOSample

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\sample.obj \
	$(OUTDIR)\dmosample.obj  \
	$(OUTDIR)\state.obj \
	$(OUTDIR)\util.obj \
	$(OUTDIR)\dmosample.res 

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	msdmo.lib \
	dmoguids.lib \
	strmiids.lib 

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).dll /DLL /PDB:$(OUTDIR)\$(PROJECT).pdb /DEF:$(PROJECT).def /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)


.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_USRDLL /D_MBCS /D"DMOSAMPLE_EXPORTS" /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
