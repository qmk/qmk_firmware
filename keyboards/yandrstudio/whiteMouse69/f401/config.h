/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                        0    1    2   3   4    5    6   7   8   9   10   11   12  13  14
#define MATRIX_COL_PINS { A15, B3, B4, B5,  B9,  B14, B13, A3, A4, A5, A6,  A7,  B0, B1, A8}
#define MATRIX_ROW_PINS { C13, B7, B6, C14, B8}


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 72
#    define DRIVER_LED_TOTAL RGBLED_NUM

#   define WS2812_SPI SPID2 // default: SPID1
#   define WS2812_SPI_MOSI_PAL_MODE 5
#   define WS2812_SPI_USE_CIRCULAR_BUFFER
// #   define WS2812_SPI_DIVISOR 8

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define RGBLIGHT_VAL_STEP 15
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 32, 96 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGBLIGHT_ANIMATIONS

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 72
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP

// #    define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
// #    define WS2812_PWM_CHANNEL 3  // default: 2
// #    define WS2812_PWM_PAL_MODE 1  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
// #    define WS2812_DMA_STREAM STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
// #    define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

// #   define WS2812_SPI SPID2 // default: SPID1
// #   define WS2812_SPI_MOSI_PAL_MODE 5
// #   define WS2812_SPI_DIVISOR 8


// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif




