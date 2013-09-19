/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "utilm_capture.h"
#include "util_capture_file.h"

public ref class UtilMCaptureFile: public UtilMCapture {
public:

	virtual property PXCMImage::ImageType mask {
		void set(PXCMImage::ImageType m) { SetMask(m); }
	};

	virtual property pxcmBool pause {
		void set(pxcmBool p) { SetPause(p); }
	};

	virtual property pxcmBool realtime {
		void set(pxcmBool rt) { SetRealtime(rt); }
	};

    virtual property pxcmI32 position {
		pxcmI32 get(void) { return QueryPosition(); }
		void    set(pxcmI32 iframe) { SetPosition(iframe); }
    };

	virtual pxcmI32 QueryPosition(void);
	virtual void SetMask(PXCMImage::ImageType types);
	virtual void SetPause(pxcmBool pause);
	virtual void SetPosition(pxcmI32 iframe);
	virtual void SetRealtime(pxcmBool realtime);

    UtilMCaptureFile(PXCMSession ^session, String ^file, pxcmBool recording);

internal:

	UtilMCaptureFile(UtilCaptureFile *instance, bool b_delete):UtilMCapture(instance,b_delete) {}
};
