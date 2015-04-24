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

#define US_TICKER_TIMER      ((LPC_TIM_TypeDef *)LPC_TIM3_BASE)
#define US_TICKER_TIMER_IRQn TIMER3_IRQn

int us_ticker_inited = 0;

void us_ticker_init(void) {
    if (us_ticker_inited) return;
    us_ticker_inited = 1;
    
    LPC_SC->PCONP |= 1 << 23; // Clock TIMER_3
    
    US_TICKER_TIMER->CTCR = 0x0; // timer mode
    uint32_t PCLK = SystemCoreClock / 4;
    
    US_TICKER_TIMER->TCR = 0x2;  // reset
    
    uint32_t prescale = PCLK / 1000000; // default to 1MHz (1 us ticks)
    US_TICKER_TIMER->PR = prescale - 1;
    US_TICKER_TIMER->TCR = 1; // enable = 1, reset = 0
    
    NVIC_SetVector(US_TICKER_TIMER_IRQn, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint32_t us_ticker_read() {
    if (!us_ticker_inited)
        us_ticker_init();
    
    return US_TICKER_TIMER->TC;
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    // set match value
    US_TICKER_TIMER->MR0 = (uint32_t)timestamp;
    // enable match interrupt
    US_TICKER_TIMER->MCR |= 1;
}

void us_ticker_disable_interrupt(void) {
    US_TICKER_TIMER->MCR &= ~1;
}

void us_ticker_clear_interrupt(void) {
    US_TICKER_TIMER->IR = 1;
}
