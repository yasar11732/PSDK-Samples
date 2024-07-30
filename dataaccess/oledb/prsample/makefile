#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = prsample
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = msdasc.lib oledb.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\session.obj \
              $(OUTDIR)\rowset.obj \
              $(OUTDIR)\main.obj \
              $(OUTDIR)\error.obj \
              $(OUTDIR)\enum.obj \
              $(OUTDIR)\datasource.obj \
              $(OUTDIR)\command.obj \
              $(OUTDIR)\prsample.res

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gt0 /Fd"x86_debu /Fd"Debug /GX /Gm /D_MBCS /D_CONSOLE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\prsample.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\prsample.res prsample.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(conlflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
