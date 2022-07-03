/* Copyright 2020 Daniel Reibl <janos.daniel.reibl@protonmail.com>
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

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x002A
#define DEVICE_VER 0x0001
#define MANUFACTURER Riblee
#define PRODUCT Handwired F401

#define MATRIX_ROWS 5
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { A10, A1, A4, A3, A2 }
#define MATRIX_COL_PINS { B10, B1, B0, B15, A8, B3, B4, B5, B6, B7, B8, B9 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* #define BACKLIGHT_PIN           A0
#define BACKLIGHT_LEVELS         5 */

#define MOUSEKEY_INTERVAL 32

#define TAPPING_TERM 175

#define RGB_DI_PIN A7
// WS2812 RGB LED strip input and number of LEDs
/* #define RGB_DI_PIN          A1
#define WS2812_PWM_DRIVER   PWMD2  // default: PWMD2
#define WS2812_PWM_CHANNEL  2      // default: 2
#define WS2812_PWM_PAL_MODE 1      // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_EXTERNAL_PULLUP
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_DMA_STREAM   STM32_DMA1_STREAM7  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL  3                   // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_PWM_TARGET_PERIOD 800000 */

/* #define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU. */

/* #define WS2812_SPI SPID1 // default: SPID1
#define WS2812_DI_PIN A7
#define WS2812_SPI_MOSI_PAL_MODE 5 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_SPI_SCK_PIN A5 // Required for F072, may be for others -- SCK pin, see the respective datasheet for the appropriate values for your MCU. default: unspecified
#define WS2812_SPI_SCK_PAL_MODE 5 // SCK pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_SPI_DIVISOR 16 */


#define RGBLED_NUM          16
/* #define RGBLIGHT_SPLIT */
/* #define RGBLED_SPLIT \
    { 26, 26 } */
#define RGBLIGHT_ANIMATIONS
#define DEBUG_LED_PIN      C13