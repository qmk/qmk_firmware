#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x4F42
#define DEVICE_VER      0x0001
#define MANUFACTURER    OsciX
#define PRODUCT         Shambles TKL

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* key matrix pins */
#define MATRIX_ROW_PINS { F5, B3, B1, F7 }
#define MATRIX_COL_PINS { D3, D1, D0, D4, C6, D7, E6, B4, B5, B6, B2, F4, F6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */


#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 0
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#endif
