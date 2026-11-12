// Copyright 2026 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Defines for the RGB matrix */
#define WS2812_PWM_DRIVER PWMD15                   // TIM15
#define WS2812_PWM_CHANNEL 2                       // TIM15_CH2
#define WS2812_PWM_PAL_MODE 14                     // PB15 AF14 = TIM15_CH2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM5   // DMA1 Channel 5
#define WS2812_PWM_DMA_CHANNEL 7                   // CSELR C5S = 7: TIM15_UP
