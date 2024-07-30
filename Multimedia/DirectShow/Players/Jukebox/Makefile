#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

all:	$(OUTDIR) $(OUTDIR)\Jukebox.exe 

$(OUTDIR)\Jukebox.exe:	$(OUTDIR)\StdAfx.obj $(OUTDIR)\globals.obj $(OUTDIR)\Jukebox.obj $(OUTDIR)\JukeboxDlg.obj $(OUTDIR)\playvideo.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\keyprovider.obj $(OUTDIR)\Jukebox.res 
	$(link) $(ldebug) /OUT:$(OUTDIR)\Jukebox.exe $(guilflags) /PDB:$(OUTDIR)\Jukebox.pdb /MACHINE:$(CPU) $(OUTDIR)\globals.obj $(OUTDIR)\Jukebox.obj $(OUTDIR)\JukeboxDlg.obj $(OUTDIR)\playvideo.obj $(OUTDIR)\StdAfx.obj $(OUTDIR)\keyprovider.obj $(OUTDIR)\Jukebox.res strmiids.lib bufferoverflowu.lib

$(OUTDIR)\StdAfx.obj:	StdAfx.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yc"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D"TARGET_WMF9" /D_MBCS /I..\..\BaseClasses StdAfx.cpp

$(OUTDIR)\globals.obj:	globals.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_AFXDLL" /D"TARGET_WMF9"  /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" globals.cpp

$(OUTDIR)\Jukebox.obj:	Jukebox.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_AFXDLL" /D"TARGET_WMF9"  /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" Jukebox.cpp

$(OUTDIR)\JukeboxDlg.obj:	JukeboxDlg.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_AFXDLL" /D"TARGET_WMF9"  /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" JukeboxDlg.cpp

$(OUTDIR)\playvideo.obj:	playvideo.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_AFXDLL" /D"TARGET_WMF9"  /D"_MBCS" /I..\..\BaseClasses /I"$(DXSDK_DIR)\Include" playvideo.cpp

$(OUTDIR)\keyprovider.obj:	keyprovider.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Yu"stdafx.h" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_AFXDLL" /D"TARGET_WMF9"  /D"_MBCS" /I..\..\BaseClasses /I..\..\Common /I"$(DXSDK_DIR)\Include" keyprovider.cpp

$(OUTDIR)\Jukebox.res:	
	 $(rc) $(rcflags) /Fo$(OUTDIR)\jukebox.res jukebox.rc

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
