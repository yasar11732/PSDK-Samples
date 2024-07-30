#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = perserve
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\server.obj \
              $(OUTDIR)\perserve.obj \
              $(OUTDIR)\pagelist.obj \
              $(OUTDIR)\factory.obj \
              $(OUTDIR)\connect.obj \
              $(OUTDIR)\perserve.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\perserve.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\perserve.res perserve.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /def:$(PROJ).def /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll $(LINK32_OBJS) $(EXTRA_LIBS) -implib:$(OUTDIR)\$(PROJ).lib

clean:
     $(CLEANUP)
