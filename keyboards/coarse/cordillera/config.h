/*
Copyright 2020 coarse <coarsekeys@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x434B // CK for Coarse Keys
#define PRODUCT_ID      0x1401 // '20 - 001
#define DEVICE_VER      0x0001 // Revision prototype
#define MANUFACTURER    Coarse
#define PRODUCT         Cordillera

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { A13, B9, F1, A10, A9 }
#define MATRIX_COL_PINS { B15, B14, B13, B12, B11, B10, B2, B1, B8, B7, B6, B5, B4, B3, A15, A14 }
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN A1
#define LED_SCROLL_LOCK_PIN A0
#define LED_PIN_ON_STATE 0

#define BACKLIGHT_PIN           A8
#define BACKLIGHT_PWM_DRIVER    PWMD1
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      1
#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

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
