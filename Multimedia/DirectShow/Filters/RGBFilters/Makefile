#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=RGBFilters
IDL=$(PROJECT)

DXDIR = "$(DXSDK_DIR)\Include"

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\TransSmpte.obj \
	$(OUTDIR)\TransNull8.obj \
	$(OUTDIR)\TransNull565.obj \
	$(OUTDIR)\TransNull555.obj \
	$(OUTDIR)\TransNull32a.obj \
	$(OUTDIR)\TransNull32.obj \
	$(OUTDIR)\TransNull24.obj \
	$(OUTDIR)\Source32stream.obj \
	$(OUTDIR)\Source32.obj \
	$(OUTDIR)\Source24stream.obj \
	$(OUTDIR)\Source24.obj \
	$(OUTDIR)\Source565stream.obj \
	$(OUTDIR)\Source565.obj \
	$(OUTDIR)\Source555stream.obj \
	$(OUTDIR)\Source555.obj \
	$(OUTDIR)\Source8BitStream.obj \
	$(OUTDIR)\Source8Bit.obj \
	$(OUTDIR)\AlphaStream.obj \
	$(OUTDIR)\AlphaSource.obj \
	$(OUTDIR)\ratestream.obj \
	$(OUTDIR)\ratesource.obj \
	$(OUTDIR)\AlphaRenderer.obj \
	$(OUTDIR)\setup.obj \
	$(OUTDIR)\RGBFilters.obj \

!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
!endif

LINK32_LIBS = \
	$(winlibs) \
	shell32.lib \
	strmiids.lib \
	$(STRMBASE) \
	winmm.lib


all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).dll 

$(OUTDIR)\$(PROJECT).dll:	$(OUTDIR)\$(IDL).h $(LINK32_OBJS)
	$(link) /NODEFAULTLIB:LIBCMTD.LIB /NODEFAULTLIB:LIBCMT.LIB /LIBPATH:"..\..\BaseClasses\$(OUTDIR)" /DLL /DEF:"$(PROJECT).def" $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).dll $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)

$(OUTDIR)\$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /h $(IDL).h /tlb $(IDL).tlb /out $(OUTDIR) $(IDL).idl

{AlphaRenderer}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{AlphaSource}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{RateSource}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{Source24}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{Source32}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{Source555}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{Source565}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{Source8Bit}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{TransNulls}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

{TransSmpte}.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**

.cpp{$(OUTDIR)}.obj:
    $(cc) /I. $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I$(OUTDIR) /I$(DXDIR) $**


.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
