/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmbase.h"
#include "pxcmetadata.h"

public ref class PXCMMetadata:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCMetadata::CUID);

    virtual pxcmStatus AttachBuffer(pxcmUID id, array<pxcmBYTE> ^buffer);
    virtual pxcmStatus QueryBuffer(pxcmUID id, [Out] array<pxcmBYTE> ^%buffer);
    virtual pxcmStatus QueryMetadata(pxcmU32 idx, [Out] pxcmUID %id);

    virtual pxcmStatus AttachSerializable(pxcmUID id, PXCMBase ^instance);
    virtual pxcmStatus CreateSerializable(pxcmUID id, pxcmUID cuid, [Out] PXCMBase ^%instance);
	generic<typename TT> where TT:PXCMBase pxcmStatus CreateSerializable(pxcmUID id, pxcmUID cuid, [Out] TT %instance) { PXCMBase^t;pxcmStatus s=CreateSerializable(id,cuid,t);instance=(TT)t;return s; }

    virtual pxcmStatus DetachMetadata(pxcmUID id);

	virtual property pxcmUID uid {
		pxcmUID get(void) { return QueryUID(); }
	};
    virtual pxcmUID    QueryUID(void);

internal:

    PXCMMetadata(PXCBase *instance,bool b_delete): PXCMBase(instance,b_delete) {}
    PXCMetadata *QueryInstance(void) { return (PXCMetadata*)m_instance; }
};
