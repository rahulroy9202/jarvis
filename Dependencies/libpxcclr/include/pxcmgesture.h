/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmsession.h"
#include "pxcmcapture.h"
#include "pxcgesture.h"

public ref class PXCMGesture:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCGesture::CUID);

	[StructLayout(LayoutKind::Explicit,Size=128)]
    value struct GeoNode {
        [Flags] enum class Label: pxcmEnum {
            LABEL_ANY=0,
            LABEL_MASK_BODY             =(pxcEnum)0xffffff00,
            LABEL_MASK_DETAILS          =0x000000ff,

            /* full body labels */
			LABEL_BODY_ELBOW_PRIMARY    =0x00004000,
            LABEL_BODY_ELBOW_LEFT       =0x00004000,
			LABEL_BODY_ELBOW_SECONDARY  =0x00008000,
            LABEL_BODY_ELBOW_RIGHT      =0x00008000,
			LABEL_BODY_HAND_PRIMARY     =0x00040000,
            LABEL_BODY_HAND_LEFT        =0x00040000,
			LABEL_BODY_HAND_SECONDARY   =0x00080000,
            LABEL_BODY_HAND_RIGHT       =0x00080000,

            /* detailed labels: Hand */
            LABEL_FINGER_THUMB          =1,
            LABEL_FINGER_INDEX,
            LABEL_FINGER_MIDDLE,
            LABEL_FINGER_RING,
            LABEL_FINGER_PINKY,

            LABEL_HAND_FINGERTIP,
			LABEL_HAND_UPPER,
			LABEL_HAND_MIDDLE,
			LABEL_HAND_LOWER,
        };

		enum class Side: pxcmEnum {
			LABEL_SIDE_ANY=0,
			LABEL_LEFT,
			LABEL_RIGHT,
		};

		enum class Openness: pxcmEnum {
			LABEL_OPENNESS_ANY=0,
			LABEL_CLOSE,
			LABEL_OPEN,
		};

        [FieldOffset(0)]   pxcmU64          timeStamp;
        [FieldOffset(8)]   pxcmUID          user;
        [FieldOffset(12)]  Label            body;
        [FieldOffset(16)]  Side				side;
		[FieldOffset(20)]  pxcmU32		    confidence;
        [FieldOffset(24)]  PXCMPoint3DF32   positionWorld;
        [FieldOffset(36)]  PXCMPoint3DF32   positionImage;
		[FieldOffset(64)]  pxcmF32          radiusWorld;
		[FieldOffset(68)]  pxcmF32		    radiusImage;
		[FieldOffset(64)]  PXCMPoint3DF32   massCenterWorld;
		[FieldOffset(76)]  PXCMPoint3DF32   massCenterImage;
		[FieldOffset(88)]  PXCMPoint3DF32   normal;
		[FieldOffset(100)] pxcmU32          openness;
		[FieldOffset(104)] Openness         opennessState;
    };

    value struct Blob {
        [Flags] enum class Label: pxcmEnum {
            LABEL_ANY			=0,
            LABEL_SCENE			=0x00000001,
        };

        pxcmU64	timeStamp;              /* time stamp */
        Label   name;					/* blob name */

		pxcmU32	labelBackground;		/* 0-255 */
		pxcmU32	labelLeftHand;			/* 0-255 */
		pxcmU32	labelRightHand;			/* 0-255 */
        PXCMArray<pxcmU32,sizeof(pxcmU32),26> reserved;
    };

    [StructLayout(LayoutKind::Explicit)]
    value struct Gesture {
        delegate void OnGesture(Gesture %gesture);

        enum class Label: pxcmEnum {
            LABEL_ANY=0,
            LABEL_MASK_SET          =   (pxcmEnum)0xffff0000,
            LABEL_MASK_DETAILS      =   0x0000ffff,

            LABEL_SET_HAND          =   0x00010000,     /* Common hand gestures */
            LABEL_SET_NAVIGATION    =   0x00020000,     /* Navigation gestures */
            LABEL_SET_POSE          =   0x00040000,     /* Common hand poses */
            LABEL_SET_CUSTOMIZED    =   0x00080000,

            /* predefined nativation gestures */
            LABEL_NAV_SWIPE_LEFT    =   LABEL_SET_NAVIGATION+1,
            LABEL_NAV_SWIPE_RIGHT,
            LABEL_NAV_SWIPE_UP,
            LABEL_NAV_SWIPE_DOWN,

            /* predefined common hand gestures */
			LABEL_HAND_WAVE			=	LABEL_SET_HAND+1,
            LABEL_HAND_CIRCLE,

            /* predefined common hand poses */
            LABEL_POSE_THUMB_UP		=	LABEL_SET_POSE+1,
			LABEL_POSE_THUMB_DOWN,
			LABEL_POSE_PEACE,
            LABEL_POSE_BIG5,
		};

        [FieldOffset(0)]  pxcmU64         timeStamp;
        [FieldOffset(8)]  pxcmUID         user;
        [FieldOffset(12)] GeoNode::Label  body;
        [FieldOffset(16)] Label           label;
        [FieldOffset(20)] pxcmU32         confidence;
		[FieldOffset(24)] pxcmBool		active;
        [FieldOffset(28)] PXCMArray<pxcmU32,sizeof(pxcmU32),9> reserved;
    };

    value struct Alert {
        delegate void OnAlert(Alert %alert);

        [Flags] enum class Label: pxcmEnum {
			LABEL_ANY				=	0,
            LABEL_FOV_LEFT          =   0x00000001,
            LABEL_FOV_RIGHT         =   0x00000002,
            LABEL_FOV_TOP           =   0x00000004,
            LABEL_FOV_BOTTOM        =   0x00000008,
			LABEL_FOV_BLOCKED	   	=	0x00000010,
			LABEL_FOV_OK			=   0x00000020,
			LABEL_GEONODE_ACTIVE	=   0x00000040,
			LABEL_GEONODE_INACTIVE	=   0x00000080,
        };

        pxcmU64         timeStamp;
        pxcmUID         user;
        GeoNode::Label  body;
        Label           label;
        PXCMArray<pxcmU32,sizeof(pxcmU32),3> reserved;
    };

    value struct ProfileInfo {
        PXCMCapture::VideoStream::DataDesc inputs;
        Gesture::Label      sets;
        GeoNode::Label      bodies;
        Blob::Label         blobs;
        Alert::Label        alerts;
		GeoNode::Label		nodeAlerts;
        pxcmU32             activationDistance;
        PXCMArray<pxcmU32,sizeof(pxcmU32),6> reserved;
    };

    virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
    virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
    virtual pxcmStatus SetProfile(ProfileInfo %pinfo);

    virtual pxcmStatus QueryUser(pxcmU32 idx, [Out] pxcmUID %user);
    virtual pxcmStatus QueryBlobData(Blob::Label label, pxcmU32 idx, [Out] Blob %data);
    virtual pxcmStatus QueryBlobImage(Blob::Label label, pxcmU32 idx, [Out] PXCMImage ^%image);
    virtual pxcmStatus QueryNodeData(pxcmUID user, GeoNode::Label body, [Out] GeoNode %data);
    virtual pxcmStatus QueryNodeData(pxcmUID user, GeoNode::Label body, array<GeoNode> ^data);
	virtual pxcmStatus QueryGestureData(pxcmUID user, GeoNode::Label body, pxcmU32 idx, [Out] Gesture %data);

    virtual pxcmStatus ProcessImageAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp);
    virtual pxcmStatus SubscribeGesture(pxcmU32 threshold, Gesture::OnGesture ^handler);
    virtual pxcmStatus SubscribeAlert(Alert::OnAlert ^handler);

    ~PXCMGesture(void) { this->!PXCMGesture(); }
    !PXCMGesture(void);

internal:

    PXCMGesture(PXCBase *instance,bool b_delete);
    PXCGesture *QueryInstance(void) { return (PXCGesture*)m_instance; }
    void DeleteGestureHandler(void);
    void DeleteAlertHandler(void);

    GCHandle                m_gesture_gch, m_alert_gch;
    class GestureHandler    *m_gesture_handler_unmanaged;
    class AlertHandler      *m_alert_handler_unmanaged;
};
