
#pragma once

#define BMP_BOOTPIN_AS_RESET
/* key matrix size */
#define MATRIX_ROWS_DEFAULT 22
#define MATRIX_COLS_DEFAULT 8
#define THIS_DEVICE_ROWS 22
#define THIS_DEVICE_COLS 8
#define IS_LEFT_HAND true
#define BMP_DEFAULT_MODE SINGLE

#define MATRIX_ROW_PINS \
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define MATRIX_COL_PINS \
    { 0, 0, 0, 0, 0, 0, 0, 0 }
#define MATRIX_LAYOUT                                                          \
    { 42, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 0, \
    54, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 46, 47, 138, 43, 74, 75, 76, 84, 85, 86, 87, 0, \
    44, 21, 27, 9, 22, 24, 29, 25, 13, 19, 20, 48, 49, 41, 77, 78, 79, 96, 97, 98, 88, 0, \
    58, 5, 23, 8, 10, 11, 12, 14, 15, 16, 52, 53, 51, 93, 94, 95, 0, \
    170, 30, 28, 7, 26, 6, 18, 17, 55, 56, 57, 136, 174, 83, 90, 91, 92, 89, 0, \
    169, 172, 171, 140, 45, 139, 137, 175, 176, 102, 173, 81, 82, 80, 99, 100, 255 }

#define KEYMAP_PRIOR_LOCALE 0
#define KEYMAP_ASCII 0
#define CONFIG_RESERVED \
    { 0, 1, 0, 0, 0, 0, 0, 0 }

#ifndef __ASSEMBLER__
#include "microshell/core/msconf.h"
#include "microshell/util/mscmd.h"
#endif

#define RGBLIGHT_SPLIT
#define RGB_DI_PIN 255
#ifdef RGB_DI_PIN
#    define RGBLED_NUM_DEFAULT 128
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP /* If defined, the RGB lighting will be switched \
                              off when the host goes to sleep */
                           /*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
#    define RGBLIGHT_BREATHE_TABLE_SIZE 256  // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
#    define RGBLIGHT_EFFECT_BREATHE_MAX 255      // 0 to 255
#endif
