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
#include "pxcmsession.h"
#include "pxccapture.h"

public ref class PXCMCapture:public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCCapture::CUID);

    [StructLayout(LayoutKind::Explicit)]
    value struct DeviceInfo {
        [FieldOffset(0)]    PXCMString<256> name;               /* device name */
        [FieldOffset(512)]  PXCMString<256> did;                /* device identifier */
        [FieldOffset(1024)] pxcmU32         didx;               /* device index */
        [FieldOffset(1028)] pxcmEnum        options;            /* additional options */
        [FieldOffset(1032)] PXCMArray<pxcmU32,sizeof(pxcmU32),6> reserved;
    };

    ref class Device : public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCCapture::Device::CUID);
        PXCM_DEFINE_CONST(DEVCAP_LIMIT,120);

        value struct StreamInfo {
            pxcmU32                 sidx;
            pxcmUID                 cuid;
            PXCMImage::ImageType    imageType;
            PXCMArray<pxcmU32,sizeof(pxcmU32),5> reserved;
        };

        enum class Property: pxcmEnum {
            /* Single value properties */
            PROPERTY_COLOR_EXPOSURE             =   1,
            PROPERTY_COLOR_BRIGHTNESS           =   2,
            PROPERTY_COLOR_CONTRAST             =   3,
            PROPERTY_COLOR_SATURATION           =   4,
            PROPERTY_COLOR_HUE                  =   5,
            PROPERTY_COLOR_GAMMA                =   6,
            PROPERTY_COLOR_WHITE_BALANCE        =   7,
            PROPERTY_COLOR_SHARPNESS            =   8,
            PROPERTY_COLOR_BACK_LIGHT_COMPENSATION  =   9,
            PROPERTY_COLOR_GAIN                     =   10,
            PROPERTY_AUDIO_MIX_LEVEL            =   100,
 
			PROPERTY_DEPTH_SATURATION_VALUE		=   200,
			PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE	=   201,
            PROPERTY_DEPTH_CONFIDENCE_THRESHOLD =   202,
            PROPERTY_DEPTH_SMOOTHING            =   203,

            /* Two value properties */
            PROPERTY_COLOR_FIELD_OF_VIEW        =   1000,
            PROPERTY_COLOR_SENSOR_RANGE         =   1002,
            PROPERTY_COLOR_FOCAL_LENGTH         =   1006,
            PROPERTY_COLOR_PRINCIPAL_POINT      =   1008,

            PROPERTY_DEPTH_FIELD_OF_VIEW        =   2000,
            PROPERTY_DEPTH_SENSOR_RANGE         =   2002,
            PROPERTY_DEPTH_FOCAL_LENGTH         =   2006,
            PROPERTY_DEPTH_PRINCIPAL_POINT      =   2008,

            /* Misc. */
            PROPERTY_ACCELEROMETER_READING      =   3000,   // three values
            PROPERTY_PROJECTION_SERIALIZABLE    =   3003,

            /* Customized properties */
            PROPERTY_CUSTOMIZED=0x04000000,
        };

        value struct DeviceCap {
            Property    label;
            pxcmF32     value;
        };

        virtual pxcmStatus QueryDevice([Out] DeviceInfo %dinfo);
        virtual pxcmStatus QueryStream(pxcmU32 sidx, [Out] StreamInfo %sinfo);
        virtual pxcmStatus CreateStream(pxcmU32 sidx, pxcmUID cuid, [Out] PXCMBase ^%stream);
		generic<typename TT> where TT:PXCMBase pxcmStatus CreateStream(pxcmU32 sidx, pxcmUID cuid, [Out] TT %stream) { PXCMBase^t;pxcmStatus s=CreateStream(sidx,cuid,t);stream=(TT)t;return s; }

        virtual pxcmStatus QueryPropertyInfo(Property pty, [Out] PXCMRangeF32 %range, [Out] pxcmF32 %step, [Out] pxcmF32 %def, [Out] pxcmBool %isAuto);
        virtual pxcmStatus QueryProperty(Property pty, [Out] pxcmF32 %value);
        virtual pxcmStatus QueryPropertyAsUID(Property ptr, [Out] pxcmUID %value);
        virtual pxcmStatus QueryPropertyAsPoint(Property pty, [Out] PXCMPointF32 %point);
        virtual pxcmStatus QueryPropertyAs3DPoint(Property pty, [Out] PXCMPoint3DF32 %point);
        virtual pxcmStatus QueryPropertyAsRange(Property pty, [Out] PXCMRangeF32 %range);

        virtual pxcmStatus SetPropertyAuto(Property pty, pxcmBool ifauto);
        virtual pxcmStatus SetProperty(Property pty, pxcmF32 value);

    internal:

        Device(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCCapture::Device *QueryInstance(void) { return (PXCCapture::Device*)m_instance; }
    };

    ref class VideoStream : public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCCapture::VideoStream::CUID);
        PXCM_DEFINE_CONST(STREAM_LIMIT,4);

        value struct ProfileInfo {
            PXCMImage::ImageInfo    imageInfo;
            PXCMRatioU32            frameRateMin;
            PXCMRatioU32            frameRateMax;
            PXCMImage::ImageOption  imageOptions;   // image creation options
            PXCMArray<pxcmU32,sizeof(pxcmU32),8> reserved;
        };

        value struct DataDesc {
            value struct StreamDesc {
                PXCMSizeU32             sizeMin;
                PXCMSizeU32             sizeMax;
                PXCMImage::ColorFormat  format;
                PXCMImage::ImageOption  options;
                PXCMArray<pxcmU32,sizeof(pxcmU32),10> reserved;
            };
            PXCMArray<StreamDesc,sizeof(PXCCapture::VideoStream::DataDesc::StreamDesc),STREAM_LIMIT> streams;
            PXCMArray<Device::DeviceCap,sizeof(PXCCapture::Device::DeviceCap),Device::DEVCAP_LIMIT>  devCaps;
            PXCMArray<pxcmU32,sizeof(pxcmU32),16> reserved;
        };

        virtual pxcmStatus QueryStream([Out] Device::StreamInfo %sinfo);
        virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %pinfo);
        virtual pxcmStatus QueryProfile([Out] ProfileInfo %pinfo);
        virtual pxcmStatus SetProfile(ProfileInfo %pinfo);
        virtual pxcmStatus ReadStreamAsync([Out] PXCMImage ^%image, [Out] PXCMScheduler::SyncPoint ^%sp);

    internal:

        VideoStream(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {} 
        PXCCapture::VideoStream *QueryInstance(void) { return (PXCCapture::VideoStream*)m_instance; }
    };

    ref class AudioStream : public PXCMBase {
    public:

        PXCM_CUID_OVERWRITE(PXCCapture::AudioStream::CUID);

        value struct ProfileInfo {
            PXCMAudio::AudioInfo    audioInfo;
            pxcmOption              audioOptions;
            PXCMArray<pxcmU32,sizeof(pxcmU32),7> reserved;
        };

        value struct DataDesc {
            PXCMAudio::AudioInfo    info;
            PXCMAudio::AudioOption  options;
            PXCMArray<pxcmU32,sizeof(pxcmU32),7+128*2> reserved;
        };

        virtual pxcmStatus QueryStream([Out] Device::StreamInfo %sinfo);
        virtual pxcmStatus QueryProfile(pxcmU32 pidx, [Out] ProfileInfo %profile);
        virtual pxcmStatus QueryProfile([Out] ProfileInfo %profile);
        virtual pxcmStatus SetProfile(ProfileInfo %profile);
        virtual pxcmStatus ReadStreamAsync([Out] PXCMAudio ^%audio, [Out] PXCMScheduler::SyncPoint ^%sp);

    internal:

        AudioStream(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
        PXCCapture::AudioStream *QueryInstance(void) { return (PXCCapture::AudioStream*)m_instance; }
    };

    virtual pxcmStatus QueryDevice(pxcmU32 didx, [Out] DeviceInfo %dinfo);
    virtual pxcmStatus CreateDevice(pxcmU32 didx, [Out] Device ^%device);

internal:

    PXCMCapture(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCCapture *QueryInstance(void) { return (PXCCapture*)m_instance; }
};
