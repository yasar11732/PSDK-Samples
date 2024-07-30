# Rules for compiling .cfgs from .xmls
.SUFFIXES: .cfg .h .xml .resx .resources

{}.resx{$(O)}.resources:
	$(MANAGED_TOOL_PATH)\sdk\bin\resgen.exe /compile $**,$*.resources

{..\}.xml{$(O)}.cfg:
    copy $** $(O)
	$(_TPG_ROOT)\Tools\gc.exe -h $*.h $*.xml

