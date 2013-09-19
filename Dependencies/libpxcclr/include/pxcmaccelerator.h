/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmimage.h"
#include "pxcmaudio.h"
#include "pxcaccelerator.h"

public ref class PXCMAccelerator: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCAccelerator::CUID);

    /* acceleration device: bit-OR'ed values */
    [Flags] enum class Device: pxcmI32 {
        DEVICE_ANY       =0x7fffffff,
        DEVICE_0         =0x00000001,
        DEVICE_1         =0x00000002,
        DEVICE_2         =0x00000004,
        DEVICE_3         =0x00000008,
        DEVICE_CURRENT   =(pxcmI32)0x80000000,
     };

    /* accleration type: bit-OR'ed values */
    [Flags] enum class AccelType: pxcmI32 {
        ACCEL_TYPE_ANY         = 0,
        ACCEL_TYPE_CPU         = 0x000000FF,
        ACCEL_TYPE_GPU         = 0x0000FF00,
        ACCEL_TYPE_GPU_VIA_DX9 = 0x00000100,
    };

    [Flags] enum class HandleType: pxcmI32 {
        HANDLE_TYPE_DX9_DEVICE     =   0x00000002, /* IDirect3DDeviceManager9* */
        HANDLE_TYPE_DX11_DEVICE    =   0x00000008, /* ID3D11Device* */
        HANDLE_TYPE_OCL_DEVICE     =   0x00000020, /* cl_context* */
    };

	virtual property AccelType accelType {
		AccelType get(void) { return QueryAccelType(); }
	};

	virtual property Device device {
		Device get(void) { return QueryDevice(); }
	};

	virtual AccelType  QueryAccelType(void);
	virtual Device     QueryDevice(void);

	virtual pxcmStatus QueryHandle(HandleType type, [Out] pxcmHDL %handle);
	virtual pxcmStatus SetHandle(HandleType type, pxcmHDL handle);

    virtual pxcmStatus CreateImage(PXCMImage::ImageInfo %info, PXCMImage::ImageOption options, PXCMImage::ImageData %data, [Out] PXCMImage ^%image);
    virtual pxcmStatus CreateAudio(PXCMAudio::AudioInfo %info, PXCMAudio::AudioOption options, PXCMAudio::AudioData %data, [Out] PXCMAudio ^%audio);
    virtual pxcmStatus CreateImage(PXCMImage::ImageInfo %info, [Out] PXCMImage ^%image);
    virtual pxcmStatus CreateAudio(PXCMAudio::AudioInfo %info, [Out] PXCMAudio ^%audio);

internal:

    PXCMAccelerator(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCAccelerator *QueryInstance(void) { return (PXCAccelerator*)m_instance; }
};
