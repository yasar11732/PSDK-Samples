#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = comperf
PSPROJ = psperf

all: $(OUTDIR) $(OUTDIR)\psperf.h  $(OUTDIR)\$(PSPROJ).dll $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_OBJS = $(OUTDIR)\psperf_i.obj \
              $(OUTDIR)\comperf.obj

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_MBCS /D_CONSOLE  /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(conlflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

EXTRA_PSLIBS = rpcrt4.lib odbccp32.lib odbc32.lib shell32.lib advapi32.lib

LINK32_PSOBJS = $(OUTDIR)\psperf_p.obj \
              $(OUTDIR)\psperf_i.obj \
              $(OUTDIR)\dlldata.obj

$(OUTDIR)\psperf.h: psperf.idl 
      $(midl) $(MIDL_OPTIMIZATION) /h psperf.h /tlb psperf.tlb psperf.idl

.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I"ps_Win32" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(LINK32_PSOBJS)
     $(link) $(ldebug) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:psperf.def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS) $(baselibs) $(olelibs) 


clean:
     $(CLEANUP)
