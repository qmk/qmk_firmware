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

#define US_TICKER_TIMER_IRQn     RIT_IRQn

int us_ticker_inited = 0;

void us_ticker_init(void) {
    if (us_ticker_inited) return;
    us_ticker_inited = 1;
    
    // Enable the RIT clock
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << 1);
    
    // Clear peripheral reset the RIT
    LPC_SYSCON->PRESETCTRL1 |= (1 << 1);
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << 1);
    
    LPC_RIT->MASK = 0;
    LPC_RIT->MASK_H = 0;
    
    LPC_RIT->COUNTER = 0;
    LPC_RIT->COUNTER_H = 0;

    LPC_RIT->COMPVAL = 0xffffffff;
    LPC_RIT->COMPVAL_H = 0x0000ffff;

    // Timer enable, enable for debug
    LPC_RIT->CTRL = 0xC;
    
    NVIC_SetVector(US_TICKER_TIMER_IRQn, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint32_t us_ticker_read() {
    if (!us_ticker_inited)
        us_ticker_init();
    
    uint64_t temp;
    temp = LPC_RIT->COUNTER | ((uint64_t)LPC_RIT->COUNTER_H << 32);
    temp /= (SystemCoreClock/1000000);
    return (uint32_t)temp;
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
	uint64_t temp = ((uint64_t)timestamp * (SystemCoreClock/1000000));
    LPC_RIT->COMPVAL = (temp & 0xFFFFFFFFL);
    LPC_RIT->COMPVAL_H = ((temp >> 32)& 0x0000FFFFL);
}

void us_ticker_disable_interrupt(void) {
    LPC_RIT->CTRL |= (1 << 3);
}

void us_ticker_clear_interrupt(void) {
    LPC_RIT->CTRL |= (1 << 0);
}
