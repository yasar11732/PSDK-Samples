#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PSPROJ = PingResp
IDL=PingResp


all: $(OUTDIR) $(OUTDIR)\$(IDL).h  $(OUTDIR)\$(PSPROJ).dll 
$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /h $(IDL).h /tlb $(IDL).tlb /out $(OUTDIR) $(IDL).idl 


EXTRA_PSLIBS = rpcrt4.lib 

LINK32_PSOBJS = $(OUTDIR)\dlldatax.obj  \
              $(OUTDIR)\$(IDL).obj \
              $(OUTDIR)\$(IDL).res 

$(OUTDIR)\dlldatax.obj:dlldatax.c
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /D_MERGE_PROXYSTUB /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.c.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /D_MERGE_PROXYSTUB /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(LINK32_PSOBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:$(PSPROJ).def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS) $(baselibs) $(olelibs) 


$(OUTDIR)\$(IDL).res:
     $(rc) $(rcflags) $(rcvars) /I $(OUTDIR) /Fo$(OUTDIR)\$(IDL).res $(IDL).rc


.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**



clean:
     $(CLEANUP)
 

