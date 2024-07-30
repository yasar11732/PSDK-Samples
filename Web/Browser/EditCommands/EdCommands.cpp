/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// EdCommands.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//	  To build a separate proxy/stub DLL,
//	  run nmake -f EdCommandsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "EdCommands.h"

#include "EdCommands_i.c"
#include "BrowserHost.h"


const DWORD dwTimeOut = 5000; // time for EXE to be idle before shutting down
const DWORD dwPause = 1000; // time to wait for threads to finish up

// Passed to CreateThread to monitor the shutdown event
static DWORD WINAPI MonitorProc(void* pv)
{
	CExeModule* p = (CExeModule*)pv;
	p->MonitorShutdown();
	return 0;
}

LONG CExeModule::Unlock()
{
	LONG l = CComModule::Unlock();
	if (l == 0)
	{
		bActivity = true;
		SetEvent(hEventShutdown); // tell monitor that we transitioned to zero
	}
	return l;
}

//Monitors the shutdown event
void CExeModule::MonitorShutdown()
{
	while (1)
	{
		WaitForSingleObject(hEventShutdown, INFINITE);
		DWORD dwWait=0;
		do
		{
			bActivity = false;
			dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
		} while (dwWait == WAIT_OBJECT_0);
		// timed out
		if (!bActivity && m_nLockCnt == 0) // if no activity let's really bail
		{
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
			CoSuspendClassObjects();
			if (!bActivity && m_nLockCnt == 0)
#endif
				break;
		}
	}
	CloseHandle(hEventShutdown);
	PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
  // CODE REVIEW: Add following security comment.
  /* The following use of CreateEvent is simplified for illustrative
  purposes. This simplified use in production code can expose a
  security risk in some situations. The first parameter might require
  specific security attributes. */
	hEventShutdown = CreateEvent(NULL, false, false, NULL);
	if (hEventShutdown == NULL)
		return false;
	DWORD dwThreadID;
	HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
	return (h != NULL);
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_BrowserHost, CBrowserHost)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (p1 != NULL && *p1 != NULL)
	{
		LPCTSTR p = p2;
		while (p != NULL && *p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1 = CharNext(p1);
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT

#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	HRESULT hRes = CoInitialize(NULL);
#endif
	_ASSERTE(SUCCEEDED(hRes));
	_Module.Init(ObjectMap, hInstance, &LIBID_EDCOMMANDSLib);
	_Module.dwThreadID = GetCurrentThreadId();
	TCHAR szTokens[] = _T("-/");

	int nRet = 0;
	BOOL bRun = TRUE;
	LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_EdCommands, FALSE);
			nRet = _Module.UnregisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_EdCommands, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	if (bRun)
	{
		_Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,
			REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
		_ASSERTE(SUCCEEDED(hRes));
		hRes = CoResumeClassObjects();
#else
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,
			REGCLS_MULTIPLEUSE);
#endif
		_ASSERTE(SUCCEEDED(hRes));

		// Create the Browser Window
		CComPtr<IBrowserHost> pApp;
		CoCreateInstance(CLSID_BrowserHost,
						 NULL,
						 CLSCTX_INPROC_SERVER,
						 IID_IBrowserHost,
						 (void**)&pApp);
		if (pApp)
		{
			pApp->Run();

			

			//long hwnd;
			HWND hwndApp;
			
			IOleWindow* pOWin;
			pApp->QueryInterface(IID_IOleWindow, (void**)&pOWin);
			pOWin->GetWindow(&hwndApp);
			pOWin->Release();
			//pApp->GetHwnd(&hwnd);
			//hwndApp = (HWND)hwnd;

			MSG msg;
			while (GetMessage(&msg, 0, 0, 0))
			{
				TranslateMessage(&msg);

				// Pass message to app on keydown so that it can pass the
				// message on to the WebBrowser control as necessary
				if (msg.message == WM_KEYDOWN)
					SendMessage(hwndApp, msg.message, msg.wParam, msg.lParam);

				DispatchMessage(&msg);
			}

			_Module.RevokeClassObjects();
			Sleep(dwPause); //wait for any threads to finish
		}
	}

	_Module.Term();
	CoUninitialize();
	return nRet;
}
