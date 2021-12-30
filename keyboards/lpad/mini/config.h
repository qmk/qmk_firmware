/* Copyright 2021 bululau
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    lpad
#define PRODUCT         mini
#define DESCRIPTION     Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D3, D4, D5, D6 }
#define MATRIX_COL_PINS { B4, B5, B6, B7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#define RGB_DI_PIN B0
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 22        //13+9


//encoder
#define ENCODERS_PAD_B { F0, F4 }
#define ENCODERS_PAD_A { F1, F5 }

#define ENCODER_RESOLUTION 4


#define OLED_TIMEOUT 100000
// #define OLED_FONT_WIDTH 6
// #define OLED_FONT_HEIGHT 8
// #define OLED_FONT_H "./lib/glcdfont.c"

/* EEPROM for via */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8


#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
