#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = inproc
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\sserver.obj

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_UNICODE /DUNICODE /D_WIN32_DCOM /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /DEF:dllsrv.def  $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
