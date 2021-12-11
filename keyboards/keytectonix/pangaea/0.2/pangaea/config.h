#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x1209 // temporary id for testing
#define PRODUCT_ID   0x4655 // temporary id for testing
#define DEVICE_VER   0x0001
#define MANUFACTURER Keytectonix
#define PRODUCT      Pangaea
#define DESCRIPTION  parts adjustable keyboard

/* key matrix size */
#define MATRIX_ROWS 9 * 2
#define MATRIX_COLS 9

/* key matrix pin assign */
#define MATRIX_ROW_PINS { B4, B5, F4, F5, F6,  D4, C6, D7, E6 }
#define MATRIX_COL_PINS { B4, B5, F4, F5, F6,  D4, C6, D7, E6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Specify the key to enter the bootloader*/
#define BOOTMAGIC_LITE_ROW 5
#define BOOTMAGIC_LITE_COLUMN 0

/* Split Keyboard specific options */
#define SOFT_SERIAL_PIN D3 /* serial communication pin */

/* RGB options */
#define RGB_DI_PIN D2
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 8
  #define RGBLIGHT_SPLIT
  #define RGBLED_SPLIT { 4, 4 }
  #ifdef RGB_MATRIX_ENABLE
    #define DRIVER_LED_TOTAL 8
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 8

    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS

    #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP
  #else
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 150 /* The maximum brightness level */
  //#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
//  #define RGBLIGHT_EFFECT_KNIGHT
//  #define RGBLIGHT_EFFECT_CHRISTMAS
//  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
//  #define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
    #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
    #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
    #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
/*== customize snake effect ==*/
    #define RGBLIGHT_EFFECT_SNAKE_LENGTH RGBLED_NUM
/*== customize knight effect ==*/
    #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 6
  #endif
#endif

// fix iPhone and iPad power adapter issue
// iOS device need lessthan 100
#define USB_MAX_POWER_CONSUMPTION 100

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
