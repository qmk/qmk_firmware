// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x1212
#define DEVICE_VER   0x0001
#define MANUFACTURER TweetyDaBird
#define PRODUCT      LBS6

// key matrix size
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

// Keyboard Matrix Assignments
#define DIRECT_PINS { { F5, NO_PIN, NO_PIN },{ C6, E6, B5 }, { D4, D7, B4 } }
//#define DIRECT_PINS { {F5, C6, E6, B5, D4, D7, B4  } }

// Encoder Assignments
#define ENCODERS_PAD_A { F7 }
#define ENCODERS_PAD_B { F6 }
#define ENCODER_RESOLUTION 2

// RGB Assignments
#define RGB_DI_PIN D2
#define DRIVER_LED_TOTAL 8

#ifdef RGB_DI_PIN
#   define RGBLED_NUM 8

#   define RGBLIGHT_HUE_STEP 8
#   define RGBLIGHT_SAT_STEP 8
#   define RGBLIGHT_VAL_STEP 8

#   define RGBLIGHT_LIMIT_VAL 200 // The maximum brightness level
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

// Bootmagic Lite key configuration
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
