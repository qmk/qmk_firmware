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
 
#include "fsl_pit_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if FSL_FEATURE_PIT_HAS_LIFETIME_TIMER
/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_HAL_ReadLifetimeTimerCount
 * Description   : Read current lifefime counter value.
 * Lifetime timer is 64-bit timer which chains timer 0 and timer 1 together. 
 * So, timer 0 and 1 should by chained by calling PIT_HAL_SetTimerChainCmd
 * before using this timer. The period of lifetime timer equals to "period of
 * timer 0 * period of timer 1". For the 64-bit value, higher 32-bit will have
 * the value of timer 1, and lower 32-bit have the value of timer 0.
*
 *END**************************************************************************/
uint64_t PIT_HAL_ReadLifetimeTimerCount(uint32_t baseAddr)
{
    uint32_t valueH = 0U, valueL = 0U;
    
    /* LTMR64H should be read before LTMR64L */
    valueH = HW_PIT_LTMR64H_RD(baseAddr);
    valueL = HW_PIT_LTMR64L_RD(baseAddr);
    return (((uint64_t)valueH << 32U) + (uint64_t)(valueL));
}
#endif /* FSL_FEATURE_PIT_HAS_LIFETIME_TIMER*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

