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

#include "fsl_dac_hal.h"

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_Init
 * Description   : Reset all the configurable registers to be reset state for DAC.
 * It should be called before configuring the DAC module.
 *
 *END*************************************************************************/
void DAC_HAL_Init(uint32_t baseAddr)
{
    /* DACx_DATL and DACx_DATH */
    HW_DAC_DATnL_WR(baseAddr, 0U, 0U); HW_DAC_DATnH_WR(baseAddr, 0U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 1U, 0U); HW_DAC_DATnH_WR(baseAddr, 1U, 0U);
#if (HW_DAC_DATnL_COUNT > 2U)
    HW_DAC_DATnL_WR(baseAddr, 2U, 0U); HW_DAC_DATnH_WR(baseAddr, 2U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 3U, 0U); HW_DAC_DATnH_WR(baseAddr, 3U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 4U, 0U); HW_DAC_DATnH_WR(baseAddr, 4U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 5U, 0U); HW_DAC_DATnH_WR(baseAddr, 5U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 6U, 0U); HW_DAC_DATnH_WR(baseAddr, 6U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 7U, 0U); HW_DAC_DATnH_WR(baseAddr, 7U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 8U, 0U); HW_DAC_DATnH_WR(baseAddr, 8U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 9U, 0U); HW_DAC_DATnH_WR(baseAddr, 9U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 10U, 0U); HW_DAC_DATnH_WR(baseAddr, 10U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 11U, 0U); HW_DAC_DATnH_WR(baseAddr, 11U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 12U, 0U); HW_DAC_DATnH_WR(baseAddr, 12U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 13U, 0U); HW_DAC_DATnH_WR(baseAddr, 13U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 14U, 0U); HW_DAC_DATnH_WR(baseAddr, 14U, 0U);
    HW_DAC_DATnL_WR(baseAddr, 15U, 0U); HW_DAC_DATnH_WR(baseAddr, 15U, 0U);
#endif /* HW_DAC_DATnL_COUNT */
    /* DACx_SR. */
    HW_DAC_SR_WR(baseAddr, 0U); /* Clear all flags. */
    /* DACx_C0. */
    HW_DAC_C0_WR(baseAddr, 0U);
    /* DACx_C1. */
    HW_DAC_C1_WR(baseAddr, 0U);
    /* DACx_C2. */
    HW_DAC_C2_WR(baseAddr, 15U);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_SetBuffValue
 * Description   : Set the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in buffer.
 *
 *END*************************************************************************/
void DAC_HAL_SetBuffValue(uint32_t baseAddr, uint8_t index, uint16_t value)
{
    assert(index < HW_DAC_DATnL_COUNT);
    BW_DAC_DATnL_DATA0(baseAddr, index, (uint8_t)(0xFFU & value) );
    BW_DAC_DATnH_DATA1(baseAddr, index, (uint8_t)((0xF00U & value)>>8U) );
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_GetBuffValue
 * Description   : Get the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in buffer.
 *
 *END*************************************************************************/
uint16_t DAC_HAL_GetBuffValue(uint32_t baseAddr, uint8_t index)
{
    assert(index < HW_DAC_DATnL_COUNT);
    uint16_t ret16;
    ret16 = BR_DAC_DATnH_DATA1(baseAddr, index);
    ret16 <<= 8U;
    ret16 |= BR_DAC_DATnL_DATA0(baseAddr, index);
    return ret16;
}

/******************************************************************************
 * EOF
 *****************************************************************************/

