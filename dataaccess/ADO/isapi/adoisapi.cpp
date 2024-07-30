//--------------------------------------------------------------------
// Microsoft ADO
//
// (c) 1991-2000 Microsoft Corporation.  All Rights Reserved.
//
// @doc
//
// @module	adoisapi.cpp | ADO ISAPI sample application
//
// @devnote None
//--------------------------------------------------------------------

#pragma warning( disable : 4146 )
// defines: ,_MBCS,_USRDLL,ISAPI_EXPORTS
const char *szProgLog = "c:\\AdoIsapi.txt";
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#include <httpext.h>
#include <stdio.h>

VOID PatchQuery(char *szQuery, char **ppszPatchedQuery);
HRESULT	FetchData(EXTENSION_CONTROL_BLOCK *pECB);
VOID OutputErrors(EXTENSION_CONTROL_BLOCK *pECB, HRESULT hrError);
VOID OutputString(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR szBuffer);
void DebugLog( const char *szErrStr, const char *FName, const int lNum  ) ; 

#ifdef _DEBUG
#define LogError( x )   DebugLog( (x),(__FILE__), (__LINE__))
#else
#define LogError( x )  
#endif 

// Connection String for Microsoft Jet Database
//const PCSTR g_pszConnection = "dsn=OLE_DB_NWind_Jet;uid=Admin;pwd=;";

// Connection String for Microsoft SQL Server Database
const PCSTR g_pszConnection = "Provider=SQLOLEDB;data source=YOUR SERVER NAME;initial catalog=northwind;uid=YOUR USER ID;pwd=YOUR USER's PASSWORD;";


BOOL WINAPI	GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
    // Initialize COM
    CoInitialize(NULL);    
    LogError("GetExtensionVersion()");
    
	pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR, HSE_VERSION_MAJOR );

	lstrcpynA( pVer->lpszExtensionDesc, "Sample ADO ISAPI Application", HSE_MAX_EXT_DLL_NAME_LEN );

	return TRUE;
} // end -- BOOL WINAPI	GetExtensionVersion(HSE_VERSION_INFO *pVer) 

BOOL WINAPI TerminateExtension(  DWORD dwFlags  )
{    
    // Unregister COM
    CoUninitialize();
    return TRUE;
} // end -- BOOL WINAPI TerminateExtension(  DWORD dwFlags  )


DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB )
{
	DWORD	dwWritten;
	char	szContent[] = "Content-type: text/html\r\n\r\n";
    LogError("HttpExtensionProc() -- entry");	
	dwWritten = sizeof(szContent);
    pECB->ServerSupportFunction (pECB->ConnID,
                                 HSE_REQ_SEND_RESPONSE_HEADER,
                                 NULL,
                                 &dwWritten,
                                 (LPDWORD)szContent);

	if (FAILED(FetchData(pECB)))
    {
        LogError("HttpExtensionProc() -- Failed...");	
		return HSE_STATUS_ERROR;
    }
	else
    {
        LogError("HttpExtensionProc() -- Successful...");	
		return HSE_STATUS_SUCCESS;
    }
} // end -- DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB ) 

char ConvertHexToDec(char cHex)
{                   
	if ((toupper(cHex) >= 'A') && (toupper(cHex) <= 'F'))
		return cHex - 'A' + 10;
	else
		return cHex - '0';
} // end -- char ConvertHexToDec(char cHex) 

// Hack to clean up the query string. This code will work
// for most, but not all cases. For instance when the query 
// string has embedded '+', this code will not work.
VOID PatchQuery(char *szQuery, char **ppszPatchedQuery)
{
	char *p = szQuery + 1;
	
	while (*p++)
	{
		if (*p == '+') //replace '+' by ' '
        {
            *p = ' ';
        }

		if( *p == '%' ) //a number begins
		{
			char ch;

			if (*++p)
			{
				ch = ConvertHexToDec(*p) << 4; //convert the first digit

				if (*++p)
				{
					ch |= ConvertHexToDec(*p);  //convert the 2nd digit
					
					if (!*(p + 1))
					{
						*(p-2) = ch;
						*(p-1) = '\0';
						break;
					}
					else
					{
						*(p-2) = ' ';
						*(p-1) = ' ';
						*p = ch;
					}
				}   
			}   
		}   
	} 

	*ppszPatchedQuery = szQuery + 1;
  	return;
}   // end -- VOID PatchQuery(char *szQuery, char **ppszPatchedQuery)

VOID OutputString(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR szBuffer)
{    
	DWORD dwBuffer = strlen(szBuffer);
	pECB->WriteClient(pECB->ConnID, (PVOID) szBuffer, &dwBuffer, 0);
    
    // for debugging we save the output to a file if _DEBUG is defined...
    LogError(szBuffer);
} // end -- VOID OutputString(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR szBuffer)

VOID OutputErrors(EXTENSION_CONTROL_BLOCK *pECB, _com_error &e)
{
	char		szBuffer[512];
	
	// output hresult
	OutputString(pECB, "<P><H1>Error Fetching Data</H1>");

	sprintf(szBuffer, "<p>Code = %08lx", e.Error());
	OutputString(pECB, szBuffer);

    sprintf(szBuffer, "<p>Code meaning = %s", e.ErrorMessage());
    OutputString(pECB, szBuffer);

	_bstr_t bstrSource(e.Source());
    sprintf(szBuffer, "<p>Source = %s", (LPCSTR) bstrSource);
	OutputString(pECB, szBuffer);
    
	_bstr_t bstrDescription(e.Description());
    sprintf(szBuffer, "<p>Description = %s", (LPCSTR) bstrDescription);
	OutputString(pECB, szBuffer);
    
	return;
} // end -- VOID OutputErrors(EXTENSION_CONTROL_BLOCK *pECB, _com_error &e)

HRESULT	FetchData(EXTENSION_CONTROL_BLOCK *pECB)
{
	HRESULT			hr = NOERROR;
	bool			fComInitialized = false;
	_RecordsetPtr	pRs = NULL;
    _ConnectionPtr  pConn = NULL; 
	FieldPtr		*rgflds = NULL;
	long			lNumFields, lFld;
	char			*pszPatchedQuery, *pszQueryPtr;
	_variant_t		vValue;
	
	OutputString(pECB, "<HEAD><TITLE>Query Results"
						"</TITLE></HEAD>\r\n<BODY>\r\n");

	OutputString(pECB, "<LINK REL=\"STYLESHEET\" HREF=\"..\\ADOStyle.css\">\r\n");

	// Updated Code to support IE 4 semantics requiring controls passed as parameters to be named
	// Search for the new parameter "Query=" in the string, and then use PatchQuery starting at the
	// equals sign.  Note: If other parameters are passed as part of the form, this code needs to 
	// be updated to find the end of the parameter and not use the entire rest of the lpszQueryString
	pszQueryPtr = strstr(pECB->lpszQueryString, "Query=") + strlen("Query=") - 1;
	PatchQuery(pszQueryPtr, &pszPatchedQuery);

	OutputString(pECB, "<P><H2>Query String</H2>");
	OutputString(pECB, pszPatchedQuery);		
	LogError(pszPatchedQuery);
	try
	{
		if (FAILED(hr = ::CoInitialize(NULL)))
        {
            _com_issue_error(hr);
        }

		fComInitialized = true;

        // Create the connection object
        pConn.CreateInstance(__uuidof(Connection ));  
        LogError( "Create Connetion object fine...");
        pConn->ConnectionString  = g_pszConnection;
        pConn->Open("","","",-1);
        LogError( "Opened Connetion object fine...");
		// Open the recordset
		pRs.CreateInstance(__uuidof(Recordset) );
        LogError( "Created  Recordset object fine...");
        pRs->PutRefActiveConnection(pConn);
        LogError( "Set Referend from Rs to Conn");
		pRs->Open(pszPatchedQuery, vtMissing, adOpenForwardOnly, adLockReadOnly, adCmdUnknown);
        LogError( "Opended Recordset object fine...");                      			
		lNumFields = pRs->Fields->Count;

		rgflds = new FieldPtr[lNumFields];
		if (!rgflds)
        {
            _com_issue_error(E_OUTOFMEMORY);
        }
		memset(rgflds, 0, lNumFields * sizeof(FieldPtr));

		for (lFld = 0; lFld < lNumFields; lFld++)
        {
            rgflds[lFld] = pRs->Fields->GetItem(lFld);
        }

		OutputString(pECB, "<P><H2>Query Results</H2>");
		OutputString(pECB, "<P><TABLE BORDER=1 CELLSPACING=4>");

		//
		// print column names
		//
		OutputString(pECB, "<TR>");

		for (lFld = 0; lFld < lNumFields; lFld++)
		{
			OutputString(pECB, "<TH>");
			OutputString(pECB, (PCSTR)(_bstr_t)rgflds[lFld]->Name);
		}
		
		//
		// print data
		// 
		while (VARIANT_FALSE == pRs->EndOfFile)
		{
 			OutputString(pECB, "<TR>");

			for (lFld = 0; lFld < lNumFields; lFld++)
			{
 				OutputString(pECB, "<TD>");

				vValue = rgflds[lFld]->Value;
				if (VT_NULL == vValue.vt)
					OutputString(pECB, "(Null)");
				else
					OutputString(pECB, (PCSTR)(_bstr_t)vValue);
			}

 			OutputString(pECB, "</TR>");

			pRs->MoveNext();
		}

		OutputString(pECB, "</TABLE>");
		OutputString(pECB, "</BODY>\r\n");
	}
	catch (_com_error &e)
	{
		OutputErrors(pECB, e);
		hr = e.Error();
	}

	if (rgflds)
			delete[] rgflds;
	
	pRs = NULL;

	if (fComInitialized)
    {
        ::CoUninitialize();
    }
	
	OutputString(pECB, "</BODY>\r\n");

	return hr;

} // end -- HRESULT	FetchData(EXTENSION_CONTROL_BLOCK *pECB)

void DebugLog( const char *szErrStr ,const char *FName, const int lNum  ) 
{
    FILE *fp;
    if( (fp=fopen(szProgLog,"at+")) == NULL )
    {
        return ;
    }

    fprintf(fp,"Error %s (%d): %s\n",FName,lNum,szErrStr ); 
    fclose(fp);

} //  end -- void DebugLog( const char *szErrStr ,const char *FName, const int lNum  ) 