
EdCommandsps.dll: dlldata.obj EdCommands_p.obj EdCommands_i.obj
	link /dll /out:EdCommandsps.dll /def:EdCommandsps.def /entry:DllMain dlldata.obj EdCommands_p.obj EdCommands_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EdCommandsps.dll
	@del EdCommandsps.lib
	@del EdCommandsps.exp
	@del dlldata.obj
	@del EdCommands_p.obj
	@del EdCommands_i.obj
