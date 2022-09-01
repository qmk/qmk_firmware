// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x1212
#define DEVICE_VER   0x0001
#define MANUFACTURER TweetyDaBird
#define PRODUCT      littlebigscroll4

// key matrix size
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

// Keyboard Matrix Assignments
#define DIRECT_PINS { { E6, D7, B5, B4, F4 } }
#define UNUSED_PINS

// Encoder Assignments
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { F7 }
#define ENCODER_RESOLUTION 2

// RGB Assignments
#define RGB_DI_PIN D2
#define DRIVER_LED_TOTAL 6


#ifdef RGB_DI_PIN
#   define RGBLED_NUM 6

#   define RGBLIGHT_HUE_STEP 8
#   define RGBLIGHT_SAT_STEP 8
#   define RGBLIGHT_VAL_STEP 8

#   define RGBLIGHT_LIMIT_VAL 175 // The maximum brightness level
# 	define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL

#   define RGBLIGHT_SLEEP  // If defined, the RGB lighting will be switched off when the host goes to sleep
# 	define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

//== all animations enable ==
#    define RGBLIGHT_ANIMATIONS
//== or choose animations ==
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING


#endif

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

// disable debug print
//#define NO_DEBUG

// disable print
//#define NO_PRINT

// disable action features
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// Bootmagic Lite key configuration
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
