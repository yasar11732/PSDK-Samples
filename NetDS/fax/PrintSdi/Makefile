# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-2003  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

!IF ("$(TARGETOS)" == "WINNT")

PROJ = PrintSDI

all: $(OUTDIR) $(OUTDIR)\$(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\PrintSDI.obj \
	$(OUTDIR)\PrintSdiVw.obj \
	$(OUTDIR)\SdiDoc.obj \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\FaxDlg.obj \
	$(OUTDIR)\MainFrm.obj \
	$(OUTDIR)\NewDocDlg.obj		

BASE_OBJS  =
EXTRA_LIBS = winfax.lib mqrt.lib
GLOBAL_DEP = resource.h
RC_DEP     = resource.h


CFLG=$(cflags)

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
  if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Inference rule for updating the object files
.cpp{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(CFLG) $(cvars) /MD /D_AFXDLL /D_MBCS /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\afxprint.res: afxprint.rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /d_AFXDLL /fo $(OUTDIR)\afxprint.res afxprint.rc

$(OUTDIR)\afxres.res:afxres.rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /d_AFXDLL /fo $(OUTDIR)\afxres.res afxres.rc

$(OUTDIR)\$(PROJ).res: PrintSdi.Rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /d_AFXDLL /fo $(OUTDIR)\$(PROJ).res PrintSdi.Rc

# Build rule for EXE
$(OUTDIR)\$(PROJ).EXE: $(BASE_OBJS) $(LINK32_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(OUTDIR)\afxprint.res $(OUTDIR)\afxres.res
    $(link) $(linkdebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).exe $(MAPFILE)


# Rules for cleaning out those old files
clean:
    $(CLEANUP)

!ELSE
!ENDIF