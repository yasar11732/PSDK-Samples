#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = dllskel
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
     if not exist "..\lib\$(NULL)" mkdir "..\lib"
     if not exist "..\lib\$(OUTDIR)/$(NULL)" mkdir "..\lib\$(OUTDIR)"
     if not exist "..\inc\$(NULL)" mkdir "..\inc"


EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\dllskel.obj \
              $(OUTDIR)\dllskel.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\dllskel.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\dllskel.res dllskel.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll $(LINK32_OBJS) $(EXTRA_LIBS) -implib:$(OUTDIR)\$(PROJ).lib
     copy $(OUTDIR)\$(PROJ).lib ..\lib\$(OUTDIR)
     copy $(PROJ).h ..\inc


clean:
     $(CLEANUP)
     if exist ..\lib\$(OUTDIR)/ del /q ..\lib\$(OUTDIR)\$(PROJ).lib