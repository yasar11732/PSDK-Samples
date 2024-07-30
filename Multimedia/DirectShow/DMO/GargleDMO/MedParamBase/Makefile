#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJECT=MedParamBase

DSHOWDIR=..\..

BASEDIR=$(DSHOWDIR)\BaseClasses

COMMONDIR=$(DSHOWDIR)\Common

LINK32_OBJS = \
	$(OUTDIR)\alist.obj \
	$(OUTDIR)\param.obj 

all:	$(OUTDIR) $(OUTDIR)\$(PROJECT).lib

$(OUTDIR)\$(PROJECT).lib:	$(LINK32_OBJS)
	$(link) /lib /OUT:$(OUTDIR)\$(PROJECT).lib /MACHINE:$(CPU) $(LINK32_OBJS) 

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /EHsc /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D_AFXDLL /D_MBCS /I$(BASEDIR) /I$(COMMONDIR) /I"$(DXSDK_DIR)\Include" $**



#$(OUTDIR)\alist.obj:	alist.cpp
#	$(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /Fp$(OUTDIR)\medparambase.pch /YX /GZ /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /D"_MBCS" /D"_LIB" /I..\..\..\..\..\..\include alist.cpp

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

clean:
        $(CLEANUP)
