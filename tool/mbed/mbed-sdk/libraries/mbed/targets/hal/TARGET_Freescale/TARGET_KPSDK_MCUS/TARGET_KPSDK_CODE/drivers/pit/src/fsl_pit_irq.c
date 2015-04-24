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

#include <stdlib.h>
#include <assert.h>
#include "fsl_pit_common.h"
#include "fsl_pit_driver.h"

/*!
 * @addtogroup pit_irq
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*!
 * @brief Function table to save PIT isr callback function pointers.
 *
 * Call PIT_DRV_InstallCallback to install isr callback functions.
 */
static pit_isr_callback_t pitIsrCallbackTable[HW_PIT_INSTANCE_COUNT][FSL_FEATURE_PIT_TIMER_COUNT] = {{NULL}};

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined (KL25Z4_SERIES)
/*!
 * @brief System default IRQ handler defined in startup code.
 *
 * Users can either edit this handler or define a callback function. Furthermore,
 * interrupt manager could be used to re-map the IRQ handler to another function.
 */
void PIT_IRQHandler(void)
{
    uint32_t i;
    for(i=0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        /* Clear interrupt flag.*/
        PIT_HAL_ClearIntFlag(g_pitBaseAddr[0], i);

        /* Run callback function if it exists.*/
        if (pitIsrCallbackTable[0][i])
        {
            (*pitIsrCallbackTable[0][i])();
        }
    }
}

#elif defined (K64F12_SERIES) || defined (K24F12_SERIES) || defined (K63F12_SERIES) || \
      defined (K22F12810_SERIES) || defined (K22F25612_SERIES) || defined (K22F51212_SERIES) || \
      defined (KV31F12810_SERIES) || defined (KV31F25612_SERIES) || defined (KV31F51212_SERIES) || \
      defined (K70F12_SERIES) 
void PIT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBaseAddr[0], 0U);

    /* Run callback function if it exists.*/
    if (pitIsrCallbackTable[0][0])
    {
        (*pitIsrCallbackTable[0][0])();
    }
}

void PIT1_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBaseAddr[0], 1U);

    /* Run callback function if it exists.*/
    if (pitIsrCallbackTable[0][1])
    {
        (*pitIsrCallbackTable[0][1])();
    }
}

void PIT2_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBaseAddr[0], 2U);

    /* Run callback function if it exists.*/
    if (pitIsrCallbackTable[0][2])
    {
        (*pitIsrCallbackTable[0][2])();
    }
}

void PIT3_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBaseAddr[0], 3U);

    /* Run callback function if it exists.*/
    if (pitIsrCallbackTable[0][3])
    {
        (*pitIsrCallbackTable[0][3])();
    }
}
#endif

/*! @} */

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_InstallCallback
 * Description   : Register pit isr callback function.
 * System default ISR interfaces are already defined in fsl_pit_irq.c. Users
 * can either edit these ISRs or use this function to register a callback
 * function. The default ISR will run the callback function it there is one
 * installed here.

 *END**************************************************************************/
void PIT_DRV_InstallCallback(uint32_t instance, uint32_t channel, pit_isr_callback_t function)
{
    assert(channel < FSL_FEATURE_PIT_TIMER_COUNT);
    assert(function != NULL);

    pitIsrCallbackTable[instance][channel] = function;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

