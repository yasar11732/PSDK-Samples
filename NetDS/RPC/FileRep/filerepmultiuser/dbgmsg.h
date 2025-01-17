/*
    Copyright Microsoft Corp. 1992 - 2001

    Debugging Routines

    FILE: DbgMsg.h
    
    PURPOSE: Routines for debugging system services
    
    FUNCTIONS:
        DbgMsgOpenLog - Opens the profile log.
        DbgMsgRecord - Records and event.
        DbgMsgCloseLog - Closes the profile log.

*/
#pragma once

// Maximum size for the debug log.
// After the log reaches this size new entries "fall off" (threy
// do not get reorded).
#define DEBUG_LOG_MAX_SIZE (10*1024*1024)

// Used for mutial exclusion when generating and 
// writing the debug information.
extern CRITICAL_SECTION DbgMsgCriticalSection;

/*
    FUNCTION: DbgMsgOpenLog

    COMMENTS:

*/
VOID DbgMsgOpenLog(LPTSTR LogFileName);

/*
    FUNCTION: DbgMsgRecordTime

    COMMENTS:  If the maximum log size has been exceeded, no action is taken.

*/
VOID DbgMsgRecord(LPTSTR msg);

/*
    FUNCTION: DbgMsgCloseLog

    COMMENTS:

*/
VOID DbgMsgCloseLog(VOID);

// end DbgMsg.h
