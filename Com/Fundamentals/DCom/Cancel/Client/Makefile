#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = cancel
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\cancel.obj \
              $(OUTDIR)\cancel.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_UNICODE /DUNICODE /D_WIN32_DCOM /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\cancel.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\cancel.res cancel.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
