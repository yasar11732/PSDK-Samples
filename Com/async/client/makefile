#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = client
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\proxy_i.obj \
              $(OUTDIR)\debug.obj \
              $(OUTDIR)\main.obj

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_EVENTSINK_ /D_ASYNC_COM_ /D_SECURE_ /D_MBCS /D_CONSOLE /I ..\proxy\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\proxy_i.obj:     ..\proxy\$(OUTDIR)\proxy_i.c
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_EVENTSINK_ /D_ASYNC_COM_ /D_SECURE_ /D_MBCS /D_CONSOLE /I ..\proxy\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\proxy\$(OUTDIR)\proxy_i.c

$(OUTDIR)\debug.obj:     ..\server\debug.c
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_EVENTSINK_ /D_ASYNC_COM_ /D_SECURE_ /D_MBCS /D_CONSOLE /I ..\proxy\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\server\debug.c

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(conlflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
