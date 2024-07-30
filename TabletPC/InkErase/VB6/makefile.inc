# Rules for compiling .cfgs from .xmls
.SUFFIXES: .cfg .h .xml .resx .resources

!if "$(BUILD_PASS)" == "PASS2"
BuildExe: $(O)\$(TARGETNAME).$(TARGETEXT)
	for /f "tokens=2 delims=()" %V in ('findstr AssemblyVersion $(_TPG_ROOT)\wisp\public\sdk\inc\tpcver.cs' ) do ..\stampver.exe -f"%V" -p"%V" $(O)\$(TARGETNAME).$(TARGETEXT) 
!else
BuildExe:
!endif
