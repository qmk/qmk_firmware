/* Copyright 2021 Danny Nguyen <danny@keeb.io>

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
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
#define ATMEGA_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B2, B3, C6, B6 }
#define MATRIX_COL_PINS { F6, B5, B4, D7, D6, D5, D3, D2 }
// MCP23018 pinout:
// Rows: B4, B3, B2, B1, B0
// Cols: A0, A1, A2, A3, A4, A5, A6, A7

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* indicator LEDs */
#define LED_NUM_LOCK_PIN F5
#define LED_CAPS_LOCK_PIN F4
#define LED_SCROLL_LOCK_PIN F1

/* number of backlight levels */
#define BACKLIGHT_PIN B7
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
