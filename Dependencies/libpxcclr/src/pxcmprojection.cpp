/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmprojection.h"

pxcmStatus PXCMProjection::ProjectImageToRealWorld(array<PXCMPoint3DF32> ^pos2d, array<PXCMPoint3DF32> ^pos3d) {
    pin_ptr<PXCMPoint3DF32> pp2(&pos2d[0]);
    pin_ptr<PXCMPoint3DF32> pp3(&pos3d[0]);
    return (pxcmStatus)QueryInstance()->ProjectImageToRealWorld(pos2d->Length,(PXCPoint3DF32*)pp2,(PXCPoint3DF32*)pp3);
}

pxcmStatus PXCMProjection::ProjectRealWorldToImage(array<PXCMPoint3DF32> ^pos3d, array<PXCMPointF32> ^pos2d) {
    pin_ptr<PXCMPoint3DF32> pp3(&pos3d[0]);
    pin_ptr<PXCMPointF32> pp2(&pos2d[0]);
    return (pxcmStatus)QueryInstance()->ProjectRealWorldToImage(pos3d->Length,(PXCPoint3DF32*)pp3,(PXCPointF32*)pp2);
}

pxcmStatus PXCMProjection::MapDepthToColorCoordinates(array<PXCMPoint3DF32> ^posd, array<PXCMPointF32> ^posc) {
    pin_ptr<PXCMPoint3DF32> ppd(&posd[0]);
    pin_ptr<PXCMPointF32> ppc(&posc[0]);
    return (pxcmStatus)QueryInstance()->MapDepthToColorCoordinates(posd->Length,(PXCPoint3DF32*)ppd,(PXCPointF32*)ppc);
}

pxcmStatus PXCMProjection::MapColorCoordinatesToDepth(array<PXCMPointF32>   ^posc,  array<PXCMPointF32> ^posd) {
    pin_ptr<PXCMPointF32> ppc(&posc[0]);
    pin_ptr<PXCMPointF32> ppd(&posd[0]);
    return (pxcmStatus)QueryInstance()->MapColorCoordinatesToDepth(posc->Length,(PXCPointF32*)ppc,(PXCPointF32*)ppd);
}

