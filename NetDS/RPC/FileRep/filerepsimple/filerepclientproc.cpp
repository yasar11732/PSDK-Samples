/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Client System Service

    FILE: FileRepClientProc.cpp
    
    PURPOSE: Remote procedures for client system service
    
    FUNCTIONS:
        RequestFile() - receives file replication requests
	ThreadProcRequest() - processes file replication requests
    in an independent thread.

    COMMENTS:

*/

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#include "common.h"

// header file generated by MIDL compiler
#include "FileRepClient.h"
#include "FileRepServer.h"

// Contains declarations for system service functions.
#include "Service.h"

// This structure simply packages up the variables to be passed
// to the processing thread.
typedef struct {
    handle_t hFileRepServer;
    HANDLE hLocalFile;
    PCONTEXT_HANDLE_TYPE phContext;
    BYTE pbBuf[MAX_BUFSIZE];
#ifdef PROF
    ULONG nReqId;
#endif
} ThreadArgs;

// Closes the file handle and frees all thread data if an error occured
// in one of the following functions.
VOID ShutdownThread(ThreadArgs *pArgs) {
    INT status;
    RPC_STATUS rpcstatus;

    if(pArgs != NULL) {
	if(pArgs->hFileRepServer != NULL) {
	    rpcstatus = RpcBindingFree(&(pArgs->hFileRepServer));
	    ASSERTE(rpcstatus == RPC_S_OK);
	}
	// Check that hLocalFile has been initialized and that initialization
	// was successful.
	if(pArgs->hLocalFile != NULL && pArgs->hLocalFile != INVALID_HANDLE_VALUE) {
	    status = CloseHandle(pArgs->hLocalFile);
	    ASSERTE(status != 0);
	}
	if(pArgs->phContext != NULL) {
	    RpcSsDestroyClientContext((VOID **)&pArgs->phContext);
	}
	AutoHeapFree(pArgs);
    }
}

/*
    FUNCTIONS: ThreadProcRequest

    PURPOSE:
        Called by FileRepRequestFile to have the Client System
        Service process the file replication request.

    PARAMETERS:
        Self-explanatory.

    RETURN VALUE: STATUS_SUCCESS or 1
 
*/
void ThreadProcRequest(ThreadArgs *pArgs) {
    UINT i = 0;
    ULONG cbRead, cbWritten;

    TCHAR Msg[MSG_SIZE];

    // Get the remainder of text from the remote file.  When the
    // server returns a NULL context handle, the read has completed and
    // the file has been closed.
    do {

        // We did not read anything yet.
        cbRead = 0;

#ifdef RETRY_EXCEPTION
	// When making aggressive calls to the server, this flag is
	// set when the call succeeded.  This makes the client service attempt
	// to contact the server even after an exception occured.
	BOOL bRetryCall = TRUE;
	while (bRetryCall) {
#endif

        RpcTryExcept {
            c_RemoteRead(pArgs->hFileRepServer,
			 &(pArgs->phContext),
			 pArgs->pbBuf,
			 &cbRead);

#ifdef RETRY_EXCEPTION
	    bRetryCall = FALSE;
#endif

	}
        RpcExcept ( ( (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
		      (RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
		      (RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
		      (RpcExceptionCode() != STATUS_ILLEGAL_INSTRUCTION) &&
		      (RpcExceptionCode() != STATUS_BREAKPOINT))
		    ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH ) {
	  
	    // Log the error code as well as the error.
	    // Msg is sufficiently large and can't overflow.
	    _stprintf(Msg, TEXT("ThreadProcRequest: Exception: c_RemoteRead failed with code %d"), RpcExceptionCode());
	    AddToMessageLog(Msg);

#ifdef RETRY_EXCEPTION
	    // This code attempts to make aggressive calls, retrying
	    // if no endpoints were available.  It is used to put servers
	    // under stress.
	    if (RpcExceptionCode() != EPT_S_NOT_REGISTERED &&
		RpcExceptionCode() != RPC_S_SERVER_UNAVAILABLE) {
#endif
	    ShutdownThread(pArgs);
	    return;
#ifdef RETRY_EXCEPTION
	    }
#endif
	}
	RpcEndExcept;

#ifdef RETRY_EXCEPTION
	}
#endif

	if(!WriteFile(pArgs->hLocalFile,
		      pArgs->pbBuf,
		      cbRead,
		      &cbWritten,
		      NULL)) {

	    _stprintf(Msg, TEXT("ThreadProcRequest: WriteFile failed with code %d"), GetLastError());
	    AddToMessageLog(Msg);

	    ShutdownThread(pArgs);
	    return;
	}
    } while(pArgs->phContext != NULL);

#ifdef PROF
    ProfRecordTime(pArgs->nReqId, TEXT("handled"));
#endif

    ShutdownThread(pArgs);

    // After this procedure returns the replication request will have
    // been handled.
    return;
}

/*
    FUNCTIONS: RequestFile

    PURPOSE:
        Called by FileRep to have the Client System
        Service request file replication from a Server System Service.

    PARAMETERS:
        Self-explanatory.

    RETURN VALUE: STATUS_SUCCESS or 1
 
*/
VOID RequestFile(handle_t hFileRepClient,
		 LPTSTR ServerName,
		 LPTSTR RemoteFileName,
		 LPTSTR LocalFileName)
{
    INT status;
    RPC_STATUS rpcstatus;

    ULONG cbRead, cbWritten;

    // Default connection to server system service is over TCP/IP.
    LPTSTR DefaultProtocolSequence = TEXT("ncacn_ip_tcp");
    
    // An empty endpoint string is used, since we are going to
    // connect to the endpoint dynamically generated by the
    // RPC run-time library.    Server calls RpcServerUseProtseq to
    // obtain a binding hadnle and a dynamic endpoint.
    LPTSTR DefaultEndpoint = TEXT("");

    LPTSTR pszUuid = NULL;
    LPTSTR pszOptions = NULL;
    LPTSTR pszStringBinding = NULL;

    ULONG ThreadIdentifier;
    HANDLE hThread;

    ThreadArgs *pArgs = NULL;

    if((pArgs = (ThreadArgs *) AutoHeapAlloc(sizeof(ThreadArgs))) == NULL) {
        RpcRaiseException(ERROR_OUTOFMEMORY);	    
        return;
    }

    // Set pArgs' fields to NULL so that we will know
    // in ShutdownThread which ones have been initialized.
    pArgs->hFileRepServer = NULL;
    pArgs->hLocalFile = NULL;
    pArgs->phContext = NULL;

#ifdef PROF
    static ULONG nTotalId;

    if (WaitForSingleObject(hProfMutex, INFINITE) == WAIT_FAILED) {
	RaiseException(GetLastError(), 0, 0, NULL);
	return;
    }

    // Record the number of the current request.
    pArgs->nReqId = nTotalId;
    // Increment the number of the request.
    nTotalId++;

    if (ReleaseMutex(hProfMutex) == FALSE) {
	RaiseException(GetLastError(), 0, 0, NULL);
	return;
    }

    TCHAR ProfMsg[MAX_PATH+16];
    _stprintf(ProfMsg, TEXT("name=\"%s\" arrived"), RemoteFileName);

    // Record the time of arrival of this request.
    ProfRecordTime(pArgs->nReqId, ProfMsg);
#endif

    // Prepare the binding information.
    if ((rpcstatus = RpcStringBindingCompose(pszUuid,
					     DefaultProtocolSequence,
					     ServerName,
					     DefaultEndpoint,
					     pszOptions,
					     &pszStringBinding)) != RPC_S_OK) {
      
	ShutdownThread(pArgs);
        RpcRaiseException(rpcstatus);
	return;
    }

    if ((rpcstatus = RpcBindingFromStringBinding(pszStringBinding, &(pArgs->hFileRepServer))) != RPC_S_OK) {
	// The binding handle is invalid
	pArgs->hFileRepServer = NULL;

	ShutdownThread(pArgs);
        RpcRaiseException(rpcstatus);
	return;
    }

    // We need to delete the string binding, since it is no longer
    // necessary.  All the binding information is now contained in the
    // binding handle.
    rpcstatus = RpcStringFree(&pszStringBinding);
    ASSERTE(rpcstatus == RPC_S_OK);

    // We did not read anything yet.
    cbRead = 0;

#ifdef RETRY_EXCEPTION
    // When making aggressive calls to the server, this flag is
    // set when the call succeeded.  This makes the client service attempt
    // to contact the server even after an exception occured.
    BOOL bRetryCall = TRUE;
    while (bRetryCall) {
#endif

    // Attempt to open the remote file.
    RpcTryExcept {
        c_RemoteOpen(pArgs->hFileRepServer,
		     &(pArgs->phContext),
		     RemoteFileName,
		     pArgs->pbBuf,
		     &cbRead);

#ifdef RETRY_EXCEPTION
	bRetryCall = FALSE;
#endif

    }
    RpcExcept ( ( (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
		  (RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
		  (RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
		  (RpcExceptionCode() != STATUS_ILLEGAL_INSTRUCTION) &&
		  (RpcExceptionCode() != STATUS_BREAKPOINT) )
		  ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH ) {
	
#ifdef RETRY_EXCEPTION
	// This code attempts to make aggressive calls, retrying
	// if no endpoints are available.  It is used to put servers
	// under stress.
	if (RpcExceptionCode() != EPT_S_NOT_REGISTERED &&
	    RpcExceptionCode() != RPC_S_SERVER_UNAVAILABLE) {
#endif
	ShutdownThread(pArgs);
        RpcRaiseException(RPC_S_CALL_FAILED);
	return;
#ifdef RETRY_EXCEPTION
        }
#endif
    }
    RpcEndExcept;

#ifdef RETRY_EXCEPTION
    }
#endif

    // Attempt to open the local file.
    if ((pArgs->hLocalFile = CreateFile(LocalFileName,
					GENERIC_WRITE,
					0,
					NULL,
					CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL)) == INVALID_HANDLE_VALUE) {
	ShutdownThread(pArgs);
        RpcRaiseException(GetLastError());
	return;
    }

    // Write the data received to local file.
    if(!WriteFile(pArgs->hLocalFile,
		  pArgs->pbBuf,
		  cbRead,
		  &cbWritten,
		  NULL)){

	ShutdownThread(pArgs);
        RpcRaiseException(GetLastError());
        return;
    }

    // If there are no errors and the call returned NULL, then
    // the file was read in a single call and has already been closed.
    // We just need to write the buffer and return.
    if(pArgs->phContext == NULL){

#ifdef PROF
	ProfRecordTime(pArgs->nReqId, TEXT("handled"));
#endif

	ShutdownThread(pArgs);
        return;
    }

    // We need to read and close the file on a different
    // thread so that the client replication utility can return.
    // The data will be transfered in the background.
    if((hThread = CreateThread(NULL,
			       0,
			       (LPTHREAD_START_ROUTINE) ThreadProcRequest,
			       pArgs,
			       0,
			       &ThreadIdentifier)) == NULL) {

	ShutdownThread(pArgs);
        RpcRaiseException(GetLastError());
	return;
    }

    // Unless we close a handle to the thread, it will remain in the
    // system even after its execution has terminated.
    status = CloseHandle(hThread);
    ASSERTE(status != 0);

    // The memory will be freed and handles closed in ThreadProcRequest.

    return;
}

// end FileRepClientProc.cpp