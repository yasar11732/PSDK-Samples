#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = sampprov
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = oledb.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib 

LINK32_OBJS = $(OUTDIR)\headers.obj \
              $(OUTDIR)\utilprop.obj \
              $(OUTDIR)\stream.obj \
              $(OUTDIR)\rowset.obj \
              $(OUTDIR)\rowinfo.obj \
              $(OUTDIR)\rowchng.obj \
              $(OUTDIR)\row.obj \
              $(OUTDIR)\persist.obj \
              $(OUTDIR)\opnrowst.obj \
              $(OUTDIR)\irowset.obj \
              $(OUTDIR)\irowiden.obj \
              $(OUTDIR)\igetrow.obj \
              $(OUTDIR)\hashtbl.obj \
              $(OUTDIR)\globals.obj \
              $(OUTDIR)\fileio.obj \
              $(OUTDIR)\fileidx.obj \
              $(OUTDIR)\extbuff.obj \
              $(OUTDIR)\dbsess.obj \
              $(OUTDIR)\dbprop.obj \
              $(OUTDIR)\dbinit.obj \
              $(OUTDIR)\datasrc.obj \
              $(OUTDIR)\cvttype.obj \
              $(OUTDIR)\crtsess.obj \
              $(OUTDIR)\common.obj \
              $(OUTDIR)\command.obj \
              $(OUTDIR)\colinfo.obj \
              $(OUTDIR)\classfac.obj \
              $(OUTDIR)\bitarray.obj \
              $(OUTDIR)\binder.obj \
              $(OUTDIR)\baseobj.obj \
              $(OUTDIR)\asserts.obj \
              $(OUTDIR)\accessor.obj \
              $(OUTDIR)\sampprov.res

$(OUTDIR)\headers.obj:     headers.cpp
     $(cc) $(cflags) $(cdebug) $(cvars) /GX /Gm /I"..\..\include" /Yc"headers.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" headers.cpp

$(OUTDIR)\globals.obj:     globals.cpp
     $(cc) $(cflags) $(cdebug) $(cvars) /GX /Gm /I"..\..\include" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" globals.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvars) /GX /Gm /I"..\..\include" /Yu"headers.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\sampprov.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\sampprov.res sampprov.rc

$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
     $(link) $(ldebug) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /DEF:sampprov.def  $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
