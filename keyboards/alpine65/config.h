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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6680 // BP for Bitmap
#define PRODUCT_ID      0x0065 // AR for Arctic
#define DEVICE_VER      0x0001
#define MANUFACTURER    Bitmap Designs
#define PRODUCT         Alpine65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { B9 , B8 , B7 , B6 , B5 , B4 , B3 , A15, A9 , A8 , B14, B12, A10, A0 , A1 }
#define MATRIX_ROW_PINS { C14, C15, C13, A2 , A3 }
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

#define RGB_DI_PIN B15
#define RGBLED_NUM 68
#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS

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
