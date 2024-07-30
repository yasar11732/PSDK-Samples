#----- Include the PSDK's WIN32.MAK to pick up defines-------------------
!include <win32.mak>

CLIENTPROJ = client
OLEIMPPROJ = oleimp

all:    $(OUTDIR) $(OUTDIR)\$(OLEIMPPROJ).exe $(OUTDIR)\$(CLIENTPROJ).exe

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

EXTRA_LIBS = odbccp32.lib odbc32.lib shell32.lib advapi32.lib



.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsdll) /D_WIN32_DCOM /D_MBCS /D_CONSOLE /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Client...
CLIENT_LINK32_OBJS = $(OUTDIR)\client.obj

$(OUTDIR)\$(CLIENTPROJ).exe:   $(CLIENT_LINK32_OBJS)
     $(link) $(ldebug) $(conlflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(CLIENTPROJ).pdb -out:$(OUTDIR)\$(CLIENTPROJ).exe $(CLIENT_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

# Server...
OLEIMP_LINK32_OBJS = $(OUTDIR)\util.obj \
              $(OUTDIR)\oleimp.obj

$(OUTDIR)\$(OLEIMPPROJ).exe:   $(OLEIMP_LINK32_OBJS)
     $(link) $(ldebug) $(guilflags) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(OLEIMPPROJ).pdb -out:$(OUTDIR)\$(OLEIMPPROJ).exe $(OLEIMP_LINK32_OBJS) $(EXTRA_LIBS) $(baselibs) $(olelibs) 

clean:
     $(CLEANUP)
