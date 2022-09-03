/* Copyright 2021 Sets3n/Сэцэн
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
 * */

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x404A
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0001
#define MANUFACTURER    sets3n
#define PRODUCT         zx50

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B1, B2, D7, D6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, E6, C7, C6, B6, B5, B4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ENCODER */
#define ENCODERS_PAD_A { D5 }
#define ENCODERS_PAD_B { D3 }
#define ENCODER_RESOLUTION 2


/* RGB pin */
#define RGB_DI_PIN D4
#ifdef RGB_DI_PIN
#define RGBLED_NUM 62

// 0 --> CapsLock 1 --> NumLock 2 --> ScollLock
#define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, \
                           12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, \
                           25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, \
                           38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, \
                           51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61 }

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKL

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 230
#define RGBLIGHT_SLEEP
#endif

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_KEYPRESSES
#endif

#define OLED_DISPLAY_128X64
#define OLED_FONT_H "lib/glcdfont.c"

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define SPLIT_MODS_ENABLE
