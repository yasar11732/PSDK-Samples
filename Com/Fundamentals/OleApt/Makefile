#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

CLIENTPROJ = oleapt

all: $(OUTDIR)  $(OUTDIR)\$(CLIENTPROJ).exe 
$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"


EXTRA_PSLIBS = rpcrt4.lib 


.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /D_MBCS /D_CONSOLE /D_UNICODE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Client

CLIENT_LINK32_OBJS = $(OUTDIR)\$(CLIENTPROJ).obj 

$(OUTDIR)\$(CLIENTPROJ).exe:   $(CLIENT_LINK32_OBJS) 
     $(link) $(ldebug) $(guilflags)  $(olelibsdll) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(CLIENTPROJ).pdb -out:$(OUTDIR)\$(CLIENTPROJ).exe $(CLIENT_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 


clean:
     $(CLEANUP)
