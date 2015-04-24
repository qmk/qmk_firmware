/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stddef.h>
#include <stdbool.h>
#include "us_ticker_api.h"
#include "cmsis.h"
#include "PeripheralNames.h"
#include "nrf_delay.h"

/*
 * Note: The micro-second timer API on the nRF51 platform is implemented using
 * the RTC counter run at 32kHz (sourced from an external oscillator). This is
 * a trade-off between precision and power. Running a normal 32-bit MCU counter
 * at high frequency causes the average power consumption to rise to a few
 * hundred micro-amps, which is prohibitive for typical low-power BLE
 * applications.
 * A 32kHz clock doesn't offer the precision needed for keeping u-second time,
 * but we're assuming that this will not be a problem for the average user.
 */

#define MAX_RTC_COUNTER_VAL     0x00FFFFFF               /**< Maximum value of the RTC counter. */
#define RTC_CLOCK_FREQ          (uint32_t)(32768)
#define RTC1_IRQ_PRI            3                        /**< Priority of the RTC1 interrupt (used
                                                          *  for checking for timeouts and executing
                                                          *  timeout handlers). This must be the same
                                                          *  as APP_IRQ_PRIORITY_LOW; taken from the
                                                          *  Nordic SDK. */
#define MAX_RTC_TASKS_DELAY     47                       /**< Maximum delay until an RTC task is executed. */

#define FUZZY_RTC_TICKS          2  /* RTC COMPARE occurs when a CC register is N and the RTC
                                     * COUNTER value transitions from N-1 to N. If we're trying to
                                     * setup a callback for a time which will arrive very shortly,
                                     * there are limits to how short the callback interval may be for us
                                     * to rely upon the RTC Compare trigger. If the COUNTER is N,
                                     * writing N+2 to a CC register is guaranteed to trigger a COMPARE
                                     * event at N+2. */

#define RTC_UNITS_TO_MICROSECONDS(RTC_UNITS) (((RTC_UNITS) * (uint64_t)1000000) / RTC_CLOCK_FREQ)
#define MICROSECONDS_TO_RTC_UNITS(MICROS)    ((((uint64_t)(MICROS) * RTC_CLOCK_FREQ) + 999999) / 1000000)

static bool              us_ticker_inited = false;
static volatile uint32_t overflowCount;                   /**< The number of times the 24-bit RTC counter has overflowed. */
static volatile bool     us_ticker_callbackPending = false;
static uint32_t          us_ticker_callbackTimestamp;

static inline void rtc1_enableCompareInterrupt(void)
{
    NRF_RTC1->EVTENCLR = RTC_EVTEN_COMPARE0_Msk;
    NRF_RTC1->INTENSET = RTC_INTENSET_COMPARE0_Msk;
}

static inline void rtc1_disableCompareInterrupt(void)
{
    NRF_RTC1->INTENCLR = RTC_INTENSET_COMPARE0_Msk;
    NRF_RTC1->EVTENCLR = RTC_EVTEN_COMPARE0_Msk;
}

static inline void rtc1_enableOverflowInterrupt(void)
{
    NRF_RTC1->EVTENCLR = RTC_EVTEN_OVRFLW_Msk;
    NRF_RTC1->INTENSET = RTC_INTENSET_OVRFLW_Msk;
}

static inline void rtc1_disableOverflowInterrupt(void)
{
    NRF_RTC1->INTENCLR = RTC_INTENSET_OVRFLW_Msk;
    NRF_RTC1->EVTENCLR = RTC_EVTEN_OVRFLW_Msk;
}

static inline void invokeCallback(void)
{
    us_ticker_callbackPending = false;
    rtc1_disableCompareInterrupt();
    us_ticker_irq_handler();
}

/**
 * @brief Function for starting the RTC1 timer. The RTC timer is expected to
 * keep running--some interrupts may be disabled temporarily.
 */
static void rtc1_start()
{
    NRF_RTC1->PRESCALER = 0; /* for no pre-scaling. */

    rtc1_enableOverflowInterrupt();

    NVIC_SetPriority(RTC1_IRQn, RTC1_IRQ_PRI);
    NVIC_ClearPendingIRQ(RTC1_IRQn);
    NVIC_EnableIRQ(RTC1_IRQn);

    NRF_RTC1->TASKS_START = 1;
    nrf_delay_us(MAX_RTC_TASKS_DELAY);
}

/**
 * @brief Function for stopping the RTC1 timer. We don't expect to call this.
 */
void rtc1_stop(void)
{
    NVIC_DisableIRQ(RTC1_IRQn);
    rtc1_disableCompareInterrupt();
    rtc1_disableOverflowInterrupt();

    NRF_RTC1->TASKS_STOP = 1;
    nrf_delay_us(MAX_RTC_TASKS_DELAY);

    NRF_RTC1->TASKS_CLEAR = 1;
    nrf_delay_us(MAX_RTC_TASKS_DELAY);
}

/**
 * @brief Function for returning the current value of the RTC1 counter.
 *
 * @return Current RTC1 counter as a 64-bit value with 56-bit precision (even
 *         though the underlying counter is 24-bit)
 */
static inline uint64_t rtc1_getCounter64(void)
{
    if (NRF_RTC1->EVENTS_OVRFLW) {
        overflowCount++;
        NRF_RTC1->EVENTS_OVRFLW = 0;
        NRF_RTC1->EVTENCLR      = RTC_EVTEN_OVRFLW_Msk;
    }
    return ((uint64_t)overflowCount << 24) | NRF_RTC1->COUNTER;
}

/**
 * @brief Function for returning the current value of the RTC1 counter.
 *
 * @return Current RTC1 counter as a 32-bit value (even though the underlying counter is 24-bit)
 */
static inline uint32_t rtc1_getCounter(void)
{
    return rtc1_getCounter64();
}

/**
 * @brief Function for handling the RTC1 interrupt.
 *
 * @details Checks for timeouts, and executes timeout handlers for expired timers.
 */
void RTC1_IRQHandler(void)
{
    if (NRF_RTC1->EVENTS_OVRFLW) {
        overflowCount++;
        NRF_RTC1->EVENTS_OVRFLW = 0;
        NRF_RTC1->EVTENCLR      = RTC_EVTEN_OVRFLW_Msk;
    }
    if (NRF_RTC1->EVENTS_COMPARE[0] && us_ticker_callbackPending && ((int)(us_ticker_callbackTimestamp - rtc1_getCounter()) <= 0)) {
        NRF_RTC1->EVENTS_COMPARE[0] = 0;
        NRF_RTC1->EVTENCLR          = RTC_EVTEN_COMPARE0_Msk;
        invokeCallback();
    }
}

void us_ticker_init(void)
{
    if (us_ticker_inited) {
        return;
    }

    rtc1_start();
    us_ticker_inited = true;
}

uint32_t us_ticker_read()
{
    if (!us_ticker_inited) {
        us_ticker_init();
    }

    /* Return a pseudo microsecond counter value. This is only as precise as the
     * 32khz low-freq clock source, but could be adequate.*/
    return RTC_UNITS_TO_MICROSECONDS(rtc1_getCounter64());
}

/**
 * Setup the us_ticker callback interrupt to go at the given timestamp.
 *
 * @Note: Only one callback is pending at any time.
 *
 * @Note: If a callback is pending, and this function is called again, the new
 * callback-time overrides the existing callback setting. It is the caller's
 * responsibility to ensure that this function is called to setup a callback for
 * the earliest timeout.
 *
 * @Note: If this function is used to setup an interrupt which is immediately
 * pending--such as for 'now' or a time in the past,--then the callback is
 * invoked a few ticks later.
 */
void us_ticker_set_interrupt(timestamp_t timestamp)
{
    if (!us_ticker_inited) {
        us_ticker_init();
    }

    /*
     * The argument to this function is a 32-bit microsecond timestamp for when
     * a callback should be invoked. On the nRF51, we use an RTC timer running
     * at 32kHz to implement a low-power us-ticker. This results in a problem
     * based on the fact that 1000000 is not a multiple of 32768.
     *
     * Going from a micro-second based timestamp to a 32kHz based RTC-time is a
     * linear mapping; but this mapping doesn't preserve wraparounds--i.e. when
     * the 32-bit micro-second timestamp wraps around unfortunately the
     * underlying RTC counter doesn't. The result is that timestamp expiry
     * checks on micro-second timestamps don't yield the same result when
     * applied on the corresponding RTC timestamp values.
     *
     * One solution is to translate the incoming 32-bit timestamp into a virtual
     * 64-bit timestamp based on the knowledge of system-uptime, and then use
     * this wraparound-free 64-bit value to do a linear mapping to RTC time.
     * System uptime on an nRF is maintained using the 24-bit RTC counter. We
     * track the overflow count to extend the 24-bit hardware counter by an
     * additional 32 bits. RTC_UNITS_TO_MICROSECONDS() converts this into
     * microsecond units (in 64-bits).
     */
    const uint64_t currentTime64 = RTC_UNITS_TO_MICROSECONDS(rtc1_getCounter64());
    uint64_t timestamp64 = (currentTime64 & ~(uint64_t)0xFFFFFFFFULL) + timestamp;
    if (((uint32_t)currentTime64 > 0x80000000) && (timestamp < 0x80000000)) {
        timestamp64 += (uint64_t)0x100000000ULL;
    }
    uint32_t newCallbackTime = MICROSECONDS_TO_RTC_UNITS(timestamp64);

    /* Check for repeat setup of an existing callback. This is actually not
     * important; the following code should work even without this check. */
    if (us_ticker_callbackPending && (newCallbackTime == us_ticker_callbackTimestamp)) {
        return;
    }

    /* Check for callbacks which are immediately (or will *very* shortly become) pending.
     * Even if they are immediately pending, they are scheduled to trigger a few
     * ticks later. This keeps things simple by invoking the callback from an
     * independent interrupt context. */
    if ((int)(newCallbackTime - rtc1_getCounter()) <= (int)FUZZY_RTC_TICKS) {
        newCallbackTime = rtc1_getCounter() + FUZZY_RTC_TICKS;
    }

    NRF_RTC1->CC[0]             = newCallbackTime & MAX_RTC_COUNTER_VAL;
    us_ticker_callbackTimestamp = newCallbackTime;
    if (!us_ticker_callbackPending) {
        us_ticker_callbackPending = true;
        rtc1_enableCompareInterrupt();
    }
}

void us_ticker_disable_interrupt(void)
{
    if (us_ticker_callbackPending) {
        rtc1_disableCompareInterrupt();
        us_ticker_callbackPending = false;
    }
}

void us_ticker_clear_interrupt(void)
{
    NRF_RTC1->EVENTS_OVRFLW     = 0;
    NRF_RTC1->EVENTS_COMPARE[0] = 0;
}
