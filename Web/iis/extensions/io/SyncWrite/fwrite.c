/* Copyright (c) 1995-2002 Microsoft Corporation

	Module Name:

		fwrite.c

	Abstract:

		This module demonstrates a simple file transfer using ISAPI application
		using the WriteClient() callback.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "httpext.h"
#include "openf.h"

#define MAX_BUFFER_SIZE 4096

DWORD SendHeaderToClient(IN EXTENSION_CONTROL_BLOCK *pecb, IN LPCSTR pszErrorMsg);
DWORD SendFileToClient(IN EXTENSION_CONTROL_BLOCK *pecb, IN LPCSTR pszFile);
DWORD SendFileOver(IN EXTENSION_CONTROL_BLOCK *pecb, IN HANDLE hFile);

/*
	Description:

		This function DllLibMain() is the main initialization function for
		this DLL. It initializes local variables and prepares it to be invoked
		subsequently.

	Arguments:

		hinstDll          Instance Handle of the DLL
		fdwReason         Reason why NT called this DLL
		lpvReserved       Reserved parameter for future use.

	Returns:

		Returns TRUE is successful; otherwise FALSE is returned.
*/

BOOL WINAPI DllMain(IN HINSTANCE hinstDll, IN DWORD fdwReason, IN LPVOID lpvContext OPTIONAL)
{
  BOOL fReturn = TRUE;

  switch (fdwReason) {

    case DLL_PROCESS_ATTACH :

			OutputDebugString("Initializing the global data in fwrite.dll\n");

			/* Initialize various data and modules. */
			
			fReturn = (InitFileHandleCache() == NO_ERROR);

			break;

    case DLL_PROCESS_DETACH :

      /*
				Only cleanup when we are called because of a FreeLibrary() (i.e., when lpvContext == NULL)
				If we are called because of a process termination, dont free anything. System will free resources and memory for us.
      */

      CleanupFileHandleCache();

      break;

    default :

      break;
  }

  return fReturn;
}

DWORD WINAPI HttpExtensionProc(IN EXTENSION_CONTROL_BLOCK *pecb)
{
	DWORD hseStatus;

	if (pecb->lpszQueryString == NULL)
		hseStatus = SendHeaderToClient(pecb, "File Not Found");
	else
		hseStatus = SendFileToClient(pecb, pecb->lpszQueryString);

	return hseStatus;
}

/*
	Description:

		Sets the ISAPI extension version information.

	Arguments:

		Version     pointer to HSE_VERSION_INFO structure

	Return Value:

		TRUE
*/

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = MAKELONG(HSE_VERSION_MINOR, HSE_VERSION_MAJOR);

	lstrcpyn((LPSTR) pVer->lpszExtensionDesc, "File Transfer Using WriteClient", HSE_MAX_EXT_DLL_NAME_LEN);

	return TRUE;
}

BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	/* Nothing specific do here for cleanup. Cleanup is done in the dll process detach in DllLibMain() */

	return TRUE;
}

DWORD SendHeaderToClient(IN EXTENSION_CONTROL_BLOCK *pecb, IN LPCSTR pszErrorMsg)
{
	HSE_SEND_HEADER_EX_INFO	SendHeaderExInfo;
	char szStatus[] = "200 OK";
	char szHeader[1024];

	/* Note the HTTP header block is terminated by a blank '\r\n' pair, followed by the document body */

	wsprintf(szHeader, "Content-Type: text/html\r\n\r\n<head><title>Simple File Transfer (Synchronous Write)</title></head>\n<body><h1>%s</h1>\n", pszErrorMsg);

	/*  Populate SendHeaderExInfo struct */

	SendHeaderExInfo.pszStatus = szStatus;
	SendHeaderExInfo.pszHeader = szHeader;
	SendHeaderExInfo.cchStatus = lstrlen(szStatus);
	SendHeaderExInfo.cchHeader = lstrlen(szHeader);
	SendHeaderExInfo.fKeepConn = FALSE;

	/* Send header - use the EX Version to send the header blob */
	
	if (!pecb->ServerSupportFunction(pecb->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &SendHeaderExInfo, NULL, NULL))
		return HSE_STATUS_ERROR;

	return HSE_STATUS_SUCCESS;
}

DWORD SendFileToClient(IN EXTENSION_CONTROL_BLOCK *pecb, IN LPCSTR pszFile)
{
	CHAR    pchBuffer[1024];
	HANDLE  hFile;
	DWORD   hseStatus = HSE_STATUS_SUCCESS;

	hFile = FcOpenFile(pecb, pszFile);

	if (hFile == INVALID_HANDLE_VALUE) {

		wsprintfA(pchBuffer, "OpenFailed: Error (%d) while opening the file %s.\n", GetLastError(), pszFile);

		hseStatus = SendHeaderToClient(pecb, pchBuffer);

	} else {

		wsprintfA(pchBuffer, "Transferred file contains...");

		hseStatus = SendHeaderToClient(pecb, pchBuffer);

		if (hseStatus == HSE_STATUS_SUCCESS) {

			hseStatus = SendFileOver(pecb, hFile);

			if (hseStatus != HSE_STATUS_PENDING) {

				if (hseStatus != HSE_STATUS_SUCCESS) {

					/* Error in transmitting the file. Send error message. */

					wsprintfA(pchBuffer, "Send Failed: Error (%d) for file %s.\n", GetLastError(), pszFile);

					SendHeaderToClient(pecb, pchBuffer);
				}
			}

			if (hseStatus != HSE_STATUS_PENDING) {

				/* Assume that the data is transmitted and close the file handle */
				
				FcCloseFile(hFile);
			}
		}
	}

	return hseStatus;
}

DWORD SendFileOver(IN EXTENSION_CONTROL_BLOCK *pecb, IN HANDLE hFile)
{
	CHAR pchBuffer[MAX_BUFFER_SIZE];
	DWORD dwBytesInFile = GetFileSize(hFile, NULL);
	DWORD nRead = 0;
	DWORD hseStatus = HSE_STATUS_SUCCESS;
	OVERLAPPED  ov;
	DWORD err;

	/* Send the whole file. Loop thru reading the file and transmitting it to client */

	memset(&ov, 0, sizeof(OVERLAPPED));

	ov.OffsetHigh = 0;
	ov.Offset = 0;
	ov.hEvent = CreateEvent(NULL, TRUE, FALSE, "OVERLAPPED::hEvent");

	if (NULL == ov.hEvent)
		return HSE_STATUS_ERROR;

	for (;;) {

		nRead = 0;

		/* read data from the file */

		if (!FcReadFromFile(hFile, pchBuffer, MAX_BUFFER_SIZE, &nRead, &ov)) {

			hseStatus = HSE_STATUS_ERROR;

			break;
		}

		/* write data to client */

		if (!pecb->WriteClient(pecb->ConnID, pchBuffer, &nRead,	0)) {

			hseStatus = HSE_STATUS_ERROR;

			break;
		}
	}

	if (NULL != ov.hEvent) {

		err = GetLastError();

		CloseHandle(ov.hEvent);

		ov.hEvent = NULL;

		SetLastError(err);
	}

	return hseStatus;
}
