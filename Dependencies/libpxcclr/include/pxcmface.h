/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmscheduler.h"
#include "pxcmaccelerator.h"
#include "pxcmcapture.h" 
#include "pxcface.h"

public ref class PXCMFaceAnalysis:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCFaceAnalysis::CUID);

    [StructLayout(LayoutKind::Explicit)]
    value struct ProfileInfo {
        [FieldOffset(0)]    PXCMCapture::VideoStream::DataDesc inputs;
        [FieldOffset(1280)] pxcmBool iftracking;
        [FieldOffset(1284)] PXCMArray<pxcmU32,sizeof(pxcmU32),7> reserved;
    };

    ref class Detection:public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCFaceAnalysis::Detection::CUID);

        [Flags] enum class ViewAngle: pxcmEnum {
            VIEW_ANGLE_0          = 0x00000001,
            VIEW_ANGLE_45         = 0x00000002,
            VIEW_ANGLE_FRONTAL    = 0x00000004,
            VIEW_ANGLE_135        = 0x00000008,
            VIEW_ANGLE_180        = 0x00000010,

            VIEW_ROLL_30          = 0x00000020,
            VIEW_ROLL_30N         = 0x00000040,
            VIEW_ROLL_60          = 0x00000080,
            VIEW_ROLL_60N         = 0x00000100,

            VIEW_ANGLE_HALF_MULTI = VIEW_ANGLE_FRONTAL | VIEW_ANGLE_45 | VIEW_ANGLE_135,
            VIEW_ANGLE_MULTI      = VIEW_ANGLE_HALF_MULTI | VIEW_ANGLE_0 | VIEW_ANGLE_180,
            VIEW_ANGLE_FRONTALROLL= VIEW_ANGLE_FRONTAL | VIEW_ROLL_30| VIEW_ROLL_30N | VIEW_ROLL_60 | VIEW_ROLL_60N,
            VIEW_ANGLE_OMNI       = (pxcmEnum)0xFFFFFFFF,
        };

        value struct ProfileInfo {
            PXCMSizeU32 minFaceSize;    /* minimum face size */
            PXCMSizeU32 maxFaceSize;    /* maximum face size */
            pxcmU64     reserved;
            ViewAngle   viewAngles;     /* algorithm limitation on face view angles */
            pxcmU32     responsiveness;
        };

        value struct Data {
            PXCMRectU32 rectangle;      /* face rectangle */
            pxcmUID     fid;            /* face identifier */
            pxcmU32     confidence;     /* 0-100 */
            ViewAngle   viewAngle;      /* face angle */
            PXCMArray<pxcmU32,sizeof(pxcmU32),4> reserved;
        };

        virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
        virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
        virtual pxcmStatus SetProfile(ProfileInfo %pinfo);
        virtual pxcmStatus QueryData(pxcmUID fid, [Out] Data %data);

    internal:

        Detection(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCFaceAnalysis::Detection *QueryInstance(void) { return (PXCFaceAnalysis::Detection*)m_instance; }
    };

    ref class Landmark:public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCFaceAnalysis::Landmark::CUID);

        [Flags] enum class Label: pxcmEnum {
            LABEL_LEFT_EYE_OUTER_CORNER   =0x0001000,
            LABEL_LEFT_EYE_INNER_CORNER   =0x0002000,
            LABEL_RIGHT_EYE_OUTER_CORNER  =0x0004000,
            LABEL_RIGHT_EYE_INNER_CORNER  =0x0008000,
            LABEL_MOUTH_LEFT_CORNER       =0x0010000,
            LABEL_MOUTH_RIGHT_CORNER      =0x0020000,
            LABEL_NOSE_TIP                =0x0040000,

            LABEL_6POINTS				  =0x003F006,
            LABEL_7POINTS				  =0x007F007,
			LABEL_SIZE_MASK				  =0x0000FFF,
        };

        value struct ProfileInfo {
            Label   labels;     /* enumeration of supported feature points */
            PXCMArray<pxcmU32,sizeof(pxcmU32),7> reserved;
        };

        value struct PoseData {
            pxcmUID fid;
            pxcmF32 yaw, roll, pitch;
            PXCMArray<pxcmU32,sizeof(pxcmU32),4> reserved;
        };

        value struct LandmarkData {
            PXCMPoint3DF32  position;
            pxcmUID         fid;
            Label           label;
            pxcmU32         lidx;
            PXCMArray<pxcmU32,sizeof(pxcmU32),6> reserved;
        };

        virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
        virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
        virtual pxcmStatus SetProfile(ProfileInfo %pinfo);
        virtual pxcmStatus QueryLandmarkData(pxcmUID fid, Label landmark, pxcmU32 lidx, [Out] LandmarkData %data);
		virtual pxcmStatus QueryLandmarkData(pxcmUID fid, Label landmark, array<LandmarkData> ^data);
        virtual pxcmStatus QueryPoseData(pxcmUID fid, [Out] PoseData %pose);

    internal:

        Landmark(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCFaceAnalysis::Landmark *QueryInstance(void) { return (PXCFaceAnalysis::Landmark*)m_instance; }
    };

    ref class Recognition:public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCFaceAnalysis::Recognition::CUID);

        value struct ProfileInfo {
			pxcmU32		modelSize;
			pxcmF32		threshold;
            PXCMArray<pxcmU32,sizeof(pxcmU32),6> reserved;
        };

		ref class Model:public PXCMBase {
		public:
			PXCM_CUID_OVERWRITE(PXCFaceAnalysis::Recognition::Model::CUID);

			virtual pxcmStatus Serialize(array<pxcmBYTE> ^buffer);
			virtual pxcmStatus Compare(array<Model^> ^models, array<pxcmF32> ^floats, [Out] pxcmU32 %index);
			virtual pxcmStatus Compare(array<Model^> ^models, [Out] pxcmU32 %index);
		internal:
	        Model(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
			PXCFaceAnalysis::Recognition::Model *QueryInstance(void) { return (PXCFaceAnalysis::Recognition::Model*)m_instance; }
		};

		virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
        virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
        virtual pxcmStatus SetProfile(ProfileInfo %pinfo);

		virtual pxcmStatus CreateModel(pxcmUID fid, [Out] Model ^%model);
		virtual pxcmStatus DeserializeModel(array<pxcmBYTE> ^buffer, [Out] Model ^%model);

    internal:

        Recognition(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCFaceAnalysis::Recognition *QueryInstance(void) { return (PXCFaceAnalysis::Recognition*)m_instance; }
    };

    virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %profile);
    virtual pxcmStatus QueryProfile([Out] ProfileInfo %profile);
    virtual pxcmStatus SetProfile(ProfileInfo %profile);

    virtual pxcmStatus QueryFace(pxcmU32 fidx, [Out] pxcmUID %fid, [Out] pxcmU64 %timeStamp);
    virtual pxcmStatus ProcessImageAsync(array<PXCMImage^> ^images, [Out] PXCMScheduler::SyncPoint ^%sp);

internal:

    PXCMFaceAnalysis(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCFaceAnalysis *QueryInstance(void) { return (PXCFaceAnalysis*)m_instance; }
};
