#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=MultiVMR9
IDL=MultiVMR9

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common


!if "$(CPU)"=="AMD64"
DXLIB="$(DXSDK_DIR)\Lib\x64"
!else
DXLIB="$(DXSDK_DIR)\Lib\x86"
!endif

LINK32_OBJS = \
	$(OUTDIR)\MixerControl.obj \
	$(OUTDIR)\MultiVMR9.obj \
	$(OUTDIR)\MultiVMR9_i.obj \
	$(OUTDIR)\UILayer.obj \
	$(OUTDIR)\RenderEngine.obj \
	$(OUTDIR)\Wizard.obj \
	$(OUTDIR)\stdafx.obj \
	$(OUTDIR)\MultiVMR9.res

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	comctl32.lib \
	quartz.lib \
	Winmm.lib \
	d3d9.lib \
	strmiids.lib 

!ifdef NODEBUG
STRMBASE = strmbase.lib
LIBC = libcmt
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
LIBC = libcmtd
!endif

STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"


all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).dll 

$(OUTDIR)\$(PROJECT).dll: $(IDL).h $(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).dll /DLL /PDB:$(OUTDIR)\$(PROJECT).pdb /DEF:$(PROJECT).def /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(LINK32_OBJS) $(STRMBASE) $(LINK32_LIBS) /NODEFAULTLIB:$(LIBC)

$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /h $(IDL).h /tlb $(IDL).tlb /out $(OUTDIR) $(IDL).idl

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\..\Inc /I..\..\..\BaseClasses /I$(BASEDIR) /I$(OUTDIR) /I"$(DXSDK_DIR)\Include" /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

{$(OUTDIR)}.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"/D_MBCS /I..\..\Inc /I..\..\..\BaseClasses /I$(BASEDIR)  /I$(OUTDIR)  /I"$(DXSDK_DIR)\Include" /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
