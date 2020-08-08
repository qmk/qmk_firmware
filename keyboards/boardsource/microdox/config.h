#pragma once

#include "config_common.h"

#define VENDOR_ID       0xF7E0
#define PRODUCT_ID      0x0412
#define DEVICE_VER      0x0000
#define MANUFACTURER    Boardsource
#define PRODUCT         microdox

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS { B2, B6, B4, B5 }

// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1 }
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN D3
#define RGBLED_SPLIT { 6, 6 }
#define EE_HANDS
#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 12    // Number of LEDs
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION