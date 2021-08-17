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
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

//                        0    1    2   3     4    5    6   7   8   9   10   11   12  13   14  15   16   17
#define MATRIX_COL_PINS { A3,  B9,  B8, C13,  C14, B7, B6,  B5, B4, B3, A15, A14, A9, B12, A8, B15, A10, A13}
#define MATRIX_ROW_PINS { B0,  B1,  B10, A5,   A6,  A7}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B2
#    define RGBLED_NUM 87
#    define DRIVER_LED_TOTAL RGBLED_NUM

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

#    define RGB_DI_PIN B2
#    define RGBLED_NUM 87
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SLEEP

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif



#define LED_CAPS_LOCK_PIN    B13
#define LED_SCROLL_LOCK_PIN  B14
#define LED_PIN_ON_STATE     0
