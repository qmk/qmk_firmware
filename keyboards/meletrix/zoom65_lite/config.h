/* Copyright 2021 meletrix
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
#define VENDOR_ID       0x806C
#define PRODUCT_ID      0x0005
#define DEVICE_VER      0x0001
#define MANUFACTURER    meletrix
#define PRODUCT         zoom65_lite

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { F0, E6, D5, F1, F4 }
#define MATRIX_COL_PINS { C7, D3, D2, D1, D0, B7, B3, B2, C6, B6, B5, B4, D7, D6, D4 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Enable encoder */
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B0 }

#define ENCODERS 1

#define ENCODER_RESOLUTION 2

// Note:  array is { col, row )
#define ENCODERS_CW_KEY  { { 5, 4 } }
#define ENCODERS_CCW_KEY { { 3, 4 } }

#define LED_CAPS_LOCK_PIN F7
#define LED_PIN_ON_STATE 0

