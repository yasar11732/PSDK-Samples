!if "$(CPU)" == "i386"
#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = RecoDll
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\stdafx.obj \
              $(OUTDIR)\recodll.obj \
              $(OUTDIR)\recodll.res

$(OUTDIR)\stdafx.obj:     stdafx.cpp
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /DRECODLL_EXPORTS /D_USRDLL /D_MBCS /I"..\..\include" /Yc"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" stdafx.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /DRECODLL_EXPORTS /D_USRDLL /D_MBCS /I"..\..\include" /Yu"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\recodll.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\recodll.res /I"..\..\Include" recodll.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /DEF:recodll.def  $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
!else
!message Sorry this sample will only build for 32bit platforms
!endif
