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

#include "fsl_lptmr_hal.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*******************************************************************************
 * EOF
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_HAL_Init
 * Description   : Initialize LPTMR module to reset state.
 *
 *END**************************************************************************/
void LPTMR_HAL_Init(uint32_t baseAddr)
{
    LPTMR_HAL_Disable(baseAddr);
    LPTMR_HAL_ClearIntFlag(baseAddr);
    LPTMR_HAL_SetIntCmd(baseAddr, false);
    LPTMR_HAL_SetPinSelectMode(baseAddr, kLptmrPinSelectCmpOut);
    LPTMR_HAL_SetPinPolarityMode(baseAddr, kLptmrPinPolarityActiveHigh);
    LPTMR_HAL_SetFreeRunningCmd(baseAddr, false);
    LPTMR_HAL_SetTimerModeMode(baseAddr, kLptmrTimerModeTimeCounter);
    LPTMR_HAL_SetPrescalerCmd(baseAddr, false);
    LPTMR_HAL_SetPrescalerValueMode(baseAddr, kLptmrPrescalerDivide2);
    LPTMR_HAL_SetPrescalerClockSourceMode(baseAddr, kLptmrPrescalerClockSourceMcgIrcClk);
    LPTMR_HAL_SetCompareValue(baseAddr, 0x0);
}
