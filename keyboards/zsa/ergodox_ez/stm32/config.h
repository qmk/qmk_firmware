// Copyright 2012 Jun Wako <wakojun@gmail.com>
// Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
// Copyright 2015 ZSA Technology Labs Inc (@zsa)
// Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ONBOARD_ROW_PINS \
    { 0, 0, 0, 0, 0, 0, 0, A7, A6, A5, A4, A3, A2, A1 }
#define MATRIX_ONBOARD_COL_PINS \
    { B15, B14, B13, B12, B11, B10 }

#ifdef REMAPPED_LEDS
// prototyped boards
#    define ERGODOX_LED_1_PIN B0
#    define ERGODOX_LED_2_PIN B1
#    define ERGODOX_LED_3_PIN B4
#else
#    define ERGODOX_LED_1_PIN B5
#    define ERGODOX_LED_2_PIN B4
#    define ERGODOX_LED_3_PIN B3

#    define WS2812_PWM_DRIVER PWMD16
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_PWM_PAL_MODE 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#    define WS2812_DMA_CHANNEL 3
#endif
