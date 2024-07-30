PROJ=ftpjr

!include <win32.mak>
all:$(OUTDIR) $(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\ftpjr.obj: ftpjr.cpp
    $(cc) $(cflags) $(cvars) $(cdebug) /EHsc /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ftpjr.cpp

ftpjr.exe: $(OUTDIR)\ftpjr.obj
    $(link) $(conlflags)  $(ldebug) /MACHINE:$(CPU) -out:$(OUTDIR)\$(PROJ).exe $(OUTDIR)\ftpjr.obj $(baselibs) wininet.lib  user32.lib kernel32.lib

clean:
    $(CLEANUP)
