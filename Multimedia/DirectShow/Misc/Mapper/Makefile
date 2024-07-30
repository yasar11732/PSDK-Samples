#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifdef NODEBUG
STRMBASE = strmbase.lib
!else
STRMBASE = strmbasd.lib
cflags=$(cflags) /DDEBUG
!endif

all:	$(OUTDIR) $(OUTDIR)\mapper.exe 

$(OUTDIR)\mapper.exe:	$(OUTDIR)\StdAfx.obj $(OUTDIR)\mapper.obj $(OUTDIR)\mapperDlg.obj $(OUTDIR)\mapper.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\mapper.exe $(guilflags) /PDB:$(OUTDIR)\mapper.pdb /MACHINE:$(CPU) $(OUTDIR)\StdAfx.obj $(OUTDIR)\mapper.obj $(OUTDIR)\mapperDlg.obj $(OUTDIR)\mapper.res strmiids.lib bufferoverflowU.lib 

$(OUTDIR)\StdAfx.obj:	StdAfx.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yc"Stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I..\..\BaseClasses StdAfx.cpp

$(OUTDIR)\mapper.obj:	mapper.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"Stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"WIN32" /D"_DEBUG" /D"_WINDOWS" /D"_AFXDLL" /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" mapper.cpp

$(OUTDIR)\mapperDlg.obj:	mapperDlg.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"Stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"WIN32" /D"_DEBUG" /D"_WINDOWS" /D"_AFXDLL" /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" mapperDlg.cpp

$(OUTDIR)\mapper.res:	
	 $(rc) $(rcflags) /Fo$(OUTDIR)\mapper.res mapper.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
