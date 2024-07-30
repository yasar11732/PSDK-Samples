#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=MultiPlayer9

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\MultiPlayer.obj \
	$(OUTDIR)\MultiPlayerDlg.obj \
	$(OUTDIR)\MultiGraphSession.obj \
	$(OUTDIR)\VMR9Subgraph.obj \
	$(OUTDIR)\stdafx.obj \
	$(OUTDIR)\DefaultMultiPlayer.res

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	comctl32.lib \
	quartz.lib \
	Winmm.lib \
	d3dx9.lib \
	strmiids.lib 

!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
!endif


!if "$(CPU)"=="AMD64"
DXLIB="$(DXSDK_DIR)\Lib\x64"
!else
DXLIB="$(DXSDK_DIR)\Lib\x86"
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(LINK32_OBJS) $(STRMBASE) $(LINK32_LIBS)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\..\Inc /I..\..\..\BaseClasses /I"$(DXSDK_DIR)\Include"  /I..\DLL\$(OUTDIR) /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
