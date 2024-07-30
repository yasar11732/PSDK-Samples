# Rules for compiling .cfgs from .xmls
.SUFFIXES: .cfg .h .xml .resx .resources

{..\}.xml{$(O)}.cfg:
    copy $** $(O)
	$(_TPG_ROOT)\Tools\gc.exe -h $*.h $*.xml

$(O)\AutoClaims.AutoClaims.resources:
	$(MANAGED_TOOL_PATH)\sdk\bin\resgen.exe /compile .\AutoClaims.resx,$(O)\AutoClaims.AutoClaims.resources



