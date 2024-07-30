#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = LocalServer
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = advapi32.lib user32.lib uuid.lib ole32.lib oleaut32.lib

LINK32_OBJS = $(OUTDIR)\server.obj \
	$(OUTDIR)\component.obj \
	$(OUTDIR)\pipe.obj \
	..\include\$(OUTDIR)\guids.obj

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.cxx{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\pipe.obj: ..\include\pipe.cxx
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /I ..\include\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS)

clean:
     $(CLEANUP)
