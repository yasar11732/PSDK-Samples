/*************************************************************************
**
**    OLE 2.0 Utilities
**
**    olestd.h
**
**    This file contains file contains data structure defintions,
**    function prototypes, constants, etc. for the common OLE 2.0
**    utilities.
**
**    These utilities include the following:
**          Debuging Assert/Verify macros
**          HIMETRIC conversion routines
**          reference counting debug support
**          OleStd API's for common compound-document app support
**
**    (c) Copyright Microsoft Corp. 1990 - 2000 All Rights Reserved
**
*************************************************************************/

#if !defined( _OLESTD_H_ )
#define _OLESTD_H_

#if !defined(__cplusplus) && !defined( __TURBOC__)
#define NONAMELESSUNION     // use strict ANSI standard (for DVOBJ.H)
#endif

#include <windows.h>
#include <shellapi.h>
#include <ole2.h>
#include <string.h>
#include <dlgs.h>           //For fileopen dlg; standard include
#include "ansiapi.h"
#include "oledlg.h"

/*************************************************************************
** DEBUG ASSERTION ROUTINES
*************************************************************************/

#if DBG
#include <assert.h>
#define FnAssert(lpstrExpr, lpstrMsg, lpstrFileName, iLine)     \
        (_assert(lpstrMsg ? lpstrMsg : lpstrExpr,               \
                 lpstrFileName,                                 \
                 iLine), NOERROR)
#endif //DBG

// BEGINING OF OLD OLESTD.H FILE
#if defined( __TURBOC__ ) || defined( WIN32 )
#define _based(a)
#endif

#ifndef RC_INVOKED
#include <dos.h>        // needed for filetime
#endif  /* RC_INVOKED */

#include <commdlg.h>    // needed for LPPRINTDLG
#include <shellapi.h>   // needed for HKEY
#include "ansiapi.h"

// String table defines...
#define  IDS_OLESTDNOCREATEFILE   700
#define  IDS_OLESTDNOOPENFILE     701
#define  IDS_OLESTDDISKFULL       702


/*
 * Some C interface declaration stuff
 */

#if ! defined(__cplusplus)
typedef struct tagINTERFACEIMPL {
      IUnknownVtbl FAR*       lpVtbl;
      LPVOID                  lpBack;
      int                     cRef;   // interface specific ref count.
} INTERFACEIMPL, FAR* LPINTERFACEIMPL;

#define INIT_INTERFACEIMPL(lpIFace, pVtbl, pBack)   \
      ((lpIFace)->lpVtbl = pVtbl, \
         ((LPINTERFACEIMPL)(lpIFace))->lpBack = (LPVOID)pBack,   \
         ((LPINTERFACEIMPL)(lpIFace))->cRef = 0  \
      )

#if defined( _DEBUG )
#define OleDbgQueryInterfaceMethod(lpUnk)   \
      ((lpUnk) != NULL ? ((LPINTERFACEIMPL)(lpUnk))->cRef++ : 0)
#define OleDbgAddRefMethod(lpThis, iface)   \
      ((LPINTERFACEIMPL)(lpThis))->cRef++

#if _DEBUGLEVEL >= 2
#define OleDbgReleaseMethod(lpThis, iface) \
      (--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
         OleDbgOut("\t" iface "* RELEASED (cRef == 0)\r\n"),1 : \
          (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
            ( \
               DebugBreak(), \
               OleDbgOut(  \
                  "\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
            ),1 : \
            1)

#else       // if _DEBUGLEVEL < 2
#define OleDbgReleaseMethod(lpThis, iface) \
      (--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
         1 : \
          (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
            ( \
               OleDbgOut(  \
                  "\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
      ),1 : \
            1)

#endif      // if _DEBUGLEVEL < 2

#else       // ! defined (_DEBUG)

#define OleDbgQueryInterfaceMethod(lpUnk)
#define OleDbgAddRefMethod(lpThis, iface)
#define OleDbgReleaseMethod(lpThis, iface)

#endif      // if defined( _DEBUG )

#endif      // ! defined(__cplusplus)

/*
 * Some docfiles stuff
 */

#define STGM_DFRALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_DENY_WRITE)
#define STGM_DFALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE)
#define STGM_SALL (STGM_READWRITE | STGM_SHARE_EXCLUSIVE)

/*
 * Some Concurrency stuff
 */

/* standard Delay (in msec) to wait before retrying an LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDRETRYDELAY    (DWORD)5000

/* Cancel the pending outgoing LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDCANCELRETRY   (DWORD)-1

/*
 * Some Icon support stuff.
 *
 * The following API's are now OBSOLETE because equivalent API's have been
 * added to the OLE2.DLL library
 *      GetIconOfFile       superceeded by OleGetIconOfFile
 *      GetIconOfClass      superceeded by OleGetIconOfClass
 *      OleUIMetafilePictFromIconAndLabel
 *                          superceeded by OleMetafilePictFromIconAndLabel
 *
 * The following macros are defined for backward compatibility with previous
 * versions of the OLE2UI library. It is recommended that the new Ole* API's
 * should be used instead.
 */
#define GetIconOfFile(hInst, lpszFileName, fUseFileAsLabel) \
   OleGetIconOfFile(lpszFileName, fUseFileAsLabel)

#define GetIconOfClass(hInst, rclsid, lpszLabel, fUseTypeAsLabel) \
   OleGetIconOfClass(rclsid, lpszLabel, fUseTypeAsLabel)

#define OleUIMetafilePictFromIconAndLabel(hIcon,pszLabel,pszSourceFile,iIcon)\
   OleMetafilePictFromIconAndLabel(hIcon, pszLabel, pszSourceFile, iIcon)


/*
 * Some Clipboard Copy/Paste & Drag/Drop support stuff
 */

//Macro to set all FormatEtc fields
#define SETFORMATETC(fe, cf, asp, td, med, li)   \
   ((fe).cfFormat=cf, \
    (fe).dwAspect=asp, \
    (fe).ptd=td, \
    (fe).tymed=med, \
    (fe).lindex=li)

//Macro to set interesting FormatEtc fields defaulting the others.
#define SETDEFAULTFORMATETC(fe, cf, med)  \
   ((fe).cfFormat=cf, \
    (fe).dwAspect=DVASPECT_CONTENT, \
    (fe).ptd=NULL, \
    (fe).tymed=med, \
    (fe).lindex=-1)

// Macro to test if two FormatEtc structures are an exact match
#define IsEqualFORMATETC(fe1, fe2)  \
   (OleStdCompareFormatEtc(&(fe1), &(fe2))==0)

// Clipboard format strings
#define CF_EMBEDSOURCE      TEXT("Embed Source")
#define CF_EMBEDDEDOBJECT   TEXT("Embedded Object")
#define CF_LINKSOURCE       TEXT("Link Source")
#define CF_CUSTOMLINKSOURCE TEXT("Custom Link Source")
#define CF_OBJECTDESCRIPTOR TEXT("Object Descriptor")
#define CF_LINKSRCDESCRIPTOR TEXT("Link Source Descriptor")
#define CF_OWNERLINK        TEXT("OwnerLink")
#define CF_FILENAME         TEXT("FileName")

#define OleStdQueryOleObjectData(lpformatetc)   \
   (((lpformatetc)->tymed & TYMED_ISTORAGE) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryLinkSourceData(lpformatetc)   \
   (((lpformatetc)->tymed & TYMED_ISTREAM) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryObjectDescriptorData(lpformatetc)    \
   (((lpformatetc)->tymed & TYMED_HGLOBAL) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryFormatMedium(lpformatetc, tymd)  \
   (((lpformatetc)->tymed & tymd) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

// Make an independent copy of a MetafilePict
#define OleStdCopyMetafilePict(hpictin, phpictout)  \
   (*(phpictout) = OleDuplicateData(hpictin,CF_METAFILEPICT,GHND|GMEM_SHARE))


// REVIEW: these need to be added to OLE2.H
#if !defined( DD_DEFSCROLLINTERVAL )
#define DD_DEFSCROLLINTERVAL    50
#endif

#if !defined( DD_DEFDRAGDELAY )
#define DD_DEFDRAGDELAY         200
#endif

#if !defined( DD_DEFDRAGMINDIST )
#define DD_DEFDRAGMINDIST       2
#endif


/* OleStdGetDropEffect
** -------------------
**
** Convert a keyboard state into a DROPEFFECT.
**
** returns the DROPEFFECT value derived from the key state.
**    the following is the standard interpretation:
**          no modifier -- Default Drop     (NULL is returned)
**          CTRL        -- DROPEFFECT_COPY
**          SHIFT       -- DROPEFFECT_MOVE
**          CTRL-SHIFT  -- DROPEFFECT_LINK
**
**    Default Drop: this depends on the type of the target application.
**    this is re-interpretable by each target application. a typical
**    interpretation is if the drag is local to the same document
**    (which is source of the drag) then a MOVE operation is
**    performed. if the drag is not local, then a COPY operation is
**    performed.
*/
#define OleStdGetDropEffect(grfKeyState)    \
   ( (grfKeyState & MK_CONTROL) ?          \
      ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_LINK : DROPEFFECT_COPY ) :  \
      ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_MOVE : 0 ) )


#define OLESTDDROP_NONE         0
#define OLESTDDROP_DEFAULT      1
#define OLESTDDROP_NONDEFAULT   2


/*
 * Some misc stuff
 */

#define EMBEDDINGFLAG "Embedding"     // Cmd line switch for launching a srvr

#define HIMETRIC_PER_INCH   2540      // number HIMETRIC units per inch
#define PTS_PER_INCH        72        // number points (font size) per inch

#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)

// Returns TRUE if all fields of the two Rect's are equal, else FALSE.
#define AreRectsEqual(lprc1, lprc2)     \
   (((lprc1->top == lprc2->top) &&     \
     (lprc1->left == lprc2->left) &&   \
     (lprc1->right == lprc2->right) && \
     (lprc1->bottom == lprc2->bottom)) ? TRUE : FALSE)

#define LSTRCPYN(lpdst, lpsrc, cch) \
(\
   (lpdst)[(cch)-1] = '\0', \
   ((cch)>1 ? _fstrncpy(lpdst, lpsrc, (cch)-1) : 0)\
)



/****** DEBUG Stuff *****************************************************/

#ifdef _DEBUG

#if !defined( _DBGTRACE )
#define _DEBUGLEVEL 2
#else
#define _DEBUGLEVEL _DBGTRACE
#endif


#if defined( NOASSERT )

#define OLEDBGASSERTDATA
#define OleDbgAssert(a)
#define OleDbgAssertSz(a, b)
#define OleDbgVerify(a)
#define OleDbgVerifySz(a, b)

#else   // ! NOASSERT

#define OLEDBGASSERTDATA    \
      static char _based(_segname("_CODE")) _szAssertFile[]= __FILE__;

#define OleDbgAssert(a) \
      (!(a) ? FnAssert(#a, NULL, _szAssertFile, __LINE__) : (HRESULT)1)

#define OleDbgAssertSz(a, b)    \
      (!(a) ? FnAssert(#a, b, _szAssertFile, __LINE__) : (HRESULT)1)

#define OleDbgVerify(a) \
      OleDbgAssert(a)

#define OleDbgVerifySz(a, b)    \
      OleDbgAssertSz(a, b)

#endif  // ! NOASSERT


#define OLEDBGDATA_MAIN(szPrefix)   \
      char near g_szDbgPrefix[] = szPrefix;    \
      OLEDBGASSERTDATA
#define OLEDBGDATA  \
      extern char near g_szDbgPrefix[];    \
      OLEDBGASSERTDATA

#define OLEDBG_BEGIN(lpsz) \
      OleDbgPrintAlways(g_szDbgPrefix,lpsz,1);

#define OLEDBG_END  \
      OleDbgPrintAlways(g_szDbgPrefix,"End\r\n",-1);

#define OleDbgOut(lpsz) \
      OleDbgPrintAlways(g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix(lpsz) \
      OleDbgPrintAlways("",lpsz,0)

#define OleDbgOutRefCnt(lpsz,lpObj,refcnt)      \
      OleDbgPrintRefCntAlways(g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect(lpsz,lpRect)      \
      OleDbgPrintRectAlways(g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOutHResult(lpsz,hr)   \
      OleDbgPrintScodeAlways(g_szDbgPrefix,lpsz,GetScode(hr))

#define OleDbgOutScode(lpsz,sc) \
      OleDbgPrintScodeAlways(g_szDbgPrefix,lpsz,sc)

#define OleDbgOut1(lpsz)    \
      OleDbgPrint(1,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix1(lpsz)    \
      OleDbgPrint(1,"",lpsz,0)

#define OLEDBG_BEGIN1(lpsz)    \
      OleDbgPrint(1,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END1 \
      OleDbgPrint(1,g_szDbgPrefix,"End\r\n",-1);

#define OleDbgOutRefCnt1(lpsz,lpObj,refcnt)     \
      OleDbgPrintRefCnt(1,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect1(lpsz,lpRect)     \
      OleDbgPrintRect(1,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut2(lpsz)    \
      OleDbgPrint(2,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix2(lpsz)    \
      OleDbgPrint(2,"",lpsz,0)

#define OLEDBG_BEGIN2(lpsz)    \
      OleDbgPrint(2,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END2 \
      OleDbgPrint(2,g_szDbgPrefix,"End\r\n",-1);

#define OleDbgOutRefCnt2(lpsz,lpObj,refcnt)     \
      OleDbgPrintRefCnt(2,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect2(lpsz,lpRect)     \
      OleDbgPrintRect(2,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut3(lpsz)    \
      OleDbgPrint(3,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix3(lpsz)    \
      OleDbgPrint(3,"",lpsz,0)

#define OLEDBG_BEGIN3(lpsz)    \
      OleDbgPrint(3,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END3 \
      OleDbgPrint(3,g_szDbgPrefix,"End\r\n",-1);

#define OleDbgOutRefCnt3(lpsz,lpObj,refcnt)     \
      OleDbgPrintRefCnt(3,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect3(lpsz,lpRect)     \
      OleDbgPrintRect(3,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut4(lpsz)    \
      OleDbgPrint(4,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix4(lpsz)    \
      OleDbgPrint(4,"",lpsz,0)

#define OLEDBG_BEGIN4(lpsz)    \
      OleDbgPrint(4,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END4 \
      OleDbgPrint(4,g_szDbgPrefix,"End\r\n",-1);

#define OleDbgOutRefCnt4(lpsz,lpObj,refcnt)     \
      OleDbgPrintRefCnt(4,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect4(lpsz,lpRect)     \
      OleDbgPrintRect(4,g_szDbgPrefix,lpsz,lpRect)

#else   //  !_DEBUG

#define OLEDBGDATA_MAIN(szPrefix)
#define OLEDBGDATA
#define OleDbgAssert(a)
#define OleDbgAssertSz(a, b)
#define OleDbgVerify(a)         (a)
#define OleDbgVerifySz(a, b)    (a)
#define OleDbgOutHResult(lpsz,hr)
#define OleDbgOutScode(lpsz,sc)
#define OLEDBG_BEGIN(lpsz)
#define OLEDBG_END
#define OleDbgOut(lpsz)
#define OleDbgOut1(lpsz)
#define OleDbgOut2(lpsz)
#define OleDbgOut3(lpsz)
#define OleDbgOut4(lpsz)
#define OleDbgOutNoPrefix(lpsz)
#define OleDbgOutNoPrefix1(lpsz)
#define OleDbgOutNoPrefix2(lpsz)
#define OleDbgOutNoPrefix3(lpsz)
#define OleDbgOutNoPrefix4(lpsz)
#define OLEDBG_BEGIN1(lpsz)
#define OLEDBG_BEGIN2(lpsz)
#define OLEDBG_BEGIN3(lpsz)
#define OLEDBG_BEGIN4(lpsz)
#define OLEDBG_END1
#define OLEDBG_END2
#define OLEDBG_END3
#define OLEDBG_END4
#define OleDbgOutRefCnt(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt1(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt2(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt3(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt4(lpsz,lpObj,refcnt)
#define OleDbgOutRect(lpsz,lpRect)
#define OleDbgOutRect1(lpsz,lpRect)
#define OleDbgOutRect2(lpsz,lpRect)
#define OleDbgOutRect3(lpsz,lpRect)
#define OleDbgOutRect4(lpsz,lpRect)

#endif  //  _DEBUG


/*************************************************************************
** Function prototypes
*************************************************************************/


//OLESTD.C
STDAPI_(int) SetDCToAnisotropic(HDC hDC, LPRECT lprcPhysical, LPRECT lprcLogical, LPRECT lprcWindowOld, LPRECT lprcViewportOld);
STDAPI_(int) SetDCToDrawInHimetricRect(HDC, LPRECT, LPRECT, LPRECT, LPRECT);
STDAPI_(int) ResetOrigDC(HDC, int, LPRECT, LPRECT);

STDAPI_(int)        XformWidthInHimetricToPixels(HDC, int);
STDAPI_(int)        XformWidthInPixelsToHimetric(HDC, int);
STDAPI_(int)        XformHeightInHimetricToPixels(HDC, int);
STDAPI_(int)        XformHeightInPixelsToHimetric(HDC, int);

STDAPI_(void) XformRectInPixelsToHimetric(HDC, LPRECT, LPRECT);
STDAPI_(void) XformRectInHimetricToPixels(HDC, LPRECT, LPRECT);
STDAPI_(void) XformSizeInPixelsToHimetric(HDC, LPSIZEL, LPSIZEL);
STDAPI_(void) XformSizeInHimetricToPixels(HDC, LPSIZEL, LPSIZEL);
STDAPI_(int) XformWidthInHimetricToPixels(HDC, int);
STDAPI_(int) XformWidthInPixelsToHimetric(HDC, int);
STDAPI_(int) XformHeightInHimetricToPixels(HDC, int);
STDAPI_(int) XformHeightInPixelsToHimetric(HDC, int);

STDAPI_(void) ParseCmdLine(LPSTR, BOOL FAR *, LPSTR);

STDAPI_(BOOL) OleStdIsOleLink(LPUNKNOWN lpUnk);
STDAPI_(LPUNKNOWN) OleStdQueryInterface(LPUNKNOWN lpUnk, REFIID riid);
STDAPI_(LPSTORAGE) OleStdCreateRootStorage(LPOLESTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdOpenRootStorage(LPOLESTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdOpenOrCreateRootStorage(LPOLESTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdCreateChildStorage(LPSTORAGE lpStg, LPOLESTR lpszStgName);
STDAPI_(LPSTORAGE) OleStdOpenChildStorage(LPSTORAGE lpStg, LPOLESTR lpszStgName, DWORD grfMode);
STDAPI_(BOOL) OleStdCommitStorage(LPSTORAGE lpStg);
STDAPI OleStdDestroyAllElements(LPSTORAGE lpStg);

STDAPI_(LPSTORAGE) OleStdCreateStorageOnHGlobal(
      HANDLE hGlobal,
      BOOL fDeleteOnRelease,
      DWORD dwgrfMode
);
STDAPI_(LPSTORAGE) OleStdCreateTempStorage(BOOL fUseMemory, DWORD grfMode);
STDAPI OleStdDoConvert(LPSTORAGE lpStg, REFCLSID rClsidNew);
STDAPI_(BOOL) OleStdGetTreatAsFmtUserType(
      REFCLSID        rClsidApp,
      LPSTORAGE       lpStg,
      CLSID FAR*      lpclsid,
      CLIPFORMAT FAR* lpcfFmt,
      LPOLESTR FAR*      lplpszType
);
STDAPI OleStdDoTreatAsClass(LPOLESTR lpszUserType, REFCLSID rclsid, REFCLSID rclsidNew);
STDAPI_(BOOL) OleStdSetupAdvises(LPOLEOBJECT lpOleObject, DWORD dwDrawAspect,
               LPOLESTR lpszContainerApp, LPOLESTR lpszContainerObj,
               LPADVISESINK lpAdviseSink, BOOL fCreate);
STDAPI OleStdSwitchDisplayAspect(
      LPOLEOBJECT             lpOleObj,
      LPDWORD                 lpdwCurAspect,
      DWORD                   dwNewAspect,
      HGLOBAL                 hMetaPict,
      BOOL                    fDeleteOldAspect,
      BOOL                    fSetupViewAdvise,
      LPADVISESINK            lpAdviseSink,
      BOOL FAR*               lpfMustUpdate
);
STDAPI OleStdSetIconInCache(LPOLEOBJECT lpOleObj, HGLOBAL hMetaPict);
STDAPI_(HGLOBAL) OleStdGetData(
      LPDATAOBJECT        lpDataObj,
      CLIPFORMAT          cfFormat,
      DVTARGETDEVICE FAR* lpTargetDevice,
      DWORD               dwAspect,
      LPSTGMEDIUM         lpMedium
);
STDAPI_(void) OleStdMarkPasteEntryList(
      LPDATAOBJECT        lpSrcDataObj,
      LPOLEUIPASTEENTRY   lpPriorityList,
      int                 cEntries
);
STDAPI_(int) OleStdGetPriorityClipboardFormat(
      LPDATAOBJECT        lpSrcDataObj,
      LPOLEUIPASTEENTRY   lpPriorityList,
      int                 cEntries
);
STDAPI_(BOOL) OleStdIsDuplicateFormat(
      LPFORMATETC         lpFmtEtc,
      LPFORMATETC         arrFmtEtc,
      int                 nFmtEtc
);
STDAPI_(void) OleStdRegisterAsRunning(LPUNKNOWN lpUnk, LPMONIKER lpmkFull, DWORD FAR* lpdwRegister);
STDAPI_(void) OleStdRevokeAsRunning(DWORD FAR* lpdwRegister);
STDAPI_(void) OleStdNoteFileChangeTime(LPOLESTR lpszFileName, DWORD dwRegister);
STDAPI_(void) OleStdNoteObjectChangeTime(DWORD dwRegister);
STDAPI OleStdGetOleObjectData(
      LPPERSISTSTORAGE    lpPStg,
      LPFORMATETC         lpformatetc,
      LPSTGMEDIUM         lpMedium,
      BOOL                fUseMemory
);
STDAPI OleStdGetLinkSourceData(
      LPMONIKER           lpmk,
      LPCLSID             lpClsID,
      LPFORMATETC         lpformatetc,
      LPSTGMEDIUM         lpMedium
);
STDAPI_(HGLOBAL) OleStdGetObjectDescriptorData(
      CLSID               clsid,
      DWORD               dwAspect,
      SIZEL               sizel,
      POINTL              pointl,
      DWORD               dwStatus,
      LPOLESTR            lpszFullUserTypeName,
      LPOLESTR            lpszSrcOfCopy
);
STDAPI_(HGLOBAL) OleStdGetObjectDescriptorDataFromOleObject(
      LPOLEOBJECT         lpOleObj,
      LPOLESTR            lpszSrcOfCopy,
      DWORD               dwAspect,
      POINTL              pointl,
      LPSIZEL             lpSizelHim
);
STDAPI_(HGLOBAL) OleStdFillObjectDescriptorFromData(
      LPDATAOBJECT       lpDataObject,
      LPSTGMEDIUM        lpmedium,
      CLIPFORMAT FAR*    lpcfFmt
);
STDAPI_(HANDLE) OleStdGetMetafilePictFromOleObject(
      LPOLEOBJECT         lpOleObj,
      DWORD               dwDrawAspect,
      LPSIZEL             lpSizelHim,
      DVTARGETDEVICE FAR* ptd
);

STDAPI_(void) OleStdCreateTempFileMoniker(LPOLESTR lpszPrefixString, UINT FAR* lpuUnique, LPOLESTR lpszName, LPMONIKER FAR* lplpmk);
STDAPI_(LPMONIKER) OleStdGetFirstMoniker(LPMONIKER lpmk);
STDAPI_(ULONG) OleStdGetLenFilePrefixOfMoniker(LPMONIKER lpmk);
STDAPI OleStdMkParseDisplayName(
      REFCLSID        rClsid,
      LPBC            lpbc,
      LPOLESTR        lpszUserName,
      ULONG FAR*      lpchEaten,
      LPMONIKER FAR*  lplpmk
);
STDAPI_(LPVOID) OleStdMalloc(ULONG ulSize);
STDAPI_(LPVOID) OleStdRealloc(LPVOID pmem, ULONG ulSize);
STDAPI_(void) OleStdFree(LPVOID pmem);
STDAPI_(ULONG) OleStdGetSize(LPVOID pmem);
STDAPI_(void) OleStdFreeString(LPOLESTR lpsz, LPMALLOC lpMalloc);
STDAPI_(LPOLESTR) OleStdCopyString(LPOLESTR lpszSrc, LPMALLOC lpMalloc);
STDAPI_(ULONG) OleStdGetItemToken(LPOLESTR lpszSrc, LPOLESTR lpszDst,int nMaxChars);

STDAPI_(UINT)     OleStdIconLabelTextOut(HDC        hDC,
                               HFONT      hFont,
                               int        nXStart,
                               int        nYStart,
                               UINT       fuOptions,
                               RECT FAR * lpRect,
                               LPOLESTR   lpszString,
                               UINT       cchString,
                               int FAR *  lpDX);

// registration database query functions
STDAPI_(UINT)     OleStdGetAuxUserType(REFCLSID rclsid,
                             WORD   wAuxUserType,
                             LPOLESTR  lpszAuxUserType,
                             int    cch,
                             HKEY   hKey);

STDAPI_(UINT)     OleStdGetUserTypeOfClass(REFCLSID rclsid,
                                 LPOLESTR lpszUserType,
                                 UINT cch,
                                 HKEY hKey);

STDAPI_(BOOL) OleStdGetMiscStatusOfClass(REFCLSID, HKEY, DWORD FAR *);
STDAPI_(CLIPFORMAT) OleStdGetDefaultFileFormatOfClass(
      REFCLSID        rclsid,
      HKEY            hKey
);

STDAPI_(void) OleStdInitVtbl(LPVOID lpVtbl, UINT nSizeOfVtbl);
STDMETHODIMP OleStdNullMethod(LPUNKNOWN lpThis);
STDAPI_(BOOL) OleStdCheckVtbl(LPVOID lpVtbl, UINT nSizeOfVtbl, LPOLESTR lpszIface);
STDAPI_(ULONG) OleStdVerifyRelease(LPUNKNOWN lpUnk, LPOLESTR lpszMsg);
STDAPI_(ULONG) OleStdRelease(LPUNKNOWN lpUnk);

STDAPI_(HDC) OleStdCreateDC(DVTARGETDEVICE FAR* ptd);
STDAPI_(HDC) OleStdCreateIC(DVTARGETDEVICE FAR* ptd);
STDAPI_(DVTARGETDEVICE FAR*) OleStdCreateTargetDevice(LPPRINTDLG lpPrintDlg);
STDAPI_(BOOL) OleStdDeleteTargetDevice(DVTARGETDEVICE FAR* ptd);
STDAPI_(DVTARGETDEVICE FAR*) OleStdCopyTargetDevice(DVTARGETDEVICE FAR* ptdSrc);
STDAPI_(BOOL) OleStdCopyFormatEtc(LPFORMATETC petcDest, LPFORMATETC petcSrc);
STDAPI_(int) OleStdCompareFormatEtc(FORMATETC FAR* pFetcLeft, FORMATETC FAR* pFetcRight);
STDAPI_(BOOL) OleStdCompareTargetDevice
   (DVTARGETDEVICE FAR* ptdLeft, DVTARGETDEVICE FAR* ptdRight);


STDAPI_(void) OleDbgPrint(
      int     nDbgLvl,
      LPSTR   lpszPrefix,
      LPSTR   lpszMsg,
      int     nIndent
);
STDAPI_(void) OleDbgPrintAlways(LPSTR lpszPrefix, LPSTR lpszMsg, int nIndent);
STDAPI_(void) OleDbgSetDbgLevel(int nDbgLvl);
STDAPI_(int) OleDbgGetDbgLevel( void );
STDAPI_(void) OleDbgIndent(int n);
STDAPI_(void) OleDbgPrintRefCnt(
      int         nDbgLvl,
      LPSTR       lpszPrefix,
      LPSTR       lpszMsg,
      LPVOID      lpObj,
      ULONG       refcnt
);
STDAPI_(void) OleDbgPrintRefCntAlways(
      LPSTR       lpszPrefix,
      LPSTR       lpszMsg,
      LPVOID      lpObj,
      ULONG       refcnt
);
STDAPI_(void) OleDbgPrintRect(
      int         nDbgLvl,
      LPSTR       lpszPrefix,
      LPSTR       lpszMsg,
      LPRECT      lpRect
);
STDAPI_(void) OleDbgPrintRectAlways(
      LPSTR       lpszPrefix,
      LPSTR       lpszMsg,
      LPRECT      lpRect
);
STDAPI_(void) OleDbgPrintScodeAlways(LPSTR lpszPrefix, LPSTR lpszMsg, SCODE sc);


STDAPI_(LPENUMFORMATETC)
  OleStdEnumFmtEtc_Create(ULONG nCount, LPFORMATETC lpEtc);

STDAPI_(LPENUMSTATDATA)
  OleStdEnumStatData_Create(ULONG nCount, LPSTATDATA lpStat);

STDAPI_(BOOL)
  OleStdCopyStatData(LPSTATDATA pDest, LPSTATDATA pSrc);

STDAPI_(HPALETTE)
  OleStdCreateStandardPalette(void);

#if defined( OBSOLETE )

/*************************************************************************
** The following API's have been converted into macros:
**          OleStdQueryOleObjectData
**          OleStdQueryLinkSourceData
**          OleStdQueryObjectDescriptorData
**          OleStdQueryFormatMedium
**          OleStdCopyMetafilePict
**          AreRectsEqual
**          OleStdGetDropEffect
**
**    These macros are defined above
*************************************************************************/
STDAPI_(BOOL) AreRectsEqual(LPRECT lprc1, LPRECT lprc2);
STDAPI_(BOOL) OleStdCopyMetafilePict(HANDLE hpictin, HANDLE FAR* phpictout);
STDAPI OleStdQueryOleObjectData(LPFORMATETC lpformatetc);
STDAPI OleStdQueryLinkSourceData(LPFORMATETC lpformatetc);
STDAPI OleStdQueryObjectDescriptorData(LPFORMATETC lpformatetc);
STDAPI OleStdQueryFormatMedium(LPFORMATETC lpformatetc, TYMED tymed);
STDAPI_(DWORD) OleStdGetDropEffect ( DWORD grfKeyState );
#endif  // OBSOLETE

// END OF OLD OLESTD.H FILE

#define UPDATELINKS_STARTDELAY 2000 // delay before first link

#ifdef __TURBOC__
#define _getcwd getcwd
#define _itoa   itoa
#define __max   max
#define _find_t find_t
#endif // __TURBOC__

#ifdef WIN32
#define _fmemset memset
#define _fmemcpy memcpy
#define _fmemcmp memcmp
#define _fstrcpy strcpy
#define _fstrncpy strncpy
#define _fstrlen strlen
#define _fstrrchr strrchr
#define _fstrtok strtok
#endif  // WIN32

#if !defined( EXPORT )
#ifdef WIN32
#define EXPORT
#else
#define EXPORT  __export
#endif  // WIN32
#endif  // !EXPORT

/*
 * Initialization / Uninitialization routines.  OleStdInitialize
 * must be called prior to using any functions in OLESTD.LIB.
 */

STDAPI_(BOOL) OleStdInitialize(HINSTANCE hInstance);
STDAPI_(void) OleStdUninitialize(void);

// object count, used to support DllCanUnloadNow and OleUICanUnloadNow
extern DWORD g_dwObjectCount;

STDAPI OleUICanUnloadNow(void);
STDAPI OleUILockLibrary(BOOL fLock);


//Dialog Identifiers as passed in Help messages to identify the source.
#define IDD_FILEOPEN            32253

// The following Dialogs are message dialogs used by OleUIPromptUser API

// Stringtable identifers
#define IDS_OLE2UIUNKNOWN       32300
#define IDS_OLE2UILINK          32301
#define IDS_OLE2UIOBJECT        32302
#define IDS_OLE2UIEDIT          32303
#define IDS_OLE2UICONVERT       32304
#define IDS_OLE2UIEDITLINKCMD_1VERB     32305
#define IDS_OLE2UIEDITOBJECTCMD_1VERB   32306
#define IDS_OLE2UIEDITLINKCMD_NVERB     32307
#define IDS_OLE2UIEDITOBJECTCMD_NVERB   32308
#define IDS_OLE2UIEDITNOOBJCMD  32309
// def. icon label (usu. "Document")
#define IDS_DEFICONLABEL        32310
#define IDS_OLE2UIPASTELINKEDTYPE  32311


#define IDS_FILTERS             32320
#define IDS_ICONFILTERS         32321
#define IDS_BROWSE              32322

//Resource identifiers for bitmaps
#define IDB_RESULTSEGA                  32325
#define IDB_RESULTSVGA                  32326
#define IDB_RESULTSHIRESVGA             32327


//Missing from windows.h
#ifndef PVOID
typedef VOID *PVOID;
#endif


//Hook type used in all structures.
typedef UINT (CALLBACK *LPFNOLEUIHOOK)(HWND, UINT, WPARAM, LPARAM);


//Strings for registered messages
#define SZOLEUI_MSG_FILEOKSTRING        "OLEUI_MSG_FILEOKSTRING"


//Help Button Identifier
#define ID_OLEUIHELP                    99

// Static text control (use this instead of -1 so things work correctly for
// localization
#define  ID_STATIC                      98

//Maximum key size we read from the RegDB.
#define OLEUI_CCHKEYMAX                 256  // make any changes to this in geticon.c too

//Maximum verb length and length of Object menu
#define OLEUI_CCHVERBMAX                32
#define OLEUI_OBJECTMENUMAX             256

//Maximum MS-DOS pathname.
#define OLEUI_CCHPATHMAX                256 // make any changes to this in geticon.c too
#define OLEUI_CCHFILEMAX                13

//Icon label length
#define OLEUI_CCHLABELMAX               40  // make any changes to this in geticon.c too

//Length of the CLSID string
#define OLEUI_CCHCLSIDSTRING            39


//Metafile utility functions
WINOLEAPI_(HGLOBAL) OleUIMetafilePictFromIconAndLabel(HICON, LPOLESTR, LPOLESTR, UINT);
STDAPI_(void)    OleUIMetafilePictIconFree(HGLOBAL);
STDAPI_(BOOL)    OleUIMetafilePictIconDraw(HDC, LPRECT, HGLOBAL, BOOL);
STDAPI_(UINT)    OleUIMetafilePictExtractLabel(HGLOBAL, LPOLESTR, UINT, LPDWORD);
STDAPI_(HICON)   OleUIMetafilePictExtractIcon(HGLOBAL);
STDAPI_(BOOL)    OleUIMetafilePictExtractIconSource(HGLOBAL,LPOLESTR,UINT FAR *);





/*************************************************************************
** INSERT OBJECT DIALOG
*************************************************************************/

//Insert Object Dialog identifiers
#define ID_IO_CREATENEW                 2100
#define ID_IO_CREATEFROMFILE            2101
#define ID_IO_LINKFILE                  2102
#define ID_IO_OBJECTTYPELIST            2103
#define ID_IO_DISPLAYASICON             2104
#define ID_IO_CHANGEICON                2105
#define ID_IO_FILE                      2106
#define ID_IO_FILEDISPLAY               2107
#define ID_IO_RESULTIMAGE               2108
#define ID_IO_RESULTTEXT                2109
#define ID_IO_ICONDISPLAY               2110
#define ID_IO_OBJECTTYPETEXT            2111
#define ID_IO_FILETEXT                  2112
#define ID_IO_FILETYPE                  2113

// Strings in OLE2UI resources
#define IDS_IORESULTNEW                 32400
#define IDS_IORESULTNEWICON             32401
#define IDS_IORESULTFROMFILE1           32402
#define IDS_IORESULTFROMFILE2           32403
#define IDS_IORESULTFROMFILEICON2       32404
#define IDS_IORESULTLINKFILE1           32405
#define IDS_IORESULTLINKFILE2           32406
#define IDS_IORESULTLINKFILEICON1       32407
#define IDS_IORESULTLINKFILEICON2       32408

/*************************************************************************
** PASTE SPECIAL DIALOG
*************************************************************************/

//Paste Special Dialog identifiers
#define ID_PS_PASTE                    500
#define ID_PS_PASTELINK                501
#define ID_PS_SOURCETEXT               502
#define ID_PS_PASTELIST                503
#define ID_PS_PASTELINKLIST            504
#define ID_PS_DISPLAYLIST              505
#define ID_PS_DISPLAYASICON            506
#define ID_PS_ICONDISPLAY              507
#define ID_PS_CHANGEICON               508
#define ID_PS_RESULTIMAGE              509
#define ID_PS_RESULTTEXT               510
#define ID_PS_RESULTGROUP              511
#define ID_PS_STXSOURCE                512
#define ID_PS_STXAS                    513

// Paste Special String IDs
#define IDS_PSPASTEDATA                32410
#define IDS_PSPASTEOBJECT              32411
#define IDS_PSPASTEOBJECTASICON        32412
#define IDS_PSPASTELINKDATA            32413
#define IDS_PSPASTELINKOBJECT          32414
#define IDS_PSPASTELINKOBJECTASICON    32415
#define IDS_PSNONOLE                   32416
#define IDS_PSUNKNOWNTYPE              32417
#define IDS_PSUNKNOWNSRC               32418
#define IDS_PSUNKNOWNAPP               32419


/*************************************************************************
** EDIT LINKS DIALOG
*************************************************************************/

// Edit Links Dialog identifiers
#define ID_EL_CHANGESOURCE             201
#define ID_EL_AUTOMATIC                202
#define ID_EL_CLOSE                    208
#define ID_EL_CANCELLINK               209
#define ID_EL_UPDATENOW                210
#define ID_EL_OPENSOURCE               211
#define ID_EL_MANUAL                   212
#define ID_EL_LINKSOURCE               216
#define ID_EL_LINKTYPE                 217
#define ID_EL_UPDATE                   218
#define ID_EL_NULL                     -1
#define ID_EL_LINKSLISTBOX             206
#define ID_EL_COL1                     220
#define ID_EL_COL2                     221
#define ID_EL_COL3                     222



/*************************************************************************
** CHANGE ICON DIALOG
*************************************************************************/

//Change Icon Dialog identifiers
#define ID_GROUP                    120
#define ID_CURRENT                  121
#define ID_CURRENTICON              122
#define ID_DEFAULT                  123
#define ID_DEFAULTICON              124
#define ID_FROMFILE                 125
#define ID_FROMFILEEDIT             126
#define ID_ICONLIST                 127
#define ID_LABEL                    128
#define ID_LABELEDIT                129
#define ID_BROWSE                   130
#define ID_RESULTICON               132
#define ID_RESULTLABEL              133

// Stringtable defines for Change Icon
#define IDS_CINOICONSINFILE         32430
#define IDS_CIINVALIDFILE           32431
#define IDS_CIFILEACCESS            32432
#define IDS_CIFILESHARE             32433
#define IDS_CIFILEOPENFAIL          32434



/*************************************************************************
** CONVERT DIALOG
*************************************************************************/

//Convert Dialog identifiers
#define IDCV_OBJECTTYPE             150
#define IDCV_DISPLAYASICON          152
#define IDCV_CHANGEICON             153
#define IDCV_ACTIVATELIST           154
#define IDCV_CONVERTTO              155
#define IDCV_ACTIVATEAS             156
#define IDCV_RESULTTEXT             157
#define IDCV_CONVERTLIST            158
#define IDCV_ICON                   159
#define IDCV_ICONLABEL1             160
#define IDCV_ICONLABEL2             161
#define IDCV_STXCURTYPE             162
#define IDCV_GRPRESULT              163
#define IDCV_STXCONVERTTO           164

// String IDs for Convert dialog
#define IDS_CVRESULTCONVERTLINK     32440
#define IDS_CVRESULTCONVERTTO       32441
#define IDS_CVRESULTNOCHANGE        32442
#define IDS_CVRESULTDISPLAYASICON   32443
#define IDS_CVRESULTACTIVATEAS      32444
#define IDS_CVRESULTACTIVATEDIFF    32445


/*************************************************************************
** BUSY DIALOG
*************************************************************************/

// Busy dialog identifiers
#define IDBZ_RETRY                      600
#define IDBZ_ICON                       601
#define IDBZ_MESSAGE1                   602
#define IDBZ_SWITCHTO                   604

// Busy dialog stringtable defines
#define IDS_BZRESULTTEXTBUSY            32447
#define IDS_BZRESULTTEXTNOTRESPONDING   32448

// Links dialog stringtable defines
#define IDS_LINK_AUTO           32450
#define IDS_LINK_MANUAL         32451
#define IDS_LINK_UNKNOWN        32452
#define IDS_LINKS               32453
#define IDS_FAILED              32454
#define IDS_CHANGESOURCE        32455
#define IDS_INVALIDSOURCE       32456
#define IDS_ERR_GETLINKSOURCE   32457
#define IDS_ERR_GETLINKUPDATEOPTIONS    32458
#define IDS_ERR_ADDSTRING       32459
#define IDS_CHANGEADDITIONALLINKS   32460
#define IDS_CLOSE               32461


/*************************************************************************
** PROMPT USER DIALOGS
*************************************************************************/
#define ID_PU_LINKS             900
#define ID_PU_TEXT              901
#define ID_PU_CONVERT           902
#define ID_PU_BROWSE            904
#define ID_PU_METER             905
#define ID_PU_PERCENT           906
#define ID_PU_STOP              907

// used for -1 ids in dialogs:
#define ID_DUMMY    999

/* inside ole2ui.c */
#ifdef __cplusplus
extern "C"
#endif

/*************************************************************************
** OLE OBJECT FEEDBACK EFFECTS
*************************************************************************/

#define OLEUI_HANDLES_USEINVERSE    0x00000001L
#define OLEUI_HANDLES_NOBORDER      0x00000002L
#define OLEUI_HANDLES_INSIDE        0x00000004L
#define OLEUI_HANDLES_OUTSIDE       0x00000008L


#define OLEUI_SHADE_FULLRECT        1
#define OLEUI_SHADE_BORDERIN        2
#define OLEUI_SHADE_BORDEROUT       3

/* objfdbk.c function prototypes */
STDAPI_(void) OleUIDrawHandles(LPRECT lpRect, HDC hdc, DWORD dwFlags, UINT cSize, BOOL fDraw);
STDAPI_(void) OleUIDrawShading(LPRECT lpRect, HDC hdc, DWORD dwFlags, UINT cWidth);
STDAPI_(void) OleUIShowObject(LPCRECT lprc, HDC hdc, BOOL fIsLink);


/*************************************************************************
** Hatch window definitions and prototypes                              **
*************************************************************************/
#define DEFAULT_HATCHBORDER_WIDTH   4

STDAPI_(BOOL) RegisterHatchWindowClass(HINSTANCE hInst);
STDAPI_(HWND) CreateHatchWindow(HWND hWndParent, HINSTANCE hInst);
STDAPI_(UINT) GetHatchWidth(HWND hWndHatch);
STDAPI_(void) GetHatchRect(HWND hWndHatch, LPRECT lpHatchRect);
STDAPI_(void) SetHatchRect(HWND hWndHatch, LPRECT lprcHatchRect);
STDAPI_(void) SetHatchWindowSize(
      HWND        hWndHatch,
      LPRECT      lprcIPObjRect,
      LPRECT      lprcClipRect,
      LPPOINT     lpptOffset
);

#define OLEUI_VERSION_MAGIC 0x4D42

#endif // _OLESTD_H_
