#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    UTD
#define PRODUCT         UTD80
#define DESCRIPTION     qmk keyboard firmware for UTD80

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B4, D5, D0, B2, B3, B0 }
#define MATRIX_COL_PINS { B1, F0, F1, F4, F5, F6, F7, C7, C6, D3, E6, D7, D6, D4, D2, D1 }
#define UNUSED_PINS

#define BACKLIGHT_PIN B7
#define BACKLIGHT_BREATHING
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif