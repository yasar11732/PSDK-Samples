/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                       Cluuid Example

    FILE:        cluuidc.c

    USAGE:       cluuidc  -n network_address
                          -p protocol_sequence
                          -e endpoint
                          -o options
                          -s string_displayed_on_server
                          -u client object uuid

    PURPOSE:     Client side of RPC distributed application

    FUNCTIONS:   main() - binds to server and calls remote procedure

    COMMENTS:    This distributed application prints a string such as
                 "hello, world" on the server. The client manages its
                 connection to the server. The client uses the implicit
                 binding handle ImpHandle defined in the file cluuid.h.

****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cluuid.h"    // header file generated by MIDL compiler

void Usage(char * pszProgramName)
{
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -n network_address\n");
    fprintf(stderr, " -e endpoint\n");
    fprintf(stderr, " -o options\n");
    fprintf(stderr, " -s string\n");
    fprintf(stderr, " -u uuid\n");
    exit(1);
}

void __cdecl main(int argc, char **argv)
{
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = "\\pipe\\cluuid";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    unsigned char * pszString           = "hello, world";
    unsigned long ulCode;
    int i;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'n':  // network address
                pszNetworkAddress = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'o':
                pszOptions = argv[++i];
                break;
            case 's':
                pszString = argv[++i];
                break;
            case 'u':
                pszUuid = argv[++i];
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

    /* Use a convenience function to concatenate the elements of  */
    /* the string binding into the proper sequence.               */
    status = RpcStringBindingCompose(pszUuid,
                                     pszProtocolSequence,
                                     pszNetworkAddress,
                                     pszEndpoint,
                                     pszOptions,
                                     &pszStringBinding);
    printf("RpcStringBindingCompose returned 0x%x\n", status);
    printf("pszStringBinding = %s\n", pszStringBinding);
    if (status) {
        exit(status);
    }

    /* Set the binding handle that will be used to bind to the server. */
    status = RpcBindingFromStringBinding(pszStringBinding,
                                         &ImpHandle);
    printf("RpcBindingFromStringBinding returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf("Calling the remote procedure 'HelloProc'\n");
    printf("  print the string '%s' on the server\n", pszString);

    RpcTryExcept {
        HelloProc(pszString);  /* make call with user message */
        printf("Calling the remote procedure 'Shutdown'\n");
        Shutdown();             // shut down the server side
    }
    RpcExcept(1) {
        ulCode = RpcExceptionCode();
        printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept

    /*  The calls to the remote procedures are complete. */
    /*  Free the string and the binding handle           */

    status = RpcStringFree(&pszStringBinding);  // remote calls done; unbind
    printf("RpcStringFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = RpcBindingFree(&ImpHandle);  // remote calls done; unbind
    printf("RpcBindingFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    exit(0);
}


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


/* end file cluuidc.c */
