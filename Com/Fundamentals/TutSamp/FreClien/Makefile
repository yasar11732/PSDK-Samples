#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = freclien
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = ..\lib\$(OUTDIR)\apputil.lib shell32.lib

LINK32_OBJS = $(OUTDIR)\guiball.obj \
              $(OUTDIR)\freclien.obj \
              $(OUTDIR)\freclien.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\inc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\freclien.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\freclien.res freclien.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS)

clean:
     $(CLEANUP)
