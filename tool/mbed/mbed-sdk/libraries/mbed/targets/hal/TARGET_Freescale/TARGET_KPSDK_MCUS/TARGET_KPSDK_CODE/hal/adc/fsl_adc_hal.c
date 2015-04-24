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

#include "fsl_adc_hal.h"

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC_HAL_Init
 * Description   :Reset all the registers into a known state for ADC
 * module. This known state is the default value indicated by the Reference
 * manual. It is strongly recommended to call this API before any operations
 * when initializing the ADC module. Note registers for calibration would not
 * be cleared in this function.
 *
 *END*************************************************************************/
void ADC_HAL_Init(uint32_t baseAddr)
{
    HW_ADC_CFG1_WR(baseAddr, 0U);
    HW_ADC_CFG2_WR(baseAddr, 0U);
    HW_ADC_CV1_WR(baseAddr, 0U);
    HW_ADC_CV2_WR(baseAddr, 0U);
    HW_ADC_SC2_WR(baseAddr, 0U);
    HW_ADC_SC3_WR(baseAddr, 0U);
#if FSL_FEATURE_ADC_HAS_PGA
    HW_ADC_PGA_WR(baseAddr, 0U);
#endif /* FSL_FEATURE_ADC_HAS_PGA */
}

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC_HAL_SetHwCmpMode
 * Description   :Set the asserted compare range when enabling hardware
 * compare function. About the selection of range mode, see to the description
 * for "adc_hw_cmp_range_mode_t".
 *
 *END*************************************************************************/
void ADC_HAL_SetHwCmpMode(uint32_t baseAddr, adc_hw_cmp_range_mode_t mode)
{
    switch (mode)
    {
    case kAdcHwCmpRangeModeOf1:
        ADC_HAL_SetHwCmpGreaterCmd(baseAddr, false);
        ADC_HAL_SetHwCmpRangeCmd(baseAddr, false);
        break;
    case kAdcHwCmpRangeModeOf2:
        ADC_HAL_SetHwCmpGreaterCmd(baseAddr, true);
        ADC_HAL_SetHwCmpRangeCmd(baseAddr, false);
        break;
    case kAdcHwCmpRangeModeOf3:
        ADC_HAL_SetHwCmpGreaterCmd(baseAddr, false);
        ADC_HAL_SetHwCmpRangeCmd(baseAddr, true);
        break;
    case kAdcHwCmpRangeModeOf4:
        ADC_HAL_SetHwCmpGreaterCmd(baseAddr, true);
        ADC_HAL_SetHwCmpRangeCmd(baseAddr, true);
        break;
    default:
        break;
    }
}

#if FSL_FEATURE_ADC_HAS_CALIBRATION

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC_HAL_GetAutoPlusSideGainValue 
 * Description   :  Get the values of CLP0 - CLP4 and CLPS internally,
 * accumulate them, and return the value that can be used to be set in PG
 * register directly. Note that this API should be called after the process of
 * auto calibration has been done.
 *
 *END*************************************************************************/
uint16_t ADC_HAL_GetAutoPlusSideGainValue(uint32_t baseAddr)
{
    uint16_t cal_var;

    /* Calculate plus-side calibration */
    cal_var = 0U;
    cal_var += BR_ADC_CLP0_CLP0(baseAddr);
    cal_var += BR_ADC_CLP1_CLP1(baseAddr);
    cal_var += BR_ADC_CLP2_CLP2(baseAddr);
    cal_var += BR_ADC_CLP3_CLP3(baseAddr);
    cal_var += BR_ADC_CLP4_CLP4(baseAddr);
    cal_var += BR_ADC_CLPS_CLPS(baseAddr);
    cal_var = 0x8000U | (cal_var>>1U);

    return cal_var;
}

#if FSL_FEATURE_ADC_HAS_DIFF_MODE

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC_HAL_GetAutoMinusSideGainValue 
 * Description   : Get the values of CLM0 - CLM4 and CLMS internally,
 * accumulate them, and return the value that can be used to be set in MG
 * register directly. Note that this API should be called after the process of
 * auto calibration has been done.
 *
 *END*************************************************************************/
uint16_t ADC_HAL_GetAutoMinusSideGainValue(uint32_t baseAddr)
{
    uint16_t cal_var;

    /* Calculate minus-side calibration */
    cal_var = 0U;
    cal_var += BR_ADC_CLM0_CLM0(baseAddr);
    cal_var += BR_ADC_CLM1_CLM1(baseAddr);
    cal_var += BR_ADC_CLM2_CLM2(baseAddr);
    cal_var += BR_ADC_CLM3_CLM3(baseAddr);
    cal_var += BR_ADC_CLM4_CLM4(baseAddr);
    cal_var += BR_ADC_CLMS_CLMS(baseAddr);
    cal_var = 0x8000U | (cal_var>>1U);

    return cal_var;
}

#endif /* FSL_FEATURE_ADC_HAS_DIFF_MODE */

#endif /* FSL_FEATURE_ADC_HAS_CALIBRATION */

/******************************************************************************
 * EOF
 *****************************************************************************/

