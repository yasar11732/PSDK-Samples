/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server

    FILE: FileRepServer.c
    
    PURPOSE: Provides file replication server.  The server
        lives in the executable and is not a system service
    
    COMMENTS:

*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <rpc.h>

// Generated by the MIDL compiler
#include "FileRepServer.h"
#include "FileRepClient.h"

// Contains declarations for system service functions.
#include "Service.h"

// Common definitions
#include "common.h"

/*
    RPC configuration.
*/

// The service listens to all the protseqs listed in this array.
// It listens for replication utilities on local RPC and for
// remote requests on TCP/IP
LPTSTR ServerProtocolArray[] = { TEXT("ncacn_ip_tcp"),
				 TEXT("ncalrpc") };

// Used in RpcServerUseProtseq.
// Specifies the maximum number of concurrent remote 
// procedure call requests the server wants to handle. 
ULONG cMaxCallsListen = RPC_C_PROTSEQ_MAX_REQS_DEFAULT;

// Similarly, but for RpcServerListen.
ULONG cMaxCallsExecute = RPC_C_LISTEN_MAX_CALLS_DEFAULT;

// Used in RpcServerListen().  The minnimum number of threads listening.
ULONG cMinimumThreads = 2;

RPC_BINDING_VECTOR * pBindingVector = NULL;

// Status variable for the RPC calls.
RPC_STATUS status;

/*
    FUNCTION: main()

    PURPOSE: Performs RPC initialization and listens for calls.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:

*/
INT _cdecl main(int argc, char **argv) {

    unsigned int i;

    // Register the service interfaces.
    status = RpcServerRegisterIf(s_FileRepServer_v1_0_s_ifspec, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerRegisterIf(s_FileRepServer_v1_0_s_ifspec, ...) failed\n"));
        exit(status);
    }
    status = RpcServerRegisterIf(FileRepClient_v1_0_s_ifspec, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerRegisterIf(FileRepClient_v1_0_s_ifspec, ...) failed\n"));
        exit(status);
    }

    for (i = 0; i < sizeof(ServerProtocolArray)/sizeof(unsigned char *); i++) {

        // Use the protocol sequences specified in ProtocolArray
        // for receiving RPCs.
        status = RpcServerUseProtseq((_TUCHAR *)ServerProtocolArray[i], cMaxCallsListen, NULL);

        if (status != RPC_S_OK){
            AddToMessageLog(TEXT("ServiceStart: RpcServerUseProtseq failed\n"));
            exit(status);
        }
    }

    // Obtain a binding vector for the server.
    status = RpcServerInqBindings(&pBindingVector);
    if (status != RPC_S_OK) {
        AddToMessageLog(TEXT("ServiceStart: RpcServerInqBindings failed\n"));
        exit(status);
    }
    
    // Register the client and the server services in the endpoint map
    // of the host computer.
    status = RpcEpRegister(s_FileRepServer_v1_0_s_ifspec, pBindingVector, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcEpRegister(s_FileRepServer_v1_0_s_ifspec, ...) failed\n"));
        exit(status);
    }
    status = RpcEpRegister(FileRepClient_v1_0_s_ifspec, pBindingVector, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcEpRegister(FileRepClient_v1_0_s_ifspec, ...) failed\n"));
        exit(status);
    }

    // Create the heap to be used by midl_user_allocate and midl_user_free
    RpcHeap = HeapCreate(0, RPC_HEAP_SIZE_INIT, RPC_HEAP_SIZE_MAX);
    
#ifdef PROF
    ProfOpenLog(TEXT("FileRepService.prof"));
#endif

    // Start accepting client calls.
    // The last argument's being 1 indicates that RpcServerListen
    // should return immediately after completing function processing. 
    status = RpcServerListen(cMinimumThreads, cMaxCallsExecute, 1);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerListen failed\n"));
        exit(status);
    }

    // End of initialization

    // RpcMgmtWaitServerListen() will block until the server has
    // stopped listening.
    status = RpcMgmtWaitServerListen();
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcMgmtWaitServerListen failed"));
        exit(status);
    }
    
    // Cleanup
    
    // Delete the binding vector.
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    if(status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerUnregisterIf failed"));
        exit(status);
    }
    
    return 0;
} // end main()

// end FileRepServer.cpp
