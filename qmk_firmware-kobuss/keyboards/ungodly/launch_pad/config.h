/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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
#define VENDOR_ID       0x5544 // "UD" = Ungodly Design
#define PRODUCT_ID      0x4C50 // "LP" = Launch Pad
#define DEVICE_VER      0x9999
#define MANUFACTURER    Ungodly Design
#define PRODUCT         Launch Pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D4, D6, D7, B4, B5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder Assignment */
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { B6 }
#define ENCODER_RESOLUTION 2

/* Midi Slider */
#define SLIDER_PIN F6

/* RGB Matrix configuration */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES
#endif

#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 22
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
// RGB Matrix
#    ifdef RGB_MATRIX_ENABLE
#        define DRIVER_LED_TOTAL RGBLED_NUM
#    endif
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LOCKING_RESYNC_ENABLE

#define MIDI_ADVANCED
