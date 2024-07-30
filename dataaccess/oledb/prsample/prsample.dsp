# Microsoft Developer Studio Project File - Name="prsample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=prsample - Win32 x86_debu
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "prsample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "prsample.mak" CFG="prsample - Win32 x86_debu"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "prsample - Win32 x86_debu" (based on "Win32 (x86) Console Application")
!MESSAGE "prsample - Win32 x86_rele" (based on "Win32 (x86) Console Application")
!MESSAGE "prsample - Win32 axp_debu" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "prsample - Win32 axp_rele" (based on "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "prsample"
# PROP BASE Intermediate_Dir "prsample"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86_debu"
# PROP Intermediate_Dir "x86_debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /Fd"Debug/prsample.pdb" /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /Fd"x86_debu/prsample.pdb" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "prsampl0"
# PROP BASE Intermediate_Dir "prsampl0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86_rele"
# PROP Intermediate_Dir "x86_rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "prsample"
# PROP BASE Intermediate_Dir "prsample"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "axp_debu"
# PROP Intermediate_Dir "axp_debu"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /Fd"x86_debu/prsample.pdb" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /Fd"x86_debu/prsample.pdb" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "prsampl0"
# PROP BASE Intermediate_Dir "prsampl0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "axp_rele"
# PROP Intermediate_Dir "axp_rele"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA

!ENDIF 

# Begin Target

# Name "prsample - Win32 x86_debu"
# Name "prsample - Win32 x86_rele"
# Name "prsample - Win32 axp_debu"
# Name "prsample - Win32 axp_rele"
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\prsample.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\command.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\datasource.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_DATAS=\
	".\prsample.h"\
	
NODEP_CPP_DATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_DATAS=\
	".\prsample.h"\
	
NODEP_CPP_DATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\enum.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_ENUM_=\
	".\prsample.h"\
	
NODEP_CPP_ENUM_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_ENUM_=\
	".\prsample.h"\
	
NODEP_CPP_ENUM_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\error.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_ERROR=\
	".\prsample.h"\
	
NODEP_CPP_ERROR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_ERROR=\
	".\prsample.h"\
	
NODEP_CPP_ERROR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_MAIN_=\
	".\prsample.h"\
	
NODEP_CPP_MAIN_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_MAIN_=\
	".\prsample.h"\
	
NODEP_CPP_MAIN_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rowset.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_ROWSE=\
	".\prsample.h"\
	
NODEP_CPP_ROWSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_ROWSE=\
	".\prsample.h"\
	
NODEP_CPP_ROWSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\session.cpp

!IF  "$(CFG)" == "prsample - Win32 x86_debu"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 x86_rele"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_debu"

DEP_CPP_SESSI=\
	".\prsample.h"\
	
NODEP_CPP_SESSI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "prsample - Win32 axp_rele"

DEP_CPP_SESSI=\
	".\prsample.h"\
	
NODEP_CPP_SESSI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	".\sdasql.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PRSample.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# End Target
# End Project
