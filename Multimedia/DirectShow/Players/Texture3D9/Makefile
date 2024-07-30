#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=Texture3D

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\dxutil.obj \
	$(OUTDIR)\DShowTextures.obj \
	$(OUTDIR)\Textures.obj \
	$(OUTDIR)\d3dfont.obj

!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
!endif

!if "$(CPU)"=="AMD64"
DXLIB="$(DXSDK_DIR)\Lib\x64"
!else
DXLIB="$(DXSDK_DIR)\Lib\x86"
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

LINK32_LIBS = \
	$(STRMBASE) \
	d3dx9.lib \
	d3d9.lib \
	winmm.lib \
	$(winlibs) \
	shell32.lib 

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(LINK32_OBJS) $(LINK32_LIBS)

{$(COMMONDIR)}.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /EHsc /Fp$(OUTDIR)\$(PROJECT).pch /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS  /I$(BASEDIR) $**

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /EHsc /Fp$(OUTDIR)\$(PROJECT).pch /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_MBCS /I$(BASEDIR) /I"$(DXSDK_DIR)\Include"  $**

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
