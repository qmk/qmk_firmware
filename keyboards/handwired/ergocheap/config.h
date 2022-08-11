/*
Copyright 2021 xSteins <itsmesteins@gmail.com>

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
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { A8, A9, B14, B12, B13, B15, B3, B11, A4, A5, A6, A7, B0, B1, B10 }
#define MATRIX_ROW_PINS { B5, B6, B7, B9, B8 }

#define DIODE_DIRECTION COL2ROW

/* key led setting */
//#define BACKLIGHT_PIN A8
//#define BACKLIGHT_PWM_DRIVER PWMD1
//#define BACKLIGHT_PWM_CHANNEL 1
//#define BACKLIGHT_LEVELS 6
//#define BACKLIGHT_BREATHING
//#define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE   5
#define TAPPING_TERM 500

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
