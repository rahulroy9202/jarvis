/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmbase.h"
#include "pxcmaccelerator.h"
#include "pxcmaudio.h"
#include "pxcmcapture.h"
#include "pxcmprojection.h"
#include "pxcmface.h"
#include "pxcmgesture.h"
#include "pxcmimage.h"
#include "pxcmmetadata.h"
#include "pxcmpowerstate.h"
#include "pxcmscheduler.h"
#include "pxcmsession.h"
#include "pxcmvoice.h"
#include "pxcmsegmentation.h"

PXCMBase^ PXCMBase::DynamicCastEx(pxcmUID cuid, PXCBase *instance) {
    if (cuid==PXCMAccelerator::CUID) return gcnew PXCMAccelerator(instance,false);
    if (cuid==PXCMAudio::CUID) return gcnew PXCMAudio(instance,false);
    if (cuid==PXCMCapture::CUID) return gcnew PXCMCapture(instance,false);
    if (cuid==PXCMCapture::Device::CUID) return gcnew PXCMCapture::Device(instance,false);
    if (cuid==PXCMProjection::CUID) return gcnew PXCMProjection(instance,false);
    if (cuid==PXCMCapture::VideoStream::CUID) return gcnew PXCMCapture::VideoStream(instance,false);
    if (cuid==PXCMCapture::AudioStream::CUID) return gcnew PXCMCapture::AudioStream(instance,false);
    if (cuid==PXCMFaceAnalysis::CUID) return gcnew PXCMFaceAnalysis(instance,false);
    if (cuid==PXCMFaceAnalysis::Detection::CUID) return gcnew PXCMFaceAnalysis::Detection(instance,false);
    if (cuid==PXCMFaceAnalysis::Landmark::CUID) return gcnew PXCMFaceAnalysis::Landmark(instance,false);
    if (cuid==PXCMFaceAnalysis::Recognition::CUID) return gcnew PXCMFaceAnalysis::Recognition(instance,false);
    if (cuid==PXCMFaceAnalysis::Recognition::Model::CUID) return gcnew PXCMFaceAnalysis::Recognition::Model(instance,false);
    if (cuid==PXCMGesture::CUID) return gcnew PXCMGesture(instance,false);
	if (cuid==PXCMSegmentation::CUID) return gcnew PXCMSegmentation(instance,false);
    if (cuid==PXCMImage::CUID) return gcnew PXCMImage(instance,false);
    if (cuid==PXCMMetadata::CUID) return gcnew PXCMMetadata(instance,false);
    if (cuid==PXCMPowerState::CUID) return gcnew PXCMPowerState(instance,false);
    if (cuid==PXCMScheduler::CUID) return gcnew PXCMScheduler(instance,false);
    if (cuid==PXCMScheduler::SyncPoint::CUID) return gcnew PXCMScheduler::SyncPoint(instance,false);
    if (cuid==PXCMSession::CUID) return gcnew PXCMSession(instance,false);
    if (cuid==PXCMVoiceRecognition::CUID) return gcnew PXCMVoiceRecognition(instance,false);
    if (cuid==PXCMVoiceSynthesis::CUID) return gcnew PXCMVoiceSynthesis(instance,false);
    return nullptr;
};

PXCMBase^ PXCMBase::DynamicCast(pxcmUID cuid) {
    PXCMBase ^base=nullptr;
    PXCBase *instance=(PXCBase*)m_instance->DynamicCast((pxcUID)cuid);
    if (instance) base=DynamicCastEx(cuid,instance);
    return base;
}

PXCMBase::PXCMBase(PXCBase *instance, bool b_delete) {
    m_instance=instance; m_delete=b_delete;

#ifdef PXCM_DEBUG_PXCMBASE
    m_cuids=gcnew array<pxcmUID>(10);
    int n=0;
    pxcmUID cuid;
    cuid=PXCMAccelerator::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMAudio::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMCapture::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMCapture::Device::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMCapture::Projection::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMCapture::VideoStream::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMCapture::AudioStream::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::Detection::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::Landmark::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::Attribute::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::Recognition::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMFaceAnalysis::Recognition::Model::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMGesture::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMGesture::GeoNode::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMGesture::Blob::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
	cuid=PXCMSegmentation::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMImage::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMMetadata::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMPowerState::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMScheduler::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMScheduler::SyncPoint::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMSession::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMVoiceCommand::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMVoiceCommand::GrammarBuilder::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMVoiceSynthesis::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
    cuid=PXCMVoiceEmotion::CUID; if (instance->DynamicCast((pxcUID)cuid)) m_cuids[n++]=cuid;
#endif
}

PXCMBase::~PXCMBase(void) {
    this->!PXCMBase();
    GC::SuppressFinalize(this);
}

PXCMBase::!PXCMBase(void) {
    if (m_delete && m_instance) {
		m_instance->Release();
		m_instance=0;
	}
}
