/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server System Service

    FILE: Service.h
    
    PURPOSE: Provides file replication service function declarations.
    
    FUNCTIONS:

    COMMENTS: These funtions may be used by the main service routines
        as well as by the client and server file replication RPC routines.

*/
#pragma once

#include "Resources.h"

// Name of the executable
#define APPNAME TEXT("FileRepService")

// Internal name of the service
#define SERVICENAME TEXT("FileRepService")

// Displayed name of the service
#define SERVICEDISPLAYNAME TEXT("File Replication Service")

// List of service dependencies
#define DEPENDENCIES TEXT("RPCSS\0\0")

#ifdef PROF
#include "Prof.h"
#endif

// The maximum number of concurrent requests that can be handled
// by the server system service for each of the priority groups.
extern const UINT ServerReqBounds[];

// The maximum number of requests that can be placed to the client
// system service from each user group.
extern const UINT ClientReqBounds[];

// The maximum number of concurrent requests that a client system
// service will handle.
extern const UINT ClientActiveReqBounds[];

// The number of priority groups.
extern const UINT NumPriGroups;

extern Counter *pServerReqCounters[];
extern Counter *pClientReqCounters[];
extern Counter *pClientActiveReqCounters[];

// Keeps queued requests.
extern Queue *ClientReqQueues[];

// Keeps requests that are being handled.
extern Queue *ClientActiveReqHashQueues[];

// Conteins the number of requests that are being
// handled for each user.
extern Queue *ClientActiveReqHashCounters[];

// The maximum number of requests for a single
// user that can be handled simultaneously.
extern const UINT MaxUserReqs;

// The priority of regular users.
// A separate queue is maintained for
// scheduling each user's requests on the client.
extern const UINT RegUsersPri;

/*
    Prototypes for shared service functions.
    See function definitions in Service.cpp for help.
*/

PSID GetUserSID();

PTOKEN_GROUPS GetUserGroups();

BOOL IsGroupMember(PSID pSID, PTOKEN_GROUPS pGroupInfo);

VOID CreateWellKnownSids(VOID);

VOID DeleteWellKnownSids(VOID);

UINT GetCurrentUserPriority(VOID);

BOOL ReportStatusToSCMgr(SERVICE_STATUS_HANDLE *sshStatusHandle,
                         SERVICE_STATUS *ssStatus,
                         DWORD dwCurrentState,
                         DWORD dwWin32ExitCode,
                         DWORD dwWaitHint);

VOID AddToMessageLog(LPTSTR lpszMsg);

VOID AddToMessageLogProcFailure(LPTSTR ProcName, DWORD ErrCode);

VOID AddToMessageLogProcFailureEEInfo(LPTSTR ProcName, DWORD ErrCode);

VOID AddRpcEEInfo(DWORD Status, LPTSTR Msg);

VOID AddRpcEEInfoAndRaiseException(DWORD Status, LPTSTR Msg);

// RPC heap size bounds.
#define RPC_HEAP_SIZE_INIT (1024*1024)
#define RPC_HEAP_SIZE_MAX (128*1024*1024)

// Heap for use by midl_user_allocate and midl_user_free.
extern HANDLE RpcHeap;

VOID * AutoHeapAlloc(size_t dwBytes);

VOID AutoHeapFree(VOID * lpMem);

// end Service.h
