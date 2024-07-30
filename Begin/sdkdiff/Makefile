# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 2002 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building makefile
!include <win32.mak>

PROJ = SDKDIFF 
!if "$(CPU)" == "i386"
all: $(OUTDIR) $(OUTDIR)\sdkdiff.exe $(OUTDIR)\sdkdiff.hlp
!else
all: $(OUTDIR) $(OUTDIR)\sdkdiff.exe
!endif

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    
#--------------------------------------------------------------------#
    
SOURCES=bar.cpp      \
        compitem.cpp \
        complist.cpp \
	errorout.cpp \
        file.cpp     \
	findgoto.cpp \
	gfile.cpp    \
	gutils.cpp   \
        line.cpp     \
	list.cpp     \
        profile.cpp  \
        scandir.cpp  \
        section.cpp  \
	status.cpp   \
	table.cpp    \
	tpaint.cpp   \
	tprint.cpp   \
	tree.cpp     \
	tscroll.cpp  \
	utils.cpp    \
        view.cpp     \
        sdkdiff.cpp   
    
OBJS=$(OUTDIR)\bar.obj      \
     $(OUTDIR)\compitem.obj \
     $(OUTDIR)\complist.obj \
     $(OUTDIR)\errorout.obj \
     $(OUTDIR)\file.obj     \
     $(OUTDIR)\findgoto.obj \
     $(OUTDIR)\gfile.obj    \
     $(OUTDIR)\gutils.obj   \
     $(OUTDIR)\line.obj     \
     $(OUTDIR)\list.obj     \
     $(OUTDIR)\profile.obj  \
     $(OUTDIR)\scandir.obj  \
     $(OUTDIR)\section.obj  \
     $(OUTDIR)\status.obj   \
     $(OUTDIR)\table.obj    \
     $(OUTDIR)\tpaint.obj   \
     $(OUTDIR)\tprint.obj   \
     $(OUTDIR)\tree.obj     \
     $(OUTDIR)\tscroll.obj  \
     $(OUTDIR)\utils.obj    \
     $(OUTDIR)\view.obj     \
     $(OUTDIR)\sdkdiff.obj   

PCH=$(OUTDIR)\precomp.obj

ELIBS=shell32.lib 

# Build rules for resource files
    
$(OUTDIR)\sdkdiff.res: sdkdiff.rc 
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\sdkdiff.res sdkdiff.rc

$(PCH):    
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\"  /Yc"precomp.h" precomp.cpp

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Yu"precomp.h" $**
    
$(OUTDIR)\sdkdiff.exe: $(PCH) $(OBJS) $(OUTDIR)\sdkdiff.res
	$(link) $(ldebug) $(guilibs) $(guiflags) /MACHINE:$(CPU) -out:$(OUTDIR)\sdkdiff.exe $(OBJS) $(ELIBS) /PDB:$(OUTDIR)\$(PROJ).PDB $(OUTDIR)\sdkdiff.res 
	
# Build rule for help file
$(OUTDIR)\sdkdiff.hlp: sdkdiff.rtf sdkdiff.hpj
    $(hc) -o .\$(OUTDIR)\sdkdiff.hlp $(hcvars) sdkdiff.hpj 
    copy sdkdiff.hlp $(OUTDIR)\sdkdiff.hlp

clean:
	$(CLEANUP)
