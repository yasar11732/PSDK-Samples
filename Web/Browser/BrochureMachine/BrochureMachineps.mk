
BrochureMachineps.dll: dlldata.obj BrochureMachine_p.obj BrochureMachine_i.obj
	link /dll /out:BrochureMachineps.dll /def:BrochureMachineps.def /entry:DllMain dlldata.obj BrochureMachine_p.obj BrochureMachine_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BrochureMachineps.dll
	@del BrochureMachineps.lib
	@del BrochureMachineps.exp
	@del dlldata.obj
	@del BrochureMachine_p.obj
	@del BrochureMachine_i.obj
