#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=PlayDMO

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\PlayDMO.obj \
	$(OUTDIR)\PlayDMODlg.obj \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\mfcdmoutil.obj \
	$(OUTDIR)\mfcutil.obj \
	$(OUTDIR)\dshowutil.obj \
	$(OUTDIR)\namedguid.obj \
	$(OUTDIR)\PlayDMO.res 

LINK32_LIBS = \
	$(ole2libs) \
	msdmo.lib \
	shell32.lib \
	strmiids.lib \
	dmoguids.lib

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /LIBPATH:$(DSROOT)\common\ /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)

{$(COMMONDIR)}.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" /I. $**

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**


.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
