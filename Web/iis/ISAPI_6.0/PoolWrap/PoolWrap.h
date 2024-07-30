/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: PoolWrap.h

Abstract:

    Header file for PoolWrap

Author:

    ISAPI developer (Microsoft employee)

--*/

#define MODULE_NAME "DemoPoolWrap"

extern LONG g_QueueFullPages;
extern LONG g_TotalRequests;

#ifdef __cplusplus
extern "C" {
#endif

BOOL
InitThread(
    VOID
    );

VOID
UninitThread(
    VOID
    );

BOOL
IsapiWriteLog(
    LPSTR   szString,
    ...
    );

#ifdef __cplusplus
}
#endif