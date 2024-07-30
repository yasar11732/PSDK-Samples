#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

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

all:	$(OUTDIR) $(OUTDIR)\RenderLog.exe

$(OUTDIR)\RenderLog.exe:	$(OUTDIR)\RenderLog.obj $(OUTDIR)\RenderLog.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\RenderLog.exe $(guilflags) /PDB:$(OUTDIR)\RenderLog.pdb /MACHINE:$(CPU) /LIBPATH:$(DXLIB) $(OUTDIR)\RenderLog.obj $(OUTDIR)\RenderLog.res Gdi32.lib Comdlg32.lib dxerr9.lib strmiids.lib bufferoverflowU.lib

$(OUTDIR)\RenderLog.obj:	RenderLog.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" RenderLog.cpp

$(OUTDIR)\RenderLog.res:	
	 $(rc) $(rcflags) /Fo$(OUTDIR)\RenderLOg.res RenderLog.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
