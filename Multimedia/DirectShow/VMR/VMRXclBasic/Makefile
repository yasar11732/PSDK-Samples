#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

# -------------------------------------------------------------------
# --- This sample builds ONLY for Windows XP
# -------------------------------------------------------------------
!if "$(TARGETOS)" == "WINNT"
!if "$(APPVER)" == "5.01" || "$(APPVER)" == "5.02"

PROJECT=VMRXclBasic

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\DShowUtils.obj \
	$(OUTDIR)\Helpers.obj \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\VMRXclBasic.obj \
	$(OUTDIR)\vmrGlobals.obj \
	$(OUTDIR)\VMRXclBasic.res

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	comctl32.lib \
	ddraw.lib \
	dxguid.lib \
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
DXLIB="$(DXSDK_DIR)\Lib\x32"
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(LINK32_OBJS) $(STRMBASE) $(LINK32_LIBS)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)


!else
!MESSAGE This sample builds only for Windows XP (or greater) platforms.
!endif
!endif
