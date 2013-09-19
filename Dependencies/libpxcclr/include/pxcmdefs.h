/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

using namespace System;

typedef Int16               pxcmI16;
typedef Int32               pxcmUID;
typedef Int32               pxcmI32;
typedef UInt32              pxcmU32;
typedef UInt64              pxcmU64;
typedef UInt16              pxcmU16;
typedef Byte                pxcmU8;
typedef Byte                pxcmBYTE;
typedef Int32               pxcmEnum;
typedef Boolean             pxcmBool;
typedef Int32               pxcmOption;
typedef IntPtr              pxcmHDL;
typedef Single              pxcmF32;
typedef Double				pxcmF64;

public value struct PXCMRectU32 {
    pxcmU32 x, y, w, h;
};

public value struct PXCMSizeU32 {
    pxcmU32 width, height;
};

public value struct PXCMRatioF32 {
    pxcmF32 denominator;
    pxcmF32 numerator;
};

public value struct PXCMRatioU32 {
    pxcmU32 denominator;
    pxcmU32 numerator;
};

public value struct PXCMPointF32 {
    pxcmF32 x, y;
};

public value struct PXCMPointU32 {
    pxcmU32 x, y;
};

public value struct PXCMRangeU32 {
    pxcmU32 min, max;
};

public value struct PXCMRangeI32 {
    pxcmI32 min, max;
};

public value struct PXCMRangeF32 {
    pxcmF32 min, max;
};

public value struct PXCMPoint3DF32 {
    pxcmF32 x, y, z;
};

#define PXCM_UID(X1,X2,X3,X4) ((pxcmUID)(((pxcmU32)(X4)<<24)+((pxcmU32)(X3)<<16)+((pxcmU32)(X2)<<8)+(pxcmU32)(X1)))
#define PXCM_DEFINE_CONST(Y,X) static const pxcmUID Y=X
#define PXCM_DEFINE_UID(Y,X1,X2,X3,X4) PXCM_DEFINE_CONST(Y,PXCM_UID(X1,X2,X3,X4))

template<typename T, int itemSize, int size>
    [Runtime::CompilerServices::UnsafeValueType]
    [StructLayout(LayoutKind::Explicit,Size=(itemSize*size))]
    public value struct PXCMArray {
    private: [FieldOffset(0)] T dummy;
    public:  
        property T default[pxcmI32] {
            T get(pxcmI32 index) { return *((&dummy)+index); }
            void set(pxcmI32 index, T x) { *((&dummy)+index)=x; }
        };
    };

template<int size>
    [Runtime::CompilerServices::UnsafeValueType]
    [StructLayout(LayoutKind::Explicit,Size=(sizeof(Char)*size))]
    public value struct PXCMString {
    private:
        [FieldOffset(0)] Char dummy;
    public:

        String ^get(void) { 
            *(&dummy+size-1)=0;
            pin_ptr<Char> pp(&dummy);
            return gcnew String((Char*)pp); 
        }

        void set(String ^str) {
            int nchars=str->Length;
            IntPtr buffer=Marshal::StringToBSTR(str);
            pin_ptr<Char> pp(&dummy);
            wcscpy_s((pxcCHAR*)pp,size,(pxcCHAR*)buffer.ToPointer());
            Marshal::FreeBSTR(buffer);
            *((pxcCHAR*)pp+((nchars<size)?nchars:size-1))=0;
        }
    };

