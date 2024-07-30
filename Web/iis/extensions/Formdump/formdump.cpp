//	Copyright (c) 1997  Microsoft Corporation
//
//	Module Name:    
//
//		formdump.cpp
//
//	Abstract:
//
//		ISAPI Extension sample illustrating how to obtain data from a web browser
//		and how to build a reply to the form. 

#define WIN32_LEAN_AND_MEAN     // the bare essential Win32 API
#include <windows.h>
#include <ctype.h>              // for isprint()
#include <httpext.h>

#include "keys.h"
#include "html.h"

#define MAX_BUFFER 4096

// local prototypes
 
void SendVariables(EXTENSION_CONTROL_BLOCK *pECB);
void HexDumper(EXTENSION_CONTROL_BLOCK *pECB, LPBYTE lpbyBuf, DWORD dwLength);
void WhoAmI(EXTENSION_CONTROL_BLOCK *pECB);
BOOL SendHttpHeaders(EXTENSION_CONTROL_BLOCK *, LPCSTR, LPCSTR);

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

BOOL WINAPI GetExtensionVersion(OUT HSE_VERSION_INFO *pVer)
{
	// set version to httpext.h version constants
	
	pVer->dwExtensionVersion = MAKELONG(HSE_VERSION_MINOR, HSE_VERSION_MAJOR);

	lstrcpyn((LPSTR) pVer->lpszExtensionDesc, "FORMDUMP - A Form Decoder and Dumper", HSE_MAX_EXT_DLL_NAME_LEN);

	return TRUE;
}       

//	Description:
//
//		Pull in all inbound data.  Build a reply page
//		so the user can see how forms appear in our key list.
//
//	Arguments:
//
//		pECB - pointer to the extenstion control block 
//
//	Returns:
//
//		HSE_STATUS_SUCCESS on successful completion
//		HSE_STATUS_ERROR on failure

DWORD WINAPI HttpExtensionProc(IN EXTENSION_CONTROL_BLOCK *pECB)
{
	// Get the keys sent by the client
	
	HKEYLIST hKeyList = GetKeyList(pECB);

	// Send HTTP headers 

	SendHttpHeaders(pECB, "200 OK", "Content-type: text/html\r\n\r\n");

	// Create a basic HTML page

	HtmlCreatePage(pECB, "FormDump.dll Reply");
	HtmlHeading(pECB, 1, "Data Available via ISAPI");
	HtmlHorizontalRule(pECB);

	// Send each form field
	
	HtmlHeading(pECB, 2, "Form Fields");

	if (!hKeyList) {

		// Report no data/error
			    
		HtmlBold(pECB, "No form fields sent");
		HtmlWriteText(pECB, " (or error decoding keys)");
		HtmlEndParagraph(pECB);
	    
	} else {

		// Print a quick overview
			  
		HtmlWriteTextLine(pECB, "The form you submitted data to just called");
		HtmlWriteTextLine(pECB, "the Internet Information Server extension");
		HtmlWriteTextLine(pECB, "FormDump.dll.  Here is a listing of what was");
		HtmlWriteTextLine(pECB, "received and what variables inside FormDump");
		HtmlWriteTextLine(pECB, "have the data.");
		HtmlEndParagraph(pECB);

		// Loop through all of the keys
		
		HKEYLIST hKey = hKeyList;

		while (hKey) {
	  
			// Details about the key
				    
			LPCTSTR lpszKeyName;
			DWORD dwLength;
			BOOL bHasCtrlChars;
			int nInstance;

			// We get info, and hKey points to next key in list
				    
			HKEYLIST hLastKey = hKey;    // keep this for later

			hKey = GetKeyInfo(hKey, &lpszKeyName, &dwLength, &bHasCtrlChars, &nInstance);

			// Build web page
				    
			HtmlBold(pECB, "Form Field Name (lpszKeyName): ");
			HtmlWriteText(pECB, lpszKeyName);
			HtmlLineBreak(pECB);

			char szMsg[32];

			HtmlBold(pECB, "Length of Data (dwLength): ");
			wsprintf(szMsg, "%u", dwLength);
			HtmlWriteText(pECB, szMsg);
			HtmlLineBreak(pECB);

			HtmlBold(pECB, "Data Has Control Characters (bHasCtrlChars): ");
			wsprintf(szMsg, "%u", bHasCtrlChars);
			HtmlWriteText(pECB, szMsg);
			HtmlLineBreak(pECB);

			HtmlBold(pECB, "Instance of Form Field (nInstance): ");
			wsprintf(szMsg, "%u", nInstance);
			HtmlWriteText(pECB, szMsg);

			if (dwLength) {

				HtmlLineBreak(pECB);
				HtmlBold(pECB, "Data Sent for Field:");
				HtmlLineBreak(pECB);

				HexDumper(pECB, GetKeyBuffer(hLastKey), dwLength);
			}

			HtmlEndParagraph(pECB);
		}

		// Clean up
	  
		FreeKeyList(hKeyList);
	}

	HtmlHorizontalRule(pECB);

	// Get user name from SID and return it in the page

	HtmlHeading(pECB, 2, "Security Context for HttpExtensionProc Thread");
	WhoAmI(pECB);
	HtmlHorizontalRule(pECB);

	// Display all server variables

	HtmlHeading(pECB, 2, "Server Variables");
	HtmlWriteTextLine(pECB, "Below is a list of all variables available via");
	HtmlWriteTextLine(pECB, "GetServerVariable ISAPI API.  Much of this");
	HtmlWriteTextLine(pECB, "information comes from the browser HTTP header.");
	HtmlEndParagraph(pECB);

	// Send server variables obtained from the HTTP header

	SendVariables(pECB);

	// Finish up...

	HtmlEndPage(pECB);

	return HSE_STATUS_SUCCESS;
}

//	Description:
//
//		This is optional ISAPI extension DLL entry point. If present, it will be
//		called before unloading the DLL, giving it a chance to perform any
//		shutdown procedures.
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
	return TRUE;
}

//	Description:
//
//		Put the inbound data in a hex dump format
//
//	Arguments:
//
//		pECB - points to the extension control block
//		lpbyByf - bytes to dump
//		dwLength - specifies the number of bytes to dump

void HexDumper(IN EXTENSION_CONTROL_BLOCK *pECB, IN LPBYTE lpbyBuf, IN DWORD dwLength)
{
	DWORD dwPos = 0;

	HtmlBeginPreformattedText(pECB);

	while (dwLength) {

		// Take min of 16 or dwLength
		
		DWORD dwSize = min(16, dwLength );

		// Build text line

		char szLine[80];
		
		wsprintf(szLine, "  %04X ", dwPos);

		for (DWORD i = 0; i < dwSize; i++) {

			char szHex[3];

			wsprintf(szHex, "%02X", lpbyBuf[i]);

			lstrcat(szLine, szHex);
			lstrcat(szLine, " " );
		}

		// Add spaces for short lines
		
		for (DWORD i = strlen(szLine); i < 16; i++)
			lstrcat(szLine, "   ");

		// Add ASCII chars
		
		for (i = 0; i < dwSize; i++) {

			if (isprint(lpbyBuf[i])) {

				char szHex[3];

				wsprintf(szHex, "%c", lpbyBuf[i]);

				lstrcat(szLine, szHex );

			} else {

				lstrcat(szLine, "." );
			}
		}

		// Write data to web page
				
		HtmlWriteTextLine(pECB, szLine);

		// Advance positions
				
		dwLength -= dwSize;
		dwPos += dwSize;
		lpbyBuf += dwSize;
	}

	HtmlEndPreformattedText(pECB);
}

//	Description:
//    
//		Dump a server variable
//
//	Arguments:
//
//		pECB - points to the extension control block
//		lpbyByf - points to ASCIIZ name of the server variable to dump

void DumpVariable(IN EXTENSION_CONTROL_BLOCK *pECB, IN LPCTSTR szName)
{
	char szBuffer[MAX_BUFFER];

	DWORD dwBufferSize = sizeof szBuffer;

	if (dwBufferSize > MAX_BUFFER)
		return;

	BOOL bReturn = pECB->GetServerVariable(pECB->ConnID, (LPSTR)szName, szBuffer, &dwBufferSize);

	if (!bReturn || !szBuffer[0])
		return;

	HtmlWriteText(pECB, szName);
	HtmlWriteText(pECB, "=");
	HtmlWriteText(pECB, szBuffer);
	HtmlLineBreak(pECB);
}

//	Description:
//
//		Send specified HTTP status string and any additional header strings
//		using new ServerSupportFunction() request HSE_SEND_HEADER_EX_INFO
//
//	Arguments:
//
//		pECB - pointer to the extension control block
//		pszStatus - HTTP status string (e.g. "200 OK")
//		pszHeaders - any additional headers, separated by CRLFs and 
//									terminated by empty line
//
//	Returns:
//
//		TRUE if headers were successfully sent
//		FALSE otherwise

BOOL SendHttpHeaders(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR pszStatus, LPCSTR pszHeaders)
{
	HSE_SEND_HEADER_EX_INFO header_ex_info;

	header_ex_info.pszStatus = pszStatus;
	header_ex_info.pszHeader = pszHeaders;
	header_ex_info.cchStatus = strlen(pszStatus);
	header_ex_info.cchHeader = strlen(pszHeaders);
	header_ex_info.fKeepConn = FALSE;

	return pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &header_ex_info, NULL, NULL);
}

//	Description:
//
//		Send all server variables (they came in the HTTP header)
//    
//	Arguments:
//
//		pECB - pointer to the extension control block

void SendVariables(IN EXTENSION_CONTROL_BLOCK * pECB)
{
	char szBuffer[4096];

	// Dump the standard variables

	DumpVariable(pECB, "AUTH_TYPE");
	DumpVariable(pECB, "CONTENT_LENGTH");
	DumpVariable(pECB, "CONTENT_TYPE");
	DumpVariable(pECB, "GATEWAY_INTERFACE");
	DumpVariable(pECB, "PATH_INFO");
	DumpVariable(pECB, "PATH_TRANSLATED");
	DumpVariable(pECB, "QUERY_STRING");
	DumpVariable(pECB, "REMOTE_ADDR");
	DumpVariable(pECB, "REMOTE_HOST");
	DumpVariable(pECB, "REMOTE_USER");
	DumpVariable(pECB, "REQUEST_METHOD");
	DumpVariable(pECB, "SCRIPT_NAME");
	DumpVariable(pECB, "SERVER_NAME");
	DumpVariable(pECB, "SERVER_PORT");
	DumpVariable(pECB, "SERVER_PROTOCOL");
	DumpVariable(pECB, "SERVER_SOFTWARE");
	DumpVariable(pECB, "AUTH_PASS");

	// Dump any others (in ALL_HTTP)

	DWORD dwBufferSize = sizeof szBuffer;

	BOOL bReturn = pECB->GetServerVariable(pECB->ConnID, "ALL_HTTP", szBuffer, &dwBufferSize);

	if (bReturn) {

		// 
		// Find lines, split key/data pair and write them as output
		// 

		char *pChar = szBuffer;

		while (*pChar) {

			if (*pChar == '\r' || *pChar == '\n') {

				pChar++;

				continue;
			}

			char *pOpts = strchr(pChar, ':');   // look for separator

			if (!pOpts)
					break;

			if (!*pOpts)
					break;

			char *pEnd = pOpts;

			while (*pEnd && *pEnd != '\r' && *pEnd != '\n')
				pEnd++;

			*pOpts = 0;         // split strings

			*pEnd = 0;

			// pChar points to variable name, pOpts + 1 points to variable val

			HtmlWriteText(pECB, pChar);
			HtmlWriteText(pECB, "=");
			HtmlWriteText(pECB, pOpts + 1);
			HtmlLineBreak(pECB);

			pChar = pEnd + 1;
		}
	}

	HtmlEndParagraph(pECB);
	HtmlHorizontalRule(pECB);
}

//	Description:
//    
//		Get the user SID, lookup the account name and display it
//
//	Arguments:
//
//		pECB - pointer to the extension control block

void WhoAmI(IN EXTENSION_CONTROL_BLOCK *pECB)
{
	HANDLE hToken;
	BYTE byBuf[1024];
	DWORD dwLen;

	SID_NAME_USE eUse;

	if (!OpenThreadToken(GetCurrentThread( ), TOKEN_QUERY, TRUE, &hToken)) {
	        
		DWORD dwError = GetLastError();

		HtmlBold(pECB, "OpenThreadToken failed. ");
		HtmlPrintf(pECB, "Error code=%u", dwError);
		HtmlEndParagraph(pECB);

		return;
	}

	PTOKEN_USER pTokenUser = (PTOKEN_USER)byBuf;

	if (!GetTokenInformation(hToken, TokenUser, pTokenUser, sizeof byBuf, &dwLen)) {
	        
		DWORD dwError = GetLastError();

		CloseHandle(hToken);

		HtmlBold(pECB, "GetTokenInformation failed. ");
		HtmlPrintf(pECB, "Error code=%u dwLen=%u", dwError, dwLen);
		HtmlEndParagraph(pECB);

		return;
	}

	char szName[256], szDomain[256];

	DWORD dwNameLen = sizeof szName;
	DWORD dwDomainLen = sizeof szDomain;

	if (!LookupAccountSid(NULL, pTokenUser->User.Sid, szName, &dwNameLen, szDomain, &dwDomainLen, &eUse)) {
	        
		DWORD dwError = GetLastError();

		CloseHandle(hToken);

		HtmlBold(pECB, "LookupAccountSid failed. ");
		HtmlPrintf(pECB, "Error code=%u dwNameLen=%u dwDomainLen=%u", dwError, dwNameLen, dwDomainLen);
		HtmlEndParagraph(pECB);

		return;
	}

	HtmlBold(pECB, "Domain: ");
	HtmlWriteText(pECB, szDomain);
	HtmlLineBreak(pECB);
	HtmlBold(pECB, "User: ");
	HtmlWriteText(pECB, szName);
	HtmlEndParagraph(pECB);

	CloseHandle( hToken );
}

