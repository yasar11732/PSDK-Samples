#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = RowsetViewer
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = htmlhelp.lib shell32.lib advapi32.lib comctl32.lib oledb.lib

LINK32_OBJS = $(OUTDIR)\headers.obj \
              $(OUTDIR)\spy.obj \
              $(OUTDIR)\property.obj \
              $(OUTDIR)\error.obj \
              $(OUTDIR)\cwinapp.obj \
              $(OUTDIR)\ctransaction.obj \
              $(OUTDIR)\ctrace.obj \
              $(OUTDIR)\cstream.obj \
              $(OUTDIR)\csession.obj \
              $(OUTDIR)\crowset.obj \
              $(OUTDIR)\crowposition.obj \
              $(OUTDIR)\crow.obj \
              $(OUTDIR)\coptions.obj \
              $(OUTDIR)\common.obj \
              $(OUTDIR)\cobjtree.obj \
              $(OUTDIR)\cmutipleresults.obj \
              $(OUTDIR)\cmdichild.obj \
              $(OUTDIR)\cmainwindow.obj \
              $(OUTDIR)\clistener.obj \
              $(OUTDIR)\cerror.obj \
              $(OUTDIR)\cenum.obj \
              $(OUTDIR)\cdialoglite.obj \
              $(OUTDIR)\cdialog.obj \
              $(OUTDIR)\cdatasource.obj \
              $(OUTDIR)\cdataset.obj \
              $(OUTDIR)\cdatalinks.obj \
              $(OUTDIR)\ccommand.obj \
              $(OUTDIR)\cbinder.obj \
              $(OUTDIR)\cbase.obj \
              $(OUTDIR)\rowsetviewer.res

$(OUTDIR)\headers.obj:     headers.cpp
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GR /Gm /GX /DFINDLEAKS /D/FD /I"..\..\include" /Yc"headers.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" headers.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GR /Gm /GX /DFINDLEAKS /D/FD /I"..\..\include" /Yu"headers.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\rowsetviewer.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\rowsetviewer.res rowsetviewer.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
