// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 2004  Microsoft Corporation.  All Rights Reserved.
//
// Module Name: extension.cpp
//
// Description:
//
//    This sample illustrates how to develop a layered service provider that is
//    capable of counting all bytes transmitted through a TCP/IP socket.
//
//    This file contains all of the Winsock extension functions that can
//    be monitored by a service provider. This is done by intercepting any
//    WSAIoctl calls with the SIO_GET_EXTENSION_FUNCTION_POINTER (see spi.cpp
//    and WSPIoctl for more info). We substitute our own function pointer so
//    that an application calls into us. Currently we intercept only TransmitFile
//    and AcceptEx.
//

#include "lspdef.h"

//
// Function: LoadExtensionFunction
//
// Description:
//    This function dynamically loads the given extension function from the
//    underlying provider. Each extension function checks to see if the 
//    corresponding extension function for the lower provider is loaded
//    before calling. If not, it will load it as needed. This is necessary
//    if the app loads the extension function for say TCP and then calls
//    that extension function on a UDP socket. Normally this isn't the case
//    but we're being defensive here.
//
BOOL
LoadExtensionFunction(
    FARPROC   **func,
    GUID        ExtensionGuid,
    LPWSPIOCTL  fnIoctl,
    SOCKET      s
    )
{
    DWORD   dwBytes;
    int     rc, 
            error;

    // Use the lower provider's WSPIoctl to load the extension function
    rc = fnIoctl(
            s,
            SIO_GET_EXTENSION_FUNCTION_POINTER,
           &ExtensionGuid,
            sizeof(GUID),
            func,
            sizeof(FARPROC),
           &dwBytes,
            NULL,
            NULL,
            NULL,
           &error
            );
    if ( SOCKET_ERROR == rc )
    {
        dbgprint("LoadExtensionFunction: WSAIoctl (SIO_GET_EXTENSION_FUNCTION) failed: %d",
            error);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

//
// Function: ExtGetAcceptExSockaddrs
//
// Description:
//      There is no need to intercept the GetAcceptExSockaddrs function since
//      it doesn't take any socket handles as parameters. If the LSP is proxying
//      connections (or something similar) where the LSP "hides" either the local
//      or remote addresses, it may be required to intercept this function and
//      change the addresses. Another option is to make this change in the
//      ExtAcceptEx function (but the addresses there are encoded).
//

//
// Function: ExtTransmitFile
//
// Description:
//    This is our provider's TransmitFile function. When an app calls WSAIoctl
//    to request the function pointer to TransmitFile, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR 
ExtTransmitFile(
    IN SOCKET hSocket,
    IN HANDLE hFile,
    IN DWORD nNumberOfBytesToWrite,
    IN DWORD nNumberOfBytesPerSend,
    IN LPOVERLAPPED lpOverlapped,
    IN LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
    IN DWORD dwFlags
    )
{
	SOCK_INFO          *SocketContext = NULL;
	LPWSAOVERLAPPEDPLUS ProviderOverlapped = NULL;
	int                 Errno = 0,
                        ret = FALSE;

    // Get the context
    SocketContext = FindAndRefSocketContext( hSocket, &Errno );
    if ( NULL == SocketContext )
    {
        dbgprint( "ExtTransmitFile: FindAndRefSocketContext failed!" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == SocketContext->Provider->NextProcTableExt.lpfnTransmitFile )
    {
        GUID    guidTransmitFile = WSAID_TRANSMITFILE;

        ret = LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnTransmitFile,
                guidTransmitFile,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                );
        if ( FALSE == ret )
        {
            dbgprint( "Next provider's TransmitFile pointer is NULL!" );
            Errno = WSAEFAULT;
            goto cleanup;
        }   
    }

    //
	// Check for overlapped I/O
    //
	if ( NULL != lpOverlapped )
	{
		ProviderOverlapped = PrepareOverlappedOperation(
                SocketContext,
                LSP_OP_TRANSMITFILE,
                NULL,
                0,
                lpOverlapped,
                NULL,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            goto cleanup;
        }

        // Save the arguments
        ProviderOverlapped->TransmitFileArgs.hFile                 = hFile;
        ProviderOverlapped->TransmitFileArgs.nNumberOfBytesToWrite = nNumberOfBytesToWrite;
        ProviderOverlapped->TransmitFileArgs.nNumberOfBytesPerSend = nNumberOfBytesPerSend;
        ProviderOverlapped->TransmitFileArgs.lpTransmitBuffers     = lpTransmitBuffers;
        ProviderOverlapped->TransmitFileArgs.dwFlags               = dwFlags;

        ret = QueueOverlappedOperation( ProviderOverlapped, SocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
	}
	else
	{
		ret = SocketContext->Provider->NextProcTableExt.lpfnTransmitFile(
                SocketContext->ProviderSocket,
                hFile,
                nNumberOfBytesToWrite,
                nNumberOfBytesPerSend,
                NULL,
                lpTransmitBuffers,
                dwFlags
                );
        if ( FALSE == ret )
            Errno = WSAGetLastError();
	}

cleanup:

    if ( NULL != SocketContext )
        DerefSocketContext(SocketContext, &Errno );

    if ( FALSE == ret )
        WSASetLastError( Errno );

    return ret;
}

//
// Function: ExtAcceptEx
//
// Description:
//    This is our provider's AcceptEx function. When an app calls WSAIoctl
//    to request the function pointer to AcceptEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR 
ExtAcceptEx(
	IN SOCKET sListenSocket,
	IN SOCKET sAcceptSocket,
	IN PVOID lpOutputBuffer,
	IN DWORD dwReceiveDataLength,
	IN DWORD dwLocalAddressLength,
	IN DWORD dwRemoteAddressLength,
	OUT LPDWORD lpdwBytesReceived,
	IN LPOVERLAPPED lpOverlapped
    )
{
	LPWSAOVERLAPPEDPLUS ProviderOverlapped = NULL;
	SOCK_INFO          *ListenSocketContext = NULL,
	                   *AcceptSocketContext = NULL;
	int                 Errno = 0,
                        ret = FALSE;


    //
    // Query the socket context for the listening socket
    //
    ListenSocketContext = FindAndRefSocketContext( sListenSocket, &Errno );
    if ( NULL == ListenSocketContext )
    {
        dbgprint( "ExtAcceptEx: FindAndRefSocketContext failed! (listen socket)" );
        goto cleanup;
    }
    //
    // Also need to query the socket context for the accept socket
    //
    AcceptSocketContext = FindAndRefSocketContext( sAcceptSocket, &Errno );
    if ( NULL == AcceptSocketContext )
    {
        dbgprint( "ExtAcceptEx: FindAndRefSocketContext failed! (accept socket)" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx )
    {
        GUID    guidAcceptEx = WSAID_ACCEPTEX;

        ret = LoadExtensionFunction(
                 (FARPROC **)&ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx,
                 guidAcceptEx,
                 ListenSocketContext->Provider->NextProcTable.lpWSPIoctl,
                 ListenSocketContext->ProviderSocket
                 );
        if ( FALSE == ret )
        {
            dbgprint("Lower provider AcceptEx == NULL!");
            Errno = WSAEFAULT;
            goto cleanup;
        }
    }

	// Check for overlapped I/O
	if ( NULL != lpOverlapped )
	{
		ProviderOverlapped = PrepareOverlappedOperation(
                ListenSocketContext,
                LSP_OP_ACCEPTEX,
                NULL,
                0,
                lpOverlapped,
                NULL,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            goto cleanup;
        }

        __try
        {
            // Save the arguments
            ProviderOverlapped->AcceptExArgs.dwBytesReceived       = (lpdwBytesReceived ? *lpdwBytesReceived : 0);
            ProviderOverlapped->AcceptExArgs.sAcceptSocket         = sAcceptSocket;
            ProviderOverlapped->AcceptExArgs.sProviderAcceptSocket = AcceptSocketContext->ProviderSocket;
            ProviderOverlapped->AcceptExArgs.lpOutputBuffer        = lpOutputBuffer;
            ProviderOverlapped->AcceptExArgs.dwReceiveDataLength   = dwReceiveDataLength;
            ProviderOverlapped->AcceptExArgs.dwLocalAddressLength  = dwLocalAddressLength;
            ProviderOverlapped->AcceptExArgs.dwRemoteAddressLength = dwRemoteAddressLength;
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Errno = WSAEFAULT;
            goto cleanup;
        }

        ret = QueueOverlappedOperation( ProviderOverlapped, ListenSocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
	}
	else
	{
		ret = ListenSocketContext->Provider->NextProcTableExt.lpfnAcceptEx(
                ListenSocketContext->ProviderSocket,
                AcceptSocketContext->ProviderSocket,
                lpOutputBuffer,
                dwReceiveDataLength,
                dwLocalAddressLength,
                dwRemoteAddressLength,
                lpdwBytesReceived,
                NULL
                );
        if ( FALSE == ret )
            Errno = WSAGetLastError();
	}

cleanup:

    if ( NULL != ListenSocketContext )
        DerefSocketContext(ListenSocketContext, &Errno );

    if ( NULL != AcceptSocketContext )
        DerefSocketContext(AcceptSocketContext, &Errno );

    if ( FALSE == ret )
        WSASetLastError( Errno );

    return ret;
}

//
// Function: ExtConnectEx
//
// Description:
//    This is our provider's ConnectEx function. When an app calls WSAIoctl
//    to request the function pointer to ConnectEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR 
ExtConnectEx(
    IN SOCKET s,
    IN const struct sockaddr FAR *name,
    IN int namelen,
    IN PVOID lpSendBuffer OPTIONAL,
    IN DWORD dwSendDataLength,
    OUT LPDWORD lpdwBytesSent,
    IN LPOVERLAPPED lpOverlapped
    )
{
    SOCK_INFO           *SocketContext = NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped = NULL;
    int                  Errno = NO_ERROR,
                         ret = FALSE;

    // Get the context
    SocketContext = FindAndRefSocketContext( s, &Errno );
    if ( NULL == SocketContext )
    {
        dbgprint( "ExtConnectEx: FindAndRefSocketContext failed!" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == SocketContext->Provider->NextProcTableExt.lpfnConnectEx )
    {
        GUID    guidConnectEx = WSAID_CONNECTEX;

        ret = LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnConnectEx,
                guidConnectEx,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                );
        if ( FALSE == ret )
        {
            dbgprint("Next proc table ConnectEx == NULL!");
            Errno = WSAEFAULT;
            goto cleanup;
        }
    }

    // Check for overlapped I/O
    if ( NULL != lpOverlapped )
    {
        ProviderOverlapped = PrepareOverlappedOperation(
                SocketContext,
                LSP_OP_CONNECTEX,
                NULL,
                0,
                lpOverlapped,
                NULL,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            dbgprint("ExtConnectEx: PrepareOverlappedOperation returned NULL");
            goto cleanup;
        }

        __try
        {
            ProviderOverlapped->ConnectExArgs.s                = s;
            ProviderOverlapped->ConnectExArgs.namelen          = namelen;
            ProviderOverlapped->ConnectExArgs.lpSendBuffer     = lpSendBuffer;
            ProviderOverlapped->ConnectExArgs.dwSendDataLength = dwSendDataLength;
            ProviderOverlapped->ConnectExArgs.dwBytesSent      = (lpdwBytesSent ? *lpdwBytesSent : 0);
            if ( namelen <= sizeof( ProviderOverlapped->ConnectExArgs.name ) )
                CopyMemory( &ProviderOverlapped->ConnectExArgs.name, name, namelen );
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Errno = WSAEFAULT;
            goto cleanup;
        }

        ret = QueueOverlappedOperation( ProviderOverlapped, SocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnConnectEx(
                SocketContext->ProviderSocket,
                name,
                namelen,
                lpSendBuffer,
                dwSendDataLength,
                lpdwBytesSent,
                NULL
                );
        if ( FALSE == ret )
            Errno = WSAGetLastError();
    }

cleanup:

    if ( NULL != SocketContext )
        DerefSocketContext( SocketContext, &Errno );

    if ( FALSE == ret )
        WSASetLastError( Errno );

    return ret;
}

//
// Function: ExtTransmitPackets
//
// Description:
//    This is our provider's TransmitPackets function. When an app calls WSAIoctl
//    to request the function pointer to TransmitPackets, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR 
ExtTransmitPackets(
    SOCKET hSocket,
    LPTRANSMIT_PACKETS_ELEMENT lpPacketArray,
    DWORD nElementCount,
    DWORD nSendSize,
    LPOVERLAPPED lpOverlapped,
    DWORD dwFlags)
{
    SOCK_INFO           *SocketContext = NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped = NULL;
    int                  Errno = NO_ERROR,
                         ret = FALSE;

    // Get the context
    SocketContext = FindAndRefSocketContext( hSocket, &Errno );
    if ( NULL == SocketContext )
    {
        dbgprint( "ExtTransmitPackets: FindAndRefSocketContext failed!" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets )
    {
        GUID    guidTransmitPackets = WSAID_TRANSMITPACKETS;

        ret = LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets,
                guidTransmitPackets,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                );
        if ( FALSE == ret )
        {
            dbgprint( "Next provider's TransmitPackets function is NULL!" );
            Errno = WSAEFAULT;
            goto cleanup;
        }
    }

    //
    // Check for overlapped I/O
    //
    if ( NULL != lpOverlapped )
    {
        ProviderOverlapped = PrepareOverlappedOperation(
                SocketContext,
                LSP_OP_TRANSMITPACKETS,
                NULL,
                0,
                lpOverlapped,
                NULL,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            dbgprint("ExtTransmitPackets: PrepareOverlappedOperation returned NULL");
            goto cleanup;
        }
        
        ProviderOverlapped->lpCallerCompletionRoutine         = NULL;
        ProviderOverlapped->TransmitPacketsArgs.s             = hSocket;
        ProviderOverlapped->TransmitPacketsArgs.lpPacketArray = lpPacketArray;
        ProviderOverlapped->TransmitPacketsArgs.nElementCount = nElementCount;
        ProviderOverlapped->TransmitPacketsArgs.nSendSize     = nSendSize;
        ProviderOverlapped->TransmitPacketsArgs.dwFlags       = dwFlags;

        ret = QueueOverlappedOperation( ProviderOverlapped, SocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnTransmitPackets(
                SocketContext->ProviderSocket,
                lpPacketArray,
                nElementCount,
                nSendSize,
                NULL,
                dwFlags
                );
        if ( FALSE == ret )
            Errno = WSAGetLastError();
    }

cleanup:

    if ( NULL != SocketContext )
        DerefSocketContext( SocketContext, &Errno );

    if ( FALSE == ret )
        WSASetLastError( Errno );

    return ret;
}

//
// Function: ExtDisconnectEx
//
// Description:
//    This is our provider's DisconnectEx function. When an app calls WSAIoctl
//    to request the function pointer to DisconnectEx, we intercept the call
//    and return a pointer to our extension function instead.
//
BOOL PASCAL FAR 
ExtDisconnectEx(
    IN SOCKET s,
    IN LPOVERLAPPED lpOverlapped,
    IN DWORD  dwFlags,
    IN DWORD  dwReserved
    )
{
    SOCK_INFO           *SocketContext = NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped = NULL;
    int                  Errno = NO_ERROR,
                         ret = FALSE;

    // Get the context
    SocketContext = FindAndRefSocketContext( s, &Errno );
    if ( NULL == SocketContext )
    {
        dbgprint( "ExtDisconnectEx: FindAndRefSocketContext failed!" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx )
    {
        GUID    guidDisconnectEx = WSAID_DISCONNECTEX;

        ret = LoadExtensionFunction(
                 (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx,
                 guidDisconnectEx,
                 SocketContext->Provider->NextProcTable.lpWSPIoctl,
                 SocketContext->ProviderSocket
                 );
        if ( FALSE == ret )
        {
            dbgprint( "Next provider's DisconnectEx function is NULL!" );
            Errno = WSAEFAULT;
            goto cleanup;
        }
    }

    // Check for overlapped I/O

    if ( NULL != lpOverlapped )
    {
        ProviderOverlapped = PrepareOverlappedOperation(
                SocketContext,
                LSP_OP_DISCONNECTEX,
                NULL,
                0,
                lpOverlapped,
                NULL,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            dbgprint("ExtDisconnectEx: PrepareOverlappedOperation returned NULL");
            goto cleanup;
        }

        ProviderOverlapped->DisconnectExArgs.s          = s;
        ProviderOverlapped->DisconnectExArgs.dwFlags    = dwFlags;
        ProviderOverlapped->DisconnectExArgs.dwReserved = dwReserved;
 
        ret = QueueOverlappedOperation( ProviderOverlapped, SocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = FALSE;
        }
        else
        {
            ret = TRUE;
        }
    }
    else
    {
        ret = SocketContext->Provider->NextProcTableExt.lpfnDisconnectEx(
                SocketContext->ProviderSocket,
                lpOverlapped,
                dwFlags,
                dwReserved
                );
        if ( FALSE == ret )
            Errno = WSAGetLastError();
    }

cleanup:

    if ( NULL != SocketContext )
        DerefSocketContext( SocketContext, &Errno );

    if ( FALSE == ret )
        WSASetLastError( Errno );

    return ret;
}

//
// Function: ExtWSARecvMsg
//
// Description:
//    This is our provider's WSARecvMsg function. When an app calls WSAIoctl
//    to request the function pointer to WSARecvMsg, we intercept the call
//    and return a pointer to our extension function instead.
//
INT PASCAL FAR 
ExtWSARecvMsg(
    IN SOCKET s,
    IN OUT LPWSAMSG lpMsg,
    OUT LPDWORD lpdwNumberOfBytesRecvd,
    IN LPWSAOVERLAPPED lpOverlapped,
    IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    )
{
    SOCK_INFO           *SocketContext = NULL;
    LPWSAOVERLAPPEDPLUS  ProviderOverlapped = NULL;
    int                  Errno = NO_ERROR,
                         ret = SOCKET_ERROR;

    // Get the context
    SocketContext = FindAndRefSocketContext( s, &Errno );
    if ( NULL == SocketContext )
    {
        dbgprint( "ExtWSARecvMsg: FindAndRefSocketContext failed!" );
        goto cleanup;
    }

    // Make sure we already have the extension function
    if ( NULL == SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg )
    {
        GUID    guidWSARecvMsg = WSAID_WSARECVMSG;

        ret = LoadExtensionFunction(
                (FARPROC **)&SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg,
                guidWSARecvMsg,
                SocketContext->Provider->NextProcTable.lpWSPIoctl,
                SocketContext->ProviderSocket
                );
        if ( FALSE == ret )
        {
            dbgprint("Next proc table WSARecvMsg == NULL!");
            Errno = WSAEFAULT;
            goto cleanup;
        }
    }

    //
    // Check for overlapped I/O
    //
    if ( NULL != lpOverlapped )
    {
        ProviderOverlapped = PrepareOverlappedOperation(
                SocketContext,
                LSP_OP_WSARECVMSG,
                NULL,
                0,
                lpOverlapped,
                lpCompletionRoutine,
                NULL,
               &Errno
                );
        if ( NULL == ProviderOverlapped )
        {
            dbgprint("ExtWSARecvMsg: PrepareOverlappedOperation returned NULL");
            goto cleanup;
        }

        __try 
        {
            ProviderOverlapped->WSARecvMsgArgs.dwNumberOfBytesRecvd = (lpdwNumberOfBytesRecvd ? *lpdwNumberOfBytesRecvd : 0);
            ProviderOverlapped->WSARecvMsgArgs.s                    = s;
            ProviderOverlapped->WSARecvMsgArgs.lpMsg                = lpMsg;
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Errno = WSAEFAULT;
            goto cleanup;
        }

        ret = QueueOverlappedOperation( ProviderOverlapped, SocketContext );
        if ( NO_ERROR != ret )
        {
            Errno = ret;
            ret = SOCKET_ERROR;
        }
    }
    else
    {
        ASSERT( SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg );

        ret = SocketContext->Provider->NextProcTableExt.lpfnWSARecvMsg(
                SocketContext->ProviderSocket,
                lpMsg,
                lpdwNumberOfBytesRecvd,
                NULL,
                NULL
                );
        if ( SOCKET_ERROR == ret )
            Errno = WSAGetLastError();
    }

cleanup:

    if ( NULL != SocketContext )
        DerefSocketContext( SocketContext, &Errno );

    if ( SOCKET_ERROR == ret )
        WSASetLastError( Errno );

    return ret;
}

