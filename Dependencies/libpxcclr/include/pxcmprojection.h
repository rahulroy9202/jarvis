/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmcapture.h"
#include "pxcprojection.h"

public ref class PXCMProjection: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(0x494A8537);

    virtual pxcmStatus ProjectImageToRealWorld   (array<PXCMPoint3DF32> ^pos2d, array<PXCMPoint3DF32> ^pos3d);
    virtual pxcmStatus ProjectRealWorldToImage   (array<PXCMPoint3DF32> ^pos3d, array<PXCMPointF32> ^pos2d);
    virtual pxcmStatus MapDepthToColorCoordinates(array<PXCMPoint3DF32> ^pos2d, array<PXCMPointF32> ^posc);
    virtual pxcmStatus MapColorCoordinatesToDepth(array<PXCMPointF32>   ^posc,  array<PXCMPointF32> ^posd);

internal:

    PXCMProjection(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCProjection *QueryInstance(void) { return (PXCProjection*)m_instance; }
};
