// Copyright 2022 LucW (@luc-languagetools)
// SPDX-License-Identifier: GPL-2.0-or-later


#pragma once


/* Select hand configuration */

// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

//#define TAPPING_FORCE_HOLD
//#define TAPPING_TERM 100

// #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD 

// MOUSE SETTINGS
// ==============

#define MOUSEKEY_TIME_TO_MAX 200

#define RGBLIGHT_LAYERS

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 90
    // #define RGBLIGHT_LIMIT_VAL 0
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
 // #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
 // #define RGB_MATRIX_KEYPRESSES // reacts to keypresses 
 // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
 // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
 // #define ENABLE_RGB_MATRIX_SPLASH
 //#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
