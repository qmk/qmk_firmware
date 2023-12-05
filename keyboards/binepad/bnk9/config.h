// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define ENCODER_DEFAULT_POS 0x3  // enable 1:1 resolution

#ifdef RGB_MATRIX_ENABLE
    #define WS2812_PIO_USE_PIO1
    // #define RGB_MATRIX_TIMEOUT 600000  // 10 minutes
    #define RGB_DISABLE_WITH_FADE_OUTS
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_LED_PROCESS_LIMIT 9  // All nine keys
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180  // Not too bright so that the LED's don't burn out

    // Timing for SK6812
    #undef WS2812_TIMING
    #undef WS2812_T0H
    #undef WS2812_T0L
    #undef WS2812_T1H
    #undef WS2812_T1L
    #define WS2812_TIMING 1250
    #define WS2812_T0H    350
    #define WS2812_T0L	  (WS2812_TIMING - WS2812_T0H)
    #define WS2812_T1H	  650
    #define WS2812_T1L	  (WS2812_TIMING - WS2812_T1H)
#endif
