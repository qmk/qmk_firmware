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

#if !defined(__SW_TIMER_H__)
#define __SW_TIMER_H__

#include <stdint.h>
#include <stdbool.h>

/*! @addtogroup sw_timer Software Timer
 * @brief This module is used to interface with Abstract Timer HAL to generate periodical timeouts
 * required through different modules of the AOA protocol. This block will be based on 1ms
 * ticks for all the timeout calculations. The HAL Interface block used to communicate with
 * this must have the same 1ms timeout configured. This module can generate different
 * software timer channels based on the same 1ms.
 */
/*! @{*/

/*! Definition of the possible status of a software channel timer. */
typedef enum SwTimerChannelStatus
{
    kSwTimerChannelExpired       = 0x00, /*!< Indicates the timer channel has counted the given ms*/
    kSwTimerChannelStillCounting = 0x01, /*!< Indicates the timeout of the channel has not expired
                                              and the timer is still counting.*/
    kSwTimerChannelIsDisable     = 0x02, /*!< Indicates the timer channel is not reserved. */
    kSwTimerChannelNotAvailable  = 0xFF  /*!< Indicates there are not available channels to reserve
                                              or the requested channel is not available.*/
}sw_timer_channel_status_t;

/*! List of status and errors. */
enum _sw_timer_errors
{
    kSwTimerStatusSuccess,           /*!< The execution was successful.*/
    kSwTimerStatusFail,              /*!< The execution failed.*/
    kSwTimerStatusInvalidChannel     /*!< The given channel is not valid. Valid channels are 0 to
                                          (SW_TIMER_NUMBER_CHANNELS - 1). */
};

/*!
 * Data type of the counter of each timer channel. If it is an int8_t the counter will count
 * up to 127ms, int16_t up to 32767ms and int32_t up to 2147483647ms.
 */
typedef int32_t time_counter_t;

/*! Max timeout value according to size of the time counter */
enum sw_timer_timeouts
{
    kSwTimerMaxTimeout = 2147483647
};

/*!
 * Data type of the free running counter. This data type should be unsigned and will count up to
 * 255ms if it is uint8_t, 65535ms for uint16_t and 4294967295ms for uint32_t.
 */
typedef uint32_t time_free_counter_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Initializes the software timer module. Prepares variables and HAL layer to provide timer 
 *        services. Starts the free running counter which will be available to get its value any 
 *        time while the service is running; it is useful whenever a module wants to keep track of 
 *        time, but do not wants to reserve a channel.
 * 
 * @return status_t        Returns software timer status after initialization.
 * @retval kSwTimerStatusSuccess  The initialization was successful and the software timer is ready 
 *                                to provide services.
 * @retval kSwTimerStatusFail     The initialization failed.
 */
uint32_t sw_timer_init_service(void);

/*!
 * @brief Deinitializes the software timer module. Shutdown HAL layer, so no timer service can be
 *        provided after the execution of this function.
 * 
 * @return void
 */
void sw_timer_shutdown_service(void);

/*!
 * @brief Reserves a free timer channel to be used by any module and returns its identifier.
 * 
 * @return uint8_t        Returns the number of the channel that was reserved.
 * @retval Any value between 0 and SW_TIMER_NUMBER_CHANNELS is a valid channel. It indicates the 
 *         channel was reserved and can be used.
 * @retval kSwTimerChannelNotAvailable  If there is not any available channel, because all 
 *                                         channels are already reserved.
 */
uint8_t sw_timer_reserve_channel(void);

/*!
 * @brief Returns the actual status of the given timer channel. The timer has to be previously
 *        started to return a valid status.
 *
 * @param timerChannel    [in] Indicates the timer channel which status is going to be returned.
 * 
 * @return sw_timer_channel_status_t     Current status of the given timer channel.
 * @retval kSwTimerChannelExpired        Indicates the timer channel has counted the given ms.
 * @retval kSwTimerChannelStillCounting  Indicates the timeout of the channel has not expired and 
                                         the timer is still counting.
 * @retval kSwTimerChannelIsDisable      Indicates the timer channel is not reserved.
 * @retval kSwTimerChannelNotAvailable   Indicates the timer channel is invalid.
 */
sw_timer_channel_status_t sw_timer_get_channel_status(uint8_t timerChannel);

/*!
 * @brief Starts the count down of the given timer channel. The timer channel has to be previously
 *        reserved.
 *
 * @param timerChannel    [in] Indicates the timer channel that is going to be started.
 * @param timeout         [in] Time in ms that the timer channel will count. The timeout should be 
                               a multiple of count unit of the timer, otherwise it will be taken 
                               the integer part of the division and the exact count will not be
                               achieved
 * 
 * @return status_t                        Reports failures in the execution of the function.
 * @retval kSwTimerStatusSuccess           A channel was started successfully.
 * @retval kSwTimerStatusInvalidChannel    The timer channel is invalid, it does not exist.
 */
uint32_t sw_timer_start_channel(uint8_t timerChannel, time_counter_t timeout);

/*!
 * @brief Releases the given timer channel, so it can be used by someone else.
 *
 * @param timerChannel    [in] Identifier of the timer channel.
 * 
 * @return status_t                        Reports failures in the execution of the function.
 * @retval kSwTimerStatusSuccess           A channel was released successfully.
 * @retval kSwTimerStatusInvalidChannel    The timer channel is invalid, it does not exist.
 */
uint32_t sw_timer_release_channel(uint8_t timerChannel);

/*!
 * @brief Gets the current value of the free running counter. Any module can keep track of the time
 *        by reading this counter and calculates time difference. No reservation of timer channel
 *        is needed. Consider for calculations that when the counter overflows it will start from
 *        0 again.
 * 
 * @return time_free_counter_t  Returns current count of the free running counter.
 */
time_free_counter_t sw_timer_get_free_counter(void);

/*!
 * @brief This function is called every 1ms by the interruption and update count down values of all
 *        timer channels.
 * 
 * @return void
 */
void sw_timer_update_counters(void);


#if defined(__cplusplus)
}
#endif /* __cplusplus*/
/*! @}*/
/*Group sw_timer*/

#endif  /* __SW_TIMER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

