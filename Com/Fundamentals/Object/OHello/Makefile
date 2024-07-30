#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

CLIENTPROJ = client
SERVERPROJ = server
PSPROJ = ohello
IDL=ohello

all: $(OUTDIR) $(OUTDIR)\$(IDL).h  $(OUTDIR)\$(PSPROJ).dll $(OUTDIR)\$(CLIENTPROJ).exe $(OUTDIR)\$(SERVERPROJ).exe 
$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(IDL).h : $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /out $(OUTDIR) $(IDL).idl


EXTRA_PSLIBS = rpcrt4.lib 

LINK32_PSOBJS = $(OUTDIR)\$(IDL)_p.obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\dlldata.obj \


.c.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(LINK32_PSOBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:$(PSPROJ).def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS) $(baselibs) $(olelibs) 



#.rc{$(OUTDIR)}.res:
#     $(rc) $(rcvars) $(rflags) $**


.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.cxx{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Client

CLIENT_LINK32_OBJS = $(OUTDIR)\$(CLIENTPROJ).obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\error.obj 

$(OUTDIR)\$(CLIENTPROJ).exe:   $(CLIENT_LINK32_OBJS) 
     $(link) $(ldebug) $(conlflags)  $(olelibsmt) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(CLIENTPROJ).pdb -out:$(OUTDIR)\$(CLIENTPROJ).exe $(CLIENT_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 


# Server
SERVER_LINK32_OBJS = $(OUTDIR)\$(SERVERPROJ).obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\chello.obj \
              $(OUTDIR)\error.obj 
$(OUTDIR)\$(SERVERPROJ).exe:   $(SERVER_LINK32_OBJS) 
     $(link) $(ldebug) $(conlflags)  $(olelibsmt) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(SERVERPROJ).pdb -out:$(OUTDIR)\$(SERVERPROJ).exe $(SERVER_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 



clean:
     $(CLEANUP)
