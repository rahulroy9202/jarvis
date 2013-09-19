/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmaccelerator.h"

pxcmStatus PXCMAudio::QueryInfo([Out] AudioInfo %info) {
    pin_ptr<AudioInfo> pp(&info);
    return (pxcmStatus)QueryInstance()->QueryInfo((PXCAudio::AudioInfo *)pp);
}

PXCMAudio::AudioOption PXCMAudio::QueryOption(void) {
    return (PXCMAudio::AudioOption)QueryInstance()->QueryOption();
}

pxcmStatus PXCMAudio::SetOption(AudioOption option) {
	return (pxcmStatus)QueryInstance()->SetOption((PXCAudio::AudioOption)options);
}

pxcmU64 PXCMAudio::QueryTimeStamp(void) {
    return (pxcmU64)QueryInstance()->QueryTimeStamp();
}

pxcmStatus PXCMAudio::SetTimeStamp(pxcmU64 ts) {
    return (pxcmStatus)QueryInstance()->SetTimeStamp((pxcU64)ts);
}

pxcmStatus PXCMAudio::CopyData(PXCMAudio ^src_audio) {
    return (pxcmStatus)QueryInstance()->CopyData(src_audio->QueryInstance());
}

pxcmStatus PXCMAudio::AcquireAccess(Access access, PXCMAccelerator ^accelerator, AudioFormat format, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCAudio::Access)access,accelerator->QueryInstance(),(PXCAudio::AudioFormat)format,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::AcquireAccess(Access access, PXCMAccelerator ^accelerator, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCAudio::Access)access,accelerator->QueryInstance(),(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::AcquireAccess(Access access, AudioFormat format, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCAudio::Access)access,(PXCAudio::AudioFormat)format,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::AcquireAccess(Access access, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCAudio::Access)access,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::TryAccess(Access access, PXCMAccelerator ^accelerator, AudioFormat format, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCAudio::Access)access,accelerator->QueryInstance(),(PXCAudio::AudioFormat)format,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::TryAccess(Access access, PXCMAccelerator ^accelerator, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCAudio::Access)access,accelerator->QueryInstance(),(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::TryAccess(Access access, AudioFormat format, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCAudio::Access)access,(PXCAudio::AudioFormat)format,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::TryAccess(Access access, [Out] AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCAudio::Access)access,(PXCAudio::AudioData*)pp);
}

pxcmStatus PXCMAudio::ReleaseAccess(AudioData %data) {
    pin_ptr<AudioData> pp(&data);
    return (pxcmStatus)QueryInstance()->ReleaseAccess((PXCAudio::AudioData*)pp);
}

array<pxcmBYTE>^ PXCMAudio::AudioData::ToByteArray(void) {
    int bytesPerSample=(((int)format&(int)AudioFormat::AUDIO_FORMAT_SIZE_MASK)>>3);
    array<pxcmBYTE> ^ba=gcnew array<pxcmBYTE>(dataSize*bytesPerSample);
    for (int i=0;i<ba->Length;i++) ba[i]=(pxcmBYTE)(*((pxcBYTE*)buffer.dataPtr.ToPointer()+i));
    return ba;
}

