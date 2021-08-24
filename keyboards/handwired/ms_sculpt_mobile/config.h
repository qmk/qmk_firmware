/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Microsoftplus

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 18

#ifdef ASTAR
#define PRODUCT         sculpt mobile astar
                        /*0   1   2   3    4   5  6   7   8 */
#define MATRIX_ROW_PINS {D7, C6, D4, D0, D1, D3, D2, E2}
/*                        A  B   C   D   E   F   G   H   I   J  K   L   M   N   O   P   Q  R  */
#define MATRIX_COL_PINS {B4, B5, E6, B7, B6, D6,  C7, F7, F6, F4,F5, F1,F0, D5, B0, B1, B2, B3}

#else
#define PRODUCT         sculpt mobile teensypp
/* 			0  1  2  3  4 5  6   7 */
#define MATRIX_ROW_PINS { F7,F6,F4,F5,F3,F2,F1,F0}
/*                        A   B   C   D   E   F   G   H   I   J  K  L   M   N   O   P   Q  R  */
#define MATRIX_COL_PINS { B7, D0, D1, D2, D3, D4, D5, D6, D7, E0,E1,C1, C0, C3, C2, C5, C4,C7}
#define UNUSED_PINS { B6,B5,B4,B3,B2,B1,B0 }

#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/*
 * Magic Key Options
 *
 * Magic keys are hotkey commands that allow control over firmware functions of
 * the keyboard. They are best used in combination with the HID Listen program,
 * found here: https://www.pjrc.com/teensy/hid_listen.html
 *
 * The options below allow the magic key functionality to be changed. This is
 * useful if your keyboard/keypad is missing keys and you want magic key support.
 *
 */

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
