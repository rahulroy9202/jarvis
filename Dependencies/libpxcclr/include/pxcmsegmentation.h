/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmsession.h"
#include "pxcmcapture.h"
#include "pxcsegmentation.h"

public ref class PXCMSegmentation:public PXCMBase {
public:
    PXCM_CUID_OVERWRITE(PXCSegmentation::CUID);

	enum class FaceMode: pxcmEnum {
        FACE_ANY=0,               
        FACE_ALG_DEFAULT,  
    };

	enum class BlendMode: pxcmEnum {
		BLEND_ANY,
		BLEND_BG_WHITE,           
		BLEND_BG_BLUE,           
		BLEND_BG_IMAGE,         
		BLEND_ALPHA_CHANNEL,    
	};

	//[StructLayout(LayoutKind::Explicit)]
    value struct Segment {
        pxcmU64  timeStamp;           
		pxcmU32  user;
		PXCMArray<pxcmU32,sizeof(pxcmU32),8> reserved;
    };

    value struct ProfileInfo {
        PXCMCapture::VideoStream::DataDesc inputs;		
		FaceMode		faceMode;				
		
		pxcmU32			maxDepthThreshold;					
		pxcmU32			minDepthThreshold;				
		pxcmF32			filterFactor;;			  
		pxcmU32			contourSmoothness;			
		pxcmU32			minPerimeter;
		BlendMode		blendMode;  
		PXCMArray<pxcmU32,sizeof(pxcmU32),32> reserved;							 
    };

    virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
    virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
    virtual pxcmStatus SetProfile(ProfileInfo %pinfo);
	virtual pxcmStatus SetROIRegions(pxcmU32 nregions, PXCRectU32 %regions);
    virtual pxcmStatus QuerySegmentData(pxcmU32 idx, [Out] Segment %data);
 
	virtual pxcmStatus SegmentImageAsync(array<PXCMImage^> ^in_images, [Out] PXCMImage ^%seg_image, [Out] PXCMScheduler::SyncPoint ^%sp);
	virtual pxcmStatus BlendImageAsync(PXCMImage ^color_image, PXCMImage ^seg_image, PXCMImage ^bg_image, [Out] PXCMImage ^%blended_image, [Out] PXCMScheduler::SyncPoint ^%sp);

	~PXCMSegmentation(void) { this->!PXCMSegmentation(); }
    !PXCMSegmentation(void);

internal:

    PXCMSegmentation(PXCBase *instance,bool b_delete);
    PXCSegmentation *QueryInstance(void) { return (PXCSegmentation*) m_instance; }
};