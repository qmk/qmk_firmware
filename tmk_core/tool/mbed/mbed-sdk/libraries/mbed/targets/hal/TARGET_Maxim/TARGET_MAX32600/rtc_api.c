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

#include "rtc_api.h"
#include "cmsis.h"
#include "rtc_regs.h"
#include "pwrseq_regs.h"
#include "clkman_regs.h"

static int rtc_inited = 0;
static volatile uint32_t overflow_cnt = 0;
static uint32_t overflow_alarm = 0;

//******************************************************************************
static void overflow_handler(void)
{
    MXC_RTCTMR->flags = MXC_F_RTC_FLAGS_ASYNC_CLR_FLAGS;
    overflow_cnt++;

    if (overflow_cnt == overflow_alarm) {
        // Enable the comparator interrupt for the alarm
        MXC_RTCTMR->inten |= MXC_F_RTC_INTEN_COMP0;
    }
}

//******************************************************************************
static void alarm_handler(void)
{
    MXC_RTCTMR->inten &= ~MXC_F_RTC_INTEN_COMP0;
    MXC_RTCTMR->flags = MXC_F_RTC_FLAGS_ASYNC_CLR_FLAGS;
}

//******************************************************************************
void rtc_init(void)
{
    if(rtc_inited) {
        return;
    }
    rtc_inited = 1;

    // Enable the clock to the synchronizer
    MXC_CLKMAN->clk_ctrl_13_rtc_int_sync = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

    // Enable the clock to the RTC
    MXC_PWRSEQ->reg0 |= MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN;

    // Set the divider from the 4kHz clock
    MXC_RTCTMR->prescale = MXC_E_RTC_PRESCALE_DIV_2_0;

    // Enable the overflow interrupt
    MXC_RTCTMR->inten |= MXC_F_RTC_FLAGS_OVERFLOW;

    // Prepare interrupt handlers
    NVIC_SetVector(RTC0_IRQn, (uint32_t)alarm_handler);
    NVIC_EnableIRQ(RTC0_IRQn);
    NVIC_SetVector(RTC3_IRQn, (uint32_t)overflow_handler);
    NVIC_EnableIRQ(RTC3_IRQn);

    // Enable the RTC
    MXC_RTCTMR->ctrl |= MXC_F_RTC_CTRL_ENABLE;
}

//******************************************************************************
void rtc_free(void)
{
    if (MXC_RTCTMR->ctrl & MXC_F_RTC_CTRL_ENABLE) {
        // Clear and disable RTC
        MXC_RTCTMR->ctrl |= MXC_F_RTC_CTRL_CLEAR;
        MXC_RTCTMR->ctrl &= ~MXC_F_RTC_CTRL_ENABLE;

        // Wait for pending transactions
        while(MXC_RTCTMR->ctrl & MXC_F_RTC_CTRL_PENDING);
    }

    // Disable the clock to the RTC
    MXC_PWRSEQ->reg0 &= ~(MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN | MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP);

    // Disable the clock to the synchronizer
    MXC_CLKMAN->clk_ctrl_13_rtc_int_sync = MXC_E_CLKMAN_CLK_SCALE_DISABLED;
}

//******************************************************************************
int rtc_isenabled(void)
{
    return (MXC_RTCTMR->ctrl & MXC_F_RTC_CTRL_ENABLE);
}

//******************************************************************************
time_t rtc_read(void)
{
    unsigned int shift_amt;
    uint32_t ovf_cnt_1, ovf_cnt_2, timer_cnt;

    // Account for a change in the default prescaler
    shift_amt = MXC_E_RTC_PRESCALE_DIV_2_12 - MXC_RTCTMR->prescale;

    // Ensure coherency between overflow_cnt and timer
    do {
        ovf_cnt_1 = overflow_cnt;
        timer_cnt = MXC_RTCTMR->timer;
        ovf_cnt_2 = overflow_cnt;
    } while (ovf_cnt_1 != ovf_cnt_2);

    return (timer_cnt >> shift_amt) + (ovf_cnt_1 << (32 - shift_amt));
}

//******************************************************************************
uint64_t rtc_read_us(void)
{
    unsigned int shift_amt;
    uint32_t ovf_cnt_1, ovf_cnt_2, timer_cnt;
    uint64_t currentUs;

    // Account for a change in the default prescaler
    shift_amt = MXC_E_RTC_PRESCALE_DIV_2_12 - MXC_RTCTMR->prescale;

    // Ensure coherency between overflow_cnt and timer
    do {
        ovf_cnt_1 = overflow_cnt;
        timer_cnt = MXC_RTCTMR->timer;
        ovf_cnt_2 = overflow_cnt;
    } while (ovf_cnt_1 != ovf_cnt_2);

    currentUs = (((uint64_t)timer_cnt * 1000000) >> shift_amt) + (((uint64_t)ovf_cnt_1 * 1000000) << (32 - shift_amt));

    return currentUs;
}

//******************************************************************************
void rtc_write(time_t t)
{
    // Account for a change in the default prescaler
    unsigned int shift_amt = MXC_E_RTC_PRESCALE_DIV_2_12 - MXC_RTCTMR->prescale;

    MXC_RTCTMR->ctrl &= ~MXC_F_RTC_CTRL_ENABLE; // disable the timer while updating
    MXC_RTCTMR->timer = t << shift_amt;
    overflow_cnt = t >> (32 - shift_amt);
    MXC_RTCTMR->ctrl |= MXC_F_RTC_CTRL_ENABLE;  // enable the timer while updating
}

//******************************************************************************
void rtc_set_wakeup(uint64_t wakeupUs)
{
    // Account for a change in the default prescaler
    unsigned int shift_amt = MXC_E_RTC_PRESCALE_DIV_2_12 - MXC_RTCTMR->prescale;

    // Disable the alarm while it is prepared
    MXC_RTCTMR->inten &= ~MXC_F_RTC_INTEN_COMP0;
    MXC_RTCTMR->flags = MXC_F_RTC_FLAGS_COMP0;      // clear interrupt

    overflow_alarm = (wakeupUs >> (32 - shift_amt)) / 1000000;

    if (overflow_alarm == overflow_cnt) {
        MXC_RTCTMR->comp[0] = (wakeupUs << shift_amt) / 1000000;
        MXC_RTCTMR->inten |= MXC_F_RTC_INTEN_COMP0;
    }

    // Enable wakeup from RTC
    MXC_PWRSEQ->msk_flags &= ~(MXC_F_PWRSEQ_MSK_FLAGS_RTC_ROLLOVER | MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR0);
}
