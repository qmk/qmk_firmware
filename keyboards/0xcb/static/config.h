/*
Copyright 2021 0xCB - Conor Burns

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
// clang-format off
/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB00
#define PRODUCT_ID      0xA455
#define DEVICE_VER      0x0001
#define MANUFACTURER    0xCB
#define PRODUCT         Static

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6


/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { D5, D6, D7, B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { B5, D4, C0, C1, C2, C3 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 10
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D1 }
// clang-format on
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* oled custom font */
#define OLED_FONT_END 255
#define OLED_FONT_H "gfxfont.c"

/* bootmagic */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
