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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA03
#define DEVICE_VER      0x0001
#define MANUFACTURER    JasonRen biu
#define PRODUCT         tdcq68

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                         0   1   2       3   4    5    6    7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A9,  A10, C13, C14, C15, A0, A1, A2, A3, A4}
#define MATRIX_ROW_PINS { A15, B3, B4, B5, B7}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5



/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 2
#    define DRIVER_LED_TOTAL RGBLED_NUM

#    define WS2812_PWM_DRIVER PWMD3
#    define WS2812_PWM_CHANNEL 4
#    define WS2812_PWM_PAL_MODE 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#    define WS2812_DMA_CHANNEL 5

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    define RGBLIGHT_VAL_STEP 18
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 32, 96 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif



