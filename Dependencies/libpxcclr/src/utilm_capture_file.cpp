/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "utilm_capture_file.h"
#include "util_capture_file.h"

UtilMCaptureFile::UtilMCaptureFile(PXCMSession ^session, String ^filename, pxcmBool recording):UtilMCapture(session) {
    if (filename==nullptr) return;
    if (m_instance) { m_instance->Release(); m_instance=0; }
    IntPtr buffer=Marshal::StringToBSTR(filename);
    m_instance=new UtilCaptureFile(session->QueryInstance(),(pxcCHAR*)buffer.ToPointer(),(pxcBool)recording);
    Marshal::FreeBSTR(buffer);
}

void UtilMCaptureFile::SetMask(PXCMImage::ImageType type) {
    UtilCaptureFile *utilcap=dynamic_cast<UtilCaptureFile*>(m_instance);
    if (utilcap) utilcap->SetMask((PXCImage::ImageType)type);
}

void UtilMCaptureFile::SetPause(pxcmBool pause) {
    UtilCaptureFile *utilcap=dynamic_cast<UtilCaptureFile*>(m_instance);
    if (utilcap) utilcap->SetPause((pxcBool)pause);
}

void UtilMCaptureFile::SetRealtime(pxcmBool realtime) {
    UtilCaptureFile *utilcap=dynamic_cast<UtilCaptureFile*>(m_instance);
    if (utilcap) utilcap->SetRealtime((pxcBool)realtime);
}

void UtilMCaptureFile::SetPosition(pxcmI32 frame) {
    UtilCaptureFile *utilcap=dynamic_cast<UtilCaptureFile*>(m_instance);
    if (utilcap) utilcap->SetPosition((pxcI32)frame);
}

pxcmI32 UtilMCaptureFile::QueryPosition(void) {
    UtilCaptureFile *utilcap=dynamic_cast<UtilCaptureFile*>(m_instance);
	return utilcap?(pxcmI32)utilcap->QueryPosition():0;
}
