/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "utilm_capture.h"
#include <vector>

UtilMCapture::UtilMCapture(PXCMSession ^session) {
    m_instance=new UtilCapture(session->QueryInstance());
	m_name_filter=IntPtr(0);
	m_instance_delete=true;
}

UtilMCapture::UtilMCapture(UtilCapture *instance, bool b_delete) {
	m_instance=instance;
	m_name_filter=IntPtr(0);
	m_instance_delete=b_delete;
}

UtilMCapture::!UtilMCapture(void) {
	if (m_instance && m_instance_delete) {
		m_instance->Release();
		m_instance=0;
	}
	if (m_name_filter!=IntPtr::Zero) {
		Marshal::FreeBSTR(m_name_filter);
		m_name_filter=IntPtr(0);
	}
}

void UtilMCapture::SetFilter(PXCMImage::ImageType type, PXCMSizeU32 %size) {
    pin_ptr<PXCMSizeU32> pp(&size);
    QueryInstance()->SetFilter((PXCImage::ImageType)type,*(PXCSizeU32*)pp);
}

void UtilMCapture::SetFilter(PXCMImage::ImageType type, PXCMSizeU32 %size, pxcmU32 fps) {
    pin_ptr<PXCMSizeU32> pp(&size);
    QueryInstance()->SetFilter((PXCImage::ImageType)type,*(PXCSizeU32*)pp, (pxcU32)fps);
}

void UtilMCapture::SetFilter(PXCMCapture::VideoStream::ProfileInfo %pinfo) {
    pin_ptr<PXCMCapture::VideoStream::ProfileInfo> pp(&pinfo);
	QueryInstance()->SetFilter((PXCCapture::VideoStream::ProfileInfo*)pp);
}

void UtilMCapture::SetFilter(PXCMSession::ImplDesc %desc) {
    pin_ptr<PXCMSession::ImplDesc> pp(&desc);
    QueryInstance()->SetFilter(*(PXCSession::ImplDesc*)pp);
}

void UtilMCapture::SetFilter(String ^name) {
	if (m_name_filter!=IntPtr::Zero) Marshal::FreeBSTR(m_name_filter);
	m_name_filter=Marshal::StringToBSTR(name);
	QueryInstance()->SetFilter((pxcCHAR*)m_name_filter.ToPointer());
}

void UtilMCapture::SetFilter(PXCMCapture::Device::Property pty, pxcmF32 value) {
    QueryInstance()->SetFilter((PXCCapture::Device::Property)pty,(pxcF32)value);
}

pxcmStatus UtilMCapture::LocateStreams(System::Collections::Generic::List<PXCMCapture::VideoStream::DataDesc> %vinputs) {
    PXCCapture::VideoStream::DataDesc *descs=new PXCCapture::VideoStream::DataDesc[vinputs.Count];
	if (!descs) return pxcmStatus::PXCM_STATUS_ALLOC_FAILED;

	int i;
	std::vector<PXCCapture::VideoStream::DataDesc*> vinputs2;
	for (i=0;i<vinputs.Count;i++) {
		pin_ptr<PXCMCapture::VideoStream::DataDesc> pp(&vinputs[i]);
		descs[i]= *((PXCCapture::VideoStream::DataDesc*)pp);
		vinputs2.push_back(&descs[i]);
	}

    pxcmStatus sts=(pxcmStatus)QueryInstance()->LocateStreams(vinputs2);

	if (sts>=pxcmStatus::PXCM_STATUS_NO_ERROR) {
		for (i=0;i<vinputs.Count;i++) {
			PXCMCapture::VideoStream::DataDesc dd;
			pin_ptr<PXCMCapture::VideoStream::DataDesc> pp(&dd);
			*((PXCCapture::VideoStream::DataDesc*)pp)=descs[i];
			vinputs[i]=dd;
		}
	}

	delete [] descs;
    return sts;
}

pxcmStatus UtilMCapture::LocateStreams(System::Collections::Generic::List<PXCMCapture::AudioStream::DataDesc> %ainputs) {
    PXCCapture::AudioStream::DataDesc *descs=new PXCCapture::AudioStream::DataDesc[ainputs.Count];
	if (!descs) return pxcmStatus::PXCM_STATUS_ALLOC_FAILED;

	int i;
	std::vector<PXCCapture::AudioStream::DataDesc*> ainputs2;
	for (i=0;i<ainputs.Count;i++) {
		pin_ptr<PXCMCapture::AudioStream::DataDesc> pp(&ainputs[i]);
		descs[i]= *((PXCCapture::AudioStream::DataDesc*)pp);
		ainputs2.push_back(&descs[i]);
	}

    pxcmStatus sts=(pxcmStatus)QueryInstance()->LocateStreams(ainputs2);

	if (sts>=pxcmStatus::PXCM_STATUS_NO_ERROR) {
		for (i=0;i<ainputs.Count;i++) {
			PXCMCapture::AudioStream::DataDesc dd;
			pin_ptr<PXCMCapture::AudioStream::DataDesc> pp(&dd);
			*((PXCCapture::AudioStream::DataDesc*)pp)=descs[i];
			ainputs[i]=dd;
		}
	}

	delete [] descs;
    return sts;
}

pxcmStatus UtilMCapture::LocateStreams(System::Collections::Generic::List<PXCMCapture::VideoStream::DataDesc> %vinputs, System::Collections::Generic::List<PXCMCapture::AudioStream::DataDesc> %ainputs) {
    PXCCapture::VideoStream::DataDesc *vdescs=new PXCCapture::VideoStream::DataDesc[vinputs.Count];
    PXCCapture::AudioStream::DataDesc *adescs=new PXCCapture::AudioStream::DataDesc[ainputs.Count];
	pxcmStatus sts=pxcmStatus::PXCM_STATUS_ALLOC_FAILED;
	if (vdescs && adescs) {
		int i;
		std::vector<PXCCapture::VideoStream::DataDesc*> vinputs2;
		for (i=0;i<vinputs.Count;i++) {
			pin_ptr<PXCMCapture::VideoStream::DataDesc> pp(&vinputs[i]);
			vdescs[i]= *((PXCCapture::VideoStream::DataDesc*)pp);
			vinputs2.push_back(&vdescs[i]);
		}
		std::vector<PXCCapture::AudioStream::DataDesc*> ainputs2;
		for (i=0;i<ainputs.Count;i++) {
			pin_ptr<PXCMCapture::AudioStream::DataDesc> pp(&ainputs[i]);
			adescs[i]= *((PXCCapture::AudioStream::DataDesc*)pp);
			ainputs2.push_back(&adescs[i]);
		}

		sts=(pxcmStatus)QueryInstance()->LocateStreams(vinputs2,ainputs2);

		if (sts>=pxcmStatus::PXCM_STATUS_NO_ERROR) {
			for (i=0;i<vinputs.Count;i++) {
				PXCMCapture::VideoStream::DataDesc dd;
				pin_ptr<PXCMCapture::VideoStream::DataDesc> pp(&dd);
				*((PXCCapture::VideoStream::DataDesc*)pp)=vdescs[i];
				vinputs[i]=dd;
			}
			for (i=0;i<ainputs.Count;i++) {
				PXCMCapture::AudioStream::DataDesc dd;
				pin_ptr<PXCMCapture::AudioStream::DataDesc> pp(&dd);
				*((PXCCapture::AudioStream::DataDesc*)pp)=adescs[i];
				ainputs[i]=dd;
			}
		}
	}
	if (vdescs) delete [] vdescs;
	if (adescs) delete [] adescs;
    return sts;
}

pxcmStatus UtilMCapture::LocateStreams(PXCMCapture::VideoStream::DataDesc %inputs) {
    pin_ptr<PXCMCapture::VideoStream::DataDesc> pp(&inputs);
    return (pxcmStatus)QueryInstance()->LocateStreams((PXCCapture::VideoStream::DataDesc*)pp);
}

pxcmStatus UtilMCapture::LocateStreams(PXCMCapture::AudioStream::DataDesc %inputs) {
    pin_ptr<PXCMCapture::AudioStream::DataDesc> pp(&inputs);
    return (pxcmStatus)QueryInstance()->LocateStreams((PXCCapture::AudioStream::DataDesc*)pp);
}

PXCMCapture::Device^ UtilMCapture::device::get(void) {
    PXCCapture::Device *device=QueryInstance()->QueryDevice();
    return device?gcnew PXCMCapture::Device(device,false):nullptr;
}

PXCMCapture^ UtilMCapture::capture::get(void) {
    PXCCapture *capture=QueryInstance()->QueryCapture();
    return capture?gcnew PXCMCapture(capture,false):nullptr;
}

PXCMCapture::VideoStream^ UtilMCapture::QueryVideoStream(pxcmI32 channel) {
    PXCCapture::VideoStream *stream=QueryInstance()->QueryVideoStream((pxcI32)channel);
    return stream?gcnew PXCMCapture::VideoStream(stream,false):nullptr;
}

PXCMCapture::VideoStream^ UtilMCapture::QueryVideoStream(pxcmI32 channel, pxcmI32 input) {
    PXCCapture::VideoStream *stream=QueryInstance()->QueryVideoStream((pxcI32)channel,input);
    return stream?gcnew PXCMCapture::VideoStream(stream,false):nullptr;
}

PXCMCapture::AudioStream^ UtilMCapture::audioStream::get(void) {
    PXCCapture::AudioStream *stream=QueryInstance()->QueryAudioStream();
    return stream?gcnew PXCMCapture::AudioStream(stream,false):nullptr;
}

pxcmStatus UtilMCapture::ReadStreamAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCCapture::VideoStream::Images images2;
    for (int j=0;j<PXCCapture::VideoStream::STREAM_LIMIT;j++) images2[j]=0;

    PXCScheduler::SyncPoint *sp2=0;
    sp=nullptr;
    pxcStatus sts=QueryInstance()->ReadStreamAsync(images2,&sp2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        for (int i=0;i<images->Length;i++)
            images[i]=(i<PXCMCapture::VideoStream::STREAM_LIMIT)?(images2[i]?gcnew PXCMImage(images2[i],true):nullptr):nullptr;
        sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    }
    return (pxcmStatus)sts;
}

pxcmStatus UtilMCapture::ReadStreamAsync(PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCAudio *audio2=0;
    PXCScheduler::SyncPoint *sp2=0;
    audio=nullptr; sp=nullptr;
    pxcStatus sts=QueryInstance()->ReadStreamAsync(&audio2,&sp2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        audio=gcnew PXCMAudio(audio2,true);
        sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    }
    return (pxcmStatus)sts;
}

pxcmStatus UtilMCapture::MapImages(int input, array<PXCMImage^> ^in, array<PXCMImage^> ^out) {
    PXCCapture::VideoStream::Images in2, out2;
    for (int i=0;i<PXCCapture::VideoStream::STREAM_LIMIT;i++) in2[i]=(i<in->Length)?(in[i]?in[i]->QueryInstance():0):0;
    for (int j=0;j<PXCCapture::VideoStream::STREAM_LIMIT;j++) out2[j]=0;
    pxcStatus sts=QueryInstance()->MapImages(input, in2, out2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        for (int k=0;k<out->Length;k++) {
			out[k]=nullptr;
            if (out2[k]) {
				out[k]=gcnew PXCMImage(out2[k],false);
				out[k]->m_delete=false;
			}
		}
    }
    return (pxcmStatus)sts;
}

PXCMImage ^UtilMCapture::QueryImage(array<PXCMImage^> ^images, PXCMImage::ImageType type) {
    for each (PXCMImage^ image in images) {
        if ((PXCMImage::ImageType)((int)image->imageInfo.format&(int)PXCMImage::ImageType::IMAGE_TYPE_MASK)==type) return image;
    }
    return nullptr;
}
