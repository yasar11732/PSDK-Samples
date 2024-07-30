#
# MAKEFILE
#
# Copyright (c)Microsoft Corporation, All Rights Reserved
#
 
target = consumer.exe

!ifndef NODEBUG
objdir=debug
!else
objdir=release
!endif

objlist = \
    $(objdir)\consumer.obj \

all: $(objdir)\$(target)

#---------------------------------------------------------------------


!if "$(CPU)"=="i386"
cc =  \
    cl -c -Od -D_MT -D_CONSOLE -DWIN32 -Z7 \
   -W3 -Di386=1 -D_X86_=1 -I.
!else
cc =  \
    cl -c -Od -D_MT -D_CONSOLE -DWIN32 -Z7 \
   -W3 -I.
!endif

link = \
    link -nodefaultlib -subsystem:console \
    -entry:mainCRTStartup -map:$(objdir)\mb.map -debug -debugtype:cv \
    -out:$(objdir)\$(target) \
	$(objlist) \
    wbemuuid.lib \
    libcmt.lib \
    kernel32.lib \
    uuid.lib \
    ole32.lib \
    oleaut32.lib \
    bufferoverflowu.lib


$(objdir)\$(target): $(objlist) 
   $(link) 

{.}.cpp{$(objdir)}.obj:
    if not exist $(objdir) md $(objdir)
    $(cc) $< -Fo$(objdir)\$(<B).obj


