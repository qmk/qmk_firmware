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
 
#include "sleep_api.h"
#include "us_ticker_api.h"
#include "cmsis.h"
#include "pwrman_regs.h"
#include "pwrseq_regs.h"
#include "ioman_regs.h"
#include "rtc_regs.h"

#define MIN_DEEP_SLEEP_US       500

uint64_t rtc_read_us(void);
void rtc_set_wakeup(uint64_t wakeupUs);
void us_ticker_deinit(void);
void us_ticker_set(timestamp_t timestamp);

static mxc_uart_regs_t *stdio_uart = (mxc_uart_regs_t*)STDIO_UART;

// Normal wait mode
void sleep(void)
{
    // Normal sleep mode for ARM core
    SCB->SCR = 0;

    __DSB();
    __WFI();
}

// Work-around for issue of clearing power sequencer I/O flag
static void clearAllGPIOWUD(void)
{
    uint32_t wud_req0 = MXC_IOMAN->wud_req0;
    uint32_t wud_req1 = MXC_IOMAN->wud_req1;

    // I/O must be a wakeup detect to clear
    MXC_IOMAN->wud_req0 = 0xffffffff;
    MXC_IOMAN->wud_req1 = 0xffffffff;

    // Clear all WUDs
    MXC_PWRMAN->wud_ctrl = (MXC_E_PWRMAN_PAD_MODE_CLEAR_SET << MXC_F_PWRMAN_WUD_CTRL_PAD_MODE_POS) | MXC_F_PWRMAN_WUD_CTRL_CLEAR_ALL;
    MXC_PWRMAN->wud_pulse0 = 1;

    // Restore WUD requests
    MXC_IOMAN->wud_req0 = wud_req0;
    MXC_IOMAN->wud_req1 = wud_req1;
}

// Low-power stop mode
void deepsleep(void)
{
    uint64_t sleepStartRtcUs;
    uint32_t sleepStartTickerUs;
    int32_t sleepDurationUs;
    uint64_t sleepEndRtcUs;
    uint64_t elapsedUs;

    __disable_irq();

    // Wait for all STDIO characters to be sent. The UART clock will stop.
    while (stdio_uart->status & MXC_F_UART_STATUS_TX_BUSY);

    // Record the current times
    sleepStartRtcUs = rtc_read_us();
    sleepStartTickerUs = us_ticker_read();

    // Get the next mbed timer expiration
    timestamp_t next_event = 0;
    us_ticker_get_next_timestamp(&next_event);
    sleepDurationUs = next_event - sleepStartTickerUs;

    if (sleepDurationUs < MIN_DEEP_SLEEP_US) {
        /* The next wakeup is too soon. */
        __enable_irq();
        return;
    }

    // Disable the us_ticker. It won't be clocked in DeepSleep
    us_ticker_deinit();

    // Prepare to wakeup from the RTC
    rtc_set_wakeup(sleepStartRtcUs + sleepDurationUs);

    // Prepare for LP1
    uint32_t reg0 = MXC_PWRSEQ->reg0;
    reg0 &= ~MXC_F_PWRSEQ_REG0_PWR_SVM3EN_SLP;  // disable VDD3 SVM during sleep mode
    reg0 &= ~MXC_F_PWRSEQ_REG0_PWR_SVM1EN_SLP;  // disable VREG18 SVM during sleep mode
    if (reg0 & MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN) {   // if real-time clock enabled during run
        reg0 |= MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP;    // enable real-time clock during sleep mode
    } else {
        reg0 &= ~MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP;   // disable real-time clock during sleep mode
    }
    reg0 |= MXC_F_PWRSEQ_REG0_PWR_CHZYEN_SLP;   // enable CHZY regulator during sleep mode
    reg0 |= MXC_F_PWRSEQ_REG0_PWR_LP1;          // go into LP1
    reg0 &= ~MXC_F_PWRSEQ_REG0_PWR_FIRST_BOOT;  // clear first boot flag
    MXC_PWRSEQ->reg0 = reg0;

    MXC_PWRSEQ->reg3 = (MXC_PWRSEQ->reg3 & ~MXC_F_PWRSEQ_REG3_PWR_ROSEL_QUICK) | (3 << MXC_F_PWRSEQ_REG3_PWR_ROSEL_QUICK_POS);

    // Deep sleep for ARM core
    SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;

    // clear latches for wakeup detect
    MXC_PWRSEQ->flags = MXC_PWRSEQ->flags;
    if (MXC_PWRSEQ->flags & MXC_F_PWRSEQ_FLAGS_PWR_IO_WAKEUP) {
        // attempt work-around for I/O flag clearing issue
        clearAllGPIOWUD();
        MXC_PWRSEQ->flags = MXC_F_PWRSEQ_FLAGS_PWR_IO_WAKEUP;
    }

    // Wait for pending RTC transaction
    while (MXC_RTCTMR->ctrl & MXC_F_RTC_CTRL_PENDING);

    // Ensure that the event register is clear
    __SEV();    // set event
    __WFE();    // clear event

    // Enter LP1
    __WFE();
    // Woke up from LP1

    // The RTC timer does not update until the next tick
    uint64_t tempUs = rtc_read_us();
    do {
        sleepEndRtcUs = rtc_read_us();
    } while(sleepEndRtcUs == tempUs);

    // Get the elapsed time from the RTC. Wakeup could have been from some other event.
    elapsedUs = sleepEndRtcUs - sleepStartRtcUs;

    // Update the us_ticker. It was not clocked during DeepSleep
    us_ticker_init();
    us_ticker_set(sleepStartTickerUs + elapsedUs);
    us_ticker_get_next_timestamp(&next_event);
    us_ticker_set_interrupt(next_event);

    __enable_irq();
}
