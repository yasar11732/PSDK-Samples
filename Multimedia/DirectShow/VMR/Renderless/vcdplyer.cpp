//------------------------------------------------------------------------------
// File: vcdplyer.cpp
//
// Desc: DirectShow sample code - VMR-based Renderless video player
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

#include <strsafe.h>

#ifndef NUMELMS
   #define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
#endif

#define MY_USER_ID 0x1234ACDE


/******************************Public*Routine******************************\
* CMovie
*
* Constructors and destructors
*
\**************************************************************************/
CMovie::CMovie(HWND hwndApplication)
    : CUnknown(NAME("Allocator Presenter"), NULL),
      m_hwndApp(hwndApplication),
      m_MediaEvent(NULL),
      m_Mode(MOVIE_NOTOPENED),
      m_Fg(NULL),
      m_Gb(NULL),
      m_Mc(NULL),
      m_Ms(NULL),
      m_Me(NULL),
      m_lpDefIP(NULL),
      m_lpDefSA(NULL),
      m_lpDefSAN(NULL),
      m_lpDefWC(NULL),
      m_bFullScreen(FALSE),
      m_bFullScreenPoss(FALSE),
      m_pddsRenderT(NULL),
      m_pddsPriText(NULL),
      m_pddsPrimary(NULL),
      m_iDuration(-1),
      m_TimeFormat(TIME_FORMAT_MEDIA_TIME)
{
    AddRef();
}

CMovie::~CMovie()
{
}

/*****************************Private*Routine******************************\
* SetRenderingMode
*
\**************************************************************************/
HRESULT
SetRenderingMode(
    IBaseFilter* pBaseFilter,
    VMRMode mode
    )
{
    IVMRFilterConfig* pConfig;
    HRESULT hr = pBaseFilter->QueryInterface(IID_IVMRFilterConfig,
                                            (LPVOID *)&pConfig);
    if(SUCCEEDED(hr))
    {
        pConfig->SetRenderingMode(mode);
        pConfig->Release();
    }
    return hr;
}


/*****************************Private*Routine******************************\
* AddVideoMixingRendererToFG()
*
\**************************************************************************/
HRESULT
CMovie::AddVideoMixingRendererToFG()
{
    IBaseFilter* pBF = NULL;
    HRESULT hRes = S_OK;

    __try {
        CHECK_HR(hRes = CoCreateInstance(CLSID_VideoMixingRenderer,
                                         NULL, CLSCTX_INPROC,IID_IBaseFilter,
                                         (LPVOID *)&pBF));

        CHECK_HR(hRes = m_Fg->AddFilter(pBF, L"Video Mixing Renderer"));
        CHECK_HR(hRes = SetRenderingMode(pBF, VMRMode_Renderless));

        CHECK_HR(hRes = pBF->QueryInterface(IID_IVMRSurfaceAllocatorNotify,
            (LPVOID *)&m_lpDefSAN));

        CHECK_HR(hRes = CreateDefaultAllocatorPresenter());
        CHECK_HR(hRes = m_lpDefSAN->AdviseSurfaceAllocator(MY_USER_ID, this));
    }
    __finally {
        RELEASE(pBF);
    }

    return hRes;
}


/******************************Public*Routine******************************\
* OpenMovie
*
\**************************************************************************/
HRESULT
CMovie::OpenMovie(
    TCHAR *lpFileName
    )
{
    USES_CONVERSION;
    HRESULT   hres = S_OK;
    IUnknown  *pUnk = NULL;
    WCHAR     FileName[MAX_PATH];

    (void)StringCchCopyW(FileName, NUMELMS(FileName), T2W(lpFileName));

    __try
    {
        CHECK_HR(hres = CoCreateInstance(CLSID_FilterGraph,
                                         NULL, CLSCTX_INPROC,
                                         IID_IUnknown, (LPVOID *)&pUnk));

        m_Mode = MOVIE_OPENED;
        CHECK_HR(hres = pUnk->QueryInterface(IID_IFilterGraph, (LPVOID *)&m_Fg));
        CHECK_HR(hres = AddVideoMixingRendererToFG());
        CHECK_HR(hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb));
        CHECK_HR(hres = m_Gb->RenderFile(FileName, NULL));
        CHECK_HR(hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&m_Mc));

        //
        // Not being able to get the IMediaEvent interface does
        // necessarly mean that we can't play the graph.
        //
        pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&m_Me);
        GetMovieEventHandle();
        pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_Ms);
    }
    __finally
    {
        if(FAILED(hres))
        {
            RELEASE(m_Ms);
            RELEASE(m_Me);
            RELEASE(m_Mc);
            RELEASE(m_Gb);
            RELEASE(m_Fg);
        }

        RELEASE(pUnk);
    }

    return hres;
}


/******************************Public*Routine******************************\
* CloseMovie
*
\**************************************************************************/
DWORD
CMovie::CloseMovie(
    )
{
    m_Mode = MOVIE_NOTOPENED;
    m_bFullScreen = FALSE;

    RELEASE(m_Mc);
    RELEASE(m_Me);
    RELEASE(m_Ms);
    RELEASE(m_lpDefWC);
    RELEASE(m_lpDefSA);
    RELEASE(m_lpDefSAN);
    RELEASE(m_lpDefIP);
    RELEASE(m_Gb);
    RELEASE(m_Fg);

    return 0L;
}


/******************************Public*Routine******************************\
* RepaintVideo
*
\**************************************************************************/
BOOL
CMovie::RepaintVideo(
    HWND hwnd,
    HDC hdc
    )
{
    BOOL bRet = FALSE;
    if(m_lpDefWC)
    {
        bRet = (m_lpDefWC->RepaintVideo(hwnd, hdc) == S_OK);
    }
    return bRet;
}


/******************************Public*Routine******************************\
* PutMoviePosition
*
\**************************************************************************/
BOOL
CMovie::PutMoviePosition(
    LONG x,
    LONG y,
    LONG cx,
    LONG cy
    )
{
    RECT rc;

    SetRect(&rc, x, y, x + cx, y + cy);
    BOOL bRet = (m_lpDefWC->SetVideoPosition(NULL, &rc) == S_OK);
    return bRet;
}


/******************************Public*Routine******************************\
* PlayMovie
*
\**************************************************************************/
BOOL
CMovie::PlayMovie(
    )
{
    REFTIME rt;
    REFTIME rtAbs;
    REFTIME rtDur;

    rt = GetCurrentPosition();
    rtDur = GetDuration();

    //
    // If we are near the end of the movie seek to the start, otherwise
    // stay where we are.
    //
    rtAbs = rt - rtDur;
    if(rtAbs < (REFTIME)0)
    {
        rtAbs = -rtAbs;
    }

    if(rtAbs <= (REFTIME)1)
    {
        SeekToPosition((REFTIME)0,FALSE);
    }

    //
    // Change mode after setting m_Mode but before starting the graph
    //
    m_Mode = MOVIE_PLAYING;
    m_Mc->Run();
    return TRUE;
}


/******************************Public*Routine******************************\
* PauseMovie
*
\**************************************************************************/
BOOL
CMovie::PauseMovie()
{
    m_Mode = MOVIE_PAUSED;
    m_Mc->Pause();
    return TRUE;
}


/******************************Public*Routine******************************\
* GetStateMovie
*
\**************************************************************************/
OAFilterState
CMovie::GetStateMovie()
{
    OAFilterState State;
    m_Mc->GetState(INFINITE,&State);
    return State;
}


/******************************Public*Routine******************************\
* StopMovie
*
\**************************************************************************/
BOOL
CMovie::StopMovie()
{
    m_Mode = MOVIE_STOPPED;
    m_Mc->Stop();
    return TRUE;
}


/******************************Public*Routine******************************\
* GetMediaEventHandle
*
* Returns the IMediaEvent event hamdle for the filter graph if the
* filter graph exists.
*
\**************************************************************************/
HANDLE
CMovie::GetMovieEventHandle()
{
    HRESULT     hr;

    if(m_Me != NULL)
    {
        if(m_MediaEvent == NULL)
        {
            hr = m_Me->GetEventHandle((OAEVENT *)&m_MediaEvent);
        }
    }
    else
    {
        m_MediaEvent = NULL;
    }

    return m_MediaEvent;
}


/******************************Public*Routine******************************\
* GetMovieEventCode
*
\**************************************************************************/
long
CMovie::GetMovieEventCode()
{
    HRESULT hr;
    long    lEventCode;
    LONG_PTR    lParam1, lParam2;

    if(m_Me != NULL)
    {
        hr = m_Me->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
        if(SUCCEEDED(hr))
        {
            hr = m_Me->FreeEventParams(lEventCode, lParam1, lParam2);
            return lEventCode;
        }
    }

    return 0L;
}


/******************************Public*Routine******************************\
* GetDuration
*
* Returns the duration of the current movie
*
\**************************************************************************/
REFTIME
CMovie::GetDuration()
{
    HRESULT hr;
    LONGLONG Duration;

    // Should we seek using IMediaSelection

    if(m_Ms != NULL && m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = m_Ms->GetDuration(&Duration);
        if(SUCCEEDED(hr))
        {
            return double(Duration);
        }
    }
    else if(m_Ms != NULL)
    {
        hr = m_Ms->GetDuration(&Duration);
        if(SUCCEEDED(hr))
        {
            return double(Duration) / UNITS;
        }
    }

    return 0;
}


/******************************Public*Routine******************************\
* GetCurrentPosition
*
* Returns the current movie position
*
\**************************************************************************/
REFTIME
CMovie::GetCurrentPosition()
{
    REFTIME rt = (REFTIME)0;
    HRESULT hr;
    LONGLONG Position;

    // Should we return a media position?

    if(m_Ms != NULL && m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = m_Ms->GetPositions(&Position, NULL);
        if(SUCCEEDED(hr))
        {
            return double(Position);
        }
    }
    else if(m_Ms != NULL)
    {
        hr = m_Ms->GetPositions(&Position, NULL);
        if(SUCCEEDED(hr))
        {
            return double(Position) / UNITS;
        }
    }

    return rt;
}


/*****************************Private*Routine******************************\
* SeekToPosition
*
\**************************************************************************/
BOOL
CMovie::SeekToPosition(
    REFTIME rt,
    BOOL bFlushData
    )
{
    HRESULT hr=S_OK;
    LONGLONG llTime =
        LONGLONG(m_TimeFormat == TIME_FORMAT_MEDIA_TIME ? rt * double(UNITS) : rt);

    if(m_Ms != NULL)
    {
        FILTER_STATE fs;

        m_Mc->GetState(100, (OAFilterState *)&fs);
        hr = m_Ms->SetPositions(&llTime, AM_SEEKING_AbsolutePositioning, NULL, 0);

        // This gets new data through to the renderers

        if(fs == State_Stopped && bFlushData)
        {
            m_Mc->Pause();
            hr = m_Mc->GetState(INFINITE, (OAFilterState *)&fs);
            m_Mc->Stop();
        }

        if(SUCCEEDED(hr))
        {
            return TRUE;
        }
    }
    return FALSE;
}


/******************************Public*Routine******************************\
* SetFullScreenMode
*
\**************************************************************************/
void
CMovie::SetFullScreenMode(
    BOOL bMode
    )
{
    if(bMode && m_bFullScreenPoss)
    {
        HRESULT hr = m_pddsPriText->Blt(NULL, m_pddsPrimary,
                                        NULL, DDBLT_WAIT, NULL);
        if(SUCCEEDED(hr))
        {
            m_iDuration = 30;
        }
    }
}


