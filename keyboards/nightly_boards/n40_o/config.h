/*
Copyright 2020 Neil Brian Ramirez

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
#define MATRIX_ROW_PINS { E6, F0, F1, D7, NO_PIN }
#define MATRIX_COL_PINS { B5, C7, D6, D4, B3, B2, B1, B0, D5, D3, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B4
#ifdef RGB_DI_PIN
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS

#endif

/* Encoders */

#define ENCODERS 3

#define ENCODERS_PAD_A { F6, F4 , B6 }
#define ENCODERS_PAD_B { F7, F5 , C6 }

#define ENCODERS_CW_KEY  { { 2, 4 },{ 4, 4 },{ 6, 4 } }
#define ENCODERS_CCW_KEY { { 1, 4 },{ 3, 4 },{ 5, 4 } }

/* Audio */

#define AUDIO_PIN B7

#define AUDIO_CLICKY

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
