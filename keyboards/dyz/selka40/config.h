/*
Copyright 2021 dayatz

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
#define MANUFACTURER    dyz
#define PRODUCT         selka40

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

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

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define LED_CAPS_LOCK_PIN B1
#define LED_NUM_LOCK_PIN B3
#define LED_SCROLL_LOCK_PIN B2

#define TAP_CODE_DELAY 10 // Need this delay for some keys like VOLD/VOLU to work
#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D7 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 3
