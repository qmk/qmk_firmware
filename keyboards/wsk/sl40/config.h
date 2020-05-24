#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xC456
#define DEVICE_VER      0x0001
#define MANUFACTURER    Worldspawn00
#define PRODUCT         SL40
#define DESCRIPTION     14-column staggered 40% keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, D2, D0 }
#define MATRIX_COL_PINS { D3, D1, F6, F7, B6, B2, B3, B1, D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F1
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

