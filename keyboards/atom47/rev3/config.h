/*
Copyright 2012 Maarten Dekkers <atomkeeb@gmail.com

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

#ifndef REV3_CONFIG_H
#define REV3_CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0003
#define MANUFACTURER    Vortex
#define PRODUCT         Core
#define DESCRIPTION     Atom47 PCB for the Vortex Core Rev.3

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {B3,B2,B1,B0}
#define MATRIX_COL_PINS {B7,F0,F1,F4,F6,D4,D6,D7,B4,B5,C6,C7,F7}
#define UNUSED_PINS

#define BACKLIGHT_PIN B6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Backlight configuration
 */
#define BACKLIGHT_LEVELS 4

#define RGB_DI_PIN F5    // The pin the LED strip is connected to
#define RGBLED_NUM 6     // Number of LEDs in your strip

#define QMK_ESC_OUTPUT B7 // usually COL
#define QMK_ESC_INPUT B3 // usually ROW
#define QMK_LED E6

#endif
