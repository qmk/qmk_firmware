/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#include "us_ticker_api.h"
#include "PeripheralNames.h"
#include "ostm_iodefine.h"

#include "RZ_A1_Init.h"
#include "MBRZA1H.h"

#define US_TICKER_TIMER_IRQn (OSTMI1TINT_IRQn)
#define CPG_STBCR5_BIT_MSTP50   (0x01u) /* OSTM1 */

#define US_TICKER_CLOCK_US_DEV (1000000)

int us_ticker_inited = 0;
static double count_clock = 0;
static uint32_t last_read = 0;
static uint32_t wrap_arround = 0;
static uint64_t ticker_us_last64 = 0;

void us_ticker_interrupt(void) {
    us_ticker_irq_handler();
}

void us_ticker_init(void) {
    if (us_ticker_inited) return;
    us_ticker_inited = 1;

    /* set Counter Clock(us) */
    if (false == RZ_A1_IsClockMode0()) {
        count_clock = ((double)CM1_RENESAS_RZ_A1_P0_CLK / (double)US_TICKER_CLOCK_US_DEV);
    } else {
        count_clock = ((double)CM0_RENESAS_RZ_A1_P0_CLK / (double)US_TICKER_CLOCK_US_DEV);
    }

    /* Power Control for Peripherals      */
    CPGSTBCR5 &= ~(CPG_STBCR5_BIT_MSTP50); /* enable OSTM1 clock */

    // timer settings
    OSTM1TT   = 0x01;    /* Stop the counter and clears the OSTM1TE bit.     */
    OSTM1CTL  = 0x02;    /* Free running timer mode. Interrupt disabled when star counter  */

    OSTM1TS   = 0x1;    /* Start the counter and sets the OSTM0TE bit.     */

    // INTC settings
    InterruptHandlerRegister(US_TICKER_TIMER_IRQn, (void (*)(uint32_t))us_ticker_interrupt);
    GIC_SetPriority(US_TICKER_TIMER_IRQn, 5);
    GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

static uint64_t ticker_read_counter64(void) {
    uint32_t cnt_val;
    uint64_t cnt_val64;

    if (!us_ticker_inited)
        us_ticker_init();

    /* read counter */
    cnt_val = OSTM1CNT;
    if (last_read > cnt_val) {
        wrap_arround++;
    }
    last_read = cnt_val;
    cnt_val64 = ((uint64_t)wrap_arround << 32) + cnt_val;

    return cnt_val64;
}

uint32_t us_ticker_read() {
    uint64_t cnt_val64;
    uint64_t us_val64;
    int check_irq_masked;

    check_irq_masked = __disable_irq();

    cnt_val64        = ticker_read_counter64();
    us_val64         = (cnt_val64 / count_clock);
    ticker_us_last64 = us_val64;

    if (!check_irq_masked) {
        __enable_irq();
    }

    /* clock to us */
    return (uint32_t)us_val64;
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    // set match value
    uint64_t timestamp64;
    uint64_t set_cmp_val64;
    volatile uint32_t set_cmp_val;
    uint64_t count_val_64;

    /* calc compare mach timestamp */
    timestamp64 = (ticker_us_last64 & 0xFFFFFFFF00000000) + timestamp;
    if (timestamp < (ticker_us_last64 & 0x00000000FFFFFFFF)) {
        /* This event is wrap arround */
        timestamp64 += 0x100000000;
    }

    /* calc compare mach timestamp */
    set_cmp_val64  = timestamp64 * count_clock;
    set_cmp_val    = (uint32_t)(set_cmp_val64 & 0x00000000FFFFFFFF);
    count_val_64   = ticker_read_counter64();
    if (set_cmp_val64 <= (count_val_64 + 500)) {
        GIC_SetPendingIRQ(US_TICKER_TIMER_IRQn);
        GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
        return;
    }
    OSTM1CMP = set_cmp_val;
    GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

void us_ticker_disable_interrupt(void) {
    GIC_DisableIRQ(US_TICKER_TIMER_IRQn);
}

void us_ticker_clear_interrupt(void) {
    GIC_ClearPendingIRQ(US_TICKER_TIMER_IRQn);
}
