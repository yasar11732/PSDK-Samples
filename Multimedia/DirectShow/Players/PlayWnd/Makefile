#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=PlayWnd

BASEDIR=..\..\BaseClasses

LINK32_OBJS = \
	$(OUTDIR)\playwnd.obj \
	$(OUTDIR)\playwnd.res

LINK32_LIBS = \
	$(baselibs) \
	quartz.lib \
	winmm.lib \
	msacm32.lib \
	olepro32.lib \
	strmiids.lib \
	user32.lib \
	gdi32.lib \
	comdlg32.lib \
	ole32.lib \
	oleaut32.lib \
	uuid.lib 	

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).exe 

$(OUTDIR)\$(PROJECT).exe:	$(LINK32_OBJS) 
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).exe $(guilflags) /PDB:$(OUTDIR)\$(PROJECT).pdb /MACHINE:$(CPU) $(LINK32_LIBS) $(LINK32_OBJS)


.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I"$(DXSDK_DIR)\Include" $**


.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
