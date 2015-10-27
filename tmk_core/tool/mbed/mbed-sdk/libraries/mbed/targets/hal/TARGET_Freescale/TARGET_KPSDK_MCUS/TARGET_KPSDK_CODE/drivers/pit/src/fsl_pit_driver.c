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
 
#include "fsl_pit_common.h"
#include "fsl_pit_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* pit source clock variable which will be updated in PIT_DRV_Init. */
uint64_t pitSourceClock;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_Init
 * Description   : Initialize PIT module.
 * This function must be called before calling all the other PIT driver functions.
 * This function un-gates the PIT clock and enables the PIT module. The isRunInDebug
 * passed into function will affect all timer channels. 
 *
 *END**************************************************************************/
void PIT_DRV_Init(uint32_t instance, bool isRunInDebug)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];

    /* Un-gate pit clock*/
    CLOCK_SYS_EnablePitClock( 0U);

    /* Enable PIT module clock*/
    PIT_HAL_Enable(baseAddr);

    /* Set timer run or stop in debug mode*/
    PIT_HAL_SetTimerRunInDebugCmd(baseAddr, isRunInDebug);
   
    /* Finally, update pit source clock frequency.*/
    pitSourceClock  = CLOCK_SYS_GetPitFreq(0);    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_InitChannel
 * Description   : Initialize PIT channel.
 * This function initialize PIT timers by channel. Pass in timer number and its
 * config structure. Timers do not start counting by default after calling this
 * function. Function PIT_DRV_StartTimer must be called to start timer counting. 
 * Call PIT_DRV_SetTimerPeriodByUs to re-set the period.
 *
 *END**************************************************************************/
void PIT_DRV_InitChannel(uint32_t instance, uint32_t channel, const pit_user_config_t * config)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    /* Set timer period.*/
    PIT_DRV_SetTimerPeriodByUs(instance, channel, config->periodUs);

    #if FSL_FEATURE_PIT_HAS_CHAIN_MODE
    /* Configure timer chained or not.*/
    PIT_HAL_SetTimerChainCmd(baseAddr, channel, config->isTimerChained);
    #endif

    /* Enable or disable interrupt.*/
    PIT_HAL_SetIntCmd(baseAddr, channel, config->isInterruptEnabled);

    /* Configure NVIC*/
    if (config->isInterruptEnabled)
    {
        /* Enable PIT interrupt.*/
        INT_SYS_EnableIRQ(g_pitIrqId[channel]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_Deinit 
 * Description   : Disable PIT module and gate control
 * This function will disable all PIT interrupts and PIT clock. Then gate the
 * PIT clock control. pit_init must be called in order to use PIT again.
 * 
 *END**************************************************************************/
void PIT_DRV_Deinit(uint32_t instance)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    uint32_t i;

    /* Disable all PIT interrupts. */
    for (i=0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        PIT_HAL_SetIntCmd(baseAddr, i, false);
        INT_SYS_DisableIRQ(g_pitIrqId[i]);
    }

    /* Disable PIT module clock*/
    PIT_HAL_Disable(baseAddr);

    /* Gate PIT clock control*/
    CLOCK_SYS_DisablePitClock( 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_StartTimer
 * Description   : Start timer counting.
 * After calling this function, timers load period value, count down to 0 and
 * then load the respective start value again. Each time a timer reaches 0,
 * it will generate a trigger pulse and set the timeout interrupt flag.
 * 
 *END**************************************************************************/
void PIT_DRV_StartTimer(uint32_t instance, uint32_t channel)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    PIT_HAL_StartTimer(baseAddr, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_StopTimer
 * Description   : Stop timer counting.
 * This function will stop every timer counting. Timers will reload their periods
 * respectively after calling PIT_DRV_StartTimer next time.
 *
 *END**************************************************************************/
void PIT_DRV_StopTimer(uint32_t instance, uint32_t channel)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    PIT_HAL_StopTimer(baseAddr, channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_SetTimerPeriodByUs
 * Description   : Set timer period in microseconds unit.
 * The period range depends on the frequency of PIT source clock. If required
 * period is out the range, try to use lifetime timer if applicable. 
 *
 *END**************************************************************************/
void PIT_DRV_SetTimerPeriodByUs(uint32_t instance, uint32_t channel, uint32_t us)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    /* Calculate the count value, assign it to timer counter register.*/
    uint32_t count = (uint32_t)(us * pitSourceClock / 1000000U - 1U);
    PIT_HAL_SetTimerPeriodByCount(baseAddr, channel, count);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ReadTimerUs
 * Description   : Read current timer value in microseconds unit.
 * This function will return an absolute time stamp in the unit of microseconds.
 * One common use of this function is to measure the running time of part of
 * code. Just call this function at both the beginning and end of code, the time
 * difference between these two time stamp will be the running time (Need to 
 * make sure the running time will not exceed the timer period). Also, the time
 * stamp returned is up-counting.
 *
 *END**************************************************************************/
uint32_t PIT_DRV_ReadTimerUs(uint32_t instance, uint32_t channel)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    /* Get current timer count, and reverse it to up-counting.*/
    uint64_t currentTime = (~PIT_HAL_ReadTimerCount(baseAddr, channel));

    /* Convert count numbers to microseconds unit.*/
    currentTime = (currentTime * 1000000U) / pitSourceClock;
    return (uint32_t)currentTime;
}

#if FSL_FEATURE_PIT_HAS_LIFETIME_TIMER
/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_SetLifetimeTimerPeriodByUs
 * Description   : Set lifetime timer period (Timers must be chained).
 * Timer 1 must be chained with timer 0 before using lifetime timer. The period
 * range is restricted by "period * pitSourceClock < max of an uint64_t integer",
 * or it may cause a overflow and is not able to set correct period.
 *
 *END**************************************************************************/
void PIT_DRV_SetLifetimeTimerPeriodByUs(uint32_t instance, uint64_t us)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    uint64_t lifeTimeCount;
    
    /* Calculate the counter value.*/
    lifeTimeCount = us * pitSourceClock / 1000000U - 1U;

    /* Assign to timers.*/
    PIT_HAL_SetTimerPeriodByCount(baseAddr, 0U, (uint32_t)lifeTimeCount);
    PIT_HAL_SetTimerPeriodByCount(baseAddr, 1U, (uint32_t)(lifeTimeCount >> 32U));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PIT_DRV_ReadLifetimeTimerUs
 * Description   : Read current lifetime value in microseconds unit.
 * Return an absolute time stamp in the unit of microseconds. The time stamp 
 * value will not exceed the timer period. Also, the timer is up-counting.
 *
 *END**************************************************************************/
uint64_t PIT_DRV_ReadLifetimeTimerUs(uint32_t instance)
{
    assert(instance < HW_PIT_INSTANCE_COUNT);

    uint32_t baseAddr = g_pitBaseAddr[instance];
    /* Get current lifetime timer count, and reverse it to up-counting.*/
    uint64_t currentTime = (~PIT_HAL_ReadLifetimeTimerCount(baseAddr));

    /* Convert count numbers to microseconds unit.*/
    /* Note: using currentTime * 1000 rather than 1000000 to avoid short time overflow. */
    return currentTime = (currentTime * 1000U) / (pitSourceClock / 1000U);
}
#endif /* FSL_FEATURE_PIT_HAS_LIFETIME_TIMER*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

