#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>


SERVERPROJ = SERVER
PSPROJ = ServerPS
IDL=SERVER


all: $(OUTDIR) $(OUTDIR)\$(IDL).h  $(OUTDIR)\$(PSPROJ).dll $(OUTDIR)\$(SERVERPROJ).exe 
$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /h $(IDL).h /tlb $(IDL).tlb /out $(OUTDIR) $(IDL).idl 


EXTRA_PSLIBS = rpcrt4.lib 

LINK32_PSOBJS = $(OUTDIR)\$(IDL)_p.obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\dlldata.obj

{$(OUTDIR)}.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I ..\PingResp\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(LINK32_PSOBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:$(PSPROJ).def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS) $(baselibs) $(olelibs) 



.rc.res:
     $(rc) $(rcvars) $(rflags) /I $(OUTDIR) $**


.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /I ..\PingResp\$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


SERVER_LINK32_OBJS = $(OUTDIR)\$(SERVERPROJ).obj \
              $(OUTDIR)\MonitorServer.obj \
              $(SERVERPROJ).res

$(OUTDIR)\$(SERVERPROJ).exe:   $(SERVER_LINK32_OBJS) 
     $(link) $(ldebug) $(guilflags) $(olelibsmt) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(SERVERPROJ).pdb -out:$(OUTDIR)\$(SERVERPROJ).exe $(SERVER_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 



clean:
     $(CLEANUP)
