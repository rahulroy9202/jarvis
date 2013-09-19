/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcmsession.h"
#include "pxcpowerstate.h"

public ref class PXCMPowerState: public PXCMBase {
public:

    PXCM_CUID_OVERWRITE(PXCPowerState::CUID);

    enum class State: pxcmEnum {
        STATE_ADAPTIVE=0,
        STATE_C0,             /* full feature set/best algorithm */
        STATE_C1,             /* reduced feature set/simplied algorithm */
        STATE_C2,             /* additional reduced feature set/simplied algorithm */
        STATE_C3,             /* idle */
    };

	virtual property State state {
		State get(void) { State s1,s2; QueryState(s1,s2); return s1; }
		void  set(State s) { SetState(s); }
	};

	virtual property State istate {
		State get(void) { State s1,s2; QueryState(s1,s2); return s2; }
	};

    virtual pxcmStatus QueryState([Out] State %state, [Out] State %istate);
    virtual pxcmStatus SetState(State state);

internal:

    PXCMPowerState(PXCBase *instance,bool b_delete):PXCMBase(instance,b_delete) {}
    PXCPowerState *QueryInstance(void) { return (PXCPowerState*)m_instance; }
};
