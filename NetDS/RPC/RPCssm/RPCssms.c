/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                        rpcssm Example

    FILE:       rpcssms.c

    USAGE:      rpcssms  -p protocol_sequence
                         -e endpoint
                         -m max calls
                         -n min calls
                         -f flag for RpcServerListen

    PURPOSE:    Server side of RPC distributed application rpcssm

    FUNCTIONS:  main() - registers server as RPC server

    COMMENTS:   This distributed application uses a context handle.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "rpcssm.h"    // header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates\n\
the [context_handle] attribute. For more information\n\
about this attribute and the RPC API functions, see the\n\
RPC programming guide and reference.\n\n"

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -e endpoint\n");
    fprintf(stderr, " -m maxcalls\n");
    fprintf(stderr, " -n mincalls\n");
    fprintf(stderr, " -f flag_wait_op\n");
    exit(1);
}

void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszSecurity         = NULL;
    unsigned char * pszEndpoint         = "\\pipe\\rpcssm";
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = TRUE;
    int i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
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

    status = RpcServerUseProtseqEp(pszProtocolSequence,
                                   cMaxCalls,
                                   pszEndpoint,
                                   pszSecurity);  // Security descriptor
    printf("RpcServerUseProtseqEp returned 0x%x\n", status);
    if (status) {
         exit(status);
    }

    status = RpcServerRegisterIf(rpcssm_ServerIfHandle, // interface to register
                                 NULL,   // MgrTypeUuid
                                 NULL);  // MgrEpv; null means use default
    printf("RpcServerRegisterIf returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);
    printf("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    if (fDontWait) {
        printf("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  //  wait operation
        printf("RpcMgmtWaitServerListen returned: 0x%x\n", status);
        if (status) {
            exit(status);
        }
    }

} // end main()


/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

/* end file rpcssms.c */
