/*
 * Copyright (c) Microsoft Corporation.  All rights reserved.
 */

/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 27 13:08:17 2000
 */
/* Compiler settings for Render.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "Render.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IFactory, ver. 0.0,
   GUID={0xCFDD0BC0,0x9906,0x11d3,{0x95,0x3D,0x00,0x00,0xF8,0x04,0xE0,0x31}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
CINTERFACE_PROXY_VTABLE(3) _IFactoryProxyVtbl = 
{
    0,
    &IID_IFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IFactoryStubVtbl =
{
    &IID_IFactory,
    0,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IBehavior, ver. 0.0,
   GUID={0xCFDD0BC1,0x9906,0x11d3,{0x95,0x3D,0x00,0x00,0xF8,0x04,0xE0,0x31}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
CINTERFACE_PROXY_VTABLE(7) _IBehaviorProxyVtbl = 
{
    0,
    &IID_IBehavior,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IBehavior_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IBehaviorStubVtbl =
{
    &IID_IBehavior,
    0,
    7,
    &IBehavior_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IEventSink, ver. 0.0,
   GUID={0xCFDD0BC2,0x9906,0x11d3,{0x95,0x3D,0x00,0x00,0xF8,0x04,0xE0,0x31}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

CINTERFACE_PROXY_VTABLE(7) _IEventSinkProxyVtbl = 
{
    0,
    &IID_IEventSink,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IEventSink_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IEventSinkStubVtbl =
{
    &IID_IEventSink,
    0,
    7,
    &IEventSink_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };

const CInterfaceProxyVtbl * _Render_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IBehaviorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IEventSinkProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Render_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IBehaviorStubVtbl,
    ( CInterfaceStubVtbl *) &_IEventSinkStubVtbl,
    0
};

PCInterfaceName const _Render_InterfaceNamesList[] = 
{
    "IFactory",
    "IBehavior",
    "IEventSink",
    0
};

const IID *  _Render_BaseIIDList[] = 
{
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _Render_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Render, pIID, n)

int __stdcall _Render_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Render, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Render, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Render, 3, *pIndex )
    
}

const ExtendedProxyFileInfo Render_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Render_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Render_StubVtblList,
    (const PCInterfaceName * ) & _Render_InterfaceNamesList,
    (const IID ** ) & _Render_BaseIIDList,
    & _Render_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
