/*******************************************
*
* EnumerateKeys.CPP
*
* This is a simple program to enumerate the
* IIS metabase keys using the IMSAdminBase 
* interface.
*
********************************************/


#define STRICT
#define INITGUID
#define WINVER 0x0400
#define _WIN32_DCOM

#include <WINDOWS.H>
#include <OLE2.H>
#include <coguid.h>

#include <stdio.h>
#include <stdlib.h>

#include "iadmw.h"
#include "iiscnfg.h"

int __cdecl wmain(
    int                 argc,
    wchar_t             *argv[])
{
	HRESULT             hr = S_OK;
	DWORD               dwEnumIndex;
	WCHAR               wszChildKeyName[METADATA_MAX_NAME_LEN];
	WCHAR               wszEnumPath[METADATA_MAX_NAME_LEN];
    COSERVERINFO        csiMachineName;
	OLECHAR             wszMachineName[MAX_PATH];
	IClassFactory       *pClassFactory = NULL;
	IMSAdminBase        *pAdminBase = NULL;   //interface pointer

	if ( (argc < 2) || (argc > 3 ) )
	{
		_putws( L"ERROR! Wrong number of parameters" );
		_putws( L"    You must supply at least the machine name\n" );

		hr = E_INVALIDARG;
        goto exit;
	}

    if ( wcslen( argv[1] ) >= MAX_PATH )
    {
		_putws( L"ERROR! bad" );

		hr = E_INVALIDARG;
        goto exit;
    }

	if ( ( argc == 3 ) && ( wcslen( argv[2] ) > METADATA_MAX_NAME_LEN ) )
	{
		_putws( L"ERROR! bad" );

		hr = E_INVALIDARG;
        goto exit;
	}

	//fill the structure for CoGetClassObject
	wcsncpy (wszMachineName, argv[1], MAX_PATH-1 );
	wszMachineName[MAX_PATH-1] = L'\0';

	csiMachineName.pAuthInfo = NULL;
	csiMachineName.dwReserved1 = 0;
	csiMachineName.dwReserved2 = 0;
	csiMachineName.pwszName = wszMachineName;

	// Initialize COM
    hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );
    if (FAILED(hr))
	{
		wprintf( L"ERROR: CoInitialize Failed! Error: 0x%08x\n", hr );
        goto exit;
	}

	hr = CoGetClassObject( CLSID_MSAdminBase, CLSCTX_SERVER, &csiMachineName,
                           IID_IClassFactory, (void**) &pClassFactory);
	if (FAILED(hr))
	{
		wprintf( L"ERROR: CoGetClassObject Failed! Error: 0x%08x\n", hr );
        goto exit;
	}

	hr = pClassFactory->CreateInstance(NULL, IID_IMSAdminBase, (void **) &pAdminBase);
	if (FAILED(hr))
	{
		wprintf( L"ERROR: CreateInstance Failed! Error: 0x%08x\n", hr );
        goto exit;
	}

	if (argc != 3)
	{
		// Set up a default path.
		wszEnumPath[0] = L'/';
		wszEnumPath[1] = L'\0';
	}
	else
	{
    	wcsncpy( wszEnumPath, argv[2], METADATA_MAX_NAME_LEN-1 );
    	wszMachineName[METADATA_MAX_NAME_LEN-1]=L'\0';
	}

	wprintf( L"Enumerating Path: %s\n", wszEnumPath );

	// Enumerate the data
	for ( dwEnumIndex = 0; SUCCEEDED(hr); dwEnumIndex++ )
	{
		hr = pAdminBase -> EnumKeys( METADATA_MASTER_ROOT_HANDLE,
                                   wszEnumPath,
                                   wszChildKeyName,
                                   dwEnumIndex);
		if ( SUCCEEDED(hr) )
		{
    		wprintf( L"[%s]\n", wszChildKeyName );
		}
	}

	if ( hr != HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS) )
	{
		wprintf( L"EnumIndex: %d \n", dwEnumIndex );
		wprintf( L"EnumKeys return code: 0x%08x\n", hr );

		goto exit;
	}

	hr = S_OK;

exit:
	if ( pClassFactory != NULL )
	{
    	pClassFactory->Release();
    	pClassFactory = NULL;
	}
	if ( pAdminBase != NULL )
	{
    	pAdminBase->Release();
    	pAdminBase = NULL;
	}

	if ( FAILED(hr) )
	{
	    wprintf( L"the example failed with 0x%08x\n", hr );
	}

	return hr;
}
