#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

#
#       builds the sdkutil.LIB library
#


PROJ = sdkutil

all:  $(OUTDIR) $(OUTDIR)\$(PROJ).lib

$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    if not exist ..\lib mkdir ..\lib
    if not exist ..\lib\$(OUTDIR) mkdir ..\lib\$(OUTDIR)


LINK32_OBJS = $(OUTDIR)\altassrt.obj   \
               $(OUTDIR)\stablize.obj


.cxx{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /D_MBCS /D_CONSOLE /D_UNICODE /I"..\include" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


$(OUTDIR)\$(PROJ).lib:   $(LINK32_OBJS)
     lib  /MACHINE:$(CPU) /out:"$(OUTDIR)\$(PROJ).lib" $(LINK32_OBJS)  
    copy $(OUTDIR)\$(PROJ).lib ..\lib\$(OUTDIR)\

clean:
     $(CLEANUP)
     if exist ..\lib\$(OUTDIR)/ del /q ..\lib\$(OUTDIR)\$(PROJ).lib
