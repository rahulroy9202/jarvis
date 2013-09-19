/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "utilm_capture_file.h"
#include "pxcmgesture.h"
#include "pxcmsegmentation.h"
#include "pxcmface.h"
#include "pxcmvoice.h"
#include "util_pipeline.h"

public ref class UtilMPipeline {
public:

	virtual bool  Init(void);
	virtual bool  AcquireFrame(bool wait);
	virtual bool  ReleaseFrame(void);
	virtual void  Close(void);
	virtual bool  LoopFrames(void);
    virtual bool  IsAudioFrame(void);
    virtual bool  IsImageFrame(void);
	virtual bool  IsDisconnected(void);
	virtual void  OnReconnect(void) {}
	virtual bool  OnDisconnect(void);
	virtual bool  OnNewFrame(void) { return true; }
	virtual PXCMSession^  QuerySession(void);
	virtual UtilMCapture^ QueryCapture(void);

	virtual void  OnImage(PXCMImage ^image) {}
	virtual void  OnAudio(PXCMAudio ^audio) {}
	virtual void  EnableImage(PXCMImage::ColorFormat format, pxcmU32 width, pxcmU32 height);
	virtual void  EnableImage(PXCMImage::ColorFormat format) { EnableImage(format,0,0); }
	virtual void  EnableAudio(PXCMAudio::AudioFormat format, pxcmU32 sampleRate, pxcmU32 nchannels);
	virtual void  EnableAudio(PXCMAudio::AudioFormat format) { EnableAudio(format,0,0); }
	virtual bool  QueryImageSize(PXCMImage::ImageType type, [Out] pxcmU32 %width, [Out] pxcU32 %height);
	virtual PXCMImage^ QueryImage(PXCMImage::ImageType type);
	virtual PXCMAudio^ QueryAudio(void);

	virtual void  EnableFaceLocation(pxcmUID iuid);
	virtual void  EnableFaceLocation(void) { EnableFaceLocation(0); }
	virtual void  EnableFaceLocation(String ^name);
    virtual void  EnableFaceLandmark(pxcmUID iuid);
    virtual void  EnableFaceLandmark(void) { EnableFaceLandmark(0); }
    virtual void  EnableFaceLandmark(String ^name);

	virtual void  OnFaceSetup(PXCMFaceAnalysis::ProfileInfo %finfo) {}
	virtual void  OnFaceDetectionSetup(PXCMFaceAnalysis::Detection::ProfileInfo %finfo) {}
	virtual void  OnFaceLandmarkSetup(PXCMFaceAnalysis::Landmark::ProfileInfo %finfo) {}
	virtual PXCMFaceAnalysis^ QueryFace(void);

	virtual void  EnableGesture(pxcmUID iuid);
	virtual void  EnableGesture(void) { EnableGesture(0); }
	virtual void  EnableGesture(String ^name);
	virtual void  OnGestureSetup(PXCMGesture::ProfileInfo %pinfo) {}
	virtual void  OnGesture(PXCMGesture::Gesture %gesture) {}
	virtual void  OnAlert(PXCMGesture::Alert %alert) {}
	virtual PXCMGesture^ QueryGesture(void);

	virtual void  EnableSegmentation(pxcmUID iuid);
	virtual void  EnableSegmentation(void) { EnableSegmentation(0); }
	virtual void  EnableSegmentation(String ^name); 
	virtual void  OnSegmentationSetup(PXCMSegmentation::ProfileInfo %pinfo) {} 
	virtual PXCMSegmentation^ QuerySegmentation(void); 
	virtual void  SetSegmentationBlendMode(PXCMSegmentation::BlendMode mode); 
	virtual pxcmStatus SetSegmentationBGImage (PXCMImage ^bgImage); 
	virtual PXCMImage^ QuerySegmentationImage(void); 
	virtual PXCMImage^ QuerySegmentationBlendedImage(void);

	virtual void  EnableVoiceRecognition(pxcmUID iuid);
	virtual void  EnableVoiceRecognition() { EnableVoiceRecognition(0); }
	virtual void  EnableVoiceRecognition(String ^name);

    virtual bool  SetVoiceCommands(array<String^> ^cmds);
    virtual bool  SetVoiceDictation(void);

	virtual void  OnVoiceRecognitionSetup(PXCMVoiceRecognition::ProfileInfo %finfo) {}
	virtual void  OnRecognized(PXCMVoiceRecognition::Recognition %data) {}
	virtual void  OnAlert(PXCMVoiceRecognition::Alert %data) {}
	virtual PXCMVoiceRecognition^ QueryVoiceRecognition(void);

    virtual void  PauseVoiceRecognition(bool pause);
    virtual void  PauseGesture(bool pause);
    virtual void  PauseFaceLocation(bool pause);
    virtual void  PauseFaceLandmark(bool pause);
	virtual void  PauseSegmentation (bool pause); 

    UtilMPipeline(PXCMSession ^session) { Setup(session,nullptr,false); }
    UtilMPipeline(void) { Setup(nullptr,nullptr,false); }
    UtilMPipeline(PXCMSession ^session, String ^filename, bool recording) { Setup(session,filename,recording); }
    UtilMPipeline(String ^filename, bool recording) { Setup(nullptr,filename,recording); }
    UtilMPipeline(PXCMSession ^session, String ^filename) { Setup(session,filename,false); }
    UtilMPipeline(String ^filename) { Setup(nullptr,filename,false); }

	virtual ~UtilMPipeline(void) { this->!UtilMPipeline(); GC::SuppressFinalize(this); }
	!UtilMPipeline(void);

internal:

    class UtilPipelineX *QueryInstance(void) { return (UtilPipelineX*)m_instance; }

	class UtilPipelineX *m_instance;
	System::Collections::Generic::List<IntPtr> ^m_strings;

#define DEFINEDELEGATE(CALLBACK,RET,ARGS) \
delegate RET CALLBACK##Delegate ARGS;	\
GCHandle m_##CALLBACK##_gch

	DEFINEDELEGATE(OnGestureSetup,void,(PXCMGesture::ProfileInfo %pinfo));
	DEFINEDELEGATE(OnSegmentationSetup,void,(PXCMSegmentation::ProfileInfo %pinfo));
	DEFINEDELEGATE(OnFaceSetup,void,(PXCMFaceAnalysis::ProfileInfo %finfo));
	DEFINEDELEGATE(OnFaceDetectionSetup,void,(PXCMFaceAnalysis::Detection::ProfileInfo %finfo));
	DEFINEDELEGATE(OnFaceLandmarkSetup,void,(PXCMFaceAnalysis::Landmark::ProfileInfo %finfo));
    DEFINEDELEGATE(OnGesture,void,(PXCMGesture::Gesture %gesture));
	DEFINEDELEGATE(OnAlertG,void,(PXCMGesture::Alert %alert));
	DEFINEDELEGATE(OnReconnect,void,(void));
	DEFINEDELEGATE(OnDisconnect,bool,(void));
	DEFINEDELEGATE(OnNewFrame,bool,(void));
	DEFINEDELEGATE(OnImageX,void,(IntPtr image));
	DEFINEDELEGATE(OnAudioX,void,(IntPtr audio));
	DEFINEDELEGATE(OnVoiceRecognitionSetup,void,(PXCMVoiceRecognition::ProfileInfo %finfo));
	DEFINEDELEGATE(OnRecognized,void,(PXCMVoiceRecognition::Recognition %data));
	DEFINEDELEGATE(OnAlertVR,void,(PXCMVoiceRecognition::Alert %data));
	
	void OnImageX(IntPtr image);
	void OnAudioX(IntPtr audio);
	void SetupDelegates();
	void FreeDelegates();
    void Setup(PXCMSession ^session, String ^filename, bool recording);
};
