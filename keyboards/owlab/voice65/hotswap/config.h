/*
Copyright 2021 kb-elmo<mail@elmo.space>

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4F53
#define PRODUCT_ID      0x564F
#define DEVICE_VER      0x0001
#define MANUFACTURER    OwLab
#define PRODUCT         Voice65 Hotswap

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B0, B1, B2, B10, B11 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A15, B8, B9, B12, B13 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* NKRO */
#ifdef NKRO_ENABLE
#    define FORCE_NKRO
#endif

/* RGB stripe */
#define RGB_DI_PIN B15
#ifdef RGB_DI_PIN
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLED_NUM 20
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_LIMIT_VAL 180
#    define OWL_VOLUME_RANGE 50
#endif

/* RGB matrix */
#ifdef RGB_MATRIX_ENABLE
#    define USE_I2CV2
#    define RGB_MATRIX_DISABLE_KEYCODES
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT  4
#    define RGB_MATRIX_LED_FLUSH_LIMIT    26
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define RGB_MATRIX_STARTUP_VAL        128
#    define DRIVER_ADDR_1                 0b0110000
#    define DRIVER_ADDR_2                 0b0110000
#    define DRIVER_COUNT                  2
#    define DRIVER_1_LED_TOTAL            67
#    define DRIVER_LED_TOTAL              DRIVER_1_LED_TOTAL
#endif

/* Encoder */
#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10
