
#pragma once

#define BMP_BOOTPIN_AS_RESET
/* key matrix size */
#define MATRIX_ROWS_DEFAULT 6
#define MATRIX_COLS_DEFAULT 7
#define THIS_DEVICE_ROWS 3
#define THIS_DEVICE_COLS 7
#define IS_LEFT_HAND true
#define BMP_DEFAULT_MODE SPLIT_MASTER

#define MATRIX_ROW_PINS \
    { 16, 16, 16 }
#define MATRIX_COL_PINS \
    { 18, 18, 18, 18, 18, 18 }
#define MATRIX_LAYOUT                                                          \
    { 1, 2, 3, 4, 5, 6,   27,26,25,24,23,22,0,\
      8, 9, 10,11,12,13,  34,33,32,31,30,29,0,\
      15,16,17,18,19,20,  41,40,39,38,37,36,0,\
                7,14,21,  42,35,28,255\
    }

#define KEYMAP_PRIOR_LOCALE 0
#define KEYMAP_ASCII 0
#define CONFIG_RESERVED \
    { 0, 1, 0, 0, 0, 0, 0, 0 }

#define RGBLIGHT_SPLIT
#define G00 255 // Dummy for bin/qmk config generation
#define RGB_DI_PIN G00
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
