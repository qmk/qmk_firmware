#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mupp
#define PRODUCT         Iso-Gherkin
#define DESCRIPTION     A 36 key ortholinear keyboard

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D0, D4 }
/*
 * #define MATRIX_COL_PINS { C6, D7, E6, B4, B5, F4, F5, F7, B1, B3, B2, B6 }
 */
#define MATRIX_COL_PINS { B6, B2, B3, B1, F4, F5, F7, B5, B4, E6, D7, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
/* #define BACKLIGHT_PIN B5 */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#define COMBO_COUNT 13
#define COMBO_TERM 200
#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define COMBO_ALLOW_ACTION_KEYS 
#define COMBO_VARIABLE_LEN
