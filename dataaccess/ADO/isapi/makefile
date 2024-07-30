!MESSAGE Before you can compile DataAcADO you MUST make the following change
!MESSAGE 
!MESSAGE Modify Line 16 of ADOISAPI.CPP 
!MESSAGE to point to the correct location of MSADO15.DLL
!MESSAGE 
!MESSAGE Then uncomment the last lines of the makefile and you are ready to build
!MESSAGE 
!MESSAGE 
#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
#!include <win32.mak>
#
#PROJ = isapi
#all:    $(OUTDIR) $(OUTDIR)\$(PROJ).dll
#
#$(OUTDIR):
#     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
#
#EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib
#
#LINK32_OBJS = $(OUTDIR)\adoisapi.obj
#
#.cpp{$(OUTDIR)}.obj:
#     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /Gm /DISAPI_EXPORTS /D_USRDLL /D_MBCS /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**
#
#$(OUTDIR)\$(PROJ).dll:   $(LINK32_OBJS)
#     $(link) $(ldebug) $(dlllflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).dll /DEF:isapi.def  $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 
#
#clean:
#     $(CLEANUP)
