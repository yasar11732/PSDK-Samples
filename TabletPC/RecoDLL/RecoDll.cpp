//-------------------------------------------------------------------------
//
//  This is part of the Microsoft Tablet PC Platform SDK
//  Copyright (C) 2002 Microsoft Corporation
//  All rights reserved.
//
//  This source code is only intended as a supplement to the
//  Microsoft Tablet PC Platform SDK Reference and related electronic 
//  documentation provided with the Software Development Kit.
//  See these sources for more detailed information. 
//
//--------------------------------------------------------------------------
//
// RecoDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "RecApis.h"
#include "assert.h"

const WCHAR *RECO_SUBKEY = L"Software\\Microsoft\\TPG\\Recognizers\\{6D0087D7-61D2-495f-9293-5B7B1C3FCEAB}";
const WCHAR *FULL_PATH_VALUE = L"Recognizer dll";
const WCHAR *RECO_MANAGER_KEY = L"CLSID\\{DE815B00-9460-4F6E-9471-892ED2275EA5}\\InprocServer32";
const WCHAR *RECOGNIZER_SUBKEY = L"CLSID\\{6D0087D7-61D2-495f-9293-5B7B1C3FCEAB}\\InprocServer32";
const WCHAR *RECOPROC_SUBKEY = L"{6D0087D7-61D2-495f-9293-5B7B1C3FCEAB}\\InprocServer32";
const WCHAR *CLSID_KEY = L"CLSID";
const WCHAR *RECOCLSID_SUBKEY = L"{6D0087D7-61D2-495f-9293-5B7B1C3FCEAB}";
const WCHAR *RECO_LANGUAGES = L"Recognized Languages";
const WCHAR *RECO_CAPABILITIES = L"Recognizer Capability Flags";
const WCHAR *RECOGNIZER_SUBPATH = L"Software\\Microsoft\\TPG\\Recognizers";
const WCHAR *TPG_SUBPATH = L"Software\\Microsoft\\TPG";
const WCHAR *RECO_SHORT_NAME = L"Recognizer Short Name";
const WCHAR *RECO_VENDOR_NAME = L"Vendor Name";

HANDLE m_hModule;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD ul_reason_for_call, 
                       void* lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            m_hModule = hModule;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

// This recognizer GUID is going to be
// {6D0087D7-61D2-495f-9293-5B7B1C3FCEAB}
// Each recognizer HAS to have a different GUID

STDAPI DllRegisterServer(void)
{
    HKEY        hKeyReco = NULL;
    HKEY        hKeyRecoManager = NULL;
    LONG        lRes = 0;   
    HKEY        hkeyMyReco;
    DWORD       dwLength = 0, dwType = 0, dwSize = 0;
    DWORD       dwDisposition;
    WCHAR       szRecognizerPath[MAX_PATH];
    HRESULT     hr = S_OK;
    RECO_ATTRS  recoAttr;

    // Write the path to this dll in the registry under
    // the recognizer subkey

    // Wipe out the previous values
    lRes = RegDeleteKeyW(HKEY_LOCAL_MACHINE, RECO_SUBKEY);
    // Create the new key
    lRes = RegCreateKeyExW(HKEY_LOCAL_MACHINE, RECO_SUBKEY, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyMyReco, &dwDisposition);
    assert(lRes == ERROR_SUCCESS);
    if (lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hkeyMyReco);
        return E_UNEXPECTED;
    }
    // Get the current path
    // Try to get the path of the RecoObj.dll
    // It should be the same as the one for the RecoCom.dll
    dwLength = GetModuleFileNameW((HMODULE)m_hModule, szRecognizerPath, MAX_PATH);
    // Write the path to the dll as a value
    lRes = RegSetValueExW(hkeyMyReco, FULL_PATH_VALUE, NULL, REG_SZ, 
        (BYTE*)szRecognizerPath, sizeof(WCHAR)*(wcslen(szRecognizerPath)+1));
    assert(lRes == ERROR_SUCCESS);
    if (lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hkeyMyReco);
        return E_UNEXPECTED;
    }   
    // We get the reco attributes
    // Here we pass NULL for the hrec because we only have one recognizer
    // we would need to loop though all the recognizer and register each
    // of them if there were more than one.
    hr = GetRecoAttributes(NULL, &recoAttr);
    if (FAILED(hr))
    {
        RegCloseKey(hkeyMyReco);
        return E_UNEXPECTED;
    }   
    lRes = RegSetValueExW(hkeyMyReco, RECO_LANGUAGES, 0, REG_BINARY, 
        (BYTE*)recoAttr.awLanguageId, 64 * sizeof(WORD));
    assert(lRes == ERROR_SUCCESS);
    if (lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hkeyMyReco);
        return E_UNEXPECTED;
    }
    lRes = RegSetValueExW(hkeyMyReco, RECO_CAPABILITIES, 0, REG_DWORD, 
        (BYTE*)&(recoAttr.dwRecoCapabilityFlags), sizeof(DWORD));
    assert(lRes == ERROR_SUCCESS);
    if (lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hkeyMyReco);
        return E_UNEXPECTED;
    }
    RegCloseKey(hkeyMyReco);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    LONG        lRes1 = 0;

    // Wipe out the registry information
    lRes1 = RegDeleteKeyW(HKEY_LOCAL_MACHINE, RECO_SUBKEY);

    // Try to erase the local machine\software\microsoft\tpg\recognizer
    // if necessary (don't care if it fails)
    RegDeleteKeyW(HKEY_LOCAL_MACHINE, RECOGNIZER_SUBPATH);
    RegDeleteKeyW(HKEY_LOCAL_MACHINE, TPG_SUBPATH);

    if (lRes1 != ERROR_SUCCESS && lRes1 != ERROR_FILE_NOT_FOUND)
    {
        return E_UNEXPECTED;
    }
    return S_OK ;
}

////////////////////////
// IRecognizer
////////////////////////
HRESULT WINAPI CreateRecognizer(CLSID *pCLSID, HRECOGNIZER *phrec)
{
    return E_NOTIMPL;
}
HRESULT WINAPI DestroyRecognizer(HRECOGNIZER hrec)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetRecoAttributes(HRECOGNIZER hrec, RECO_ATTRS* pRecoAttrs)
{
    // Check the the hrec
    // TODO

    // Check the pRecoAttrs pointer
    if (IsBadWritePtr(pRecoAttrs, sizeof(RECO_ATTRS)))
        return E_POINTER;

    // Initialize the Reco Attribute structure
    ZeroMemory(pRecoAttrs, sizeof(RECO_ATTRS));

    // Fill in the vendor name and the recognizer "friendly" name
    wcsncpy(pRecoAttrs->awcVendorName, RECO_VENDOR_NAME, wcslen(RECO_VENDOR_NAME)+1);
    wcsncpy(pRecoAttrs->awcFriendlyName, RECO_SHORT_NAME, wcslen(RECO_SHORT_NAME)+1);
    // Put the languages supported by the recognizer in the awLanguageId array
    pRecoAttrs->awLanguageId[0] = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
    // Set the reco capability flag
    pRecoAttrs->dwRecoCapabilityFlags = 0;
    return S_OK;
}
HRESULT WINAPI CreateContext(HRECOGNIZER hrec, HRECOCONTEXT *phrc)
{
    return E_NOTIMPL;
}
HRESULT WINAPI DestroyContext(HRECOCONTEXT hrc)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GUIDToIndex(HRECOGNIZER hrec, GUID* pGUID, ULONG* pIndex)
{
    return E_NOTIMPL;
}
HRESULT WINAPI IndexToGUID(HRECOGNIZER hrec, ULONG Index, GUID* pGUID)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetResultPropertyList(HRECOGNIZER hrec, ULONG* pPropertyCount, ULONG*pPropIndexes)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetPreferredPacketDescription(HRECOGNIZER hrec, PACKET_DESCRIPTION* pPacketDescription)
{
    return E_NOTIMPL;
}

////////////////////////
// IRecoContext
////////////////////////
HRESULT WINAPI AddStroke(HRECOCONTEXT hrc, PACKET_DESCRIPTION* pPacketDesc, ULONG cbPacket, BYTE *pPacket, const XFORM *pXForm)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetBestResultString(HRECOCONTEXT hrc, ULONG *pcbSize, WCHAR* pszBestResult)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetBestAlternate(HRECOCONTEXT hrc, HRECOALT* pHrcAlt)
{
    return E_NOTIMPL;
}
HRESULT WINAPI DestroyAlternate(HRECOALT hrcalt)
{
    return E_NOTIMPL;
}
HRESULT WINAPI SetGuide(HRECOCONTEXT hrc, const RECO_GUIDE* pGuide, ULONG iIndex)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetGuide(HRECOCONTEXT hrc, RECO_GUIDE* pGuide, ULONG *piIndex)
{
    return E_NOTIMPL;
}
HRESULT WINAPI AdviseInkChange(HRECOCONTEXT hrc, BOOL bNewStroke)
{
    return E_NOTIMPL;
}
HRESULT WINAPI SetCACMode(HRECOCONTEXT hrc, int iMode)
{
    return E_NOTIMPL;
}
HRESULT WINAPI EndInkInput(HRECOCONTEXT hrc)
{
    return E_NOTIMPL;
}
HRESULT WINAPI CloneContext(HRECOCONTEXT hrc, HRECOCONTEXT* pCloneHrc)
{
    return E_NOTIMPL;
}
HRESULT WINAPI ResetContext(HRECOCONTEXT hrc)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetAlternateList(HRECOCONTEXT hrc, RECO_RANGE* pRecoRange, ULONG*pcAlt, HRECOALT*phrcalt, ULONG iBreak)
{
    return E_NOTIMPL;
}
HRESULT WINAPI Process(HRECOCONTEXT hrc, BOOL *pbPartialProcessing)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetLatticePtr(HRECOCONTEXT hrc, RECO_LATTICE **ppLattice)
{
    return E_NOTIMPL;
}


////////////////////////
// IAlternate
////////////////////////
HRESULT WINAPI GetString(HRECOALT hrcalt, RECO_RANGE *pRecoRange, ULONG* pcSize, WCHAR* szString)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetStrokeRanges(HRECOALT hrcalt, RECO_RANGE* pRecoRange, ULONG* pcRanges, STROKE_RANGE* pStrokeRange)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetSegmentAlternateList(HRECOALT hrcalt, RECO_RANGE* pRecoRange, ULONG *pcAlts, HRECOALT* pAlts)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetMetrics(HRECOALT hrcalt, RECO_RANGE* pRecoRange, LINE_METRICS lm, LINE_SEGMENT* pls)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetGuideIndex(HRECOALT hrcalt, RECO_RANGE* pRecoRange, RECO_GUIDE* pGuide, ULONG iIndex)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetConfidenceLevel(HRECOALT hrcalt, RECO_RANGE* pRecoRange, CONFIDENCE_LEVEL* pcl)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetPropertyRanges(HRECOALT hrcalt, ULONG id, ULONG* pcRanges, RECO_RANGE* pRecoRange)
{
    return E_NOTIMPL;
}
HRESULT WINAPI GetRangePropertyValue(HRECOALT hrcalt, ULONG id, RECO_RANGE* pRecoRange, ULONG*cbSize, BYTE* pProperty)
{
    return E_NOTIMPL;
}

