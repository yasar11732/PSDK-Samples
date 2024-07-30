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

PROJ = Simple

all: $(OUTDIR) $(OUTDIR)\$(PROJ).exe

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\Simple.obj 


BASE_OBJS  =
EXTRA_LIBS = winfax.lib Shell32.lib
GLOBAL_DEP = resource.h
RC_DEP     = resource.h


CFLG=$(cflags) -DUNICODE -D_UNICODE

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
  if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Inference rule for updating the object files
.c{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(CFLG) $(cvars)  /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\$(PROJ).res: Simple.Rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(PROJ).res Simple.Rc

# Build rule for EXE
$(OUTDIR)\$(PROJ).exe: $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res
    $(link) $(linkdebug) $(conflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(conlibs) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).exe


# Rules for cleaning out those old files
clean:
    $(CLEANUP)

!ELSE
!ENDIF