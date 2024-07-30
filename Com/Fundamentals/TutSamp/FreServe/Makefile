#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = freserve
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\server.obj \
              $(OUTDIR)\freserve.obj \
              $(OUTDIR)\factory.obj \
              $(OUTDIR)\ball.obj \
              $(OUTDIR)\freserve.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\freserve.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\freserve.res freserve.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /def:$(PROJ).def /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll $(LINK32_OBJS) $(EXTRA_LIBS) -implib:$(OUTDIR)\$(PROJ).lib

clean:
     $(CLEANUP)
