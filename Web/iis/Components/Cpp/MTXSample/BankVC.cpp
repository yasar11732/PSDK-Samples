// BankVC.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f BankVCps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "BankVC.h"

#include "BankVC_i.c"
#include "Account.h"
#include "CreateTable.h"
#include "MoveMoney.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Account, CAccount)
	OBJECT_ENTRY(CLSID_CreateTable, CCreateTable)
	OBJECT_ENTRY(CLSID_MoveMoney, CMoveMoney)
END_OBJECT_MAP()

// DLL Entry Point

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance, &LIBID_BANKVCLib);

		DisableThreadLibraryCalls(hInstance);
	}	
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}

	return TRUE;
}

// Used to determine whether the DLL can be unloaded

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}

// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib

	return _Module.RegisterServer(TRUE);
}

// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
}


