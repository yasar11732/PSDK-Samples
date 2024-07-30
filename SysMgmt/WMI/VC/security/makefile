#***************************************************************************
#
#  Copyright (c)  Microsoft Corporation.
#
#  File:   makefile
#
#  Module: WMI Client Security Sample
#
#  Purpose: nmake makefile to build the WMI client security sample
#
#  History:
#
#***************************************************************************

TARGET  = Security.exe

goal:   $(TARGET)

OBJS   = $(OBJDIR)\Security.obj

LIBS = msvcrt.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib \
 advapi32.lib ole32.lib oleaut32.lib uuid.lib credui.lib wbemuuid.lib bufferoverflowu.lib

#
# Compiler and link flags
#

!ifndef NODEBUG
OBJDIR=debug
LINK    = -debug -debugtype:cv /NOD /entry:wmainCRTStartup
CFLAGS  = -c -Od -Z7 -W3 -nologo \
 -DWIN32 -DSTRICT -DDEBUG /D "_WIN32_DCOM" -D_UNICODE
!else
OBJDIR=release
LINK    = -debug:none  /NOD /entry:wmainCRTStartup
CFLAGS  = -c -Ot -W3 -nologo  \
 -DWIN32 -DSTRICT /D "_WIN32_DCOM"  -D_UNICODE -Dunicode
!endif #NODEBUG

cc = cl $(CFLAGS)

.cpp{$(OBJDIR)}.obj:
    if not exist $(OBJDIR) md $(OBJDIR)
    $(cc) $< -Fo$(OBJDIR)\$(<B).obj

$(TARGET) : $(OBJS) $(DEFFILE)
    link @<<    
    $(LINK)
    -out:$(OBJDIR)\$(TARGET)
    -subsystem:console,$(APPVER)
    $(OBJS)
    $(LIBS) 
<<

##### Dependencies #####

Security.obj   : Security.cpp
