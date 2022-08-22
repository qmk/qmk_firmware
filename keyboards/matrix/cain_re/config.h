/**
 * config.h
 *
    Copyright 2020 astro <yuleiz@gmail.com>

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

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, C7, C6, D5, D2, D4, D7, B7, D1 }
#define MATRIX_COL_PINS { F1, F4, F5, F6, B5, B6, B3, B2, B1, D0, B4, D6}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E6

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LED_MAP { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3 }
#endif

#define CAPS_PIN    D3
#define NUM_PIN     F7
#define SCROLL_PIN  B0
