/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmbase.h"
#include "pxcscheduler.h"

public ref class PXCMScheduler: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCScheduler::CUID);

    enum class Priority: pxcmEnum {
        PRIORITY_NORMAL = 0,
        PRIORITY_LOW    = 1,
        PRIORITY_HIGH   = 2
    };

    ref class SyncPoint:public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCScheduler::SyncPoint::CUID);
        PXCM_DEFINE_CONST(TIMEOUT_INFINITE,PXCScheduler::SyncPoint::TIMEOUT_INFINITE);
        PXCM_DEFINE_CONST(SYNCEX_LIMIT,PXCScheduler::SyncPoint::SYNCEX_LIMIT);

        virtual pxcmStatus QueryPtr(PXCMBase ^ptr);
        virtual pxcmStatus Synchronize(pxcmU32 timeout);
        virtual pxcmStatus Synchronize(void);

        /* if idx!=0, the function waits for any sync point */
        static pxcmStatus SynchronizeEx(array<SyncPoint^> ^sps, [Out] pxcmU32 %idx, pxcmU32 timeout);
        static pxcmStatus SynchronizeEx(array<SyncPoint^> ^sps, pxcmU32 timeout);
        static pxcmStatus SynchronizeEx(array<SyncPoint^> ^sps, [Out] pxcmU32 %idx);
        static pxcmStatus SynchronizeEx(array<SyncPoint^> ^sps);

		/* Dispose an sync point array */
		static void Dispose(array<SyncPoint^> ^sps);

    internal:

        SyncPoint(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCScheduler::SyncPoint *QueryInstance(void) { return (PXCScheduler::SyncPoint *)m_instance; }
    };

    virtual property Priority priority {
		void        set(Priority p) { SetPriority(p); }
		Priority    get(void) { Priority p; QueryPriority(p); return p; }
    };

    virtual pxcmStatus SetPriority(Priority priority);
    virtual pxcmStatus QueryPriority([Out] Priority %priority);

internal:

    PXCMScheduler(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCScheduler *QueryInstance(void) { return (PXCScheduler*)m_instance; }
};
