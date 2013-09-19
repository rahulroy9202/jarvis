/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmcapture.h"
#include "pxcmsession.h"
#include "util_capture.h"

public ref class UtilMCapture {
public:

    virtual property PXCMCapture^ capture {
        PXCMCapture^ get(void);
    };
    virtual property PXCMCapture::Device^ device {
        PXCMCapture::Device^ get(void);
    };
    virtual property PXCMCapture::AudioStream^ audioStream {
        PXCMCapture::AudioStream^ get(void);
    };

    virtual void SetFilter(PXCMImage::ImageType type, PXCMSizeU32 %size);
    virtual void SetFilter(PXCMImage::ImageType type, PXCMSizeU32 %size, pxcmU32 fps);
	virtual void SetFilter(PXCMCapture::VideoStream::ProfileInfo %pinfo);
    virtual void SetFilter(PXCMSession::ImplDesc %desc);
    virtual void SetFilter(String ^name);
    virtual void SetFilter(PXCMCapture::Device::Property pty, pxcmF32 value);

    virtual pxcmStatus LocateStreams(PXCMCapture::VideoStream::DataDesc %inputs);
    virtual pxcmStatus LocateStreams(PXCMCapture::AudioStream::DataDesc %inputs);
    virtual pxcmStatus LocateStreams(System::Collections::Generic::List<PXCMCapture::VideoStream::DataDesc> %vinputs);
    virtual pxcmStatus LocateStreams(System::Collections::Generic::List<PXCMCapture::AudioStream::DataDesc> %ainputs);
    virtual pxcmStatus LocateStreams(System::Collections::Generic::List<PXCMCapture::VideoStream::DataDesc> %vinputs,System::Collections::Generic::List<PXCMCapture::AudioStream::DataDesc> %ainputs);

    virtual pxcmStatus MapImages(int input, array<PXCMImage^> ^in, array<PXCMImage^> ^out);
    virtual PXCMImage ^QueryImage(array<PXCMImage^> ^in, PXCMImage::ImageType type);

    virtual PXCMCapture::VideoStream^ QueryVideoStream(pxcmI32 channel);
    virtual PXCMCapture::VideoStream^ QueryVideoStream(pxcmI32 channel, pxcmI32 input);

    virtual pxcmStatus ReadStreamAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp);
    virtual pxcmStatus ReadStreamAsync([Out] PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp);

    UtilMCapture(PXCMSession ^session);

internal:

    UtilMCapture(UtilCapture *instance, bool b_delete);
	virtual ~UtilMCapture(void) { this->!UtilMCapture(); GC::SuppressFinalize(this); }
	!UtilMCapture(void);
	UtilCapture *QueryInstance(void) { return m_instance; }

protected:

	IntPtr		 m_name_filter;
	UtilCapture *m_instance;
	bool         m_instance_delete;
};
