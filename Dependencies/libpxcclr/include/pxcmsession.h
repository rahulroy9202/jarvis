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
#include "pxcsession.h"

public ref class PXCMSession: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCSession::CUID);

    value struct ImplVersion {
        pxcmU16  major;
        pxcmU16  minor;
    };

    /* bit OR'ed values */
    [Flags] enum class ImplGroup: pxcmEnum {
        IMPL_GROUP_ANY                  =    0,
        IMPL_GROUP_OBJECT_RECOGNITION   =    0x00000001,
        IMPL_GROUP_SPEECH_RECOGNITION   =    0x00000002,
        IMPL_GROUP_SENSOR               =    0x00000004,

        IMPL_GROUP_CORE                 =    (pxcmEnum)0x80000000,
        IMPL_GROUP_USER                 =    0x40000000,  /* user defined algorithms */
    };

    /* bit OR'ed values */
    [Flags] enum class ImplSubgroup: pxcmEnum {
        IMPL_SUBGROUP_ANY                   = 0,
        IMPL_SUBGROUP_FACE_ANALYSIS         =    0x00000001,
        IMPL_SUBGROUP_GESTURE_RECOGNITION   =    0x00000010,
        IMPL_SUBGROUP_AUDIO_CAPTURE         =    0x00000001,
        IMPL_SUBGROUP_VIDEO_CAPTURE         =    0x00000002,
        IMPL_SUBGROUP_VOICE_RECOGNITION     =    0x00000001,
        IMPL_SUBGROUP_VOICE_SYNTHESIS       =    0x00000002,
    };

    [StructLayout(LayoutKind::Explicit)]
    value struct ImplDesc {
        [FieldOffset(0)  ] ImplGroup               group;          /* implementation group */
        [FieldOffset(4)  ] ImplSubgroup            subgroup;       /* implementation sub-group */
        [FieldOffset(8)  ] pxcmUID                 algorithm;      /* algorithm identifier */      
        [FieldOffset(12) ] pxcmUID                 iuid;           /* implementation unique id */
        [FieldOffset(16) ] ImplVersion             version;        /* implementation version */
        [FieldOffset(20) ] PXCMAccelerator::AccelType acceleration;   /* implementation acceleration support */
        [FieldOffset(24) ] pxcmU32                 merit;          /* implementation merit */
        [FieldOffset(28) ] pxcmU32                 vendor;         /* vendor */
        [FieldOffset(32) ] PXCMArray<pxcmUID,sizeof(pxcmUID),4>    cuids;
        [FieldOffset(48) ] PXCMString<256>         friendlyName;
        [FieldOffset(560)] PXCMArray<pxcmU32,sizeof(pxcmU32),12>   reserved;
    };

    virtual property ImplVersion version {
		ImplVersion get(void) { ImplVersion v; QueryVersion(v); return v; }
    };
	virtual pxcmStatus QueryVersion([Out] ImplVersion %);

    virtual pxcmStatus QueryImpl(ImplDesc %templat, pxcmU32 idx, [Out] ImplDesc %desc);
    virtual pxcmStatus QueryImpl(pxcmU32 idx, [Out] ImplDesc %desc);

    virtual pxcmStatus CreateScheduler([Out] PXCMScheduler ^%instance);

    virtual pxcmStatus CreateAccelerator(PXCMAccelerator::AccelType type, [Out] PXCMAccelerator ^%instance);
    virtual pxcmStatus CreateAccelerator([Out] PXCMAccelerator ^%instance);

    virtual pxcmStatus CreateImpl(PXCMScheduler ^sch, PXCMAccelerator ^accel, ImplDesc %desc, pxcmUID iuid, pxcmUID cuid, [Out] PXCMBase ^%instance);
    virtual pxcmStatus CreateImpl(pxcmUID iuid, pxcmUID cuid, [Out] PXCMBase ^%instance);
    virtual pxcmStatus CreateImpl(ImplDesc %desc, pxcmUID cuid, [Out] PXCMBase ^%instance);
	virtual pxcmStatus CreateImpl(pxcmUID cuid, [Out] PXCMBase ^%instance) { return CreateImpl(0,cuid,instance); }
	virtual pxcmStatus CreateImpl(PXCMScheduler ^sch, PXCMAccelerator ^accel, ImplDesc %desc, pxcmUID cuid, [Out] PXCMBase ^%instance) { return CreateImpl(sch,accel,desc,0,cuid,instance); }

	generic<typename TT> where TT:PXCMBase pxcmStatus CreateImpl(PXCMScheduler ^sch, PXCMAccelerator ^accel, ImplDesc %desc, pxcmUID iuid, pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateImpl(sch,accel,desc,iuid,cuid,t);instance=(TT)t;return s;}
	generic<typename TT> where TT:PXCMBase pxcmStatus CreateImpl(pxcmUID iuid, pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateImpl(iuid,cuid,t);instance=(TT)t;return s;}
    generic<typename TT> where TT:PXCMBase pxcmStatus CreateImpl(ImplDesc %desc, pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateImpl(desc,cuid,t);instance=(TT)t;return s;}
	generic<typename TT> where TT:PXCMBase pxcmStatus CreateImpl(pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateImpl(cuid,t);instance=(TT)t;return s;}
	generic<typename TT> where TT:PXCMBase pxcmStatus CreateImpl(PXCMScheduler ^sch, PXCMAccelerator ^accel, ImplDesc %desc, pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateImpl(sch,accel,desc,cuid,t);instance=(TT)t;return s;}

    virtual pxcmStatus LoadImplFromFile(String ^moduleName);
    virtual pxcmStatus UnloadImplFromFile(String ^moduleName);

    static pxcmStatus  CreateInstance([Out] PXCMSession ^%session);

internal:

    PXCMSession(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCSession *QueryInstance(void) { return (PXCSession*)m_instance; }
};
