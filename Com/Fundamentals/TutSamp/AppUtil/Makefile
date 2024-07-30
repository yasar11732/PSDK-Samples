#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = apputil
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).lib

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
     if not exist "..\lib\$(NULL)" mkdir "..\lib"
     if not exist "..\lib\$(OUTDIR)/$(NULL)" mkdir "..\lib\$(OUTDIR)"
     if not exist "..\inc\$(NULL)" mkdir "..\inc"

LINK32_OBJS = $(OUTDIR)\apputil.obj

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\$(PROJ).lib:   $(LINK32_OBJS)
    lib  /MACHINE:$(CPU) /out:"$(OUTDIR)\$(PROJ).lib" $(LINK32_OBJS)  
    copy $(OUTDIR)\$(PROJ).LIB ..\lib\$(OUTDIR)
    copy $(PROJ).h ..\inc


clean:
     $(CLEANUP)
     if exist ..\lib\$(OUTDIR)/ del /q ..\lib\$(OUTDIR)\$(PROJ).lib
