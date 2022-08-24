#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDA31 // "MD"
#define PRODUCT_ID      0x0002 // "RD"
#define DEVICE_VER      0x0002
#define MANUFACTURER    DaVinci Ergonomics Laboratory
#define PRODUCT         DaVinci v1 mini Keyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

// wiring of each half
#define MATRIX_ROW_PINS { B4, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#define RGBLED_NUM 14    // Number of LEDs

#define RGBLIGHT_SPLIT   // sync LEDs between RIGHT and LEFT hand

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

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL 
#define MK_C_OFFSET_0 8
#define MK_C_OFFSET_UNMOD 16
#define MK_C_OFFSET_1 28
#define MK_C_OFFSET_2 40
#define MK_C_INTERVAL_0 16
#define MK_C_INTERVAL_UNMOD 16
#define MK_C_INTERVAL_1 16
#define MK_C_INTERVAL_2 16