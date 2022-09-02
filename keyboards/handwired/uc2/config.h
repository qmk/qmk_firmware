// Copyright 2022 Andy Chiu (@Andy Chiu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"



#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

#define MASTER_RIGHT

#define RGB_DI_PIN D3
#define DRIVER_LED_TOTAL 108

#ifdef RGB_DI_PIN
#    ifdef RGBLIGHT_ENABLE
#        define RGBLED_NUM 86 //108
#        define RGBLIGHT_LED_MAP {71,65,59,53,49,50,54,60,66,72,76,80,85,81,77,73,67,61,55,56,62,68,74,78,82,83,84,79,75,69,63,57,51,47,46,48,52,58,64,70,40,39,33,27,21,8,5,0,1,2,3,4,15,11,14,13,10,7,6,9,12,16,17,18,19,20,22,23,24,25,26,28,29,30,31,32,34,35,36,37,38,42,41,43,44,45}
#        define RGBLIGHT_HUE_STEP 8
#        define RGBLIGHT_SAT_STEP 8
#        define RGBLIGHT_VAL_STEP 8
#        define RGBLIGHT_LIMIT_VAL 100 /* The maximum brightness level */
#        define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#    elif defined RGB_MATRIX_ENABLE
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
//#   define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

/* Encoder*/
#ifdef ENCODER_ENABLE
// #define ENCODER_DIRECTION_FLIP
    #define ENCODERS_PAD_A { B4 }
    #define ENCODERS_PAD_B { B5 }
    #define ENCODER_RESOLUTION 4
#endif
