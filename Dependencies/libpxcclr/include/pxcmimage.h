/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

#include "pxcmbase.h"
#include "pxcimage.h"

ref class PXCMAccelerator;
public ref class PXCMImage:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCImage::CUID);

    [Flags] enum class ImageType: pxcmEnum {
        IMAGE_TYPE_COLOR    =0x00010000,
        IMAGE_TYPE_DEPTH    =0x00020000,
        IMAGE_TYPE_MASK     =(pxcmEnum)0xffff0000
    };

    enum class ColorFormat: pxcmEnum {
        COLOR_FORMAT_YUY2       =   (pxcmEnum)ImageType::IMAGE_TYPE_COLOR,
        COLOR_FORMAT_NV12,
        COLOR_FORMAT_RGB32,
        COLOR_FORMAT_RGB24,
        COLOR_FORMAT_GRAY,
        COLOR_FORMAT_DEPTH      =   (pxcmEnum)ImageType::IMAGE_TYPE_DEPTH,
        COLOR_FORMAT_VERTICES,
    };

    enum class ImageOption: pxcmOption {
        IMAGE_OPTION_NO_UV_MAP          =   0x00000001,
        IMAGE_OPTION_NO_CONFIDENCE_MAP  =   0x00000002,
    };

    value struct ImageInfo {
        pxcmU32     width;
        pxcmU32     height;
        ColorFormat format;
        pxcmU32     reserved;
    };

    [Flags] enum class SurfaceType: pxcmEnum {
        SURFACE_TYPE_SYSTEM_MEMORY   =   0x00010000, /* if used in ImageData: planes[], pitches[] */
        SURFACE_TYPE_DX9_SURFACE     =   0x00020000, /* if used in ImageData: surfaceHandle with type IDirect3DSurface9* */
        SURFACE_TYPE_DX11_SURFACE    =   0x00040000, /* if used in ImageData: surfaceHandle with type ID3D11Texture2D* */
        SURFACE_TYPE_OCL_MEMOBJ      =   0x00080000, /* if used in ImageData: surfaceHandle with type cl_mem* */
    };

    [StructLayout(LayoutKind::Explicit)] value struct ImageBuffer {
        [FieldOffset(0)]  pxcmHDL surfaceHandle;
        [FieldOffset(0)]  PXCMArray<pxcmI32,sizeof(pxcmI32),4>  pitches;
        [FieldOffset(16)] PXCMArray<pxcmHDL,sizeof(void*),4>  planes;
    };

    [StructLayout(LayoutKind::Explicit)]
    value struct ImageData {
        [FieldOffset(0)]  ColorFormat   format;
        [FieldOffset(4)]  SurfaceType   type;
        [FieldOffset(8)]  pxcmU64       reserved;
        [FieldOffset(16)] ImageBuffer   buffer;

	    /* Import and export functions */
		virtual array<pxcmBYTE>^ ToByteArray(pxcmI32 index, pxcmI32 size);
		virtual array<pxcmI16>^ ToShortArray(pxcmI32 index, pxcmI32 size);
		virtual array<pxcmF32>^ ToFloatArray(pxcmI32 index, pxcmI32 size);

	    virtual System::Drawing::Bitmap^ ToBitmap(pxcmI32 index, pxcmU32 width, pxcmU32 height);
		virtual System::Drawing::Bitmap^ ToBitmap(pxcmU32 width, pxcmU32 height) { return ToBitmap(0,width,height); }
		virtual System::Windows::Media::Imaging::WriteableBitmap^ ToWritableBitmap(pxcmI32 index, pxcmU32 width, pxcmU32 height, pxcmF64 dpiX, pxcmF64 dpiY);
		virtual System::Windows::Media::Imaging::WriteableBitmap^ ToWritableBitmap(pxcmU32 width, pxcmU32 height, pxcmF64 dpiX, pxcmF64 dpiY) { return ToWritableBitmap(0,width,height,dpiX,dpiY); }
	};

    [Flags] enum class Access: pxcmEnum {
        ACCESS_READ         = 1,
        ACCESS_WRITE        = 2,
        ACCESS_READ_WRITE   = ACCESS_READ | ACCESS_WRITE,
    };
    
    virtual property ImageInfo imageInfo {
		ImageInfo   get(void) { ImageInfo info; QueryInfo(info); return info; }
    };
	virtual pxcmStatus QueryInfo([Out] ImageInfo %);

	[System::Obsolete("Use options instead")]
    virtual property pxcmOption option {
		pxcmOption  get(void) { return QueryOption(); }
		void        set(pxcmOption opt) { SetOption(opt); }
    };

    virtual property pxcmOption options {
		pxcmOption  get(void) { return QueryOption(); }
		void        set(pxcmOption flags) { SetOption(flags); }
    };
	virtual pxcmOption QueryOption(void);
	virtual pxcmStatus SetOption(pxcmOption);

    virtual property pxcmU64 timeStamp {
		pxcmU64     get(void) { return QueryTimeStamp(); }
		void        set(pxcmU64 ts) { SetTimeStamp(ts); }
    };
	virtual pxcmU64 QueryTimeStamp(void);
	virtual pxcmStatus SetTimeStamp(pxcmU64);

    virtual property PXCMRectU32 roi {
		PXCMRectU32 get(void) { return QueryROI(); }
		void        set(PXCMRectU32 roi2) { SetROI(roi2); }
    };
	virtual PXCMRectU32 QueryROI(void);
	virtual pxcmStatus  SetROI(PXCMRectU32);

    /* Copy data from another image */
    virtual pxcmStatus   CopyData(PXCMImage ^src_image);

    /* Functions expose the internal buffer storage */ 
    virtual pxcmStatus   AcquireAccess(Access access, PXCMAccelerator ^accelerator, ColorFormat format, [Out] ImageData %data);
    virtual pxcmStatus   AcquireAccess(Access access, PXCMAccelerator ^accelerator, [Out] ImageData %data);
    virtual pxcmStatus   AcquireAccess(Access access, ColorFormat format, [Out] ImageData %data);
    virtual pxcmStatus   AcquireAccess(Access access, [Out] ImageData %data);

    virtual pxcmStatus   TryAccess(Access access, PXCMAccelerator ^accelerator, ColorFormat format, [Out] ImageData %data);
    virtual pxcmStatus   TryAccess(Access access, PXCMAccelerator ^accelerator, [Out] ImageData %data);
    virtual pxcmStatus   TryAccess(Access access, ColorFormat format, [Out] ImageData %data);
    virtual pxcmStatus   TryAccess(Access access, [Out] ImageData %data);
    virtual pxcmStatus   ReleaseAccess(ImageData %data);

	[System::Obsolete("Use ImageData.ToBitmap instead")]
    virtual pxcmStatus QueryBitmap(ref class PXCMSession ^session, [Out] System::Drawing::Bitmap ^%bitmap);

	static void Dispose(array<PXCMImage^> ^images);

internal:

    PXCMImage(PXCBase *instance, bool b_delete):PXCMBase(instance,b_delete) {}
    PXCImage *QueryInstance(void) { return (PXCImage*)m_instance; }
};

