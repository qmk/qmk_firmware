/*
Copyright 2017 Lei Yu <yuleiz@gmail.com>
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */

#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0x1977
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ning
#define PRODUCT         sf68
#define DESCRIPTION     q.m.k. keyboard firmware for sf68

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 9

// Change this to how you wired your keyboard
// COLS: Left to right, ROWS: Top to bottom
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, C6}
#define MATRIX_COL_PINS { C7, D0, D1, D2, D3, D4, D5, D6, D7}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

// rgb led

//#define RGBLIGHT_ANIMATION
#undef RGBLED_NUM
#define RGB_DI_PIN F0
#define RGBLED_NUM 1
//#define RGBLIGHT_HUE_STEP 8
//#define RGBLIGHT_SAT_STEP 8
//#define RGBLIGHT_VAL_STEP 8
//#define RGB_LIGHT_TIMER
//#define ws2812_PORTREG PORTF
//#define ws2812_DDRREG DDRF

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

#endif
