/* Copyright 2021 TW59420 <https://github.com/TW59420>
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
#define VENDOR_ID       0x416D
#define PRODUCT_ID      0x4E45
// #define VENDOR_ID       0x6964  /* "id" */
// #define PRODUCT_ID      0x0042
#define DEVICE_VER      0x0001
#define MANUFACTURER    IDOBAO
#define PRODUCT         ID42

/* Key Matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/*
 * Keyboard Matrix Assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D5, C6, B6, E6 }
#define MATRIX_COL_PINS { B4, D7, D6, D4, B5, C7, F0, F7, F6, F1, F4, F5 }
// #define UNUSED_PINS {}
#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* Other settings */

/* Debounce reduces chatter (unintended double-presses) - set 0 if
   debouncing is not needed */
#define DEBOUNCE 5

/* NKRO by default is required to be turned on. This forces it on
   during keyboard startup regardless of EEPROM setting. */
#define FORCE_NKRO

/* Change the USB polling rate to 1000hz (1ms) and use larger value of keys
   per scan for elite games */
#define USB_POLLING_INTERVAL_MS  2
#define QMK_KEYS_PER_SCAN  12

/* LED Matrix & Animations */
#define RGB_DI_PIN B3
#if defined(RGB_DI_PIN) && defined(RGB_MATRIX_ENABLE)
    #define DRIVER_LED_TOTAL 42

    #define RGBLIGHT_ANIMATIONS
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS     // enable framebuffer effects
    #define RGB_DISABLE_WHEN_USB_SUSPENDED     // turn off effects when suspended
    #define RGB_MATRIX_KEYPRESSES

    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8

    /*
     * RGB Matrix Animation modes. Explicitly enabled
     * For full list of effects, see:
    * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
    */
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_BAND_SAT
    #define ENABLE_RGB_MATRIX_BAND_VAL
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #define ENABLE_RGB_MATRIX_CYCLE_ALL
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #define ENABLE_RGB_MATRIX_DUAL_BEACON
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #define ENABLE_RGB_MATRIX_RAINDROPS
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    #define ENABLE_RGB_MATRIX_HUE_BREATHING
    #define ENABLE_RGB_MATRIX_HUE_PENDULUM
    #define ENABLE_RGB_MATRIX_HUE_WAVE
    #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    #define ENABLE_RGB_MATRIX_PIXEL_FLOW
    #define ENABLE_RGB_MATRIX_PIXEL_RAIN

    #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
        #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
        #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
    #endif

    #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
        #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
        #define ENABLE_RGB_MATRIX_SPLASH
        #define ENABLE_RGB_MATRIX_MULTISPLASH
        #define ENABLE_RGB_MATRIX_SOLID_SPLASH
        #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    #endif
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
//#define NO_ACTION_LAYER     // disable layers
//#define NO_ACTION_TAPPING   // disable tap dance and other tapping features
//#define NO_ACTION_ONESHOT   // disable one-shot modifiers

/* disable these deprecated features by default */
#define NO_ACTION_MACRO     // disable old-styel macro handling
#define NO_ACTION_FUNCTION  // disable old-style function handling
