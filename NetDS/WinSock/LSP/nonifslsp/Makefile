!include <win32.mak>

all: $(OUTDIR)  $(OUTDIR)\nonifslsp.dll $(OUTDIR)\instlsp.exe

$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

DLL_OBJS=  $(OUTDIR)\spi.obj        \
           $(OUTDIR)\extension.obj  \
           $(OUTDIR)\overlap.obj    \
           $(OUTDIR)\provider.obj   \
           $(OUTDIR)\sockinfo.obj   \
           $(OUTDIR)\lspguid.obj    \
           $(OUTDIR)\asyncselect.obj

INSTALL_OBJS= $(OUTDIR)\lspguid.obj     \
	      $(OUTDIR)\lspadd.obj	\
	      $(OUTDIR)\lspdel.obj   	\
	      $(OUTDIR)\lspmap.obj	\
	      $(OUTDIR)\lsputil.obj	\
	      $(OUTDIR)\instlsp.obj     \
              $(OUTDIR)\prnpinfo.obj    \
              $(OUTDIR)\provider.obj

LIBS= ws2_32.lib ole32.lib rpcrt4.lib $(baselibs)

$(OUTDIR)\provider.obj:
	$(cc) ..\common\provider.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\provider.obj

.cpp{$(OUTDIR)}.obj:
	$(cc) $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\nonifslsp.dll: $(DLL_OBJS)
	$(link) $(linkdebug) $(dlllflags) -def:nonifslsp.def \
	-out:$*.dll -pdb:$*.pdb $(guilibsdll) $** $(LIBS) 
	Echo COMPILED NONIFSLSP.DLL

$(OUTDIR)\lspadd.obj:
	$(cc) ..\install\lspadd.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\lspadd.obj

$(OUTDIR)\lspdel.obj:
	$(cc) ..\install\lspdel.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\lspdel.obj
	
$(OUTDIR)\lspmap.obj:
	$(cc) ..\install\lspmap.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\lspmap.obj

$(OUTDIR)\lsputil.obj:
	$(cc) ..\install\lsputil.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\lsputil.obj
	
$(OUTDIR)\instlsp.obj:
	$(cc) ..\install\instlsp.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\instlsp.obj
	
$(OUTDIR)\prnpinfo.obj:
	$(cc) ..\\install\prnpinfo.cpp $(cdebug) $(cflags) -DSTRICT -DFD_SETSIZE=1024 /GS $(cvarsdll) /Fo$(OUTDIR)\prnpinfo.obj              
	
$(OUTDIR)\instlsp.exe: $(INSTALL_OBJS)
    	$(link) $(linkdebug) $(conlflags) -out:$*.exe $** $(LIBS) 
	Echo COMPILED INSTLSP.EXE
clean:
    rmdir /s /q $(OUTDIR)
