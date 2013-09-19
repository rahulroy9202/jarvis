/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmface.h"

pxcmStatus PXCMFaceAnalysis::Detection::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCFaceAnalysis::Detection::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Detection::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCFaceAnalysis::Detection::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Detection::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCFaceAnalysis::Detection::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Detection::QueryData(pxcmUID fid, [Out] Data %data) {
    pin_ptr<Data> pp(&data);
    return (pxcmStatus)QueryInstance()->QueryData((pxcUID)fid, (PXCFaceAnalysis::Detection::Data*)pp);
}

pxcmStatus PXCMFaceAnalysis::Landmark::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCFaceAnalysis::Landmark::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Landmark::QueryProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCFaceAnalysis::Landmark::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Landmark::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCFaceAnalysis::Landmark::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Landmark::QueryLandmarkData(pxcmUID fid, Label landmark, pxcmU32 lidx, [Out] LandmarkData %data) {
    pin_ptr<LandmarkData> pp(&data);
    return (pxcmStatus)QueryInstance()->QueryLandmarkData((pxcUID)fid,(PXCFaceAnalysis::Landmark::Label)landmark,(pxcU32)lidx,(PXCFaceAnalysis::Landmark::LandmarkData*)pp);
}

pxcmStatus PXCMFaceAnalysis::Landmark::QueryLandmarkData(pxcmUID fid, Label landmark, array<LandmarkData> ^data) {
	pxcmStatus sts=pxcmStatus::PXCM_STATUS_ITEM_UNAVAILABLE;
	for (int i=0;i<data->Length;i++) {
		if (QueryLandmarkData(fid,landmark,i,data[i])>=pxcmStatus::PXCM_STATUS_NO_ERROR)
			sts=pxcmStatus::PXCM_STATUS_NO_ERROR;
		else
			data[i].label=(Label)0;
	}
	return sts;
}

pxcmStatus PXCMFaceAnalysis::Landmark::QueryPoseData(pxcmUID fid, [Out] PoseData %pose) {
    pin_ptr<PoseData> pp(&pose);
    return (pxcmStatus)QueryInstance()->QueryPoseData((pxcUID)fid,(PXCFaceAnalysis::Landmark::PoseData*)pp);
}

pxcmStatus PXCMFaceAnalysis::Recognition::Model::Serialize(array<pxcmBYTE> ^buffer) {
	pin_ptr<pxcmBYTE> pp(&buffer[0]);
	return (pxcmStatus)QueryInstance()->Serialize((pxcBYTE*)pp);
}

pxcmStatus PXCMFaceAnalysis::Recognition::Model::Compare(array<Model^> ^models, array<pxcF32> ^scores, [Out] pxcmU32 %index) {
	if (models->Length!=scores->Length) return pxcmStatus::PXCM_STATUS_PARAM_UNSUPPORTED;
	PXCFaceAnalysis::Recognition::Model **models2=(PXCFaceAnalysis::Recognition::Model **)new PXCFaceAnalysis::Recognition::Model*[models->Length];
	pin_ptr<pxcF32> pp(&scores[0]);
	int nmodels;
	for (nmodels=0;nmodels<models->Length;nmodels++) {
		if (!models[nmodels]) break;
		models2[nmodels]=models[nmodels]->QueryInstance();
	}
	pxcU32 index2=0;
	pxcStatus sts=(nmodels?QueryInstance()->Compare(models2,nmodels,(pxcF32*)pp,&index2):PXC_STATUS_NO_ERROR);
	index=index2;
	delete [] models2;
	return (pxcmStatus)sts;
}

pxcmStatus PXCMFaceAnalysis::Recognition::Model::Compare(array<Model^> ^models, [Out] pxcmU32 %index) {
	PXCFaceAnalysis::Recognition::Model **models2=(PXCFaceAnalysis::Recognition::Model **)new PXCFaceAnalysis::Recognition::Model*[models->Length];
	int nmodels;
	for (nmodels=0;nmodels<models->Length;nmodels++) {
		if (!models[nmodels]) break;
		models2[nmodels]=models[nmodels]->QueryInstance();
	}
	pxcU32 index2=0;
	pxcStatus sts=(nmodels?QueryInstance()->Compare(models2,nmodels,&index2):PXC_STATUS_NO_ERROR);
	index=index2;
	delete [] models2;
	return (pxcmStatus)sts;
}

pxcmStatus PXCMFaceAnalysis::Recognition::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCFaceAnalysis::Recognition::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Recognition::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCFaceAnalysis::Recognition::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Recognition::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCFaceAnalysis::Recognition::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::Recognition::CreateModel(pxcmUID fid, [Out] Model ^%model) {
	PXCFaceAnalysis::Recognition::Model *model2=0;
	pxcStatus sts=QueryInstance()->CreateModel((pxcUID)fid,&model2);
	model=nullptr;
	if (sts>=PXC_STATUS_NO_ERROR) model=gcnew Model(model2,true);
	return (pxcmStatus)sts;
}

pxcmStatus PXCMFaceAnalysis::Recognition::DeserializeModel(array<pxcmBYTE> ^buffer, [Out] Model ^%model) {
	pin_ptr<pxcmBYTE> pp(&buffer[0]);
	PXCFaceAnalysis::Recognition::Model *model2=0;
	pxcStatus sts=QueryInstance()->DeserializeModel((pxcBYTE*)pp,&model2);
	model=(sts>=PXC_STATUS_NO_ERROR)?gcnew Model(model2,true):nullptr;
	return (pxcmStatus)sts;
}

pxcmStatus PXCMFaceAnalysis::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCFaceAnalysis::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::QueryProfile([Out] ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCFaceAnalysis::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::SetProfile(ProfileInfo %profile) {
    pin_ptr<ProfileInfo> pp(&profile);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCFaceAnalysis::ProfileInfo*)pp);
}

pxcmStatus PXCMFaceAnalysis::QueryFace(pxcmU32 fidx, [Out] pxcmUID %fid, [Out] pxcmU64 %timeStamp) {
	pxcUID fid2;
	pxcU64 timeStamp2;
	pxcStatus sts=QueryInstance()->QueryFace((pxcU32)fidx,&fid2,&timeStamp2);
	fid=fid2;
	timeStamp=timeStamp2;
	return (pxcmStatus)sts;
}

pxcmStatus PXCMFaceAnalysis::ProcessImageAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCScheduler::SyncPoint *sp2=0;
    pxcStatus sts;
    sp=nullptr;

    if (images) {
		PXCCapture::VideoStream::Images images2;
        for (int i=0;i<PXCCapture::VideoStream::STREAM_LIMIT;i++)
            images2[i]=(i<images->Length)?(images[i]?images[i]->QueryInstance():0):0;
        sts=QueryInstance()->ProcessImageAsync(images2,&sp2);
    } else {
        sts=QueryInstance()->ProcessImageAsync(0,&sp2);
    }

    if (sts>=PXC_STATUS_NO_ERROR) sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    return (pxcmStatus)sts;
}

