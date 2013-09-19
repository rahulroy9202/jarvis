/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmbase.h"
#include "pxcaudio.h"

ref class PXCMAccelerator;
public ref class PXCMAudio: public PXCMBase {
public:
    PXCM_CUID_OVERWRITE(PXCAudio::CUID);
    
    enum class AudioFormat: pxcmEnum {
        AUDIO_FORMAT_PCM        = PXC_UID(16,'P','C','M'),  // 16-bit PCM
        AUDIO_FORMAT_IEEE_FLOAT = PXC_UID(32,'F','L','T'),  // 32-bit float
        AUDIO_FORMAT_SIZE_MASK  = 0xff
    };

    [Flags] enum class ChannelMask: pxcmEnum {
        CHANNEL_MASK_FRONT_LEFT     =0x00000001,
        CHANNEL_MASK_FRONT_RIGHT    =0x00000002,
        CHANNEL_MASK_FRONT_CENTER   =0x00000004,
        CHANNEL_MASK_LOW_FREQUENCY  =0x00000008,
        CHANNEL_MASK_BACK_LEFT      =0x00000010,
        CHANNEL_MASK_BACK_RIGHT     =0x00000020,
        CHANNEL_MASK_SIDE_LEFT      =0x00000200,
        CHANNEL_MASK_SIDE_RIGHT     =0x00000400,
    };

    value struct AudioInfo {
        pxcmU32     bufferSize;
        AudioFormat format;
        pxcmU32     sampleRate;
        pxcmU32     nchannels;
        ChannelMask channelMask;
        PXCMArray<pxcmU32,sizeof(pxcmU32),3> reserved;
    };

    [Flags] enum class AudioOption: pxcmOption {
    };

    [Flags] enum class SurfaceType: pxcmEnum {
        SURFACE_TYPE_SYSTEM_MEMORY   =   0x00000001,
        SURFACE_TYPE_DX9_SURFACE     =   0x00000002,
    };

    [StructLayout(LayoutKind::Explicit)]
    value struct AudioBuffer {
        [FieldOffset(0)] pxcmHDL    dataPtr;
        [FieldOffset(0)] pxcmHDL    surfaceHandle;

        property pxcmF32 F32[pxcmI32] {
            pxcmF32 get(pxcmI32 i) { return (pxcmF32)(*((pxcF32*)dataPtr.ToPointer()+i)); }
            void    set(pxcmI32 i, pxcmF32 v) { *((pxcF32*)dataPtr.ToPointer()+i)=(pxcF32)v; }
        };

        property pxcmI16 I16[pxcmI32] {
            pxcmI16 get(pxcmI32 i) { return (pxcmI16)(*((pxcI16*)dataPtr.ToPointer()+i)); }
            void    set(pxcmI32 i, pxcmI16 v) { *((pxcI16*)dataPtr.ToPointer()+i)=(pxcI16)v; }
        };

        property pxcmBYTE BYTE[pxcmI32] {
            pxcmBYTE get(pxcmI32 i) { return (pxcmBYTE)(*((pxcBYTE*)dataPtr.ToPointer()+i)); }
            void     set(pxcmI32 i, pxcmBYTE v) { *((pxcBYTE*)dataPtr.ToPointer()+i)=(pxcBYTE)v; }
        };
    };

    value struct AudioData {
        AudioFormat   format;
        SurfaceType   type;
        pxcmU32       dataSize;
        pxcmU32       reserved;
        AudioBuffer   buffer;

        array<pxcmBYTE>^ ToByteArray(void);
    };

    [Flags] enum class Access: pxcmEnum {
        ACCESS_READ         = 1,
        ACCESS_WRITE        = 2,
        ACCESS_READ_WRITE   = ACCESS_READ | ACCESS_WRITE,
    };

    /* Query functions */
    virtual property AudioInfo audioInfo {
		AudioInfo   get(void) { AudioInfo info; QueryInfo(info); return info; }
    };
	virtual pxcmStatus QueryInfo([Out] AudioInfo %info);

    virtual property AudioOption options {
		AudioOption get(void) { return QueryOption(); }
		void        set(AudioOption flags) { SetOption(flags); }
    };
	virtual AudioOption QueryOption(void);
	virtual pxcmStatus  SetOption(AudioOption option);

    virtual property pxcmU64 timeStamp {
		pxcmU64     get(void) { return QueryTimeStamp(); }
		void        set(pxcmU64 ts) { SetTimeStamp(ts); }
    };
	virtual pxcmU64    QueryTimeStamp(void);
	virtual pxcmStatus SetTimeStamp(pxcmU64);

    /* Copy data from another audio */
    virtual pxcmStatus  CopyData(PXCMAudio ^src_audio);

    /* Functions expose the internal buffer storage */ 
    virtual pxcmStatus  AcquireAccess(Access access, PXCMAccelerator ^accelerator, AudioFormat format, [Out] AudioData %data);
    virtual pxcmStatus  AcquireAccess(Access access, PXCMAccelerator ^accelerator, [Out] AudioData %data);
    virtual pxcmStatus  AcquireAccess(Access access, AudioFormat format, [Out] AudioData %data);
    virtual pxcmStatus  AcquireAccess(Access access, [Out] AudioData %data);
    virtual pxcmStatus  TryAccess(Access access, PXCMAccelerator ^accelerator, AudioFormat format, [Out] AudioData %data);
    virtual pxcmStatus  TryAccess(Access access, PXCMAccelerator ^accelerator, [Out] AudioData %data);
    virtual pxcmStatus  TryAccess(Access access, AudioFormat format, [Out] AudioData %data);
    virtual pxcmStatus  TryAccess(Access access, [Out] AudioData %data);
    virtual pxcmStatus  ReleaseAccess(AudioData %data);

internal:

    PXCMAudio(PXCBase *instance, bool b_delete):PXCMBase(instance,b_delete) {}
    PXCAudio *QueryInstance(void) { return (PXCAudio*)m_instance; }
};
