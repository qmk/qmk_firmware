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

#include "fsl_wdog_hal.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
 
/*FUNCTION**********************************************************************
 *
 * Function Name : WDOG_HAL_Init
 * Description   : Initialize WDOG peripheral to reset state.
 *
 *END**************************************************************************/
void WDOG_HAL_Init(uint32_t baseAddr)
{
    wdog_common_config wdogCommonConfig;
    wdogCommonConfig.commonConfig.workInWaitModeEnable = (uint8_t)true;
    wdogCommonConfig.commonConfig.workInDebugModeEnable = (uint8_t)false;
    wdogCommonConfig.commonConfig.workInStopModeEnable = (uint8_t)true;
    wdogCommonConfig.commonConfig.clockSource = (uint8_t)kWdogClockSourceBusClock;
    wdogCommonConfig.commonConfig.interruptEnable = (uint8_t)false;
    wdogCommonConfig.commonConfig.windowModeEnable = (uint8_t)false;
    wdogCommonConfig.commonConfig.updateRegisterEnable = (uint8_t)true; 
    wdogCommonConfig.commonConfig.wdogEnable = (uint8_t)(true);

    WDOG_HAL_Unlock(baseAddr);
    WDOG_HAL_SetTimeoutValue(baseAddr, 0x004C4B4CU);
    WDOG_HAL_SetWindowValue(baseAddr, 0);
    WDOG_HAL_SetClockPrescalerValueMode(baseAddr, kWdogClockPrescalerValueDevide5);
    WDOG_HAL_ClearIntFlag(baseAddr);
    WDOG_HAL_SetCommonConfig(baseAddr, wdogCommonConfig);

}

/*******************************************************************************
 * EOF
 *******************************************************************************/

