/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmdefs.h"
#include "pxcmstatus.h"
#include "pxcbase.h"

//#define PXCM_DEBUG_PXCMBASE

using namespace System;
using namespace System::Runtime::InteropServices;

public ref class PXCMBase {
public:

    PXCM_DEFINE_CONST(CUID,PXCBase::CUID);
    PXCM_DEFINE_CONST(WORKING_PROFILE,PXCBase::WORKING_PROFILE);

    virtual PXCMBase^ DynamicCast(pxcmUID cuid);
	generic<typename TT> where TT:PXCMBase TT DynamicCast(pxcmUID cuid) { return (TT)DynamicCast(cuid); }

    virtual ~PXCMBase(void);
    !PXCMBase(void);

internal:

    PXCMBase(PXCBase *instance,bool b_delete);
    PXCBase         *m_instance;
    bool            m_delete;

#ifdef PXCM_DEBUG_PXCMBASE
    array<pxcmUID>  ^m_cuids;
#endif

    static PXCMBase^ DynamicCastEx(pxcmUID cuid, PXCBase *instance);
};

#define PXCM_CUID_OVERWRITE(X) PXCM_DEFINE_CONST(CUID,X)

