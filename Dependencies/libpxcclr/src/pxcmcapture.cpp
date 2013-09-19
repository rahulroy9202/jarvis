/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmcapture.h"

static void Exercise(void) {
    PXCMCapture::DeviceInfo info;
    info.name.set(gcnew String("abcde"));
    String ^name2=info.name.get();

    PXCMCapture::VideoStream::DataDesc req;
    req.streams[0].format=req.streams[0].format;
    req.devCaps[0].label=req.devCaps[0].label;
}

pxcmStatus PXCMCapture::Device::QueryDevice([Out] DeviceInfo %dinfo) {
    pin_ptr<DeviceInfo> pp(&dinfo);
    return (pxcmStatus)QueryInstance()->QueryDevice((PXCCapture::DeviceInfo*)pp);
}

pxcmStatus PXCMCapture::Device::QueryStream(pxcmU32 sidx, [Out] StreamInfo %sinfo) {
    pin_ptr<StreamInfo> pp(&sinfo);
    return (pxcmStatus)QueryInstance()->QueryStream((pxcU32)sidx,(PXCCapture::Device::StreamInfo*)pp);
}

pxcmStatus PXCMCapture::Device::CreateStream(pxcmU32 sidx, pxcmUID cuid, PXCMBase ^%stream) {
	stream=nullptr;
	PXCBase *instance=0;
    pxcmStatus sts=(pxcmStatus)QueryInstance()->CreateStream((pxcU32)sidx,(pxcUID)cuid,(void**)&instance);
	if (sts>=pxcmStatus::PXCM_STATUS_NO_ERROR) {
		stream=PXCMBase::DynamicCastEx(cuid,instance);
		if (stream) stream->m_delete=true;
	}
	return sts;
}

pxcmStatus PXCMCapture::Device::QueryPropertyInfo(Property pty, [Out] PXCMRangeF32 %range, [Out] pxcmF32 %step, [Out] pxcmF32 %def, [Out] pxcmBool %isAuto) {
    pxcF32 step2=0, def2=0;
    pxcBool isAuto2=false;
    pin_ptr<PXCMRangeF32> pp(&range);
    pxcStatus sts=QueryInstance()->QueryPropertyInfo((PXCCapture::Device::Property)pty,(PXCRangeF32*)pp,&step2,&def2,&isAuto2);
    step=(pxcmF32)step2;
    def=(pxcmF32)def2;
    isAuto=(isAuto2!=false);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::Device::QueryProperty(Property label, [Out] pxcmF32 %value) {
    pxcF32 value2;
    pxcStatus sts=QueryInstance()->QueryProperty((PXCCapture::Device::Property)label,&value2);
    value=(pxcmF32)value2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::Device::QueryPropertyAsUID(Property label, [Out] pxcmUID %value) {
    pxcUID value2;
    pxcStatus sts=QueryInstance()->QueryPropertyAsUID((PXCCapture::Device::Property)label,&value2);
    value=(pxcmUID)value2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::Device::QueryPropertyAsPoint(Property pty, [Out] PXCMPointF32 %point) {
    pin_ptr<PXCMPointF32> pp(&point);
    return (pxcmStatus)QueryInstance()->QueryPropertyAsPoint((PXCCapture::Device::Property)pty,(PXCPointF32*)pp);
}

pxcmStatus PXCMCapture::Device::QueryPropertyAs3DPoint(Property pty, [Out] PXCMPoint3DF32 %point) {
    pin_ptr<PXCMPoint3DF32> pp(&point);
    return (pxcmStatus)QueryInstance()->QueryPropertyAs3DPoint((PXCCapture::Device::Property)pty,(PXCPoint3DF32*)pp);
}

pxcmStatus PXCMCapture::Device::QueryPropertyAsRange(Property pty, [Out] PXCMRangeF32 %range) {
    pin_ptr<PXCMRangeF32> pp(&range);
    return (pxcmStatus)QueryInstance()->QueryPropertyAsRange((PXCCapture::Device::Property)pty,(PXCRangeF32*)pp);
}

pxcmStatus PXCMCapture::Device::SetPropertyAuto(Property label, pxcmBool ifauto) {
    pxcStatus sts=QueryInstance()->SetPropertyAuto((PXCCapture::Device::Property)label,(pxcBool)ifauto);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::Device::SetProperty(Property label, pxcmF32 value) {
    pxcStatus sts=QueryInstance()->SetProperty((PXCCapture::Device::Property)label,(pxcF32)value);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::VideoStream::QueryStream([Out] Device::StreamInfo %sinfo) {
    pin_ptr<Device::StreamInfo> pp(&sinfo);
    return (pxcmStatus)QueryInstance()->QueryStream((PXCCapture::Device::StreamInfo*)pp);
}

pxcmStatus PXCMCapture::VideoStream::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcmU32)pidx,(PXCCapture::VideoStream::ProfileInfo*)pp);
}

pxcmStatus PXCMCapture::VideoStream::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCCapture::VideoStream::ProfileInfo*)pp);
}

pxcmStatus PXCMCapture::VideoStream::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    PXCCapture::VideoStream::ProfileInfo*pp2=(PXCCapture::VideoStream::ProfileInfo*)pp;
    return (pxcmStatus)QueryInstance()->SetProfile(pp2);
}

pxcmStatus PXCMCapture::VideoStream::ReadStreamAsync(PXCMImage ^%image, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCImage *image2=0;     // this is on the stack. so not movable
    PXCScheduler::SyncPoint *sp2=0;
    pxcStatus sts=QueryInstance()->ReadStreamAsync(&image2,&sp2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        image=gcnew PXCMImage(image2,true);
        sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    }
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::AudioStream::QueryStream([Out] Device::StreamInfo %sinfo) {
    pin_ptr<Device::StreamInfo> pp(&sinfo);
    return (pxcmStatus)QueryInstance()->QueryStream((PXCCapture::Device::StreamInfo*)pp);
}

pxcmStatus PXCMCapture::AudioStream::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcmU32)pidx,(PXCCapture::AudioStream::ProfileInfo*)pp);
}

pxcmStatus PXCMCapture::AudioStream::QueryProfile([Out] ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCCapture::AudioStream::ProfileInfo*)pp);
}

pxcmStatus PXCMCapture::AudioStream::SetProfile(ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCCapture::AudioStream::ProfileInfo*)pp);
}

pxcmStatus PXCMCapture::AudioStream::ReadStreamAsync([Out] PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCAudio *audio2=0;     // this is on the stack. so not movable
    PXCScheduler::SyncPoint *sp2=0;
    pxcStatus sts=QueryInstance()->ReadStreamAsync(&audio2,&sp2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        audio=gcnew PXCMAudio(audio2,true);
        sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    }
    return (pxcmStatus)sts;
}

pxcmStatus PXCMCapture::QueryDevice(pxcmU32 didx, [Out] DeviceInfo %dinfo) {
    pin_ptr<DeviceInfo> pp(&dinfo);
    return (pxcmStatus)QueryInstance()->QueryDevice((pxcU32)didx,(PXCCapture::DeviceInfo*)pp);
}

pxcmStatus PXCMCapture::CreateDevice(pxcmU32 didx, [Out] Device ^%device) {
    PXCCapture::Device *instance=0;
    pxcStatus sts=QueryInstance()->CreateDevice((pxcU32)didx,&instance);
    if (sts>=PXC_STATUS_NO_ERROR) device=gcnew Device(instance,true);
    return (pxcmStatus)sts;
}
