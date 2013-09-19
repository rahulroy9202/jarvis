/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmaccelerator.h"
#include "pxcmsession.h"
#include "pxcsmartptr.h"

pxcmStatus PXCMImage::QueryInfo([Out] ImageInfo %info) {
    pin_ptr<ImageInfo> pp(&info);
    return (pxcmStatus)QueryInstance()->QueryInfo((PXCImage::ImageInfo*)pp);
}

pxcmOption PXCMImage::QueryOption(void) {
    return (pxcmOption)QueryInstance()->QueryOption();
}

pxcmU64 PXCMImage::QueryTimeStamp(void) {
    return (pxcmU64)QueryInstance()->QueryTimeStamp();
}

PXCMRectU32 PXCMImage::QueryROI(void) {
    PXCMRectU32 rect;
    pin_ptr<PXCMRectU32> pp=&rect;
    *((PXCRectU32*)pp)=QueryInstance()->QueryROI();
    return rect;
}

pxcmStatus PXCMImage::SetOption(pxcmOption flags) {
    return (pxcmStatus)QueryInstance()->SetOption((pxcOption)flags);
}

pxcmStatus PXCMImage::SetTimeStamp(pxcmU64 ts) {
    return (pxcmStatus)QueryInstance()->SetTimeStamp((pxcU64)ts);
}

pxcmStatus PXCMImage::SetROI(PXCMRectU32 roi) {
    pin_ptr<PXCMRectU32> pp(&roi);
    return (pxcmStatus)QueryInstance()->SetROI(*((PXCRectU32*)pp));
}

pxcmStatus PXCMImage::CopyData(PXCMImage ^src_image) {
    return (pxcmStatus)QueryInstance()->CopyData(src_image->QueryInstance());
}

pxcmStatus PXCMImage::AcquireAccess(Access access, PXCMAccelerator ^accelerator, ColorFormat format, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCImage::Access)access,accelerator->QueryInstance(),(PXCImage::ColorFormat)format,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::AcquireAccess(Access access, PXCMAccelerator ^accelerator, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCImage::Access)access,accelerator->QueryInstance(),0,(PXCImage::ImageData*)pp);
}

try{
pxcmStatus PXCMImage::AcquireAccess(Access access, ColorFormat format, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCImage::Access)access,0,(PXCImage::ColorFormat)format,(PXCImage::ImageData*)pp);
}
}
catch(Exception e){}


pxcmStatus PXCMImage::AcquireAccess(Access access, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->AcquireAccess((PXCImage::Access)access,0,0,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::TryAccess(Access access, PXCMAccelerator ^accelerator, ColorFormat format, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCImage::Access)access,accelerator->QueryInstance(),(PXCImage::ColorFormat)format,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::TryAccess(Access access, PXCMAccelerator ^accelerator, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCImage::Access)access,accelerator->QueryInstance(),0,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::TryAccess(Access access, ColorFormat format, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCImage::Access)access,0,(PXCImage::ColorFormat)format,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::TryAccess(Access access, [Out] ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->TryAccess((PXCImage::Access)access,0,0,(PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::ReleaseAccess(ImageData %data) {
    pin_ptr<ImageData> pp(&data);
    return (pxcmStatus)QueryInstance()->ReleaseAccess((PXCImage::ImageData*)pp);
}

pxcmStatus PXCMImage::QueryBitmap(PXCMSession ^session, [Out] System::Drawing::Bitmap ^%bitmap) {
    bitmap=nullptr;
    PXCImage::ImageInfo info;
    pxcStatus sts=QueryInstance()->QueryInfo(&info);
    if (sts<PXC_STATUS_NO_ERROR) return (pxcmStatus)sts;

    ImageData data;
    pxcmStatus sts2=AcquireAccess(Access::ACCESS_READ,ColorFormat::COLOR_FORMAT_RGB32,data);
    if (sts2<pxcmStatus::PXCM_STATUS_NO_ERROR) return sts2;

	System::Drawing::Bitmap ^bitmap2=data.ToBitmap(info.width, info.height);
	bitmap=gcnew System::Drawing::Bitmap(bitmap2); // make a copy
	delete bitmap2;

    sts2=ReleaseAccess(data);
    return sts2;
}

array<pxcmBYTE>^ PXCMImage::ImageData::ToByteArray(pxcmI32 index, pxcI32 size) {
	if (type!=SurfaceType::SURFACE_TYPE_SYSTEM_MEMORY) return nullptr;
	array<pxcmBYTE>^ data=gcnew array<pxcmBYTE>(size);
	Marshal::Copy(buffer.planes[index],data,0,size);
	return data;
}

array<pxcmI16>^ PXCMImage::ImageData::ToShortArray(pxcmI32 index, pxcI32 size) {
	if (type!=SurfaceType::SURFACE_TYPE_SYSTEM_MEMORY) return nullptr;
	array<pxcmI16>^ data=gcnew array<pxcmI16>(size);
	Marshal::Copy((IntPtr)buffer.planes[index],data,0,size);
	return data;
}

array<pxcmF32>^ PXCMImage::ImageData::ToFloatArray(pxcmI32 index, pxcI32 size) {
	if (type!=SurfaceType::SURFACE_TYPE_SYSTEM_MEMORY) return nullptr;
	array<pxcmF32>^ data=gcnew array<pxcmF32>(size);
	Marshal::Copy((IntPtr)buffer.planes[index],data,0,size);
	return data;
}

System::Drawing::Bitmap^ PXCMImage::ImageData::ToBitmap(pxcmI32 index, pxcmU32 width, pxcmU32 height) {
	if (type!=SurfaceType::SURFACE_TYPE_SYSTEM_MEMORY) return nullptr;

	System::Drawing::Bitmap ^bitmap=nullptr;
	switch (format) {
	case PXCMImage::ColorFormat::COLOR_FORMAT_RGB32:
		bitmap=gcnew System::Drawing::Bitmap(width,height,buffer.pitches[index],System::Drawing::Imaging::PixelFormat::Format32bppRgb,(IntPtr)buffer.planes[0]);
		break;
	case PXCMImage::ColorFormat::COLOR_FORMAT_RGB24:
		bitmap=gcnew System::Drawing::Bitmap(width,height,buffer.pitches[index],System::Drawing::Imaging::PixelFormat::Format24bppRgb,(IntPtr)buffer.planes[0]);
		break;
	case PXCMImage::ColorFormat::COLOR_FORMAT_DEPTH:
		bitmap=gcnew System::Drawing::Bitmap(width,height,buffer.pitches[index],System::Drawing::Imaging::PixelFormat::Format16bppGrayScale,(IntPtr)buffer.planes[index]);
		break;
	}
	return bitmap;
}

System::Windows::Media::Imaging::WriteableBitmap^ PXCMImage::ImageData::ToWritableBitmap(pxcmI32 index, pxcmU32 width, pxcmU32 height, pxcmF64 dpiX, pxcmF64 dpiY) {
	if (type!=SurfaceType::SURFACE_TYPE_SYSTEM_MEMORY) return nullptr;

	System::Windows::Media::Imaging::WriteableBitmap ^bitmap=nullptr;
	switch (format) {
	case PXCMImage::ColorFormat::COLOR_FORMAT_RGB32:
		bitmap=gcnew System::Windows::Media::Imaging::WriteableBitmap(width,height,dpiX,dpiY,System::Windows::Media::PixelFormats::Bgr32,nullptr);
		bitmap->WritePixels(System::Windows::Int32Rect(0,0,width,height),(IntPtr)buffer.planes[index],buffer.pitches[index]*height,buffer.pitches[index]);
		break;
	case PXCMImage::ColorFormat::COLOR_FORMAT_RGB24:
		bitmap=gcnew System::Windows::Media::Imaging::WriteableBitmap(width,height,dpiX,dpiY,System::Windows::Media::PixelFormats::Bgr24,nullptr);
		bitmap->WritePixels(System::Windows::Int32Rect(0,0,width,height),(IntPtr)buffer.planes[index],buffer.pitches[index]*height,buffer.pitches[index]);
		break;
	case PXCMImage::ColorFormat::COLOR_FORMAT_DEPTH:
		bitmap=gcnew System::Windows::Media::Imaging::WriteableBitmap(width,height,dpiX,dpiY,System::Windows::Media::PixelFormats::Gray16,nullptr);
		bitmap->WritePixels(System::Windows::Int32Rect(0,0,width,height),(IntPtr)buffer.planes[index],buffer.pitches[index]*height,buffer.pitches[index]);
		break;
	}
	return bitmap;
}

void PXCMImage::Dispose(array<PXCMImage^> ^images) {
	for each (PXCMImage^ m in images)
		if (m!=nullptr) delete m;
}

