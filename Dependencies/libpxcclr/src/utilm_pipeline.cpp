/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "utilm_pipeline.h"

#pragma unmanaged

class UtilPipelineX: public UtilPipeline {
public:

	UtilPipelineX(PXCSession *session=NULL, const pxcCHAR *file=0, bool recording=false):UtilPipeline(session,file,recording) {}

	typedef void (*OnGestureSetupProc)(PXCGesture::ProfileInfo *pinfo);
	OnGestureSetupProc p_OnGestureSetup;
	virtual void  OnGestureSetup(PXCGesture::ProfileInfo *pinfo) {
		p_OnGestureSetup(pinfo);
	}

	typedef void (*OnSegmentationSetupProc)(PXCSegmentation::ProfileInfo *pinfo);
	OnSegmentationSetupProc p_OnSegmentationSetup;
	virtual void  OnSegmentationSetup(PXCSegmentation::ProfileInfo *pinfo) {
		p_OnSegmentationSetup(pinfo);
	}

	typedef void (*OnFaceSetupProc)(PXCFaceAnalysis::ProfileInfo *pinfo);
	OnFaceSetupProc p_OnFaceSetup;
	virtual void  OnFaceSetup(PXCFaceAnalysis::ProfileInfo *finfo) {
		p_OnFaceSetup(finfo);	
	}

	typedef void (*OnFaceDetectionSetupProc)(PXCFaceAnalysis::Detection::ProfileInfo *pinfo);
	OnFaceDetectionSetupProc p_OnFaceDetectionSetup;
	virtual void  OnFaceDetectionSetup(PXCFaceAnalysis::Detection::ProfileInfo *finfo) {
		p_OnFaceDetectionSetup(finfo);
	}

	typedef void (*OnFaceLandmarkSetupProc)(PXCFaceAnalysis::Landmark::ProfileInfo *pinfo);
	OnFaceLandmarkSetupProc p_OnFaceLandmarkSetup;
	virtual void  OnFaceLandmarkSetup(PXCFaceAnalysis::Landmark::ProfileInfo *finfo) {
        p_OnFaceLandmarkSetup(finfo);
    }


	typedef void (PXCAPI *OnGestureProc)(PXCGesture::Gesture *data);
	OnGestureProc p_OnGesture;
	virtual void  PXCAPI OnGesture(PXCGesture::Gesture *gesture) {
		p_OnGesture(gesture);
	}

	typedef void (PXCAPI *OnAlertGProc)(PXCGesture::Alert *alert);
	OnAlertGProc p_OnAlertG;
	virtual void  PXCAPI OnAlert(PXCGesture::Alert *alert) {
		p_OnAlertG(alert);
	}

	typedef void (*OnReconnectProc)(void);
	OnReconnectProc p_OnReconnect;
	virtual void  OnReconnect(void) {
		p_OnReconnect();
	}

	typedef bool (*OnDisconnectProc)(void);
	OnDisconnectProc p_OnDisconnect;
	virtual bool  OnDisconnect(void) {
		return p_OnDisconnect();
	}

	typedef bool (*OnNewFrameProc)(void);
	OnNewFrameProc p_OnNewFrame;
	virtual bool  OnNewFrame(void) {
		return p_OnNewFrame();
	}

	typedef bool (*OnImageXProc)(void *image);
	OnImageXProc p_OnImageX;
	virtual void  OnImageX(PXCImage* image) {
		p_OnImageX(image);
	}
	virtual void  OnImage(PXCImage *image) {
		OnImageX(image);
	}

	typedef bool (*OnAudioXProc)(void *audio);
	OnAudioXProc p_OnAudioX;
	virtual void  OnAudioX(PXCAudio* audio) {
		p_OnAudioX(audio);
	}
	virtual void  OnAudio(PXCAudio *audio) {
		OnAudioX(audio);
	}

	typedef void (*OnVoiceRecognitionSetupProc)(PXCVoiceRecognition::ProfileInfo *finfo);
	OnVoiceRecognitionSetupProc p_OnVoiceRecognitionSetup;
	virtual void  OnVoiceRecognitionSetup(PXCVoiceRecognition::ProfileInfo *finfo) {
		p_OnVoiceRecognitionSetup(finfo);
	}

	typedef void (PXCAPI *OnRecognizedProc)(PXCVoiceRecognition::Recognition *data);
	OnRecognizedProc p_OnRecognized;
	virtual void  PXCAPI OnRecognized(PXCVoiceRecognition::Recognition *data) {
		p_OnRecognized(data);
	}

	typedef void (PXCAPI *OnAlertVRProc)(PXCVoiceRecognition::Alert *data);
	OnAlertVRProc p_OnAlertVR;
	virtual void  PXCAPI OnAlert(PXCVoiceRecognition::Alert *data) {
		p_OnAlertVR(data);
	}
};

#pragma managed

#define SETUPDELEGATEX(CALLBACK,CALLBACK1) \
{	\
	CALLBACK##Delegate ^CALLBACK##_dgt=gcnew CALLBACK##Delegate(this,&UtilMPipeline:: CALLBACK1);	\
	m_##CALLBACK##_gch=GCHandle::Alloc(##CALLBACK##_dgt);	\
	m_instance->p_##CALLBACK=static_cast<UtilPipelineX::CALLBACK##Proc>(Marshal::GetFunctionPointerForDelegate(CALLBACK##_dgt).ToPointer());	\
}
#define SETUPDELEGATE(X) SETUPDELEGATEX(X,X)
#define FREEDELEGATE(CALLBACK) if (m_##CALLBACK##_gch.IsAllocated) m_##CALLBACK##_gch.Free()

void UtilMPipeline::SetupDelegates(void) {
	SETUPDELEGATE(OnGestureSetup);
	SETUPDELEGATE(OnSegmentationSetup);
	SETUPDELEGATE(OnFaceSetup);
    SETUPDELEGATE(OnFaceDetectionSetup);
    SETUPDELEGATE(OnFaceLandmarkSetup);
    SETUPDELEGATE(OnGesture);
	SETUPDELEGATEX(OnAlertG,OnAlert);
	SETUPDELEGATE(OnReconnect);
	SETUPDELEGATE(OnDisconnect);
	SETUPDELEGATE(OnNewFrame);
	SETUPDELEGATE(OnImageX);
	SETUPDELEGATE(OnAudioX);
	SETUPDELEGATE(OnVoiceRecognitionSetup);
	SETUPDELEGATE(OnRecognized);
	SETUPDELEGATEX(OnAlertVR,OnAlert);
}

void UtilMPipeline::FreeDelegates(void) {
	FREEDELEGATE(OnGestureSetup);
	FREEDELEGATE(OnSegmentationSetup);
    FREEDELEGATE(OnFaceSetup);
    FREEDELEGATE(OnFaceDetectionSetup);
    FREEDELEGATE(OnFaceLandmarkSetup);
	FREEDELEGATE(OnGesture);
	FREEDELEGATE(OnAlertG);
	FREEDELEGATE(OnReconnect);
	FREEDELEGATE(OnDisconnect);
	FREEDELEGATE(OnNewFrame);
	FREEDELEGATE(OnImageX);
	FREEDELEGATE(OnAudioX);
	FREEDELEGATE(OnVoiceRecognitionSetup);
	FREEDELEGATE(OnRecognized);
	FREEDELEGATE(OnAlertVR);
}

void UtilMPipeline::Setup(PXCMSession ^session, String ^filename, bool recording) {
	m_strings=gcnew System::Collections::Generic::List<IntPtr>();
    PXCSession *session2=(session!=nullptr)?session->QueryInstance():0;
    pxcCHAR *filename2=0;
    if (filename!=nullptr) {
	    IntPtr filename3=Marshal::StringToBSTR(filename);
	    m_strings->Add(filename3);
        filename2=(pxcCHAR*)filename3.ToPointer();
    }
    m_instance=new UtilPipelineX(session2,filename2,recording);
	SetupDelegates();
}

UtilMPipeline::!UtilMPipeline(void) {
	if (m_instance) {
		FreeDelegates();
		m_instance->Release();
		m_instance=0;
	}
	if (m_strings) {
		for (int i=0;i<m_strings->Count;i++)
			Marshal::FreeBSTR(m_strings[i]);
		m_strings=nullptr;
	}
}

void UtilMPipeline::EnableImage(PXCMImage::ColorFormat format, pxcmU32 width, pxcmU32 height) {
	QueryInstance()->EnableImage((PXCImage::ColorFormat)format,(pxcU32)width,(pxcU32)height);
}

void UtilMPipeline::EnableAudio(PXCMAudio::AudioFormat format, pxcmU32 sampleRate, pxcmU32 nchannels) {
	QueryInstance()->EnableAudio((PXCAudio::AudioFormat)format,(pxcU32)sampleRate,(pxcU32)nchannels);
}

void UtilMPipeline::EnableGesture(pxcmUID iuid) {
	QueryInstance()->EnableGesture((pxcUID)iuid);
}

void UtilMPipeline::EnableGesture(String ^name) {
	IntPtr module_name=Marshal::StringToBSTR(name);
	QueryInstance()->EnableGesture((pxcCHAR*)module_name.ToPointer());
	Marshal::FreeBSTR(module_name);
}

void UtilMPipeline::EnableSegmentation(pxcmUID iuid){
	QueryInstance()->EnableSegmentation((pxcUID)iuid);
}

void UtilMPipeline::EnableSegmentation(String ^name){
	IntPtr module_name=Marshal::StringToBSTR(name);
	QueryInstance()->EnableSegmentation((pxcCHAR*)module_name.ToPointer());
	Marshal::FreeBSTR(module_name);
}

void UtilMPipeline::EnableFaceLocation(pxcmUID iuid) {
	QueryInstance()->EnableFaceLocation((pxcUID)iuid);
}

void UtilMPipeline::EnableFaceLocation(String ^name) {
	IntPtr module_name=Marshal::StringToBSTR(name);
	QueryInstance()->EnableFaceLocation((pxcCHAR*)module_name.ToPointer());
	Marshal::FreeBSTR(module_name);
}

void UtilMPipeline::EnableFaceLandmark(pxcmUID iuid) {
	QueryInstance()->EnableFaceLandmark((pxcUID)iuid);
}

void UtilMPipeline::EnableFaceLandmark(String ^name) {
	IntPtr module_name=Marshal::StringToBSTR(name);
	QueryInstance()->EnableFaceLandmark((pxcCHAR*)module_name.ToPointer());
	Marshal::FreeBSTR(module_name);
}


PXCMSession^ UtilMPipeline::QuerySession(void) {
	PXCSession *session=QueryInstance()->QuerySession();
	return session?gcnew PXCMSession(session,false):nullptr;
}

UtilMCapture^ UtilMPipeline::QueryCapture(void)	{
	UtilCapture *capture=QueryInstance()->QueryCapture();
	return capture?gcnew UtilMCapture(capture,false):nullptr;
}

PXCMGesture^ UtilMPipeline::QueryGesture(void)	{
	PXCGesture *gesture=QueryInstance()->QueryGesture();
	return gesture?gcnew PXCMGesture(gesture,false):nullptr;
}

PXCMSegmentation^ UtilMPipeline::QuerySegmentation(void) {
	PXCSegmentation *segmentor=QueryInstance()->QuerySegmentation();
	return segmentor?gcnew PXCMSegmentation(segmentor,false):nullptr;
}

PXCMImage^ UtilMPipeline::QuerySegmentationImage(void) {
	PXCImage *segImage = QueryInstance()->QuerySegmentationImage(); 
	return segImage?gcnew PXCMImage(segImage, false):nullptr; 
}

PXCMImage^ UtilMPipeline::QuerySegmentationBlendedImage(void) {
	PXCImage *blendedImage = QueryInstance()->QuerySegmentationBlendedImage(); 
	return blendedImage?gcnew PXCMImage(blendedImage, false):nullptr; 
}

void UtilMPipeline::SetSegmentationBlendMode(PXCMSegmentation::BlendMode mode)
{ 
	QueryInstance()->SetSegmentationBlendMode((PXCSegmentation::BlendMode) mode);
	return;
}

pxcmStatus UtilMPipeline::SetSegmentationBGImage(PXCMImage ^bgImage)
{
    pxcStatus sts = QueryInstance()->SetSegmentationBGImage(bgImage->QueryInstance());
	return (pxcmStatus) sts;
}

PXCMFaceAnalysis^ UtilMPipeline::QueryFace(void) {
	PXCFaceAnalysis *face=QueryInstance()->QueryFace();
	return face?gcnew PXCMFaceAnalysis(face,false):nullptr;
}

bool UtilMPipeline::QueryImageSize(PXCMImage::ImageType type, [Out] pxcmU32 %width, [Out] pxcU32 %height) {
	pxcU32 width2, height2;
	if (!QueryInstance()->QueryImageSize((PXCImage::ImageType)type,width2,height2)) return false;
	width=(pxcmU32)width2; height=(pxcmU32)height2;
	return true;
}

PXCMImage^ UtilMPipeline::QueryImage(PXCMImage::ImageType type) {
	PXCImage *image=QueryInstance()->QueryImage((PXCImage::ImageType)type);
	return image?gcnew PXCMImage(image,false):nullptr;
}

PXCMAudio^ UtilMPipeline::QueryAudio(void) {
	PXCAudio *audio=QueryInstance()->QueryAudio();
	return audio?gcnew PXCMAudio(audio,false):nullptr;
}

bool UtilMPipeline::IsDisconnected(void) {
	return QueryInstance()->IsDisconnected();
}

bool UtilMPipeline::IsAudioFrame(void) {
	return QueryInstance()->IsAudioFrame();
}

bool UtilMPipeline::IsImageFrame(void) {
	return QueryInstance()->IsImageFrame();
}

bool UtilMPipeline::Init(void) {
	return QueryInstance()->Init();
}

bool UtilMPipeline::AcquireFrame(bool wait) {
	return QueryInstance()->AcquireFrame(wait);
}

bool UtilMPipeline::ReleaseFrame(void) {
	return QueryInstance()->ReleaseFrame();
}

void UtilMPipeline::Close(void) {
	return QueryInstance()->Close();
}

bool UtilMPipeline::LoopFrames(void) {
	return QueryInstance()->LoopFrames();
}

bool UtilMPipeline::OnDisconnect(void) {
	System::Threading::Thread::Sleep(10); 
	return true;
}

void UtilMPipeline::OnImageX(IntPtr image) {
	PXCImage *uimage=(PXCImage*)image.ToPointer();
	PXCMImage ^mimage=gcnew PXCMImage(uimage,false);
	OnImage(mimage);
}

void UtilMPipeline::OnAudioX(IntPtr audio) {
	PXCAudio *uaudio=(PXCAudio*)audio.ToPointer();
	PXCMAudio ^maudio=gcnew PXCMAudio(uaudio,false);
	OnAudio(maudio);
}

void UtilMPipeline::EnableVoiceRecognition(pxcmUID iuid) {
	QueryInstance()->EnableVoiceRecognition((pxcUID)iuid);
}

void UtilMPipeline::EnableVoiceRecognition(String ^name) {
	IntPtr module_name=Marshal::StringToBSTR(name);
	QueryInstance()->EnableVoiceRecognition((pxcCHAR*)module_name.ToPointer());
	Marshal::FreeBSTR(module_name);
}

bool UtilMPipeline::SetVoiceCommands(array<String^> ^cmds) {
    std::vector<std::wstring> cmds2;
    for (int i=0;i<cmds->Length;i++) {
		IntPtr cmd=Marshal::StringToBSTR(cmds[i]);
		cmds2.push_back(std::wstring((pxcCHAR*)cmd.ToPointer()));
    	Marshal::FreeBSTR(cmd);
    }
    return (bool)QueryInstance()->SetVoiceCommands(cmds2);
}

bool UtilMPipeline::SetVoiceDictation(void) {
    return (bool)QueryInstance()->SetVoiceDictation();
}

PXCMVoiceRecognition^ UtilMPipeline::QueryVoiceRecognition(void) {
	PXCVoiceRecognition *vr=QueryInstance()->QueryVoiceRecognition();
	return vr?gcnew PXCMVoiceRecognition(vr,false):nullptr;
}

void UtilMPipeline::PauseVoiceRecognition(bool pause) {
    QueryInstance()->PauseVoiceRecognition((pxcBool)pause);
}

void UtilMPipeline::PauseGesture(bool pause) {
    QueryInstance()->PauseGesture((pxcBool)pause);
}

void UtilMPipeline::PauseSegmentation(bool pause) {
    QueryInstance()->PauseSegmentation((pxcBool)pause);
}

void UtilMPipeline::PauseFaceLocation(bool pause) {
    QueryInstance()->PauseFaceLocation((pxcBool)pause);
}

void UtilMPipeline::PauseFaceLandmark(bool pause) {
    QueryInstance()->PauseFaceLandmark((pxcBool)pause);
}


