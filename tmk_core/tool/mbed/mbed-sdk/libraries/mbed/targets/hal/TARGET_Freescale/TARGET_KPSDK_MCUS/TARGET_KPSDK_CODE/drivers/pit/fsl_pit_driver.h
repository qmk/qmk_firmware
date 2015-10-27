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
#ifndef __FSL_PIT_DRIVER_H__
#define __FSL_PIT_DRIVER_H__
 
#include <stdint.h>
#include <stdbool.h>
#include "fsl_pit_hal.h"
 
/*!
 * @addtogroup pit_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief PIT timer configuration structure
 *
 * Define structure PitConfig and use the PIT_DRV_InitChannel() function to make necessary
 * initializations. You may also use the remaining functions for PIT configuration.
 *
 * @note The timer chain feature is not valid in all devices. Check the 
 * fsl_pit_features.h for accurate settings. If it's not valid, the value set here
 * will be bypassed inside the PIT_DRV_InitChannel() function. 
 */
typedef struct PitUserConfig {
    bool isInterruptEnabled;  /*!< Timer interrupt 0-disable/1-enable*/
    bool isTimerChained;      /*!< Chained with previous timer, 0-not/1-chained*/
    uint32_t periodUs;        /*!< Timer period in unit of microseconds*/
} pit_user_config_t;

/*! @brief PIT ISR callback function typedef */
typedef void (*pit_isr_callback_t)(void);

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialize and Shutdown
 * @{
 */

/*!
 * @brief Initializes the PIT module.
 * 
 * This function must be called before calling all the other PIT driver functions.
 * This function un-gates the PIT clock and enables the PIT module. The isRunInDebug
 * passed into function affects all timer channels. 
 *
 * @param instance PIT module instance number.
 * @param isRunInDebug Timers run or stop in debug mode.
 *        - true:  Timers continue to run in debug mode.
 *        - false: Timers stop in debug mode.
 */
void PIT_DRV_Init(uint32_t instance, bool isRunInDebug);

/*!
 * @brief Disables the PIT module and gate control.
 *
 * This function disables all PIT interrupts and PIT clock. It then gates the
 * PIT clock control. PIT_DRV_Init must be called if you want to use PIT again.
 *
 * @param instance PIT module instance number.
 */
void PIT_DRV_Deinit(uint32_t instance);

/*!
 * @brief Initializes the PIT channel.
 * 
 * This function initializes the PIT timers by using a channel. Pass in the timer number and its
 * configuration structure. Timers do not start counting by default after calling this
 * function. The function PIT_DRV_StartTimer must be called to start the timer counting. 
 * Call the PIT_DRV_SetTimerPeriodByUs to re-set the period.
 *
 * This is an example demonstrating how to define a PIT channel configuration structure:
   @code
   pit_user_config_t pitTestInit = {
        .isInterruptEnabled = true,
        // Only takes effect when chain feature is available.
        // Otherwise, pass in arbitrary value(true/false).
        .isTimerChained = false, 
        // In unit of microseconds.
        .periodUs = 1000,
   };
   @endcode
 *
 * @param instance PIT module instance number.
 * @param channel Timer channel number.
 * @param config PIT channel configuration structure.
 */
void PIT_DRV_InitChannel(uint32_t instance, uint32_t channel, const pit_user_config_t * config);

/* @} */

/*!
 * @name Timer Start and Stop 
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timers load period value, count down to 0 and
 * then load the respective start value again. Each time a timer reaches 0,
 * it generates a trigger pulse and sets the timeout interrupt flag.
 *
 * @param instance PIT module instance number.
 * @param channel Timer channel number.
 */
void PIT_DRV_StartTimer(uint32_t instance, uint32_t channel);

/*!
 * @brief Stops the timer counting.
 *
 * This function stops every timer counting. Timers reload their periods
 * respectively after the next time they call the PIT_DRV_StartTimer.
 *
 * @param instance PIT module instance number.
 * @param channel Timer channel number.
 */
void PIT_DRV_StopTimer(uint32_t instance, uint32_t channel);

/* @} */

/*!
 * @name Timer Period
 * @{
 */

/*!
 * @brief Sets the timer period in microseconds.
 *
 * The period range depends on the frequency of the PIT source clock. If the required period
 * is out of range, use the lifetime timer. 
 * 
 * @param instance PIT module instance number.
 * @param channel Timer channel number.
 * @param us Timer period in microseconds.
 */
void PIT_DRV_SetTimerPeriodByUs(uint32_t instance, uint32_t channel, uint32_t us);

/*!
 * @brief Reads the current timer value in microseconds.
 * 
 * This function returns an absolute time stamp in microseconds.
 * One common use of this function is to measure the running time of a part of
 * code. Call this function at both the beginning and end of code. The time
 * difference between these two time stamps is the running time. Make sure the 
 * running time does not exceed the timer period. The time stamp returned is
 * up-counting.
 *
 * @param instance PIT module instance number.
 * @param channel Timer channel number.
 * @return Current timer value in microseconds.
 */
uint32_t PIT_DRV_ReadTimerUs(uint32_t instance, uint32_t channel);

#if FSL_FEATURE_PIT_HAS_LIFETIME_TIMER
/*!
 * @brief Sets the lifetime timer period.
 * 
 * Timer 1 must be chained with timer 0 before using the lifetime timer. The period
 * range is restricted by "period * pitSourceClock < max of an uint64_t integer",
 * or it may cause an overflow and be unable to set the correct period.
 *
 * @param instance PIT module instance number.
 * @param period Lifetime timer period in microseconds.
 */
void PIT_DRV_SetLifetimeTimerPeriodByUs(uint32_t instance, uint64_t us);

/*!
 * @brief Reads the current lifetime value in microseconds.
 *
 * This feature returns an absolute time stamp in microseconds. The time stamp 
 * value does not exceed the timer period. The timer is up-counting.
 *
 * @param instance PIT module instance number.
 * @return Current lifetime timer value in microseconds.
 */
uint64_t PIT_DRV_ReadLifetimeTimerUs(uint32_t instance);
#endif /*FSL_FEATURE_PIT_HAS_LIFETIME_TIMER*/

/* @} */

/*!
 * @name ISR Callback Function 
 * @{
 */

/*!
 * @brief Registers the PIT ISR callback function. 
 *
 * System default ISR interfaces are already defined in the fsl_pit_irq.c. Users 
 * can either edit these ISRs or use this function to register a callback
 * function. The default ISR runs the callback function if there is one
 * installed.
 *
 * @param instance PIT module instance number.
 * @param channel    Timer channel number.
 * @param function Pointer to pit ISR callback function.
 */
void PIT_DRV_InstallCallback(uint32_t instance, uint32_t channel, pit_isr_callback_t function);

/* @} */

#if defined(__cplusplus)
}
#endif
 
/*! @}*/
 
#endif /* __FSL_PIT_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

