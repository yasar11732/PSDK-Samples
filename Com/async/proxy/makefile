#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PSPROJ = proxy
IDL= proxy

all:    $(OUTDIR) $(OUTDIR)\$(PSPROJ).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(IDL).h: $(IDL).idl
      $(midl) $(MIDL_OPTIMIZATION) /h $(IDL).h /tlb $(IDL).tlb /out $(OUTDIR) $(IDL).idl

EXTRA_PSLIBS = rpcrt4.lib 

LINK32_PSOBJS = $(OUTDIR)\$(IDL)_p.obj \
              $(OUTDIR)\$(IDL)_i.obj \
              $(OUTDIR)\dlldata.obj

{$(OUTDIR)}.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /DREGISTER_PROXY_DLL /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PSPROJ).dll:   $(OUTDIR)\$(IDL).h $(LINK32_PSOBJS) 
     $(link) $(ldebug) $(dlllflags) $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PSPROJ).pdb -out:$(OUTDIR)\$(PSPROJ).dll /DEF:$(PSPROJ).def  $(LINK32_PSOBJS) $(EXTRA_PSLIBS)

clean:
     $(CLEANUP)
