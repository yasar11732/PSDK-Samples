#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = client
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\$(PROJ).obj \
              ..\include\$(OUTDIR)\guids.obj \
              $(OUTDIR)\pipe.obj 


.cxx{$(OUTDIR)}.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /EHsc /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"  /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /c $<

$(OUTDIR)\pipe.obj: ..\include\pipe.cxx
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(conlflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)