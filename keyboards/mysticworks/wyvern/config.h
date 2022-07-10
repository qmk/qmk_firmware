/* Copyright 2020 Albert Dong <albert@mysticworks.xyz>
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

/* USB Device Descriptor Parameter */
#define VENDOR_ID       0x4D59  // "MY" - Mystic Works
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mystic Works
#define PRODUCT         Wyvern

/* Key Matrix Size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS {D0,D1,D5,D3,F7,F6,F5,F4,F1,F0}
#define MATRIX_COL_PINS {E6,B0,D4,D6,D7,B4,B5,B6,C6,C7}
#define UNUSED_PINS {B7,D2}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
