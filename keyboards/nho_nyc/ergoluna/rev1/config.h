/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Fruitkt

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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 7

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
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, F4 }
#define MATRIX_COL_PINS { B6, F5, D4, C6, D7, E6, B4 }

#define DIODE_DIRECTION COL2ROW


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN B5
#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 30    // Number of LEDs
#define RGBLED_SPLIT { 15, 15 }
#endif

#define SOFT_SERIAL_PIN D2
#define SERIAL_USE_MULTI_TRANSACTION


/* Select hand configuration */
#define EE_HANDS
// #define MASTER_LEFT
// #define MASTER_RIGHT

#if !defined(NO_ACTION_MACRO)
    #define NO_ACTION_MACRO
#endif


#if !defined(NO_ACTION_FUNCTION)
    #define NO_ACTION_FUNCTION
#endif

// Use the Luna version to get the ErgoLuna logo instead of the qmk logo
#define OLED_FONT_H "lib/glcdfont_luna.c"


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
