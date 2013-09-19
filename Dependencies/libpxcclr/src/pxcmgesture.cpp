/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmgesture.h"

#pragma unmanaged

typedef void (PXCAPI *OnGestureProc)(PXCGesture::Gesture *data);
typedef void (PXCAPI *OnAlertProc)(PXCGesture::Alert *alert);

class GestureHandler: public PXCGesture::Gesture::Handler {
public:
    GestureHandler(OnGestureProc instance) { m_instance=instance; }
    virtual void PXCAPI OnGesture(PXCGesture::Gesture *data) {
        m_instance(data);
    }
protected:
    OnGestureProc m_instance;
};

class AlertHandler: public PXCGesture::Alert::Handler {
public:
    AlertHandler(OnAlertProc instance) { m_instance=instance; }
    virtual void PXCAPI OnAlert(PXCGesture::Alert *alert) {
        m_instance(alert);
    }
protected:
    OnAlertProc m_instance;
};

#pragma managed

pxcmStatus PXCMGesture::QueryUser(pxcmU32 idx, [Out] pxcmUID %user) {
    pxcUID user2;
    pxcStatus sts=QueryInstance()->QueryUser((pxcU32)idx,&user2);
    user=(pxcmUID)user2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMGesture::QueryGestureData(pxcmUID user, GeoNode::Label body, pxcmU32 idx, [Out] Gesture %data) {
    pin_ptr<Gesture> pp2(&data);
    return (pxcmStatus)QueryInstance()->QueryGestureData((pxcUID)user,(PXCGesture::GeoNode::Label)body,(pxcU32)idx,(PXCGesture::Gesture*)pp2);
}

pxcmStatus PXCMGesture::QueryNodeData(pxcmUID user, GeoNode::Label body, [Out] GeoNode %data) {
    pin_ptr<GeoNode> pp2(&data);
    return (pxcmStatus)QueryInstance()->QueryNodeData((pxcUID)user,(PXCGesture::GeoNode::Label)body,(PXCGesture::GeoNode*)pp2);
}

pxcmStatus PXCMGesture::QueryNodeData(pxcmUID user, GeoNode::Label body, array<GeoNode> ^data) {
	pxcmStatus sts=pxcmStatus::PXCM_STATUS_ITEM_UNAVAILABLE;
	for (int i=0;i<data->Length;i++,body++) {
		if (QueryNodeData(user,body,data[i])<pxcmStatus::PXCM_STATUS_NO_ERROR)
			data[i].body=GeoNode::Label::LABEL_ANY;
		else
			sts=pxcmStatus::PXCM_STATUS_NO_ERROR;
	}
	return sts;
}

pxcmStatus PXCMGesture::QueryBlobData(Blob::Label label, pxcmU32 idx, [Out] Blob %data) {
    pin_ptr<Blob> pp2(&data);
    return (pxcmStatus)QueryInstance()->QueryBlobData((PXCGesture::Blob::Label)label,(pxcU32)idx,(PXCGesture::Blob*)pp2);
}

pxcmStatus PXCMGesture::QueryBlobImage(Blob::Label label, pxcmU32 idx, [Out] PXCMImage ^%image) {
    PXCImage *image2=0;
    pxcStatus sts=QueryInstance()->QueryBlobImage((PXCGesture::Blob::Label)label,(pxcU32)idx,&image2);
    if (sts>=PXC_STATUS_NO_ERROR) image=gcnew PXCMImage(image2,true);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMGesture::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCGesture::ProfileInfo*)pp);
}

pxcmStatus PXCMGesture::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile(PXCGesture::WORKING_PROFILE,(PXCGesture::ProfileInfo*)pp);
}

pxcmStatus PXCMGesture::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCGesture::ProfileInfo*)pp);
}

pxcmStatus PXCMGesture::ProcessImageAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp) {
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
    if (sts>=PXC_STATUS_NO_ERROR && sp2) sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMGesture::SubscribeGesture(pxcmU32 threshold, Gesture::OnGesture ^handler) {
    DeleteGestureHandler();
	if (handler==nullptr) return (pxcmStatus)QueryInstance()->SubscribeGesture(0,0);
    m_gesture_gch=GCHandle::Alloc(handler);
    OnGestureProc cb=static_cast<OnGestureProc>(Marshal::GetFunctionPointerForDelegate(handler).ToPointer());
    m_gesture_handler_unmanaged=new GestureHandler(cb);
    return (pxcmStatus)QueryInstance()->SubscribeGesture((pxcU32)threshold,m_gesture_handler_unmanaged);
}

pxcmStatus PXCMGesture::SubscribeAlert(Alert::OnAlert ^handler) {
    DeleteAlertHandler();
	if (handler==nullptr) return (pxcmStatus)QueryInstance()->SubscribeAlert(0);
    m_alert_gch=GCHandle::Alloc(handler);
    OnAlertProc cb=static_cast<OnAlertProc>(Marshal::GetFunctionPointerForDelegate(handler).ToPointer());
    m_alert_handler_unmanaged=new AlertHandler(cb);
    return (pxcmStatus)QueryInstance()->SubscribeAlert(m_alert_handler_unmanaged);
}

PXCMGesture::PXCMGesture(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {
    m_gesture_handler_unmanaged=0;
    m_alert_handler_unmanaged=0;
}

void PXCMGesture::DeleteGestureHandler(void) {
    if (m_gesture_gch.IsAllocated) m_gesture_gch.Free();
    if (m_gesture_handler_unmanaged) { delete m_gesture_handler_unmanaged; m_gesture_handler_unmanaged=0; }
}

void PXCMGesture::DeleteAlertHandler(void) {
    if (m_alert_gch.IsAllocated) m_alert_gch.Free();
    if (m_alert_handler_unmanaged) { delete m_alert_handler_unmanaged; m_alert_handler_unmanaged=0; }
}

PXCMGesture::!PXCMGesture(void) {
    DeleteGestureHandler();
    DeleteAlertHandler();
}
