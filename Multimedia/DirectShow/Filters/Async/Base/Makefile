#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

!ifndef NODEBUG
cflags=$(cflags) /DDEBUG
!endif

all:	$(OUTDIR) $(OUTDIR)\asynbase.lib 

$(OUTDIR)\asynbase.lib:	$(OUTDIR)\asyncio.obj $(OUTDIR)\asyncrdr.obj 
	$(link) /lib $(ldebug) /OUT:$(OUTDIR)\asynbase.lib /MACHINE:$(CPU) $(OUTDIR)\asyncio.obj $(OUTDIR)\asyncrdr.obj 

$(OUTDIR)\asyncio.obj:	asyncio.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /DSTRICT /D_MT /D_LIB /I..\..\..\BaseClasses /I..\include /I..\filter /I"$(DXSDK_DIR)\Include" asyncio.cpp

$(OUTDIR)\asyncrdr.obj:	asyncrdr.cpp
	$(cc) $(cflags) $(cdebug) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /DINC_OLE2 /DSTRICT /D_MT /D_LIB /I..\..\..\BaseClasses /I..\include /I..\filter /I"$(DXSDK_DIR)\Include" asyncrdr.cpp

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
