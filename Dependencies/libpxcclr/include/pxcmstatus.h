/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

using namespace System;

public enum class pxcmStatus: Int32 {
    PXCM_STATUS_NO_ERROR=0,

    /* errors */
    PXCM_STATUS_FEATURE_UNSUPPORTED=     -1,     /* Unsupported feature */
    PXCM_STATUS_PARAM_UNSUPPORTED=       -2,     /* Unsupported parameter(s) */
    PXCM_STATUS_ITEM_UNAVAILABLE=        -3,     /* Item not found/not available */

    PXCM_STATUS_HANDLE_INVALID=          -101,   /* Invalid session, algorithm instance, or pointer */
    PXCM_STATUS_ALLOC_FAILED=            -102,   /* Memory allocation failure */

    PXCM_STATUS_DEVICE_FAILED=           -201,   /* Acceleration device failed/lost */
    PXCM_STATUS_DEVICE_LOST=             -202,   /* Acceleration device lost */
    PXCM_STATUS_DEVICE_BUSY=             -203,   /* Acceleration device busy */

    PXCM_STATUS_EXEC_ABORTED=            -301,   /* Execution aborted due to errors in upstream components */
    PXCM_STATUS_EXEC_INPROGRESS=         -302,   /* Asynchronous operation is in execution */
    PXCM_STATUS_EXEC_TIMEOUT=            -303,   /* Operation time out */

    /* warnings */
    PXCM_STATUS_TIME_GAP=                101,    /* time gap in time stamps */
    PXCM_STATUS_PARAM_INPLACE=           102,    /* the same parameters already defined */
};

