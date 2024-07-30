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

PROJ = SampleRoute

all: $(OUTDIR) $(OUTDIR)\$(PROJ).dll

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\FaxSiren.obj 


BASE_OBJS  =
EXTRA_LIBS = winfax.lib user32.lib
GLOBAL_DEP = resource.h
RC_DEP     = resource.h


CFLG=$(cflags) -DUNICODE -D_UNICODE

# If $(OUTDIR) does not exist, then create
$(OUTDIR) :
  if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Inference rule for updating the object files
.cpp{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(CFLG) $(cvarsdll)  /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Build rule for resource file
$(OUTDIR)\$(PROJ).res: FaxSiren.Rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(PROJ).res FaxSiren.Rc

# Build rule for EXE
$(OUTDIR)\$(PROJ).dll: $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res
    $(link) $(linkdebug) $(dlllflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(OUTDIR)\$(PROJ).res $(conlibsdll) $(dlllibs) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).dll -def:FaxSiren.def


# Rules for cleaning out those old files
clean:
    $(CLEANUP)

!ELSE
!ENDIF