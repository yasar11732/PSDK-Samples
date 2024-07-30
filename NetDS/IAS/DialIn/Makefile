!if ("$(APPVER)" != "5.02") 

!include <win32.mak>

proj=dialin

all: $(OUTDIR) $(OUTDIR)\$(proj).dll

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)\$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(proj).c

$(OUTDIR)\$(proj).dll: $(OUTDIR)\$(proj).obj
        $(link) $(linkdebug) $(dlllflags) $(guilibsdll) -def:$(proj).def -out:$(OUTDIR)\$(proj).dll  $(OUTDIR)\$(proj).obj rassapi.lib

clean:
	$(CLEANUP)
!else
!message This sample intended for Windows XP or Windows 2000
!endif
