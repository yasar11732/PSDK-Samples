#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=DmoEnum

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\dmoenum.obj \
	$(OUTDIR)\dmoenumdlg.obj  \
	$(OUTDIR)\buildinsd.obj  \
	$(OUTDIR)\dmoenum.res 

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	msdmo.lib \
	dmoguids.lib \
	strmiids.lib 

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I. /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
