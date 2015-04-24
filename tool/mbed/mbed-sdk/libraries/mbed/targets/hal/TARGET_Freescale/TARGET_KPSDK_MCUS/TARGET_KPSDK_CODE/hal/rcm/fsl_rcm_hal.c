/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_rcm_hal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : RCM_HAL_GetSrcStatusCmd
 * Description   : Get the reset source status
 * 
 * This function will get the current reset source status for specified source
 *
 *END**************************************************************************/
bool RCM_HAL_GetSrcStatusCmd(uint32_t baseAddr, rcm_source_names_t srcName)
{
    bool retValue = false;

    assert(srcName < kRcmSrcNameMax);

    switch (srcName)
    {
    case kRcmWakeup:                     /* low-leakage wakeup reset */
        retValue = (bool)BR_RCM_SRS0_WAKEUP(baseAddr);
        break;
    case kRcmLowVoltDetect:              /* low voltage detect reset */
        retValue = (bool)BR_RCM_SRS0_LVD(baseAddr);
        break;
    case kRcmLossOfClk:                  /* loss of clock reset */
        retValue = (bool)BR_RCM_SRS0_LOC(baseAddr);
        break;
#if FSL_FEATURE_RCM_HAS_LOL
    case kRcmLossOfLock:                 /* loss of lock reset */
        retValue = (bool)BR_RCM_SRS0_LOL(baseAddr);
        break;
#endif
    case kRcmWatchDog:                   /* watch dog reset */
        retValue = (bool)BR_RCM_SRS0_WDOG(baseAddr);
        break;
    case kRcmExternalPin:                /* external pin reset */
        retValue = (bool)BR_RCM_SRS0_PIN(baseAddr);
        break;
    case kRcmPowerOn:                    /* power on reset */
        retValue = (bool)BR_RCM_SRS0_POR(baseAddr);
        break;
    case kRcmJtag:                       /* JTAG generated reset */
        retValue = (bool)BR_RCM_SRS1_JTAG(baseAddr);
        break;
    case kRcmCoreLockup:                 /* core lockup reset */
        retValue = (bool)BR_RCM_SRS1_LOCKUP(baseAddr);
        break;
    case kRcmSoftware:                   /* software reset */
        retValue = (bool)BR_RCM_SRS1_SW(baseAddr);
        break;
    case kRcmSystem:                     /* system reset request bit set reset */
        retValue = (bool)BR_RCM_SRS1_MDM_AP(baseAddr);
        break;
    case kRcmEzport:                     /* EzPort reset */
        retValue = (bool)BR_RCM_SRS1_EZPT(baseAddr);
        break;
    case kRcmStopModeAckErr:             /* stop mode ack error reset */
        retValue = (bool)BR_RCM_SRS1_SACKERR(baseAddr);
        break;
    default:
        retValue = false;
        break;
    }

    return retValue;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

