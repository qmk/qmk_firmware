/*
Copyright 2020 Ananya Kirti

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
#define MATRIX_COLS 15
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
#define MATRIX_ROW_PINS { B3, B7, A10, B9 ,A9}
#define MATRIX_COL_PINS { B12, B15, B10, B13, B14, B11, B8, A0, A1, B5, B0, B2, B6, B1, B4}

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN A3
#define RGBLED_NUM 20
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

#define LED_CAPS_LOCK_PIN A6
#define LED_SCROLL_LOCK_PIN A7