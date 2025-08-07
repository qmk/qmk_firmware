// Copyright 2025 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Defines for the RGB matrix */
#ifdef RGB_MATRIX_ENABLE
#   define WS2812_PWM_DRIVER PWMD15
#   define WS2812_PWM_CHANNEL 2
#   define WS2812_PWM_PAL_MODE 1
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#   define WS2812_DMA_CHANNEL 2
#   define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM15_UP
#endif
