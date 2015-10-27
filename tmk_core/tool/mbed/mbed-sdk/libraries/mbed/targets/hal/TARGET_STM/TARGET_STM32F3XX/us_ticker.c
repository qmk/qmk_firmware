/* mbed Microcontroller Library
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stddef.h>
#include "us_ticker_api.h"
#include "PeripheralNames.h"

// 32-bit timer selection
#define TIM_MST            TIM2
#define TIM_MST_IRQ        TIM2_IRQn
#define TIM_MST_RCC        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE)

static int us_ticker_inited = 0;

void us_ticker_init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    if (us_ticker_inited) return;
    us_ticker_inited = 1;

    // Enable timer clock
    TIM_MST_RCC;

    // Configure time base
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFFFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler     = (uint16_t)(SystemCoreClock / 1000000) - 1; // 1 �s tick
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM_MST, &TIM_TimeBaseStructure);

    NVIC_SetVector(TIM_MST_IRQ, (uint32_t)us_ticker_irq_handler);
    NVIC_EnableIRQ(TIM_MST_IRQ);

    // Enable timer
    TIM_Cmd(TIM_MST, ENABLE);
}

uint32_t us_ticker_read() {
    if (!us_ticker_inited) us_ticker_init();
    return TIM_MST->CNT;
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    // Set new output compare value
    TIM_SetCompare1(TIM_MST, (uint32_t)timestamp);
    // Enable IT
    TIM_ITConfig(TIM_MST, TIM_IT_CC1, ENABLE);
}

void us_ticker_disable_interrupt(void) {
    TIM_ITConfig(TIM_MST, TIM_IT_CC1, DISABLE);
}

void us_ticker_clear_interrupt(void) {
    TIM_ClearITPendingBit(TIM_MST, TIM_IT_CC1);
}
