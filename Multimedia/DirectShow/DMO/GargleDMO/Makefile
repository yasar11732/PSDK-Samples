#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

DIRS= \
	ControlBase\~ \
	MedParamBase\~ \
	DMOBase\~ \

PROJECT=GargleDMO

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\GargleDMO.obj \
	$(OUTDIR)\GargDMOProp.obj \
	$(OUTDIR)\Gargle.obj \
	$(OUTDIR)\GargleDMO.res 

LINK32_LIBS = \
	shell32.lib \
	$(ole2libs) \
	msdmo.lib \
	dmoguids.lib \
	strmiids.lib \
	ControlBase\$(OUTDIR)\controlbase.lib \
	MedParamBase\$(OUTDIR)\medparambase.lib

all:	$(DIRS) $(OUTDIR) $(OUTDIR)\$(PROJECT).dll

$(DIRS):
!include <sdkbld.mak>


$(OUTDIR)\$(PROJECT).dll:	$(LINK32_OBJS)
	$(link) $(ldebug) /OUT:$(OUTDIR)\$(PROJECT).dll /DLL /PDB:$(OUTDIR)\$(PROJECT).pdb /DEF:$(PROJECT).def /MACHINE:$(CPU) $(LINK32_OBJS) $(LINK32_LIBS)

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_USRXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /IDMOBase /IMedParamBase /IControlBase /I"$(DXSDK_DIR)\Include" $**

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /I$(BASEDIR) /fo $@ $<

        
#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
