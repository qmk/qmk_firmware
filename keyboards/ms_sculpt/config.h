// Copyright 2022 Jean Bernard (@jn-bernard)
// SPDX-License-Identifier: GPL-2.0-or-later

##pragma once

#define RGB_DI_PIN A1
#define RGBLED_NUM 16

#define RGBLIGHT_ANIMATIONS
#define WS2812_PWM_DRIVER PWMD5  // PWMDx= = TIMx
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", , zero-based number
#define WS2812_DMA_STREAM STM32_DMA1_STREAM0  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

//#define DEBUG_MATRIX_SCAN_RATE
#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 13

/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 18
