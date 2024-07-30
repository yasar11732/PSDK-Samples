#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = stoserve
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\stoserve.obj \
              $(OUTDIR)\server.obj \
              $(OUTDIR)\paper.obj \
              $(OUTDIR)\factory.obj \
              $(OUTDIR)\connect.obj \
              $(OUTDIR)\stoserve.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\stoserve.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\stoserve.res stoserve.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /def:$(PROJ).def /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll $(LINK32_OBJS) $(EXTRA_LIBS) -implib:$(OUTDIR)\$(PROJ).lib

clean:
     $(CLEANUP)
