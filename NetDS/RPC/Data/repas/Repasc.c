/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                       repas Example

    FILE:       repasc.c

    USAGE:      repasc  -n network_address
                       -p protocol_sequence
                       -e endpoint
                       -o options
                       -c count of elements in linked list
                       -v value of first element in linked list
                       -d delta between values in linked list

    PURPOSE:    Client side of RPC distributed application.
                This sample demonstrates the represent_as example.
                A char string is sent over the network as a unicode string.

    RELATED:    repass.c - server main
                repasp.c - remote procedures
                repascu.c - client utility procedures

    FUNCTIONS:  main() - bind to server and call remote procedure

    COMMENTS:   This sample program generates a client and server can share
                an interface, but one side can use a different representation
                than the other.

                The client side in this example does all operations using
                character strings, and the server side does all operations
                using UNICODE strings.  Two procedures are provided, one
                defined with ASCII strings, one with UNICODE strings.
                The wire format reflects these definitions, yet the client
                and server see pure ASCII and pure UNICODE respectively.

                The [represent_as] attribute (used in the client and server
                side acf files) requires the four user-supplied functions
                whose names start with the name of the transmitted type
                (in the client side's case: WCHAR_STRING)

                The [in, out] attributes applied to remote procedure
                parameters require the two user-supplied functions
                midl_user_allocate and midl_user_free.

                The other functions are utilities that are used to
                build or display the data structures.


****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "repasc.h"    // client's side header file generated by MIDL compiler

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates\n\
the use of the [represent_as] attribute. For more information\n\
about the attributes and the RPC API functions, see the\n\
RPC programming guide and reference.\n\n"

#define MAX_ELEMENTS 50

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -n network_address\n");
    fprintf(stderr, " -e endpoint\n");
    fprintf(stderr, " -o options\n");
    fprintf(stderr, " -c count_of_elements\n");
    fprintf(stderr, " -v value\n");
    fprintf(stderr, " -d delta\n");
    exit(1);
}

void __cdecl main(int argc, char **argv)
{
    RPC_STATUS status;
    unsigned char * pszUuid             = NULL;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszNetworkAddress   = NULL;
    unsigned char * pszEndpoint         = "\\pipe\\repas";
    unsigned char * pszOptions          = NULL;
    unsigned char * pszStringBinding    = NULL;
    int i;
    int cElements = 10;
    short sValue = 100;
    short sDelta = 10;

    char    FirstBuffer[100];

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
            case 'c':
                cElements = atoi(argv[++i]);
                if (cElements > MAX_ELEMENTS)
                    cElements = MAX_ELEMENTS;
                break;
            case 'v':
                sValue = (short)atoi(argv[++i]);
                break;
            case 'd':
                sDelta = (short)atoi(argv[++i]);
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

    /* Use a convenience function to concatenate the elements of the string */
    /* binding into the syntax needed by RpcBindingFromStringBinding.       */
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
                                         &hrepas);
    printf("RpcBindingFromStringBinding returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    RpcTryExcept {
        // initialize a string to be shipped
        strcpy(FirstBuffer,"This ASCII string is sent from the client to the server as UNICODE");

        printf("\nThe Client side is about to send:\n\"%s\"\n\n", FirstBuffer );

        printf("Calling the remote procedure 'ModifyMyWString'\n");
        // note that the client sees the interface using ascii, not unicode
        ModifyMyWString( &FirstBuffer );
        printf("The Client side got back:\n\"%s\"\n\n", FirstBuffer );


        // initialize a string to be shipped
        strcpy(FirstBuffer,"And this ASCII string is sent from the client to the server as ASCII");

        printf("The Client side is about to send:\n\"%s\"\n\n", FirstBuffer );
        printf("Calling the remote procedure 'ModifyMyString'\n");
        // note that the client sees the interface using ascii
        ModifyMyString( &FirstBuffer );
        printf("The Client side got back:\n\"%s\"\n\n", FirstBuffer );

        printf("Calling the remote procedure 'Shutdown'\n");
        Shutdown();  // shut down the server side
    }
    RpcExcept(1) {
        printf("Runtime reported exception %ld\n", RpcExceptionCode() );
    }
    RpcEndExcept

    /* The calls to the remote procedures are complete.            */
    /* Free the string and the binding handle using RPC API calls. */
    status = RpcStringFree(&pszStringBinding);
    printf("RpcStringFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = RpcBindingFree(&hrepas);
    printf("RpcBindingFree returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    exit(0);

}  // end main()

/* end file repasc.c */
