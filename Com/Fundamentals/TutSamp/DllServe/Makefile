#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = dllserve
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\utilcar.obj \
              $(OUTDIR)\server.obj \
              $(OUTDIR)\sample.obj \
              $(OUTDIR)\factory.obj \
              $(OUTDIR)\dllserve.obj \
              $(OUTDIR)\crucar.obj \
              $(OUTDIR)\car.obj \
              $(OUTDIR)\dllserve.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\dllserve.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\dllserve.res dllserve.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb /DEF:$(PROJ).def -out:$(OUTDIR)\$(PROJ).dll $(LINK32_OBJS) $(EXTRA_LIBS) -implib:$(OUTDIR)\$(PROJ).lib

clean:
     $(CLEANUP)
