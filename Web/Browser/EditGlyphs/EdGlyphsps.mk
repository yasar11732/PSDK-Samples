
EdGlyphsps.dll: dlldata.obj EdGlyphs_p.obj EdGlyphs_i.obj
	link /dll /out:EdGlyphsps.dll /def:EdGlyphsps.def /entry:DllMain dlldata.obj EdGlyphs_p.obj EdGlyphs_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EdGlyphsps.dll
	@del EdGlyphsps.lib
	@del EdGlyphsps.exp
	@del dlldata.obj
	@del EdGlyphs_p.obj
	@del EdGlyphs_i.obj
