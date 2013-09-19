/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmmetadata.h"

pxcmStatus PXCMMetadata::AttachBuffer(pxcmUID id, array<pxcmBYTE> ^buffer) {
    pin_ptr<pxcmBYTE> pp(&buffer[0]);
    return (pxcmStatus)QueryInstance()->AttachBuffer((pxcUID)id,(pxcBYTE*)pp,buffer->Length);
}

pxcmStatus PXCMMetadata::QueryBuffer(pxcmUID id, [Out] array<pxcmBYTE> ^%buffer) {
    buffer=nullptr;
    pxcU32 bufferSize=0;
    pxcStatus sts=QueryInstance()->QueryBuffer((pxcUID)id,0,&bufferSize);
    if (sts>=PXC_STATUS_NO_ERROR) {
        buffer=gcnew array<pxcmBYTE>(bufferSize);
        pin_ptr<pxcmBYTE> pp(&buffer[0]);
        sts=QueryInstance()->QueryBuffer((pxcUID)id,(pxcBYTE*)pp,&bufferSize);
    }
    return (pxcmStatus)sts;
}

pxcmStatus PXCMMetadata::QueryMetadata(pxcmU32 idx, [Out] pxcmUID %id) {
    pxcUID id2;
    pxcStatus sts=QueryInstance()->QueryMetadata((pxcU32)idx,&id2);
    id=id2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMMetadata::AttachSerializable(pxcmUID id, PXCMBase ^instance) {
    return (pxcmStatus)QueryInstance()->AttachSerializable((pxcUID)id,instance->m_instance);
}

pxcmStatus PXCMMetadata::CreateSerializable(pxcmUID id, pxcmUID cuid, [Out] PXCMBase ^%instance) {
    void *instance2=0;
    pxcStatus sts=QueryInstance()->CreateSerializable((pxcUID)id,(pxcUID)cuid,&instance2);
    instance=(sts>=PXC_STATUS_NO_ERROR)?PXCMBase::DynamicCastEx(cuid,(PXCBase*)instance2):nullptr;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMMetadata::DetachMetadata(pxcmUID id) {
    return (pxcmStatus)QueryInstance()->DetachMetadata((pxcUID)id);
}

pxcmUID PXCMMetadata::QueryUID(void) {
    return (pxcmUID)QueryInstance()->QueryUID();
}
