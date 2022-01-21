/*
Copyright 2020 Danny Nguyen <danny@keeb.io>

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
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x2133
#define DEVICE_VER      0x0200
#define MANUFACTURER    Keebio
#define PRODUCT         BDN9 Rev. 2

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { B12, B5, B6 }, \
    { B14, B4, B7 }, \
    { A3, F1, F0 } \
}

// Left, Right, Middle
#define ENCODERS_PAD_A { A8, B3, A10 }
#define ENCODERS_PAD_B { A4, A15, A9 }
#define TAP_CODE_DELAY 10

#define RGB_DI_PIN B15
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 11
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
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#        define ENABLE_RGB_MATRIX_ALPHAS_MODS
#        define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_BREATHING
#        define ENABLE_RGB_MATRIX_BAND_SAT
#        define ENABLE_RGB_MATRIX_BAND_VAL
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        define ENABLE_RGB_MATRIX_CYCLE_ALL
#        define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define ENABLE_RGB_MATRIX_DUAL_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        define ENABLE_RGB_MATRIX_RAINDROPS
#        define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#        define ENABLE_RGB_MATRIX_HUE_BREATHING
#        define ENABLE_RGB_MATRIX_HUE_PENDULUM
#        define ENABLE_RGB_MATRIX_HUE_WAVE
#        define ENABLE_RGB_MATRIX_PIXEL_RAIN
#        define ENABLE_RGB_MATRIX_PIXEL_FLOW
#        define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#        define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#        define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define ENABLE_RGB_MATRIX_SPLASH
#        define ENABLE_RGB_MATRIX_MULTISPLASH
#        define ENABLE_RGB_MATRIX_SOLID_SPLASH
#        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    endif
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
