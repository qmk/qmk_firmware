/*
Copyright 2021 marby3

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
#define VENDOR_ID    0x4346
#define PRODUCT_ID   0x4346
#define DEVICE_VER   0x0001
#define MANUFACTURER marby3
#define PRODUCT      formy46

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B1, B3, B2, B6 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2

/* Split hand configration */
#define SPLIT_HAND_MATRIX_GRID B1, D4
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT

/* RGB Matrix define */
#define RGB_DI_PIN D3
#ifdef RGB_MATRIX_ENABLE
    #define RGBLED_NUM 46  // Number of LEDs
    #define DRIVER_LED_TOTAL RGBLED_NUM
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // Sane brightness values so the board has enough power to operate
    #define RGBLED_SPLIT { 23, 23 } // broken leds :(
    #define RGB_MATRIX_SPLIT RGBLED_SPLIT
/* RGB Matrix mode disabe */
//    #define DISABLE_RGB_MATRIX_ALPHAS_MODS
//    #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//    #define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #define DISABLE_RGB_MATRIX_BREATHING
//    #define DISABLE_RGB_MATRIX_BAND_SAT
    #define DISABLE_RGB_MATRIX_BAND_VAL
//    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//    #define DISABLE_RGB_MATRIX_CYCLE_ALL
    #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
    #define DISABLE_RGB_MATRIX_DUAL_BEACON
    #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
    #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #define DISABLE_RGB_MATRIX_RAINDROPS
//    #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    #define DISABLE_RGB_MATRIX_HUE_BREATHING
    #define DISABLE_RGB_MATRIX_HUE_PENDULUM
    #define DISABLE_RGB_MATRIX_HUE_WAVE
    #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
    #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    #define DISABLE_RGB_MATRIX_SPLASH
    #define DISABLE_RGB_MATRIX_MULTISPLASH
    #define DISABLE_RGB_MATRIX_SOLID_SPLASH
    #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLED_NUM 16
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif


/* Joystick define */
#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXES_COUNT 2

/* Rotary encoder define */
#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F7 }
#define ENCODER_RESOLUTION 4  //Default Setting

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Feature disable options */
//#define NO_DEBUG                //disable debugging
//#define NO_PRINT                //disable printing/debugging using hid_listen
//#define NO_ACTION_LAYER         //disable layers
//#define NO_ACTION_TAPPING       //disable tap dance and other tapping features
//#define NO_ACTION_ONESHOT       //disable one-shot modifiers
#define NO_ACTION_MACRO           //disable old-style macro handling using MACRO(), action_get_macro() (deprecated)
#define NO_ACTION_FUNCTION        //disable old-style function handling using fn_actions, action_function() (deprecated)


/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

