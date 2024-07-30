//	Copyright (c) 1997-2002 Microsoft Corporation
//
//	Module Name:
//
//		InvokObjThreads.cpp
//
//	Abstract:
//
//	ISAPI Extension sample to invoke an automation server method
//	from worker threads

#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <httpext.h>
#include "IsapiThread.h"

// Prototype for worker thread function

DWORD WINAPI WorkerThread(LPVOID pParam);

// Import type library information about the COM object

#import "GetUserName.dll"

// Global thread pool object

ISAPITHREAD *pThreadPool;

//	Description:
//
//		The initialization function for this DLL.
//
//	Arguments:
//
//		hinstDll - Instance handle of the DLL
//		dwReason - Reason why NT called this DLL
//		lpvContext - Reserved parameter for future use
//
//	Return Value:
//
//		Returns TRUE if successfull; otherwise FALSE.

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)	{

		case DLL_PROCESS_ATTACH:

			// Allocate the thread pool object
			
			pThreadPool = new ISAPITHREAD;

			if (!pThreadPool) {

				#ifdef _DEBUG
					OutputDebugString("Failed to allocate thread pool object. InvokObjThreads is terminating.\r\n");
				#endif  // _DEBUG

				return FALSE;
			}

			// Initialize the worker threads
			
			if (!pThreadPool->InitThreadPool(WorkerThread)) {

				#ifdef _DEBUG
					OutputDebugString("Failed to initialize worker threads. InvokObjThreads is terminating.\r\n");
				#endif  // _DEBUG

				delete pThreadPool;
				
				return FALSE;
			}

			break;

		case DLL_PROCESS_DETACH:

			break;

		default:

			return TRUE;
	}

	return TRUE;
}

//	Description:
//
//		This is required ISAPI Extension DLL entry point.
//
//	Arguments:
//
//		pVer - poins to extension version info structure 
//
//	Returns:
//
//		Always returns TRUE

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR, HSE_VERSION_MAJOR );

	lstrcpyn( pVer->lpszExtensionDesc, "InvokObjThreads ISAPI Sample", HSE_MAX_EXT_DLL_NAME_LEN );

	return TRUE;
}

//	Purpose:
//
//		Demonstrate how to create an instance of the automation object
//		using VC++ 5.0 extensions and how to invoke its method.
//
//	Arguments:
//
//		pECB - pointer to the extenstion control block 
//
//	Returns:
//
//		HSE_STATUS_SUCCESS on successful transmission completion
//		HSE_STATUS_ERROR on failure

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pecb)
{
	HSE_SEND_HEADER_EX_INFO HeaderExInfo;

	// Add the request to the work item queue.
	// If successful, we're done.  If not, return an error to the client

	if (pThreadPool->QueueWorkItem(pecb))
			return HSE_STATUS_PENDING;

	// Send headers back to client

	HeaderExInfo.pszStatus = "200 OK";
	HeaderExInfo.cchStatus = strlen(HeaderExInfo.pszStatus);
	HeaderExInfo.pszHeader = "Content-type: text/html\r\n\r\n";
	HeaderExInfo.cchHeader = strlen(HeaderExInfo.pszHeader);
	HeaderExInfo.fKeepConn = FALSE;

	pecb->ServerSupportFunction(pecb->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &HeaderExInfo, NULL, NULL);

	// Send back a message to the client indicating that the queue is full
	
	CHAR szOutput[] = "<h1>InvokObjThreads.dll</h1><hr>The resource is busy.  Pleast try again later.";

	DWORD dwBuffSize = strlen(szOutput);

	pecb->WriteClient(pecb->ConnID, szOutput, &dwBuffSize, 0);

	return HSE_STATUS_SUCCESS;
}

//	Description:
//
//		This is optional ISAPI extension DLL entry point.
//		If present, it will be called before unloading the DLL,
//		giving it a chance to perform any shutdown procedures.
//
//	Arguments:
//
//		dwFlags - specifies whether the DLL can refuse to unload or not
//
//	Returns:
//
//		TRUE, if the DLL can be unloaded

BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	// Delete the thread pool object

	delete pThreadPool;

	// It is now OK to unload

	return TRUE;
}

//	Description:
//
//		Implements the worker thread functionality
//
//	Arguments:
//
//		pParam - A pointer to the threadpool object to which the thread belongs
//
//	Returns:
//
//		0

DWORD WINAPI WorkerThread(LPVOID pParam)
{
	ISAPITHREAD *pThreadPool = (ISAPITHREAD *)pParam;

	#ifdef _DEBUG
		CHAR szDebug[1024];
	#endif

	// Get the ThreadId for this thread

	DWORD dwThreadId = GetCurrentThreadId();

	#ifdef _DEBUG
		wsprintf(szDebug,	"Initializing worker thread %d.\r\n", dwThreadId);

		OutputDebugString(szDebug);
	#endif // _DEBUG

	// Initialize COM for this thread

	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr))	{

		#ifdef _DEBUG
			wsprintf(szDebug, "CoIntialize failed for thread %d: 0x%08x (%d)\r\n", dwThreadId, hr, hr);

			OutputDebugString(szDebug);
		#endif // _DEBUG

		return FALSE;
	}

	// Initialize and instance of the automation server for this thread

	GETUSERNAMELib::IGetUserNameObjPtr pItf;
	
	hr = pItf.CreateInstance(L"GetUserNameObj.GetUserNameObj.1");

	if (FAILED(hr)) {

		#ifdef _DEBUG
			wsprintf(szDebug, "Failed to get interface pointer for thread %d: 0x%08x (%d)\r\n", dwThreadId, hr, hr);

			OutputDebugString(szDebug);
		#endif // _DEBUG

		goto ExitWorkerThread;
	}

	// Completed thread initialization.  Now wait for work
	
	for (;;) {

		#ifdef _DEBUG
			wsprintf(szDebug, "Thread %d waiting for work.\r\n", dwThreadId);

			OutputDebugString(szDebug);
		#endif  // _DEBUG

		DWORD dwResult = WaitForSingleObject(pThreadPool->m_hWorkerThreadSemaphore, INFINITE);

		// Check to see that the wait succeeded

		if (dwResult != WAIT_OBJECT_0) {

			#ifdef _DEBUG
				wsprintf(szDebug, "Thread %d exiting due to wait failure.\r\n", dwThreadId);

				OutputDebugString(szDebug);
			#endif  // _DEBUG

			goto ExitWorkerThread;
		}

		// Get the next work item in the queue.  If the work item is NULL,
		// the thread should exit gracefully.
		
		EXTENSION_CONTROL_BLOCK *pecb = pThreadPool->GetWorkItem();

		if (!pecb) {

			#ifdef _DEBUG
				wsprintf(szDebug, "Thread %d exiting gracefully.\r\n", dwThreadId);

				OutputDebugString(szDebug);
			#endif  // _DEBUG

			goto ExitWorkerThread;
		}

		///////
		// Process the work item
		///////

		#ifdef _DEBUG
			wsprintf(szDebug, "Thread %d processing work item.\r\n", dwThreadId);

			OutputDebugString(szDebug);
		#endif  // _DEBUG

		// Get the request token from IIS and set the token for this thead

		HANDLE hRequestToken;

		pecb->ServerSupportFunction(pecb->ConnID, HSE_REQ_GET_IMPERSONATION_TOKEN, &hRequestToken, NULL, NULL);

		SetThreadToken(NULL, hRequestToken);

		// Send headers back to client

		HSE_SEND_HEADER_EX_INFO HeaderExInfo;

		HeaderExInfo.pszStatus = "200 OK";
		HeaderExInfo.cchStatus = strlen( HeaderExInfo.pszStatus );
		HeaderExInfo.pszHeader = "Content-type: text/html\r\n\r\n";
		HeaderExInfo.cchHeader = strlen( HeaderExInfo.pszHeader );
		HeaderExInfo.fKeepConn = FALSE;

		pecb->ServerSupportFunction(pecb->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &HeaderExInfo, NULL, NULL);

		// Build the output using the result of the call to GetUserNameObj's GetMyName method

		char szOutput[1024];
			
		wsprintf(szOutput, "<h1>Request handled by thread %d.</h1><hr>The GetMyName method returned %s.", dwThreadId, (char *)pItf->GetMyName());

		// Send the output back to the client
		
		DWORD dwBuffSize = strlen(szOutput);
			
		pecb->WriteClient(pecb->ConnID, szOutput, &dwBuffSize, 0);

		// Notify IIS that we are done processing the request
		
		pecb->ServerSupportFunction(pecb->ConnID, HSE_REQ_DONE_WITH_SESSION, NULL, NULL, NULL);
	}

ExitWorkerThread:

	// Uninitialize COM for this thread and return
	
	CoUninitialize();

	return 0;
}




