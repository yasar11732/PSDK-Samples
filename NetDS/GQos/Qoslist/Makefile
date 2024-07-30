TARGETOS=BOTH

!include <win32.mak>

objs=$(OUTDIR)\qoslist.obj

all: $(OUTDIR)\qoslist.exe

$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

# Update the object file if necessary

.cpp{$(OUTDIR)}.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\qoslist.exe: $(OUTDIR) $(objs) #$(common_objs)
    $(link) $(linkdebug) $(conlflags) -out:$(OUTDIR)\qoslist.exe $(objs) $(conlibsmt) qosname.lib

clean:
    if exist "$(OUTDIR)/$(NULL)" rd /s /q $(OUTDIR)
