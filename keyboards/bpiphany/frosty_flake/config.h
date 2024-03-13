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

#pragma once


/*
 * Frosty Flake Rev. 20140521 made by Bathroom Ephiphanies
 * Ported from the Bathroom Epiphanies TMK Firmware:
 * https://github.com/BathroomEpiphanies/epiphanies_tmk_keyboard/tree/master/be_controllers
 *
 */

/* key matrix size */
#define MATRIX_ROWS 18 // ColA - ColR in the schematic
#define MATRIX_COLS 8  // Row0 - Row7 in the schematic

/*
 * Keyboard Matrix Assignments
 *
 * MATRIX_ROW_PINS and MATRIX_COL_PINS aren't actually used and are included
 * for data driven compatibility.
 */
#define MATRIX_COL_PINS { B0, B3, B2, B1, B6, B4, B5, C7 }
#define MATRIX_ROW_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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
