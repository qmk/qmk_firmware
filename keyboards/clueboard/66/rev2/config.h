#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xC1ED
#define PRODUCT_ID      0x2320
#define DEVICE_VER      0x0001
#define MANUFACTURER    Clueboard
#define PRODUCT         Clueboard
#define DESCRIPTION     QMK keyboard firmware for Clueboard

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/* ROWS: Top to bottom, COLS: Left to right
*/
#define MATRIX_ROW_PINS { B2, C7, C6, B6, B5, B0, B3, D5, D3, D2 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, E6, B1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

 /* Backlight configuration
 */
#define BACKLIGHT_LEVELS 1

/* Underlight configuration
 */
#define RGB_DI_PIN D7
#define RGBLED_NUM 14     // Number of LEDs
#define RGBLIGHT_HUE_STEP 32
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#define RGBLIGHT_EFFECT_BREATHE_MAX 200
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 666*2
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3   // How many LEDs wide to light up
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 1   // The led to start at
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 5  // How many LEDs to travel
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4    // How many LEDs wide to light up
