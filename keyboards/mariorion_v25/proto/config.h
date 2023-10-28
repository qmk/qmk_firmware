// Copyright 2023 Maria (@toril940)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define WS2812_EXTERNAL_PULLUP

#define WS2812_PWM_DRIVER PWMD17
#define WS2812_PWM_CHANNEL 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL 1
// #define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM17_UP

#define INDICATOR_0 C8
#define INDICATOR_1 C7
#define INDICATOR_2 C6