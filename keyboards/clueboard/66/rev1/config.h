#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xC1ED
#define PRODUCT_ID      0x2301
#define DEVICE_VER      0x0003
#define MANUFACTURER    Clueboard
#define PRODUCT         Clueboard
#define DESCRIPTION     QMK keyboard firmware for Clueboard

/* key matrix size
 */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* ROWS: Top to bottom, COLS: Left to right
 */
#define MATRIX_COL_PINS { B3, F1, F4, F5, F6, C7, C6, B6, B5, B4, D7, D6, D4, F7, B0, B1 }
#define MATRIX_ROW_PINS { D1, D0, D2, D5, D3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

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

/* Underlight configuration
 */
#define RGB_DI_PIN B2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
