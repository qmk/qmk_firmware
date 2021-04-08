/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#define DEVICE_VER      0x0001
#define VENDOR_ID       0x320F
#define PRODUCT_ID      0x5044
#define MANUFACTURER    Glorious
#define PRODUCT         GMMK Pro

/* key matrix size */
#define MATRIX_ROWS 11
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS  { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10 }
#define MATRIX_COL_PINS  { A0, A1, A2, A3, A4, A8, A9, A10 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


#define TAP_CODE_DELAY 10
#define ENCODERS_PAD_A { C15 }
#define ENCODERS_PAD_B { C14 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
