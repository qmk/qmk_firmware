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
#include "fsl_pit_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_clock_manager.h"

static int us_ticker_inited = 0;

void us_ticker_init(void) {
    if (us_ticker_inited) {
        return;
    }
    us_ticker_inited = 1;
    
    //Common for ticker/timer
    uint32_t busClock;
    CLOCK_SYS_EnablePitClock(0);
    PIT_HAL_Enable(PIT_BASE);
    CLOCK_SYS_GetFreq(kBusClock, &busClock);
    
    //Timer
    PIT_HAL_SetTimerPeriodByCount(PIT_BASE, 0, busClock / 1000000 - 1);
    PIT_HAL_SetTimerPeriodByCount(PIT_BASE, 1, 0xFFFFFFFF);
    PIT_HAL_SetTimerChainCmd(PIT_BASE, 1, true);
    PIT_HAL_StartTimer(PIT_BASE, 0);
    PIT_HAL_StartTimer(PIT_BASE, 1);
    
    //Ticker
    PIT_HAL_SetTimerPeriodByCount(PIT_BASE, 2, busClock / 1000000 - 1);
    PIT_HAL_SetTimerChainCmd(PIT_BASE, 3, true);
    NVIC_SetVector(PIT3_IRQn, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(PIT3_IRQn);
}


uint32_t us_ticker_read() {
    if (!us_ticker_inited) {
        us_ticker_init();
    }

    return ~(PIT_HAL_ReadTimerCount(PIT_BASE, 1));
}

void us_ticker_disable_interrupt(void) {
    PIT_HAL_SetIntCmd(PIT_BASE, 3, false);
}

void us_ticker_clear_interrupt(void) {
    PIT_HAL_ClearIntFlag(PIT_BASE, 3);
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    int delta = (int)(timestamp - us_ticker_read());
    if (delta <= 0) {
        // This event was in the past:
        us_ticker_irq_handler();
        return;
    }
 
    PIT_HAL_StopTimer(PIT_BASE, 3);
    PIT_HAL_StopTimer(PIT_BASE, 2);
    PIT_HAL_SetTimerPeriodByCount(PIT_BASE, 3, (uint32_t)delta);
    PIT_HAL_SetIntCmd(PIT_BASE, 3, true);
    PIT_HAL_StartTimer(PIT_BASE, 3);
    PIT_HAL_StartTimer(PIT_BASE, 2);
}
