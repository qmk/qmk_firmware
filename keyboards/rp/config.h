// Copyright 2022 Thomas Haukland (@Thomas Haukland)
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
//
#define RGBLED_NUM 3

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif

/* RGB settings. */
 #define RGB_DI_PIN GP8 
 #define WS2812_PWM_DRIVER PWMD2
 #define WS2812_PWM_CHANNEL 2
 #define WS2812_PWM_PAL_MODE 1
 #define WS2812_EXTERNAL_PULLUP
 #define WS2812_DMA_STREAM STM32_DMA1_STREAM1
 #define WS2812_DMA_CHANNEL 3
 #define WS2812_PWM_TARGET_PERIOD 900000

#define ENABLE_RGB_MATRIX_BREATHING


