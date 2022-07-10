/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xB141
#define PRODUCT_ID      0x0602 //F is 6th in alphabet, 02 as in DUO
#define DEVICE_VER      0x0001
#define MANUFACTURER    ParyzFilip
#define PRODUCT         Freoduo

/* key matrix size */
/* rows are doubled-up */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* wiring of each half */
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B2, B6, F6, B3, B1, F7 }
#define EE_HANDS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 3

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* ws2812 RGB LED */
#define RGB_DI_PIN D4
#if !defined(RGBLED_NUM)
#    define RGBLED_NUM 18
#    define RGBLIGHT_SPLIT
#    define RGBLED_SPLIT { 9, 9 }
// Switch RGB sides with LED MAP.
#    define RGBLIGHT_LED_MAP { 8, 7, 6, 5, 4, 3, 2, 1, 0, 17, 16, 15, 14, 13, 12, 11, 10, 9}
#    define RGBLIGHT_LAYERS
#endif
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define RGBLIGHT_HUE_STEP 16
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
