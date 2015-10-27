/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */
 
#include "mbed_error.h"
#include "us_ticker_api.h"
#include "PeripheralNames.h"
#include "tmr_regs.h"

#define US_TIMER        MXC_TMR0
#define US_TIMER_IRQn   TMR0_IRQn

static int us_ticker_inited = 0;
static uint32_t ticks_per_us;
static uint32_t tick_win;
static volatile uint64_t current_cnt;   // Hold the current ticks
static volatile uint64_t event_cnt;     // Holds the value of the next event

#define ticks_to_us(ticks)  ((ticks) / ticks_per_us);
#define MAX_TICK_VAL    ((uint64_t)0xFFFFFFFF * ticks_per_us)

//******************************************************************************
static inline void inc_current_cnt(uint32_t inc) {

    // Overflow the ticker when the us ticker overflows
    current_cnt += inc;
    if(current_cnt > MAX_TICK_VAL) {
        current_cnt -= (MAX_TICK_VAL + 1);
    }
}

//******************************************************************************
static inline int event_passed(uint64_t current, uint64_t event) {

    // Determine if the event has already happened.
    // If the event is behind the current ticker, within a window,
    // then the event has already happened.
    if(((current < tick_win) && ((event < current) || 
        (event > (MAX_TICK_VAL - (tick_win - current))))) || 
        ((event < current) && (event > (current - tick_win)))) {
        return 1;
    }

    return 0;
}

//******************************************************************************
static inline uint64_t event_diff(uint64_t current, uint64_t event) {

    // Check to see if the ticker will overflow before the event
    if(current <= event) {
        return (event - current);
    }

    return ((MAX_TICK_VAL - current) + event);
}

//******************************************************************************
static void tmr_handler(void)
{
    uint32_t term_cnt32 = US_TIMER->term_cnt32;
    US_TIMER->term_cnt32 = 0xFFFFFFFF;  // reset to max value to prevent further interrupts
    US_TIMER->intfl = (MXC_F_TMR_INTFL_TIMER0 | MXC_F_TMR_INTFL_TIMER1);    // clear interrupt
    NVIC_ClearPendingIRQ(US_TIMER_IRQn);

    inc_current_cnt(term_cnt32);

    if (event_passed(current_cnt + US_TIMER->count32, event_cnt )) {
        // the timestamp has expired
        event_cnt = 0xFFFFFFFFFFFFFFFFULL;  // reset to max value
        us_ticker_irq_handler();
    } else {

        uint64_t diff = event_diff(current_cnt, event_cnt);
        if (diff < (uint64_t)0xFFFFFFFF) {
            // the event occurs before the next overflow
            US_TIMER->term_cnt32 = diff;

            // Since the timer keeps counting after the terminal value is reached, it is possible that the new
            // terminal value is in the past.    
            if (US_TIMER->term_cnt32 < US_TIMER->count32) {
                // the timestamp has expired
                US_TIMER->term_cnt32 = 0xFFFFFFFF;  // reset to max value to prevent further interrupts
                US_TIMER->intfl = (MXC_F_TMR_INTFL_TIMER0 | MXC_F_TMR_INTFL_TIMER1);    // clear interrupt
                NVIC_ClearPendingIRQ(US_TIMER_IRQn);
                event_cnt = 0xFFFFFFFFFFFFFFFFULL;  // reset to max value
                us_ticker_irq_handler();
            }
        }
    }
}

//******************************************************************************
void us_ticker_init(void)
{
    if (us_ticker_inited)
        return;
    us_ticker_inited = 1;

    current_cnt = 0;
    event_cnt = 0xFFFFFFFFFFFFFFFFULL;  // reset to max value

    if (SystemCoreClock <= 1000000) {
        error("us_ticker cannot operate at this SystemCoreClock");
        return;
    }

    // Configure timer for 32-bit continuous mode with /1 prescaler
    US_TIMER->ctrl = MXC_E_TMR_MODE_CONTINUOUS << MXC_F_TMR_CTRL_MODE_POS | (0 << MXC_F_TMR_CTRL_PRESCALE_POS);
    ticks_per_us = SystemCoreClock / 1000000;

    // Set the tick window to 10ms
    tick_win = SystemCoreClock/100;

    // Set timer overflow to the max
    US_TIMER->term_cnt32 = 0xFFFFFFFF;
    US_TIMER->pwm_cap32 = 0xFFFFFFFF;
    US_TIMER->count32 = 0;

    US_TIMER->intfl = (MXC_F_TMR_INTFL_TIMER0 | MXC_F_TMR_INTFL_TIMER1);    // clear pending interrupts

    NVIC_SetVector(US_TIMER_IRQn, (uint32_t)tmr_handler);
    NVIC_EnableIRQ(US_TIMER_IRQn);

    US_TIMER->inten |= MXC_F_TMR_INTEN_TIMER0;  // enable interrupts
    US_TIMER->ctrl |= MXC_F_TMR_CTRL_ENABLE0;   // enable timer
}

//******************************************************************************
void us_ticker_deinit(void)
{
    US_TIMER->ctrl = 0;     // disable timer
    US_TIMER->inten = 0;    // disable interrupts
    US_TIMER->intfl = (MXC_F_TMR_INTFL_TIMER0 | MXC_F_TMR_INTFL_TIMER1);    // clear interrupts
    us_ticker_inited = 0;
}

//******************************************************************************
uint32_t us_ticker_read(void)
{
    uint64_t current_cnt1, current_cnt2;
    uint32_t term_cnt, tmr_cnt;
    int intfl1, intfl2;

    if (!us_ticker_inited)
        us_ticker_init();

    // Ensure coherency between current_cnt and US_TIMER->count32
    do {
        current_cnt1 = current_cnt;
        intfl1 = US_TIMER->intfl;
        term_cnt = US_TIMER->term_cnt32;
        tmr_cnt = US_TIMER->count32;
        intfl2 = US_TIMER->intfl;
        current_cnt2 = current_cnt;
    } while ((current_cnt1 != current_cnt2) || (intfl1 != intfl2));

    if (intfl1) {
        current_cnt1 += term_cnt;
    }

    current_cnt1 += tmr_cnt;

    return (current_cnt1 / ticks_per_us);
}

//******************************************************************************
void us_ticker_set_interrupt(timestamp_t timestamp)
{
    // Note: interrupts are disabled before this function is called.
    US_TIMER->ctrl &= ~MXC_F_TMR_CTRL_ENABLE0;  // disable timer

    if (US_TIMER->intfl) {
        US_TIMER->intfl = (MXC_F_TMR_INTFL_TIMER0 | MXC_F_TMR_INTFL_TIMER1);    // clear interrupt
        NVIC_ClearPendingIRQ(US_TIMER_IRQn);
        inc_current_cnt(US_TIMER->term_cnt32);
    }

    // add and reset the current count value
    inc_current_cnt(US_TIMER->count32);
    US_TIMER->count32 = 0;

    // add the number of cycles that the timer is disabled here for 
    inc_current_cnt(200);

    event_cnt = (uint64_t)timestamp * ticks_per_us;

    // Check to see if the event has already passed
    if (!event_passed(current_cnt, event_cnt)) {
        uint64_t diff = event_diff(current_cnt, event_cnt);
        if (diff < (uint64_t)0xFFFFFFFF) {
            // the event occurs before the next overflow
            US_TIMER->term_cnt32 = diff;
        } else {
            // the event occurs after the next overflow 
            US_TIMER->term_cnt32 = 0xFFFFFFFF;  // set to max
        }
    } else {
        // the requested timestamp occurs in the past
        // set the timer up to immediately expire
        US_TIMER->term_cnt32 = 1;
    }
    US_TIMER->ctrl |= MXC_F_TMR_CTRL_ENABLE0;   // enable timer
}

//******************************************************************************
void us_ticker_disable_interrupt(void)
{
    // There are no more events, set timer overflow to the max
    US_TIMER->term_cnt32 = 0xFFFFFFFF;
}

//******************************************************************************
void us_ticker_clear_interrupt(void)
{
    // cleared in the local handler
}

//******************************************************************************
void us_ticker_set(timestamp_t timestamp)
{
    US_TIMER->ctrl &= ~MXC_F_TMR_CTRL_ENABLE0;  // disable timer
    current_cnt = (uint64_t)timestamp * ticks_per_us;
    US_TIMER->count32 = 0;
    US_TIMER->term_cnt32 = 0xFFFFFFFF;
    US_TIMER->ctrl |= MXC_F_TMR_CTRL_ENABLE0;   // enable timer

    if (((uint64_t)timestamp * ticks_per_us) >= event_cnt) {
        // The next timestamp has elapsed. Trigger the interrupt to handle it.
        NVIC_SetPendingIRQ(US_TIMER_IRQn);
    }
}
