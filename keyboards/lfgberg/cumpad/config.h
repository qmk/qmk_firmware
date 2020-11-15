/* Copyright 2020 Lfgberg
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
 */

#pragma once

#include "config_common.h"
/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C47
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
/*Product Info*/
#define MANUFACTURER    Lfgberg
#define PRODUCT         Cumpad

#define TAPPING_TERM 400

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 8

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { F7, B3, B1 }
#define MATRIX_COL_PINS { F4, F5, F6, B5, B4, E6, C6, D7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
