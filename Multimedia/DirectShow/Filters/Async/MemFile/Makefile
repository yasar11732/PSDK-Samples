#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
STRMBASE = strmbase.lib
MSVCRT = msvcrt.lib
ATLS = atls.lib
!else
STRMBASE = strmbasd.lib
MSVCRT = msvcrtd.lib
ATLS = atlsd.lib
!endif

!if "$(CPU)"=="AMD64"
ATLS = 
!endif


STRMBASE="$(MSSDK)\samples\multimedia\directshow\baseclasses\$(OUTDIR)\$(STRMBASE)"

all:	$(OUTDIR) $(OUTDIR)\memfile.exe 

$(OUTDIR)\memfile.exe:	$(OUTDIR)\memfile.obj 
	$(link) $(ldebug) /OUT:$(OUTDIR)\memfile.exe /LIBPATH:"..\base\$(OUTDIR)" /NODEFAULTLIB /PDB:$(OUTDIR)\memfile.pdb /SUBSYSTEM:CONSOLE /MACHINE:$(CPU) $(STRMBASE) strmiids.lib winmm.lib odbc32.lib odbccp32.lib $(MSVCRT) kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib $(ATLS) asynbase.lib bufferoverflowu.lib "$(OUTDIR)\memfile.obj"

$(OUTDIR)\memfile.obj:	memfile.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsmt) /Fp$(OUTDIR)\memfile.pch /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_CONSOLE /DINC_OLE2 /D_MT /D_DLL /Dtry=__try /Dexcept=__except /Dleave=__leave /Dfinally=__finally /I..\..\..\BaseClasses /I..\include /I"$(DXSDK_DIR)\Include" memfile.cpp
        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
