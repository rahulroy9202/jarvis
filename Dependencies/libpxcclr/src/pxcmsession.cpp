/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmsession.h"
#include "pxcmcapture.h"

static void Exercise(void) {
    PXCMSession::ImplDesc desc;
    desc.cuids[0]=desc.cuids[1];
    desc.friendlyName.set("abcd");
    desc.friendlyName.get();
}

pxcmStatus PXCMSession::CreateInstance(PXCMSession ^% session) {
    PXCSession *instance;
    pxcmStatus sts=(pxcmStatus)PXCSession_Create(&instance);
    session=gcnew PXCMSession(instance,true);
    return sts;
}

pxcmStatus PXCMSession::QueryVersion([Out] ImplVersion %version) {
    pin_ptr<ImplVersion> pp(&version);
    return (pxcmStatus)QueryInstance()->QueryVersion((PXCSession::ImplVersion*)pp);
}

pxcmStatus PXCMSession::QueryImpl(ImplDesc %templat, pxcmU32 idx, [Out] ImplDesc %desc) {
    pin_ptr<ImplDesc> t1=&templat, t2=&desc;
    return (pxcmStatus)QueryInstance()->QueryImpl((PXCSession::ImplDesc*)t1,(pxcU32)idx,(PXCSession::ImplDesc*)t2);
}

pxcmStatus PXCMSession::QueryImpl(pxcmU32 idx, [Out] ImplDesc %desc) {
    pin_ptr<ImplDesc> t2=&desc;
    return (pxcmStatus)QueryInstance()->QueryImpl(0,(pxcU32)idx,(PXCSession::ImplDesc*)t2);
}

pxcmStatus PXCMSession::CreateScheduler([Out] PXCMScheduler ^%instance) {
    PXCScheduler *sch;
    pxcStatus sts=QueryInstance()->CreateScheduler(&sch);
    if (sts>=PXC_STATUS_NO_ERROR) instance=gcnew PXCMScheduler(sch,true);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::CreateAccelerator(PXCMAccelerator::AccelType type, [Out] PXCMAccelerator ^%instance) {
    PXCAccelerator *accel;
    pxcStatus sts=QueryInstance()->CreateAccelerator((PXCAccelerator::AccelType)type,&accel);
    if (sts>=PXC_STATUS_NO_ERROR) instance=gcnew PXCMAccelerator(accel,true);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::CreateAccelerator([Out] PXCMAccelerator ^%instance) {
    PXCAccelerator *accel;
    pxcStatus sts=QueryInstance()->CreateAccelerator(0,&accel);
    if (sts>=PXC_STATUS_NO_ERROR) instance=gcnew PXCMAccelerator(accel,true);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::CreateImpl(PXCMScheduler ^sch, PXCMAccelerator ^accel, ImplDesc %desc, pxcmUID iuid, pxcmUID cuid, [Out] PXCMBase ^%instance) {
    pxcStatus sts=PXC_STATUS_ITEM_UNAVAILABLE;
    PXCCapture *instance2=0;
    pin_ptr<ImplDesc> pp(&desc);
    sts=QueryInstance()->CreateImpl(sch->QueryInstance(),accel->QueryInstance(),(PXCSession::ImplDesc*)pp,(pxcUID)iuid,(pxcUID)cuid,(void**)&instance2);
    if (sts>=PXC_STATUS_NO_ERROR) {
		instance=PXCMBase::DynamicCastEx(cuid,instance2);
		if (instance) instance->m_delete=true;
	}
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::CreateImpl(pxcmUID iuid, pxcmUID cuid, [Out] PXCMBase ^%instance) {
    pxcStatus sts=PXC_STATUS_ITEM_UNAVAILABLE;
    PXCBase *instance2=0;
    sts=QueryInstance()->CreateImpl((pxcUID)iuid,(pxcUID)cuid,(void**)&instance2);
    if (sts>=PXC_STATUS_NO_ERROR) {
		instance=PXCMBase::DynamicCastEx(cuid,instance2);
		if (instance) instance->m_delete=true;
	}
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::CreateImpl(ImplDesc %desc, pxcmUID cuid, [Out] PXCMBase ^%instance) {
    pxcStatus sts=PXC_STATUS_ITEM_UNAVAILABLE;
    PXCBase *instance2=0;
    pin_ptr<ImplDesc> pp(&desc);
    sts=QueryInstance()->CreateImpl((PXCSession::ImplDesc*)pp,(pxcUID)cuid,(void**)&instance2);
    if (sts>=PXC_STATUS_NO_ERROR) {
		instance=PXCMBase::DynamicCastEx(cuid,instance2);
		if (instance) instance->m_delete=true;
	}
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::LoadImplFromFile(String ^moduleName) {
    IntPtr buffer=Marshal::StringToBSTR(moduleName);
    pxcStatus sts=QueryInstance()->LoadImplFromFile((pxcCHAR*)buffer.ToPointer());
    Marshal::FreeBSTR(buffer);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSession::UnloadImplFromFile(String ^moduleName) {
    IntPtr buffer=Marshal::StringToBSTR(moduleName);
    pxcStatus sts=QueryInstance()->UnloadImplFromFile((pxcCHAR*)buffer.ToPointer());
    Marshal::FreeBSTR(buffer);
    return (pxcmStatus)sts;
}

