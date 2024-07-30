!MESSAGE Before you can compile ADOVCGEN you MUST make the following changes
!MESSAGE 
!MESSAGE Modify Line 9 of ADOHeader.h 
!MESSAGE to point to the correct location of MSADO15.dll
!MESSAGE 
!MESSAGE and modify line 11 of ADOHeader.h
!MESSAGE to point to the correct location of OLEDB32.dll
!MESSAGE
!MESSAGE Then uncomment the last lines of the makefile and you are ready to build
!MESSAGE 
!MESSAGE 
# When mofications are complete uncomment the lines below here
#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
#!include <win32.mak>
#
#PROJ = ADVCGEN
#all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe
#
#$(OUTDIR):
#     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
#
#LINK32_OBJS = $(OUTDIR)\stdafx.obj \
#              $(OUTDIR)\datagrid.obj \
#              $(OUTDIR)\advcgendlg.obj \
#              $(OUTDIR)\advcgen.obj \
#              $(OUTDIR)\advcgen.res
#
#$(OUTDIR)\stdafx.obj:     stdafx.cpp
#     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /D_MBCS /D_AFXDLL /Yc"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" stdafx.cpp
#
#.cpp{$(OUTDIR)}.obj:
#     $(cc) $(cflags) $(cdebug) $(cvarsdll) /Gm /GX /D_MBCS /D_AFXDLL /Yu"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**
#
#$(OUTDIR)\advcgen.res:
#     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\advcgen.res advcgen.rc
#
#$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
#     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) 
#
#clean:
#     $(CLEANUP)
