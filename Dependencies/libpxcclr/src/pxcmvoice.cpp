/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmvoice.h"

#pragma unmanaged

typedef void (PXCAPI *OnRecognizedProc)(PXCVoiceRecognition::Recognition *data);

class CommandHandler: public PXCVoiceRecognition::Recognition::Handler {
public:
    CommandHandler(OnRecognizedProc r) { m_recognized=r; }
    virtual void PXCAPI OnRecognized(PXCVoiceRecognition::Recognition *data) {
        if (m_recognized) m_recognized(data);
    }
protected:
    OnRecognizedProc    m_recognized;
};

typedef void (PXCAPI *OnAlertProc)(PXCVoiceRecognition::Alert *data);

class AlertHandler: public PXCVoiceRecognition::Alert::Handler {
public:
    AlertHandler(OnAlertProc r) { m_alert=r; }
    virtual void PXCAPI OnAlert(PXCVoiceRecognition::Alert *data) {
        if (m_alert) m_alert(data);
    }
protected:
    OnAlertProc    m_alert;
};

#pragma managed

pxcmStatus PXCMVoiceRecognition::CreateGrammar([Out] pxcmUID %gid) {
    pxcUID gid2=0;
    pxcStatus sts=QueryInstance()->CreateGrammar(&gid2);
    gid=(pxcmUID)gid2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMVoiceRecognition::DeleteGrammar(pxcmUID gid) {
    return (pxcmStatus)QueryInstance()->DeleteGrammar((pxcUID)gid);
}

pxcmStatus PXCMVoiceRecognition::AddGrammar(pxcmUID gid, pxcmEnum label, String ^command) {
    IntPtr buffer=Marshal::StringToBSTR(command);
    pxcStatus sts=QueryInstance()->AddGrammar((pxcUID)gid, (pxcEnum)label,(pxcCHAR*)buffer.ToPointer());
    Marshal::FreeBSTR(buffer);
    return (pxcmStatus)sts;
}

pxcmStatus PXCMVoiceRecognition::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCVoiceRecognition::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceRecognition::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCVoiceRecognition::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceRecognition::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCVoiceRecognition::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceRecognition::ProcessAudioEOS(void) {
	return (pxcmStatus)QueryInstance()->ProcessAudioAsync(0,0);
}

pxcmStatus PXCMVoiceRecognition::ProcessAudioAsync(PXCMAudio ^audio, [Out] PXCMScheduler::SyncPoint ^%sp) {
    PXCScheduler::SyncPoint *sp2=0;
    pxcStatus sts;

    sp=nullptr;
    if (audio) {
        sts=QueryInstance()->ProcessAudioAsync(audio->QueryInstance(),&sp2);
    } else {
        sts=QueryInstance()->ProcessAudioAsync(0,&sp2);
    }
    if (sts>=PXC_STATUS_NO_ERROR && sp2) sp=gcnew PXCMScheduler::SyncPoint(sp2,true);

    return (pxcmStatus)sts;
}

pxcmStatus PXCMVoiceRecognition::SetGrammar(pxcmUID gid) {
    return (pxcmStatus)QueryInstance()->SetGrammar((pxcUID)gid);
}

pxcmStatus PXCMVoiceRecognition::SetDictation() {
    return (pxcmStatus)QueryInstance()->SetGrammar(0);
}

pxcmStatus PXCMVoiceRecognition::SubscribeRecognition(pxcmU32 threshold, Recognition::OnRecognized ^handler) {
    DeleteCommandHandler();
    OnRecognizedProc cbr=0;
    if (handler) {
        m_recognized_gch=GCHandle::Alloc(handler);
        cbr=static_cast<OnRecognizedProc>(Marshal::GetFunctionPointerForDelegate(handler).ToPointer());
        m_command_handler_unmanaged=new CommandHandler(cbr);
    }
    return (pxcmStatus)QueryInstance()->SubscribeRecognition((pxcU32)threshold,m_command_handler_unmanaged);
}

pxcmStatus PXCMVoiceRecognition::SubscribeAlert(Alert::OnAlert ^handler) {
    DeleteAlertHandler();
    OnAlertProc cbr=0;
    if (handler) {
        m_alert_gch=GCHandle::Alloc(handler);
        cbr=static_cast<OnAlertProc>(Marshal::GetFunctionPointerForDelegate(handler).ToPointer());
        m_alert_handler_unmanaged=new AlertHandler(cbr);
    }
    return (pxcmStatus)QueryInstance()->SubscribeAlert(m_alert_handler_unmanaged);
}

PXCMVoiceRecognition::PXCMVoiceRecognition(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {
    m_command_handler_unmanaged=0;
	m_alert_handler_unmanaged=0;
}

void PXCMVoiceRecognition::DeleteCommandHandler(void) {
    if (m_recognized_gch.IsAllocated) m_recognized_gch.Free();
    if (m_command_handler_unmanaged) { delete m_command_handler_unmanaged; m_command_handler_unmanaged=0; }
}

void PXCMVoiceRecognition::DeleteAlertHandler(void) {
    if (m_alert_gch.IsAllocated) m_alert_gch.Free();
    if (m_alert_handler_unmanaged) { delete m_alert_handler_unmanaged; m_alert_handler_unmanaged=0; }
}

PXCMVoiceRecognition::!PXCMVoiceRecognition(void) {
    DeleteCommandHandler();
	DeleteAlertHandler();
}

pxcmStatus PXCMVoiceSynthesis::QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((pxcU32)pidx,(PXCVoiceSynthesis::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceSynthesis::QueryProfile([Out] ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->QueryProfile((PXCVoiceSynthesis::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceSynthesis::SetProfile(ProfileInfo %pinfo) {
    pin_ptr<ProfileInfo> pp(&pinfo);
    return (pxcmStatus)QueryInstance()->SetProfile((PXCVoiceSynthesis::ProfileInfo*)pp);
}

pxcmStatus PXCMVoiceSynthesis::QueueSentence(String ^sentence, [Out] pxcmUID %id) {
    IntPtr buffer=Marshal::StringToBSTR(sentence);
    pxcUID id2;
    pxcStatus sts=QueryInstance()->QueueSentence((pxcCHAR*)buffer.ToPointer(),sentence->Length,&id2);
    Marshal::FreeBSTR(buffer);
    id=(pxcUID)id2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMVoiceSynthesis::ProcessAudioAsync(pxcmUID id, [Out] PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp) {
    sp=nullptr; audio=nullptr;

    PXCAudio *audio2=0;
    PXCScheduler::SyncPoint *sp2=0;
    pxcStatus sts=QueryInstance()->ProcessAudioAsync((pxcUID)id,&audio2,&sp2);
    if (sts>=PXC_STATUS_NO_ERROR) {
        if (audio2) audio=gcnew PXCMAudio(audio2,true);
        if (sp2) sp=gcnew PXCMScheduler::SyncPoint(sp2,true);
    }
    return (pxcmStatus)sts;
}

static void exercise(void) {
	PXCMVoiceRecognition::ProfileInfo pinfo;
	pinfo.speaker.get();
	pinfo.speaker.set("abc");
}
