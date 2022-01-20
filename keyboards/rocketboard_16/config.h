/*
Copyright 2020 Seth Bonner <fl3tching101@gmail.com>

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
#define VENDOR_ID       0xB034
#define PRODUCT_ID      0xFF16
#define DEVICE_VER      0x0001
#define MANUFACTURER    Rocketboard
#define PRODUCT         Rocketboard-16

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { A9, B13, B14, B15, B3 }
#define MATRIX_COL_PINS { B8, B9, B10, B11 }
#define DIODE_DIRECTION COL2ROW

/* Bootmagic key - row 4, col 1 */
#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN A4
#define RGBLED_NUM 16
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP

// OLED stuff
#define OLED_DISPLAY_128X64
#define OLED_FONT_H "custom_font.h"

// Allows for rotary encoder volume control
#define TAP_CODE_DELAY 20

/* Encoder stuff */
#define ENCODERS_PAD_A \
    { A0, A2 }
#define ENCODERS_PAD_B \
    { A1, A3 }

#define LOCKING_SUPPORT_ENABLE
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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
