#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

CLIENTPROJ = client
SERVERPROJ = server
PSPROJ = callas
IDL=callas


all: $(OUTDIR) $(OUTDIR)\$(IDL).h  $(OUTDIR)\$(PSPROJ).dll $(OUTDIR)\$(CLIENTPROJ).exe $(OUTDIR)\$(SERVERPROJ).exe 
$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /out $(OUTDIR) $(IDL).idl


EXTRA_PSLIBS = rpcrt4.lib 

LINK32_PSOBJS = $(OUTDIR)\$(IDL)_p.obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\dlldata.obj \
              $(OUTDIR)\call_as.obj 


.c.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(LINK32_PSOBJS)
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:$(PSPROJ).def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS) $(baselibs) $(olelibs) 



$(OUTDIR)\call_as.obj: call_as.c
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.cxx{$(OUTDIR)}.obj:
     $(cc) $(cflags) -Gz $(cdebug) $(cvarsmt) /D_MBCS /D_CONSOLE /D_UNICODE /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Client

$(OUTDIR)\client.obj: client.c
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /DREGISTER_PROXY_DLL /D_WIN32_DCOM /DPSPERF_EXPORTS /D_USRDLL /D_MBCS /I $(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


CLIENT_LINK32_OBJS = $(OUTDIR)\$(CLIENTPROJ).obj \
              $(OUTDIR)\$(IDL)_i.obj 

$(OUTDIR)\$(CLIENTPROJ).exe:   $(CLIENT_LINK32_OBJS) 
     $(link) $(ldebug) $(conlflags)  $(olelibsmt) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(CLIENTPROJ).pdb -out:$(OUTDIR)\$(CLIENTPROJ).exe $(CLIENT_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 


SERVER_LINK32_OBJS = $(OUTDIR)\$(SERVERPROJ).obj \
              $(OUTDIR)\$(IDL)_i.obj 

$(OUTDIR)\$(SERVERPROJ).exe:   $(SERVER_LINK32_OBJS) 
     $(link) $(ldebug) $(conlflags)  $(olelibsmt) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(SERVERPROJ).pdb -out:$(OUTDIR)\$(SERVERPROJ).exe $(SERVER_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 



clean:
     $(CLEANUP)




#EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib

#EXTRA_PSLIBS = rpcrt4.lib 