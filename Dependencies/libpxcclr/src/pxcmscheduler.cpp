/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmscheduler.h"

pxcmStatus PXCMScheduler::SyncPoint::QueryPtr(PXCMBase ^ptr) {
    return (pxcmStatus)QueryInstance()->QueryPtr(ptr->m_instance);
}

pxcmStatus PXCMScheduler::SyncPoint::Synchronize(pxcmU32 timeout) {
    return (pxcmStatus)QueryInstance()->Synchronize((pxcU32)timeout);
}

pxcmStatus PXCMScheduler::SyncPoint::Synchronize(void) {
    return (pxcmStatus)QueryInstance()->Synchronize((pxcU32)PXCScheduler::SyncPoint::TIMEOUT_INFINITE);
}

pxcmStatus PXCMScheduler::SyncPoint::SynchronizeEx(array<SyncPoint^> ^sps, [Out] pxcmU32 %idx, pxcmU32 timeout) {
    PXCScheduler::SyncPoint **sps2=(PXCScheduler::SyncPoint **)new PXCScheduler::SyncPoint*[sps->Length];
    if (!sps2) return pxcmStatus::PXCM_STATUS_ALLOC_FAILED;

    int i,k= -1;
    for (i=0;i<sps->Length;i++) {
        if (sps[i]!=nullptr) {
            sps2[i]=sps[i]->QueryInstance();
            if (sps2[i]) k=i;
        } else {
            sps2[i]=0;
        }
    }

    pxcStatus sts=PXC_STATUS_HANDLE_INVALID;
    if (k>=0) {
        sts=sps2[k]->SynchronizeEx(sps->Length,sps2,(pxcU32 *)&i,(pxcU32)timeout);
        idx=(pxcmU32)i;
    }
    delete [] sps2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMScheduler::SyncPoint::SynchronizeEx(array<SyncPoint^> ^sps, pxcmU32 timeout) {
    PXCScheduler::SyncPoint **sps2=(PXCScheduler::SyncPoint **)new PXCScheduler::SyncPoint*[sps->Length];
    if (!sps2) return pxcmStatus::PXCM_STATUS_ALLOC_FAILED;

    int i,k= -1;
    for (i=0;i<sps->Length;i++) {
        if (sps[i]!=nullptr) {
            sps2[i]=sps[i]->QueryInstance();
            if (sps2[i]) k=i;
        } else {
            sps2[i]=0;
        }
    }

    pxcStatus sts=PXC_STATUS_HANDLE_INVALID;
    if (k>=0) sts=sps2[k]->SynchronizeEx(sps->Length,sps2,0,(pxcU32)timeout);
    delete [] sps2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMScheduler::SyncPoint::SynchronizeEx(array<SyncPoint^> ^sps, [Out] pxcmU32 %idx) {
    return SynchronizeEx(sps,idx,PXCMScheduler::SyncPoint::TIMEOUT_INFINITE);
}

pxcmStatus PXCMScheduler::SyncPoint::SynchronizeEx(array<SyncPoint^> ^sps) {
    return SynchronizeEx(sps,PXCMScheduler::SyncPoint::TIMEOUT_INFINITE);
}

void PXCMScheduler::SyncPoint::Dispose(array<SyncPoint^> ^sps) {
	for each (SyncPoint^ sp in sps)
		if (sp!=nullptr) delete sp;
}

pxcmStatus PXCMScheduler::SetPriority(Priority priority) {
    return (pxcmStatus)QueryInstance()->SetPriority((PXCScheduler::Priority)priority);
}

pxcmStatus PXCMScheduler::QueryPriority([Out] Priority %priority) {
    PXCScheduler::Priority priority2=(PXCScheduler::Priority)0;
    pxcStatus sts=QueryInstance()->QueryPriority(&priority2);
	priority=(PXCMScheduler::Priority)priority2;
    return (pxcmStatus)sts;
}

