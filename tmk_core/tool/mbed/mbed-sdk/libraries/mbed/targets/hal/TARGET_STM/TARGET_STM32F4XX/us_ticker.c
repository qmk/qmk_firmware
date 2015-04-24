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

#define US_TICKER_TIMER TIM2
#define US_TICKER_TIMER_IRQn TIM2_IRQn

int us_ticker_inited = 0;

void us_ticker_init(void) {
    if (us_ticker_inited) return;
    us_ticker_inited = 1;
    
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    
    uint32_t PCLK = SystemCoreClock / 4;
    
    uint32_t prescale = PCLK / 1000000; // default to 1MHz (1 us ticks)
    US_TICKER_TIMER->PSC = prescale - 1;
    US_TICKER_TIMER->CR1 |= TIM_CR1_CEN;
    // Trigger an update - this needs to happen after the counter is enabled.
    US_TICKER_TIMER->EGR |= TIM_EGR_UG;

    NVIC_SetVector(US_TICKER_TIMER_IRQn, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint32_t us_ticker_read() {
    if (!us_ticker_inited)
        us_ticker_init();
    
    return US_TICKER_TIMER->CNT;
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    // set match value
    US_TICKER_TIMER->CCR1 = (uint32_t)timestamp;
    // enable compare interrupt
    US_TICKER_TIMER->DIER |= TIM_DIER_CC1IE;
}

void us_ticker_disable_interrupt(void) {
    US_TICKER_TIMER->DIER &= ~TIM_DIER_CC1IE;
}

void us_ticker_clear_interrupt(void) {
    US_TICKER_TIMER->SR &= ~TIM_SR_CC1IF;
}
