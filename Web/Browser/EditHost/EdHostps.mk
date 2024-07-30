
EdHostps.dll: dlldata.obj EdHost_p.obj EdHost_i.obj
	link /dll /out:EdHostps.dll /def:EdHostps.def /entry:DllMain dlldata.obj EdHost_p.obj EdHost_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EdHostps.dll
	@del EdHostps.lib
	@del EdHostps.exp
	@del dlldata.obj
	@del EdHost_p.obj
	@del EdHost_i.obj
