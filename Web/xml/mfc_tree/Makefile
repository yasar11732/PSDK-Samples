!include <win32.mak>

PROJ=XMLTree
ALL : $(OUTDIR) $(OUTDIR)\$(PROJ).exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

LINK32_OBJS= \
	$(OUTDIR)\StdAfx.obj \
	$(OUTDIR)\XMLTree.obj  \
        $(OUTDIR)\XMLTreeDlg.obj \
        $(OUTDIR)\XMLTree.res


# Generic rule for building ALL CPP files and placing their OBJ's in the OUTDIR
$(OUTDIR)\stdafx.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Yc"stdafx.h" /Fp$(OUTDIR)\ /D_AFXDLL /D_MBCS stdafx.cpp

$(OUTDIR)\XMLTree.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Yu"stdafx.h" /Fp$(OUTDIR)\ /D_AFXDLL /D_MBCS XMLTree.cpp

$(OUTDIR)\XMLTreeDlg.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Yu"stdafx.h" /Fp$(OUTDIR)\ /D_AFXDLL /D_MBCS XMLTreeDlg.cpp

$(OUTDIR)\XMLTree.res:
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\XMLTree.res /I res /d _AFXDLL XMLTree.rc

$(OUTDIR)\$(PROJ).exe:  $(LINK32_OBJS)
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(PROJ).exe $(LINK32_OBJS) $(winlibs) 

CLEAN :
        $(CLEANUP)

