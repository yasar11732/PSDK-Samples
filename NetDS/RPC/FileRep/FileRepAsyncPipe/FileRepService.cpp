/*

    File Replication Sample
    Server System Service

    FILE: FileRepService.cpp
    
    PURPOSE: Provides file replication services.
    
    USAGE: 
        FileRepService

    FUNCTIONS:
        main() - calls the StartServiceCtrlDispatcher function to
            connect to the SCM and start the control dispatcher thread.
        ServiceMain() - the entry point for the service.
        ServiceCtrl() - this function is called by the dispatcher thread.
            It handles the control code passed to it.
        ServiceStart() - performs actual initialization and starts the service.
            Makes the RPC server listen for calls.
        ServiceStop() - stops listening for RPCs.

    COMMENTS:

*/

// Common definitions
#include "common.h"

#define SECURITY_WIN32

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <rpc.h>
#include <Ntdsapi.h>
#include <Ntsecapi.h>
#include <Security.h>
#include <Secext.h>
#include <Dsgetdc.h>
#include <Lm.h>

// Generated by the MIDL compiler
#include "FileRepServer.h"
#include "FileRepClient.h"

// Contains declarations for system service functions.
#include "Service.h"

#ifdef PROF
#include "Prof.h"
#endif

#ifdef DEBUG1
#include "DbgMsg.h"
#endif

/*
    Internal funtion declarations.
    See definitions for more info.
*/

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

VOID WINAPI ServiceCtrl(DWORD Opcode);

VOID ServiceStart(DWORD dwArgc, LPTSTR *lpszArgv);

VOID ServiceStop();

/*
    FUNCTION: main()

    PURPOSE: main() calls StartServiceCtrlDispatcher to register the
        main service thread.    When this call returns,
        the service has stopped.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
*/
VOID _cdecl main(int argc, char **argv){

    // Since we provide a single service there is only
    // one entry in the service dispatch table
    SERVICE_TABLE_ENTRY DispatchTable[] = {
        { SERVICENAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

    // The service control manager may be starting the service with
    // this call, so we must call StartServiceCtrlDispatcher.
    if (!StartServiceCtrlDispatcher(DispatchTable)) {
        AddToMessageLog(TEXT("StartServiceCtrlDispatcher failed"));
    }
}

/*
    FUNCTION: ServiceMain

    PURPOSE: To perform actual initialization of the client service.    It
        is the entry point into the service.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
        This routine performs the service initialization and then calls
        the user defined ServiceStart() routine to perform majority
        of the work.
*/
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv) {

    // Initial service configuration
    ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
    ssStatus.dwCurrentState = SERVICE_START_PENDING; 
    ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ssStatus.dwWin32ExitCode = 0; 
    ssStatus.dwServiceSpecificExitCode = 0; 
    ssStatus.dwCheckPoint = 0; 
    ssStatus.dwWaitHint = 0; 
    
    sshStatusHandle = RegisterServiceCtrlHandler(SERVICENAME, ServiceCtrl);

    // Tell the SCM that the service is starting up.
    if (!SetServiceStatus(sshStatusHandle, &ssStatus)) {
        AddToMessageLog(TEXT("ServiceMain: SetServiceStatus failed\n"));
        return; 
    } 
    
    // Initialize the service and start it.
    ServiceStart(dwArgc, lpszArgv);

    return; 
}

/*
    FUNCTION: ServiceCtrl

    PURPOSE: This function is called by the SCM whenever
        ControlService() is called on this service.

    PARAMETERS:
        dwCtrlCode - type of control requested

    RETURN VALUE:
        none

    COMMENTS:
*/

VOID WINAPI ServiceCtrl(DWORD Opcode) { 

    // We only handle the STOP control requsts.
    switch(Opcode) {

        case SERVICE_CONTROL_STOP: 
            // Stop the service. 
            ServiceStop();
            break;

        default: 
            AddToMessageLog(TEXT("ServiceCtrl: unrecognized or unimplemented opcode\n"));
    }

    return; 
}

/*
    FUNCTION: ServiceStart

    PURPOSE: Actual code of the service
             that does the work.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
        Starts the service listening for RPC requests.
*/
VOID ServiceStart (DWORD dwArgc, LPTSTR *szArgList){
  RPC_STATUS status;

    // Report the status to the service control manager.
    if (!ReportStatusToSCMgr(&sshStatusHandle, &ssStatus, SERVICE_START_PENDING, NO_ERROR, 1000)) {
        AddToMessageLog(TEXT("ServiceStart: ReportStatusToSCMgr failed\n"));
        ServiceStop();
        return;
    }

    // Allow the user to override settings with command line switches.
    for (unsigned i = 1; i < dwArgc; i++) {
        // Well-formed argument switches start with '/' or '-' and are
        // two characters long.
        if (((*szArgList[i] == TEXT('-')) || (*szArgList[i] == TEXT('/'))) && _tcsclen(szArgList[i]) == 2) {

            switch (_totlower(*(szArgList[i]+1))) {

                case TEXT('f'):
		  bNoFileIO = true;
		  break;

                default:
		  AddToMessageLog(TEXT("ServiceStart: bad arguments"));
		  ServiceStop();
		  return;
            }
        }
        else {
	  AddToMessageLog(TEXT("ServiceStart: bad arguments"));
	  ServiceStop();
	  return;
        }
    }


    if (!StartFileRepServer()) {
      ServiceStop();
    }
    else {
      bServerListening = TRUE;

      // Tell The SCM that the service is running.
      if (!ReportStatusToSCMgr(&sshStatusHandle, &ssStatus, SERVICE_RUNNING, NO_ERROR, 0)){
        AddToMessageLog(TEXT("ServiceStart: ReportStatusToSCMgr failed"));
        ServiceStop();
        return;
      }

      // RpcMgmtWaitServerListen() will block until the server has
      // stopped listening.
      status = RpcMgmtWaitServerListen();
      if (status != RPC_S_OK){
        AddToMessageLogProcFailureEEInfo(TEXT("ServiceStart: RpcMgmtWaitServerListen"), status);
        ServiceStop();
        return;
      }
    }

    return;
}

VOID ServiceStop(VOID) {
  ServerStop();
}

// end FileRepService.cpp
