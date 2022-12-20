/*
Copyright 2015 Álvaro "Gondolindrim" Volpato  <gondolindrim@acheronproject.com>

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
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_COL_PINS { B12, A2 , A1 , A0 , F1 , F0 , C15, C14, C13, A7 , A6 , A5 , A4 , B7}
#define MATRIX_ROW_PINS { B9 , B8 , A3 , B0 , B1 }
#define DIODE_DIRECTION COL2ROW

//#define BACKLIGHT_PIN           A6
//#define BACKLIGHT_PWM_DRIVER    PWMD3
//#define BACKLIGHT_PWM_CHANNEL   1
//#define BACKLIGHT_PAL_MODE      1
//#define BACKLIGHT_LEVELS 6
//#define BACKLIGHT_BREATHING
//#define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

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
