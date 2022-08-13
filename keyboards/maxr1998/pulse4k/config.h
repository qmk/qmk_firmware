/*
 * Copyright (C) 2019-2020  Maxr1998 <max.rumpf1998@gmail.com>
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

/* Key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* Matrix pins */
#define MATRIX_ROW_PINS { B4, E6 }
#define MATRIX_COL_PINS { B7, B3, F0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Rotary encoders */
#define ENCODERS_PAD_A { D2, F6 }
#define ENCODERS_PAD_B { D3, F5 }
#define ENCODER_RESOLUTION 4

/* Combo setup */
#define COMBO_COUNT 1
#define COMBO_TERM 150

/* RGB LED Setup */
#define RGB_DI_PIN          F7 // pin the DI on the WS2812B is hooked-up to
#define RGBLIGHT_ANIMATIONS    // run RGB animations
#define RGBLED_NUM          2  // number of LEDs

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
