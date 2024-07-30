all:headdump.exe

!include <win32.mak>

lflags= /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO -subsystem:console,$(APPVER) -entry:mainCRTStartup
headdump.obj: headdump.cpp
    $(cc) $(cflags) $(cvars) $(cdebug) headdump.cpp

headdump.exe: headdump.obj
    $(link) $(lflags)  -out:headdump.exe headdump.obj wininet.lib  user32.lib kernel32.lib

clean:
    del *.exe
    del *.obj

