#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

# -------------------------------------------------------------------
# --- This sample builds ONLY for Windows XP
# -------------------------------------------------------------------
!if "$(TARGETOS)" == "WINNT"
!if "$(APPVER)" == "5.01" || "$(APPVER)" == "5.02"

PROJECT=vmrmulti

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\AP.obj \
	$(OUTDIR)\CMultiSAP.obj \
	$(OUTDIR)\DDrawSupport.obj \
	$(OUTDIR)\movie.obj \
	$(OUTDIR)\VMRMulti.obj \
	$(OUTDIR)\resource.res

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	comctl32.lib \
	quartz.lib \
	Winmm.lib \
	strmiids.lib 

!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS) $(OUTDIR)\sparkles.obj $(OUTDIR)\effect.obj $(OUTDIR)\d3dutil.obj $(OUTDIR)\d3dtextr.obj $(OUTDIR)\d3dmath.obj
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_OBJS) $(OUTDIR)\sparkles.obj $(OUTDIR)\effect.obj $(OUTDIR)\d3dutil.obj $(OUTDIR)\d3dtextr.obj $(OUTDIR)\d3dmath.obj $(STRMBASE) $(LINK32_LIBS) 

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

$(OUTDIR)\effect.obj: .\effects\Effect.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" .\effects\effect.cpp

$(OUTDIR)\sparkles.obj: .\Sparkles\sparkles.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" .\Sparkles\sparkles.cpp

$(OUTDIR)\d3dutil.obj: .\D3DHelpers\d3dutil.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I. /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" .\D3DHelpers\d3dutil.cpp

$(OUTDIR)\d3dtextr.obj: .\D3DHelpers\d3dtextr.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I. /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" .\D3DHelpers\d3dtextr.cpp

$(OUTDIR)\d3dmath.obj: .\D3DHelpers\d3dmath.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\Inc /I. /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" .\D3DHelpers\d3dmath.cpp

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
