# Rules for compiling .cfgs from .xmls
.SUFFIXES: .cfg .h .xml .resx .resources

$(O)\InkClipboard.InkClipboard.resources:
	$(MANAGED_TOOL_PATH)\sdk\bin\resgen.exe /compile .\InkClipboard.resx,$(O)\InkClipboard.InkClipboard.resources

{..\}.xml{$(O)}.cfg:
    copy $** $(O)
	$(_TPG_ROOT)\Tools\gc.exe -h $*.h $*.xml

