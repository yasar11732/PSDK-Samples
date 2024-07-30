# Rules for compiling .cfgs from .xmls
.SUFFIXES: .cfg .h .xml .resx .resources

{..\}.xml{$(O)}.cfg:
    copy $** $(O)
	$(_TPG_ROOT)\Tools\gc.exe -h $*.h $*.xml

