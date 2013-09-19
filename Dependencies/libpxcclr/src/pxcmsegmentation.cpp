/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmsegmentation.h"

#pragma managed

pxcmStatus PXCMSegmentation::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCSegmentation::ProfileInfo*)pp);
}

pxcmStatus PXCMSegmentation::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile(PXCMSegmentation::WORKING_PROFILE,(PXCSegmentation::ProfileInfo*)pp);
}

pxcmStatus PXCMSegmentation::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCSegmentation::ProfileInfo*)pp);
}

pxcmStatus PXCMSegmentation::SetROIRegions(pxcmU32 nregions, PXCRectU32 %regions)
{
	return ((pxcmStatus) (PXC_STATUS_FEATURE_UNSUPPORTED)); 
}

pxcmStatus PXCMSegmentation::QuerySegmentData(pxcmU32 idx, [Out] PXCMSegmentation::Segment %data)
{
	pin_ptr<PXCMSegmentation::Segment> pp2(&data);
    return (pxcmStatus)QueryInstance()->QuerySegmentData((pxcU32)idx,(PXCSegmentation::Segment*)pp2);
}

pxcmStatus PXCMSegmentation::SegmentImageAsync(array<PXCMImage^> ^in_images, [Out] PXCMImage ^%seg_image, [Out] PXCMScheduler::SyncPoint ^%sp)
{
	PXCScheduler::SyncPoint *sp2=0;
	PXCImage *seg_image2 = 0; 
    pxcStatus sts;

    sp=nullptr;
    if (in_images) {
        PXCCapture::VideoStream::Images images2;
        for (int i=0;i<PXCCapture::VideoStream::STREAM_LIMIT;i++)
            images2[i]=(i<in_images->Length)?(in_images[i]?in_images[i]->QueryInstance():0):0;
        sts = QueryInstance()->SegmentImageAsync(images2, &seg_image2, &sp2);
    } else {
        sts=PXC_STATUS_PARAM_UNSUPPORTED;
    }

    if (sts>=PXC_STATUS_NO_ERROR && sp2) {
		seg_image = gcnew PXCMImage(seg_image2, true); 
		sp = gcnew PXCMScheduler::SyncPoint(sp2,true);
	}
    return (pxcmStatus)sts;
}

pxcmStatus PXCMSegmentation::BlendImageAsync(PXCMImage ^color_image, PXCMImage ^seg_image, PXCMImage ^bg_image, [Out] PXCMImage ^%blended_image, [Out] PXCMScheduler::SyncPoint ^%sp)
{
	sp=nullptr, blended_image=nullptr; 

	if (!color_image || !seg_image)
		return pxcmStatus::PXCM_STATUS_PARAM_UNSUPPORTED; 

	PXCScheduler::SyncPoint *sp2=0;
	PXCImage *blended_image2=0;

	pxcStatus sts = QueryInstance()->BlendImageAsync(color_image->QueryInstance(), seg_image->QueryInstance(),
		(bg_image)?bg_image->QueryInstance():0, &blended_image2, &sp2); 
	 
	if (sts>=PXC_STATUS_NO_ERROR && sp2) {
		blended_image = gcnew PXCMImage(blended_image2, true);
		sp = gcnew PXCMScheduler::SyncPoint(sp2,true);
	}
    return (pxcmStatus)sts;
}

PXCMSegmentation::PXCMSegmentation(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {
}

PXCMSegmentation::!PXCMSegmentation(void) {
}