/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmaccelerator.h"

PXCMAccelerator::AccelType PXCMAccelerator::QueryAccelType(void) {
    return (AccelType)QueryInstance()->QueryAccelType();
}

PXCMAccelerator::Device PXCMAccelerator::QueryDevice(void) {
    return (Device)QueryInstance()->QueryDevice();
}

pxcmStatus PXCMAccelerator::QueryHandle(HandleType type, pxcmHDL %handle) {
    pxcHDL handle2=0;
	handle=IntPtr::Zero;
    pxcStatus sts=QueryInstance()->QueryHandle((PXCAccelerator::HandleType)type,&handle2);
	if (sts>=PXC_STATUS_NO_ERROR) handle=IntPtr(handle2);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMAccelerator::SetHandle(HandleType type, pxcmHDL handle) {
    return (pxcmStatus)QueryInstance()->SetHandle((PXCAccelerator::HandleType)type,handle.ToPointer());
}

pxcmStatus PXCMAccelerator::CreateImage(PXCMImage::ImageInfo %info, PXCMImage::ImageOption options, PXCMImage::ImageData %data, [Out] PXCMImage ^%image) {
    pin_ptr<PXCMImage::ImageInfo> ppi=&info;
    pin_ptr<PXCMImage::ImageData> ppd=&data;
    PXCImage *image2=0;
    pxcmStatus sts=(pxcmStatus)QueryInstance()->CreateImage((PXCImage::ImageInfo*)ppi,(PXCImage::ImageOption)options,(PXCImage::ImageData*)ppd,&image2);
    image=(sts>=pxcmStatus::PXCM_STATUS_NO_ERROR)?gcnew PXCMImage(image2,true):nullptr;
    return sts;
}

pxcmStatus PXCMAccelerator::CreateImage(PXCMImage::ImageInfo %info, [Out] PXCMImage ^%image) {
    pin_ptr<PXCMImage::ImageInfo> ppi=&info;
    PXCImage *image2=0;
    pxcmStatus sts=(pxcmStatus)QueryInstance()->CreateImage((PXCImage::ImageInfo*)ppi,0,0,&image2);
    image=(sts>=pxcmStatus::PXCM_STATUS_NO_ERROR)?gcnew PXCMImage(image2,true):nullptr;
    return sts;
}

pxcmStatus PXCMAccelerator::CreateAudio(PXCMAudio::AudioInfo %info, PXCMAudio::AudioOption options, PXCMAudio::AudioData %data, [Out] PXCMAudio ^%audio) {
    pin_ptr<PXCMAudio::AudioInfo> ppi=&info;
    pin_ptr<PXCMAudio::AudioData> ppd=&data;
    PXCAudio *audio2=0;
    pxcmStatus sts=(pxcmStatus)QueryInstance()->CreateAudio((PXCAudio::AudioInfo*)ppi,(pxcOption)options,(PXCAudio::AudioData*)ppd,&audio2);
    audio=(sts>=pxcmStatus::PXCM_STATUS_NO_ERROR)?gcnew PXCMAudio(audio2,true):nullptr;
    return sts;
}

pxcmStatus PXCMAccelerator::CreateAudio(PXCMAudio::AudioInfo %info, [Out] PXCMAudio ^%audio) {
    pin_ptr<PXCMAudio::AudioInfo> ppi=&info;
    PXCAudio *audio2=0;
    pxcmStatus sts=(pxcmStatus)QueryInstance()->CreateAudio((PXCAudio::AudioInfo*)ppi,0,0,&audio2);
    audio=(sts>=pxcmStatus::PXCM_STATUS_NO_ERROR)?gcnew PXCMAudio(audio2,true):nullptr;
    return sts;
}
