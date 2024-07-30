#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

PROJ = CmdLineConsumer
all:    $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = wbemuuid.lib rpcrt4.lib urlmon.lib oledlg.lib comsupp.lib comctl32.lib version.lib shell32.lib advapi32.lib mpr.lib netapi32.lib 

LINK32_OBJS = $(OUTDIR)\stdafx.obj \
              $(OUTDIR)\provider.obj \
              $(OUTDIR)\factory.obj \
              $(OUTDIR)\consumer.obj \
              $(OUTDIR)\cmdlineconsumerdlg.obj \
              $(OUTDIR)\cmdlineconsumer.obj \
              $(OUTDIR)\cmdlineconsumer.res

$(OUTDIR)\stdafx.obj:     stdafx.cpp
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /D_WIN32_DCOM /D_AFXDLL /Yc"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" stdafx.cpp

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /GX /D_WIN32_DCOM /D_AFXDLL /Yu"stdafx.h" /Fp"$(OUTDIR)\\" /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\cmdlineconsumer.res:
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\cmdlineconsumer.res cmdlineconsumer.rc

$(OUTDIR)\$(PROJ).exe:   $(LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
