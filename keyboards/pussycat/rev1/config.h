/*
Copyright 2021 mrninhvn (https://github.com/mrninhvn)

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
#define VENDOR_ID       0x6E64  // Hai-Ninh Dang
#define PRODUCT_ID      0x7063
#define DEVICE_VER      0x0001
#define MANUFACTURER    mrninhvn
#define PRODUCT         PussyCat

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { A6, A7, B0, B1, B2, B10, B14, B15, B8, B9, A2, A10, C15, C14, C13 }
#define MATRIX_ROW_PINS { A8, B11, A5, A4, A3 }
#define DIODE_DIRECTION COL2ROW

// #define BACKLIGHT_PIN A8
// #define BACKLIGHT_PWM_DRIVER PWMD1
// #define BACKLIGHT_PWM_CHANNEL 1
// #define BACKLIGHT_LEVELS 6
// #define BACKLIGHT_BREATHING
// #define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* OLED DRIVER CONFIG */
#define OLED_DISPLAY_CUSTOM
#define OLED_DISPLAY_WIDTH 64
#define OLED_DISPLAY_HEIGHT 128
#define OLED_COM_PIN_OFFSET 32
#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#define OLED_BLOCK_TYPE uint16_t
#define OLED_SOURCE_MAP \
    { 0, 8, 16, 24, 32, 40, 48, 56 }
#define OLED_TARGET_MAP \
    { 56, 48, 40, 32, 24, 16, 8, 0 }
#define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#define OLED_COM_PINS COM_PINS_ALT
#define OLED_IC OLED_IC_SH1107
#define OLED_BRIGHTNESS 255
#define OLED_TIMEOUT 15000
#define OLED_UPDATE_INTERVAL 200

// #define RGBLIGHT_ANIMATIONS
// #define RGB_DI_PIN B15
// #define RGBLED_NUM 20
// #define WS2812_SPI SPID2

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
