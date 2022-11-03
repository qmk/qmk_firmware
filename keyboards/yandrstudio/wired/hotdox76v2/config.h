/* Copyright 2021 JasonRen(biu)
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAA9
#define DEVICE_VER      0x0002
#define MANUFACTURER    JasonRen biu
#define PRODUCT         hotdox76V2

/* key matrix size */
#define MATRIX_ROWS 6*2
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { D6, D7, B4, B5, B6, C6 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0, E6 }
#define MATRIX_ROW_PINS_RIGHT { D6, D7, B4, B5, B6, C6 }
#define MATRIX_COL_PINS_RIGHT { F7, F6, F5, F4, F1, F0, E6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW



// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4

#define TAP_CODE_DELAY 15


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_MATRIX_SPLIT {43, 43}
#    define SPLIT_TRANSPORT_MIRROR

#    define RGB_DI_PIN D3
#    define RGBLED_NUM (43*2)
#    define DRIVER_LED_TOTAL RGBLED_NUM

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define RGBLIGHT_VAL_STEP 15
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 112, 32 }

#    define RGB_MATRIX_KEYPRESSES

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGBLIGHT_ANIMATIONS

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#endif


#ifdef RGBLIGHT_ENABLE

#    define RGBLIGHT_SPLIT
#    define RGBLED_SPLIT {43, 43}
#    define RGB_DI_PIN D3
#    define RGBLED_NUM (43*2)
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SLEEP
#    define WS2812_TRST_US 100

// #    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#endif

#ifdef SPLIT_KEYBOARD

// #   define MASTER_RIGHT

#   define USE_SERIAL

#   define SOFT_SERIAL_PIN D2

#   define SPLIT_TRANSPORT_MIRROR

// #   define SPLIT_USB_DETECT

#   define SPLIT_MODS_ENABLE
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#   define SPLIT_OLED_ENABLE
#   define SPLIT_TRANSACTION_IDS_KB KEYBOARD_CURRENT_ALPA_SYNC

#endif


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
