/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                       dynept Example

    FILE:       dynepts.c

    USAGE:      dynepts  -p protocol_sequence
                         -m max calls
                         -n min calls
                         -f flag for RpcServerListen

    PURPOSE:    Server side of RPC distributed application dynept

    FUNCTIONS:  main() - registers server as RPC server

    COMMENTS:   This version of the distributed application that prints
                "What a dynamic world" (or other string) on the server
                features a client that manages its connection to the server.
                It uses the binding handle dynept_IfHandle, defined in
                the file dynept.h.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dynept.h"    // header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates\n\
the use of dynamic endpoints. For more information\n\
about the attributes and the RPC API functions, see the\n\
RPC programming guide and reference.\n\n"

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -m maxcalls\n");
    fprintf(stderr, " -n mincalls\n");
    fprintf(stderr, " -f flag_wait_op\n");
    exit(1);
}

/* main:  register the interface, start listening for clients */
void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    RPC_BINDING_VECTOR * pBindingVector = NULL;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszSecurity         = NULL;
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = FALSE;
    unsigned int    fRegistered         = 0;
    unsigned int    fEndpoint           = 0;
    int i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'm':
                cMaxCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'n':
                cMinCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'f':
                fDontWait = (unsigned int) atoi(argv[++i]);
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    status = RpcServerUseProtseq(pszProtocolSequence,
                                 cMaxCalls,
                                 pszSecurity);  // Security descriptor
    printf("RpcServerUseProtseq returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    status = RpcServerRegisterIf(dynept_ServerIfHandle,  // interface to register
                                 NULL,   // MgrTypeUuid
                                 NULL);  // MgrEpv; null means use default
    printf("RpcServerRegisterIf returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }
    else
        fRegistered = 1;

    status = RpcServerInqBindings(&pBindingVector);
    printf("RpcServerInqBindings returned 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    status = RpcEpRegister( dynept_ServerIfHandle,
                            pBindingVector,
                            NULL,
                            "" );
    printf("RpcEpRegister returned: 0x%x\n", status);
    if (status) {
        goto cleanup;
    }
    else
        fEndpoint = 1;

    printf("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);
    printf("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        goto cleanup;
    }

    if (fDontWait) {
        printf("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  // wait operation
        printf("RpcMgmtWaitServerListen returned: 0x%x\n", status);
    }

  cleanup:

    if ( fEndpoint )
    {
        status = RpcEpUnregister(dynept_ServerIfHandle,
                                 pBindingVector,
                                 NULL);
        printf( "RpcEpUnregister returned 0x%x\n", status);
    }

    if ( pBindingVector )
    {
        status = RpcBindingVectorFree(&pBindingVector);
        printf( "RpcBindingVectorFree returned 0x%x\n", status);
    }

    if ( fRegistered )
    {
        printf("Calling RpcServerUnregisterIf\n");
        status = RpcServerUnregisterIf(NULL, NULL, FALSE);
        printf("RpcServerUnregisterIf returned 0x%x\n", status);
    }

    exit (status);

}  // end main()


/*********************************************************************/
/*                MIDL allocate and free                             */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

/* end file dynepts.c */
