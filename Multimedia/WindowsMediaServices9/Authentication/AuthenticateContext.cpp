//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media Technologies
//  Copyright (C) Microsoft Corporation. All rights reserved.
//
//  File:       AuthenticateContext.cpp
//
//  Contents:
//
//--------------------------------------------------------------------------


#include "stdafx.h"
#include "Authenticate.h"
#include "AuthenticatePlugin.h"
#include "AuthenticateContext.h"

//
// TODO: Change the realm, domain, username, and password here
//
#define REALM_NAME      L"MyRealm"
#define ANON_DOMAIN     L""
#define ANON_USER       L""
#define ANON_PSWD       L""

/////////////////////////////////////////////////////////////////////////////
// CAuthenticateContext
///////////////////////////////////////////////////////////////////////////////

CAuthenticateContext::CAuthenticateContext() :
    m_hToken( NULL ),
    m_bstrUsername( L"" ),
    m_State( 0 )
{
    InitializeCriticalSection( &m_CritSec );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
CAuthenticateContext::~CAuthenticateContext()
{
    DeleteCriticalSection( &m_CritSec );

    if( NULL != m_hToken )
    {
        CloseHandle( m_hToken );
    }

    if( NULL != m_pWMSAuthenticationPlugin )
    {
        m_pWMSAuthenticationPlugin->Release();
    }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::Initialize
(
    IWMSAuthenticationPlugin* pAuthenticator
)
{
    if( NULL == pAuthenticator)
    {
        return( E_INVALIDARG );
    }

    HRESULT hr = S_OK;

    EnterCriticalSection( &m_CritSec );

    m_pWMSAuthenticationPlugin = pAuthenticator;
    m_pWMSAuthenticationPlugin->AddRef();

    LeaveCriticalSection( &m_CritSec );

    return( hr );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::GetAuthenticationPlugin
(
    IWMSAuthenticationPlugin **ppAuthenPlugin
)
{
    if( NULL == ppAuthenPlugin)
    {
        return( E_INVALIDARG );
    }

    HRESULT hr = S_OK;

    EnterCriticalSection( &m_CritSec );

    do
    {
        if( NULL == m_pWMSAuthenticationPlugin )
        {
            hr = E_UNEXPECTED;
            break;
        }

        hr = m_pWMSAuthenticationPlugin->QueryInterface( IID_IWMSAuthenticationPlugin, (void**)ppAuthenPlugin );

    }
    while( FALSE );

    LeaveCriticalSection( &m_CritSec );

    return( hr );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::Authenticate
(
    VARIANT ResponseBlob,
    IWMSContext *pUserCtx,
    IWMSContext *pPresentationCtx,
    IWMSCommandContext *pCommandContext,
    IWMSAuthenticationCallback *pCallback,
    VARIANT Context
)
{

    if( NULL == pCallback )
    {
        return(E_INVALIDARG);
    }

    HRESULT hr = S_OK;
    EnterCriticalSection( &m_CritSec );

    DWORD dwState = WMS_AUTHENTICATION_ERROR;

    VARIANT ChallengeBlob;
    VariantInit( &ChallengeBlob );

    do
    {
        if( WMS_AUTHENTICATION_SUCCESS == m_State )
        {
            dwState = m_State;
            break;
        }

        if ( 0 == LogonUserW(
                    ANON_USER,
                    ANON_DOMAIN,
                    ANON_PSWD,
                    LOGON32_LOGON_NETWORK,
                    LOGON32_PROVIDER_DEFAULT,
                    &m_hToken ) )
        {
            m_hToken = NULL;
            m_bstrUsername = L"";
            hr = HRESULT_FROM_WIN32( ERROR_LOGON_FAILURE );
            dwState = WMS_AUTHENTICATION_DENIED;
            break;
        }
        else
        {
            m_State = dwState = WMS_AUTHENTICATION_SUCCESS;
            m_bstrUsername = ANON_USER;
        }

    } while( FALSE );

    LeaveCriticalSection( &m_CritSec );

    pCallback->OnAuthenticateComplete( (WMS_AUTHENTICATION_RESULT) dwState, ChallengeBlob, Context );

    VariantClear( &ChallengeBlob );

    return( S_OK );

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::GetLogicalUserID
(
    BSTR* bstrUserID
)
{
    if( NULL == bstrUserID )
    {
        return( E_POINTER );
    }

    HRESULT hr = S_OK;
    EnterCriticalSection( &m_CritSec );

    if( WMS_AUTHENTICATION_SUCCESS == m_State )
    {
        *bstrUserID = SysAllocString( m_bstrUsername.m_str );

        if( NULL == *bstrUserID )
        {
            hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        *bstrUserID = NULL;
    }

    LeaveCriticalSection( &m_CritSec );

    return( hr );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::GetImpersonationAccountName
(
    BSTR* bstrAccountName
)
{
    if( NULL == bstrAccountName )
    {
        return( E_POINTER );
    }

    HRESULT hr = E_NOTIMPL;
    EnterCriticalSection( &m_CritSec );

    //
    // TODO: Add code here to return the Impersonation Account Name
    //
    // hr = ...

    LeaveCriticalSection( &m_CritSec );

    return( hr );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CAuthenticateContext::GetImpersonationToken
(
    long* Token
)
{
    if( NULL == Token )
    {
        return( E_POINTER );
    }

    HRESULT hr = S_OK;

    EnterCriticalSection( &m_CritSec );

    *Token = HandleToLong(m_hToken);

    LeaveCriticalSection( &m_CritSec );

    return( hr );
}
