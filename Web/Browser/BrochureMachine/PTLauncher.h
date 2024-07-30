/*
 * Copyright (c) 2000 Microsoft Corporation.  All rights reserved.
 */

// PTLauncher.h : Declaration of the CPTLauncher

#ifndef __PTLAUNCHER_H_
#define __PTLAUNCHER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CPTLauncher
class ATL_NO_VTABLE CPTLauncher :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CPTLauncher, &CLSID_PTLauncher>,
  public CComControl<CPTLauncher>,
  public IDispatchImpl<IPTLauncher, &IID_IPTLauncher, &LIBID_BROCHUREMACHINELib>,
  public IOleControlImpl<CPTLauncher>,
  public IOleObjectImpl<CPTLauncher>,
  public IOleInPlaceActiveObjectImpl<CPTLauncher>,
  public IOleInPlaceObjectWindowlessImpl<CPTLauncher>,
  /* The following untrusted use of IObjectSafetyImpl is for simplicity
  in this sample code.  This usage in production code can expose a
  security risk in some situations. */
  public IObjectSafetyImpl<CPTLauncher,
           INTERFACESAFE_FOR_UNTRUSTED_CALLER |
           INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
  CPTLauncher()
  {
  }

DECLARE_REGISTRY_RESOURCEID(IDR_PTLAUNCHER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPTLauncher)
  COM_INTERFACE_ENTRY(IPTLauncher)
  COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceObject)
    COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY(IOleControl)
    COM_INTERFACE_ENTRY(IOleObject)
    COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// IPTLauncher
public:
  STDMETHOD(LaunchPT)();
};

#endif //__PTLAUNCHER_H_
