/* Copyright 2023 Cutie Club
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
#define VENDOR_ID 0xFB9C
#define PRODUCT_ID 0x4D1B
#define DEVICE_VER 0x0000
#define MANUFACTURER Cutie Club
#define PRODUCT Fidelity

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { A15, B3, B5, B6, B7 }
#define MATRIX_COL_PINS { A7, A6, A5, A4, A3, A9, A8, B15, B14, B13, B12, B11, B10, B2, B1, B0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN B4

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
