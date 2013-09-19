/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmsession.h"
#include "pxcmcapture.h"
#include "pxcvoice.h"

public ref class PXCMVoiceRecognition:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCVoiceRecognition::CUID);

    [StructLayout(LayoutKind::Explicit,CharSet=CharSet::Unicode,Size=2112)]
    value struct Recognition {
        delegate void OnRecognized(Recognition %data);

        value struct NBest {
            pxcmEnum label;
            pxcmU32  confidence;
        };

        [FieldOffset(0)]    pxcmU64     timeStamp;
        [FieldOffset(8),MarshalAs(UnmanagedType::ByValArray,SizeConst=4)] array<NBest>^ nBest;
        [FieldOffset(40)]   PXCMArray<pxcmU32,sizeof(pxcmU32),5> reserved;
        [FieldOffset(60)]   pxcU32      duration;
        [FieldOffset(64),MarshalAs(UnmanagedType::ByValTStr, SizeConst=1024)] String ^dictation;

		property pxcmEnum label {
			pxcmEnum get() { return nBest[0].label; }
			void set(pxcmEnum value) { nBest[0].label=value; }
		}
		property pxcmU32 confidence {
			pxcmU32 get() { return nBest[0].confidence; }
			void set(pxcmU32 value) { nBest[0].confidence=value; }
		}
    };

	value struct Alert {
		delegate void OnAlert(Alert %data);

		enum class Label: pxcmEnum {
			LABEL_VOLUME_HIGH=0x0001,
			LABEL_VOLUME_LOW=0x0002,
            LABEL_SNR_LOW=0x00004,
            LABEL_SPEECH_UNRECOGNIZABLE=0x00008,
		};

		pxcmU64	timeStamp;
		Label	label;
		PXCMArray<pxcmU32,sizeof(pxcmU32),6> reserved;
	};

	[StructLayout(LayoutKind::Explicit)]
    value struct ProfileInfo {
        enum class Language: pxcmEnum {
            LANGUAGE_US_ENGLISH		= PXCM_UID('e','n','U','S'),
            LANGUAGE_GB_ENGLISH     = PXCM_UID('e','n','G','B'),
            LANGUAGE_DE_GERMAN      = PXCM_UID('d','e','D','E'),
            LANGUAGE_US_SPANISH     = PXCM_UID('e','s','U','S'),
            LANGUAGE_FR_FRENCH      = PXCM_UID('f','r','F','R'),
            LANGUAGE_IT_ITALIAN     = PXCM_UID('i','t','I','T'),
            LANGUAGE_JP_JAPANESE    = PXCM_UID('j','a','J','P'),
            LANGUAGE_CN_CHINESE     = PXCM_UID('z','h','C','N'),
            LANGUAGE_BR_PORTUGUESE  = PXCM_UID('p','t','B','R'),
        };

        [FieldOffset(0)]    PXCMCapture::AudioStream::DataDesc inputs;  // supported input format
		[FieldOffset(1088)] PXCMString<128> speaker;		// speaker name
        [FieldOffset(1344)] Language		language;		// supported language
		[FieldOffset(1348)] Alert::Label	alerts;			// interested alerts
		[FieldOffset(1352)] pxcmU32			endOfSentence;	// end of sentence in ms
        [FieldOffset(1356)] PXCMArray<pxcmU32,sizeof(pxcmU32),13> reserved;
    };

    pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
    pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
    pxcmStatus SetProfile(ProfileInfo %pinfo);

    pxcmStatus CreateGrammar([Out] pxcmUID %gid);
    pxcmStatus AddGrammar(pxcmUID gid, pxcmEnum label, String ^command);
    pxcmStatus SetGrammar(pxcmUID gid);
    pxcmStatus DeleteGrammar(pxcmUID gid);
    pxcmStatus SetDictation();

	[System::Obsolete("Use ProcessAudioEOS instead")]
	pxcmStatus ProcessAudioAsync(void) { return ProcessAudioEOS(); }
	pxcmStatus ProcessAudioEOS(void);
    pxcmStatus ProcessAudioAsync(PXCMAudio ^audio, [Out] PXCMScheduler::SyncPoint ^%sp);
    pxcmStatus SubscribeRecognition(pxcmU32 threshold, Recognition::OnRecognized ^handler);
    pxcmStatus SubscribeAlert(Alert::OnAlert ^handler);

    ~PXCMVoiceRecognition(void) { this->!PXCMVoiceRecognition(); }
    !PXCMVoiceRecognition(void);

internal:

    PXCMVoiceRecognition(PXCBase *instance,bool b_delete);
    PXCVoiceRecognition *QueryInstance(void) { return (PXCVoiceRecognition*)m_instance; }

	void DeleteCommandHandler(void);
	void DeleteAlertHandler(void);

    GCHandle                    m_recognized_gch;
    class CommandHandler        *m_command_handler_unmanaged;

    GCHandle                    m_alert_gch;
    class AlertHandler          *m_alert_handler_unmanaged;
};

public ref class PXCMVoiceSynthesis: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCVoiceSynthesis::CUID);

    value struct ProfileInfo {
        enum class Language: pxcmEnum {
            LANGUAGE_US_ENGLISH		= PXCM_UID('e','n','U','S'),
            LANGUAGE_GB_ENGLISH     = PXCM_UID('e','n','G','B'),
            LANGUAGE_DE_GERMAN      = PXCM_UID('d','e','D','E'),
            LANGUAGE_US_SPANISH     = PXCM_UID('e','s','U','S'),
            LANGUAGE_FR_FRENCH      = PXCM_UID('f','r','F','R'),
            LANGUAGE_IT_ITALIAN     = PXCM_UID('i','t','I','T'),
            LANGUAGE_JP_JAPANESE    = PXCM_UID('j','a','J','P'),
            LANGUAGE_CN_CHINESE     = PXCM_UID('z','h','C','N'),
            LANGUAGE_BR_PORTUGUESE  = PXCM_UID('p','t','B','R'),
        };

        enum class Voice: pxcmEnum {
            VOICE_FEMALE=1,
        };

        PXCMCapture::AudioStream::DataDesc outputs;  // output format, need bufferSize to limit the latency.
        Language                language;
        Voice                   voice;
        pxcmF32                 rate;
        pxcmU32                 volume;
        PXCMArray<pxcmU32,sizeof(pxcmU32),4> reserved;
    };

    pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
    pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
    pxcmStatus SetProfile(ProfileInfo %pinfo);

    pxcmStatus QueueSentence(String ^sentence, [Out] pxcmUID %id);
    pxcmStatus ProcessAudioAsync(pxcmUID id, [Out] PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp);

internal:

    PXCMVoiceSynthesis(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCVoiceSynthesis *QueryInstance(void) { return (PXCVoiceSynthesis*)m_instance; }
};
