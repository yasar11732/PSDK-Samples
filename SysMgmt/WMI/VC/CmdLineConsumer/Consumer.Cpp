// **************************************************************************

// Copyright (c)  Microsoft Corporation, All Rights Reserved
//
// File:  Consumer.cpp
//
// Description:
//			Event consumer class implementation
// 
// History:
//
// **************************************************************************

#include "stdafx.h"
#include "Consumer.h"
#include <objbase.h>
#include <strsafe.h>

CConsumer::CConsumer(CListBox	*pOutputList)
{
	m_cRef = 0L;
	m_pOutputList = pOutputList;
}

CConsumer::~CConsumer()
{
}

STDMETHODIMP CConsumer::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
    *ppv=NULL;

    if (riid == IID_IUnknown || riid == IID_IWbemUnboundObjectSink)
        *ppv=this;

    if (*ppv != NULL)
    {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CConsumer::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CConsumer::Release(void)
{
    if (--m_cRef != 0L)
        return m_cRef;

    delete this;
    return 0L;
}

STDMETHODIMP CConsumer::IndicateToConsumer(IWbemClassObject *pLogicalConsumer,
											long lNumObjects,
											IWbemClassObject **ppObjects)
{
/* for easy reference.
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
*/

	// NOTE: If this routine returns a failure code, including 
	// GPFs from called routines, CIMOM will recreate the object 
	// and call here again. If you see this routine being called 
	// twice for every indication, it means this routine is 
	// returning a failure code somehow. Especially watch the 
	// AddRef()/Release() semantics for the embedded object.
	// If they're too low, you'll return a GPF.
	CString clMyBuff;
	BSTR tgtProp = NULL;
	BSTR showProp = NULL;
	BSTR tgt = NULL;
	UINT showWindow = SW_SHOWNORMAL;
	VARIANT pVal, pVal1;
	CString appName;

	VariantInit(&pVal);
	VariantInit(&pVal1);

	TRACE(_T("Indicate() called\n"));

	tgtProp = SysAllocString(L"cmdLine");
	if (!tgtProp)
        return E_OUTOFMEMORY;

	showProp = SysAllocString(L"ShowWindow");
	if (!showProp)
        return E_OUTOFMEMORY;

	// clear my output buffer.
	clMyBuff.Empty();

	//--------------------------------
	// NOTICE that I only call once per call, not once per object passed since
	//  I dont care what object caused the event anyway.

	// get the 'Item' property out of the embedded object.
	if((pLogicalConsumer->Get(tgtProp, 0L, &pVal, NULL, NULL) == S_OK) &&
		(pLogicalConsumer->Get(showProp, 0L, &pVal1, NULL, NULL) == S_OK))
	{
		// pull out the command.
		tgt = V_BSTR(&pVal);

		//if the application name does not contain any slashes,
		//assume it is in the System directory		
		if (appName.Find('\\') < 0 &&
			appName.Find('/') < 0)
		{
			TCHAR tchSystemInfo[MAX_PATH + 1];
            if (GetSystemDirectory(tchSystemInfo, MAX_PATH+1)!= 0)
			{
				appName += tchSystemInfo;
				appName += _T("\\");
				appName += tgt;
			}
		}
		else	//full path must have been specified, pass it on to CreateProcess
		{
			appName += tgt; 		
		}

		// take onto the display line.
		clMyBuff = _T("cmdLine will run: ");
		clMyBuff += appName;		

		// how to run the program.
		showWindow = (UINT)V_UI1(&pVal1);
	
		// call CreateProcess
		STARTUPINFO si;
		memset(&si, 0, sizeof(si));
		si.cb          = sizeof(si);
		si.dwFlags     = STARTF_USESHOWWINDOW;
		si.wShowWindow = (unsigned short)showWindow;

		PROCESS_INFORMATION pi;
		memset(&pi, 0, sizeof(pi));
		if (!CreateProcess(appName, NULL, NULL, NULL, FALSE,
							0, NULL, NULL, &si, &pi))
		{
			DWORD lastErr = GetLastError();
			TCHAR msg[100];
			_itot(lastErr, msg, 10);
			CString errMsg = _T("CreateProcess failed. Error ");
			errMsg +=(LPCTSTR)&msg[0];

			m_pOutputList->AddString(errMsg);
		}
		else
		{	
			// output the buffer.
			m_pOutputList->AddString(clMyBuff);

			//IMPORTANT: remember to close handles after the spawned process 
			//has signalled its completion:

			//CloseHandle(pi.hProcess);
            //CloseHandle(pi.hThread);
		}
	}
	else
	{
		TRACE(_T("Get() cmdLine failed\n"));
	}

	SysFreeString(tgtProp);
	VariantClear(&pVal);

	TRACE(_T("walked indication list\n"));

	return S_OK;
}

// **************************************************************************
//
//	ErrorString()
//
// Description:
//		Converts an HRESULT to a displayable string.
//
// Parameters:
//		hRes (in) - HRESULT to be converted.
//
// Returns:
//		ptr to displayable string.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
LPCTSTR CConsumer::ErrorString(HRESULT hRes)
{
    TCHAR szBuffer2[19];
	static TCHAR szBuffer[24];
	LPCTSTR psz;

	switch(hRes) 
    {
    case WBEM_NO_ERROR:
		psz = _T("WBEM_NO_ERROR");
		break;
    case WBEM_S_FALSE:
		psz = _T("WBEM_S_FALSE");
		break;
    case WBEM_S_NO_MORE_DATA:
		psz = _T("WBEM_S_NO_MORE_DATA");
		break;
	case WBEM_E_FAILED:
		psz = _T("WBEM_E_FAILED");
		break;
	case WBEM_E_NOT_FOUND:
		psz = _T("WBEM_E_NOT_FOUND");
		break;
	case WBEM_E_ACCESS_DENIED:
		psz = _T("WBEM_E_ACCESS_DENIED");
		break;
	case WBEM_E_PROVIDER_FAILURE:
		psz = _T("WBEM_E_PROVIDER_FAILURE");
		break;
	case WBEM_E_TYPE_MISMATCH:
		psz = _T("WBEM_E_TYPE_MISMATCH");
		break;
	case WBEM_E_OUT_OF_MEMORY:
		psz = _T("WBEM_E_OUT_OF_MEMORY");
		break;
	case WBEM_E_INVALID_CONTEXT:
		psz = _T("WBEM_E_INVALID_CONTEXT");
		break;
	case WBEM_E_INVALID_PARAMETER:
		psz = _T("WBEM_E_INVALID_PARAMETER");
		break;
	case WBEM_E_NOT_AVAILABLE:
		psz = _T("WBEM_E_NOT_AVAILABLE");
		break;
	case WBEM_E_CRITICAL_ERROR:
		psz = _T("WBEM_E_CRITICAL_ERROR");
		break;
	case WBEM_E_INVALID_STREAM:
		psz = _T("WBEM_E_INVALID_STREAM");
		break;
	case WBEM_E_NOT_SUPPORTED:
		psz = _T("WBEM_E_NOT_SUPPORTED");
		break;
	case WBEM_E_INVALID_SUPERCLASS:
		psz = _T("WBEM_E_INVALID_SUPERCLASS");
		break;
	case WBEM_E_INVALID_NAMESPACE:
		psz = _T("WBEM_E_INVALID_NAMESPACE");
		break;
	case WBEM_E_INVALID_OBJECT:
		psz = _T("WBEM_E_INVALID_OBJECT");
		break;
	case WBEM_E_INVALID_CLASS:
		psz = _T("WBEM_E_INVALID_CLASS");
		break;
	case WBEM_E_PROVIDER_NOT_FOUND:
		psz = _T("WBEM_E_PROVIDER_NOT_FOUND");
		break;
	case WBEM_E_INVALID_PROVIDER_REGISTRATION:
		psz = _T("WBEM_E_INVALID_PROVIDER_REGISTRATION");
		break;
	case WBEM_E_PROVIDER_LOAD_FAILURE:
		psz = _T("WBEM_E_PROVIDER_LOAD_FAILURE");
		break;
	case WBEM_E_INITIALIZATION_FAILURE:
		psz = _T("WBEM_E_INITIALIZATION_FAILURE");
		break;
	case WBEM_E_TRANSPORT_FAILURE:
		psz = _T("WBEM_E_TRANSPORT_FAILURE");
		break;
	case WBEM_E_INVALID_OPERATION:
		psz = _T("WBEM_E_INVALID_OPERATION");
		break;
	case WBEM_E_INVALID_QUERY:
		psz = _T("WBEM_E_INVALID_QUERY");
		break;
	case WBEM_E_INVALID_QUERY_TYPE:
		psz = _T("WBEM_E_INVALID_QUERY_TYPE");
		break;
	case WBEM_E_ALREADY_EXISTS:
		psz = _T("WBEM_E_ALREADY_EXISTS");
		break;
    case WBEM_S_ALREADY_EXISTS:
        psz = _T("WBEM_S_ALREADY_EXISTS");
        break;
    case WBEM_S_RESET_TO_DEFAULT:
        psz = _T("WBEM_S_RESET_TO_DEFAULT");
        break;
    case WBEM_S_DIFFERENT:
        psz = _T("WBEM_S_DIFFERENT");
        break;
    case WBEM_E_OVERRIDE_NOT_ALLOWED:
        psz = _T("WBEM_E_OVERRIDE_NOT_ALLOWED");
        break;
    case WBEM_E_PROPAGATED_QUALIFIER:
        psz = _T("WBEM_E_PROPAGATED_QUALIFIER");
        break;
    case WBEM_E_PROPAGATED_PROPERTY:
        psz = _T("WBEM_E_PROPAGATED_PROPERTY");
        break;
    case WBEM_E_UNEXPECTED:
        psz = _T("WBEM_E_UNEXPECTED");
        break;
    case WBEM_E_ILLEGAL_OPERATION:
        psz = _T("WBEM_E_ILLEGAL_OPERATION");
        break;
    case WBEM_E_CANNOT_BE_KEY:
        psz = _T("WBEM_E_CANNOT_BE_KEY");
        break;
    case WBEM_E_INCOMPLETE_CLASS:
        psz = _T("WBEM_E_INCOMPLETE_CLASS");
        break;
    case WBEM_E_INVALID_SYNTAX:
        psz = _T("WBEM_E_INVALID_SYNTAX");
        break;
    case WBEM_E_NONDECORATED_OBJECT:
        psz = _T("WBEM_E_NONDECORATED_OBJECT");
        break;
    case WBEM_E_READ_ONLY:
        psz = _T("WBEM_E_READ_ONLY");
        break;
    case WBEM_E_PROVIDER_NOT_CAPABLE:
        psz = _T("WBEM_E_PROVIDER_NOT_CAPABLE");
        break;
    case WBEM_E_CLASS_HAS_CHILDREN:
        psz = _T("WBEM_E_CLASS_HAS_CHILDREN");
        break;
    case WBEM_E_CLASS_HAS_INSTANCES:
        psz = _T("WBEM_E_CLASS_HAS_INSTANCES");
        break;
    case WBEM_E_QUERY_NOT_IMPLEMENTED:
        psz = _T("WBEM_E_QUERY_NOT_IMPLEMENTED");
        break;
    case WBEM_E_ILLEGAL_NULL:
        psz = _T("WBEM_E_ILLEGAL_NULL");
        break;
    case WBEM_E_INVALID_QUALIFIER_TYPE:
        psz = _T("WBEM_E_INVALID_QUALIFIER_TYPE");
        break;
    case WBEM_E_INVALID_PROPERTY_TYPE:
        psz = _T("WBEM_E_INVALID_PROPERTY_TYPE");
        break;
    case WBEM_E_VALUE_OUT_OF_RANGE:
        psz = _T("WBEM_E_VALUE_OUT_OF_RANGE");
        break;
    case WBEM_E_CANNOT_BE_SINGLETON:
        psz = _T("WBEM_E_CANNOT_BE_SINGLETON");
        break;
	default:
	  _itot(hRes, szBuffer2, 16);
	  StringCbCopy(szBuffer, sizeof(szBuffer),_T("0x"));
      StringCbCat(szBuffer, sizeof(szBuffer), szBuffer2);
	  psz = szBuffer;
	}
	return psz;
}

