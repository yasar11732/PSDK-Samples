!include <Win32.Mak>

proj=scintro

EXTRA_LIBS = winscard.lib

all: $(OUTDIR) $(OUTDIR)\$(proj).exe

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(proj).obj: $(proj).cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -I..\include /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(proj).cpp

$(OUTDIR)\$(proj).exe: $(OUTDIR)\$(proj).obj
    $(link) $(ldebug) $(conlflags) $(conlibs) $(EXTRA_LIBS) -out:$(OUTDIR)\$(proj).exe $(OUTDIR)\$(proj).obj /PDB:$(OUTDIR)\$(proj).PDB

clean:
	$(CLEANUP)
