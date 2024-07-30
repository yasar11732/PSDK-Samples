
EDAnnotatorps.dll: dlldata.obj EDAnnotator_p.obj EDAnnotator_i.obj
	link /dll /out:EDAnnotatorps.dll /def:EDAnnotatorps.def /entry:DllMain dlldata.obj EDAnnotator_p.obj EDAnnotator_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EDAnnotatorps.dll
	@del EDAnnotatorps.lib
	@del EDAnnotatorps.exp
	@del dlldata.obj
	@del EDAnnotator_p.obj
	@del EDAnnotator_i.obj
