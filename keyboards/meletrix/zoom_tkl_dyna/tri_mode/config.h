// Copyright 2023-2025 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Encoder configuration
// #undef ENCODER_MAP_KEY_DELAY
// #define ENCODER_MAP_KEY_DELAY 10

// WS2812 PWM Driver
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_DMA_STREAM AT32_DMA1_STREAM2
#define WS2812_PWM_DMAMUX_CHANNEL 2
#define WS2812_PWM_DMAMUX_ID  AT32_DMAMUX_TMR4_CH3

// RGB LED configuration
// #define WS2812_TIMING 1250
// #define WS2812_T1H 850
// #define WS2812_T0H 250
