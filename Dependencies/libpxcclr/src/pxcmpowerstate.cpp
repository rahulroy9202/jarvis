/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#include "pxcmpowerstate.h"

pxcmStatus PXCMPowerState::QueryState([Out] State %state, [Out] State %istate) {
    PXCPowerState::State state2, istate2;
    pxcStatus sts=QueryInstance()->QueryState(&state2, &istate2);
    state=(State)state2;
    istate=(State)istate2;
    return (pxcmStatus)sts;
}

pxcmStatus PXCMPowerState::SetState(State state) {
    return (pxcmStatus)QueryInstance()->SetState((PXCPowerState::State)state);
}
