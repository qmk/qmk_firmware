#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x484C  // "HL"
#define PRODUCT_ID      0x0087  // "TKL"
#define DEVICE_VER      0x0001
#define MANUFACTURER    Hardlineworks
#define PRODUCT         OTD-PLUS

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { D2, D4, D1, E6, F5, C6, B6, F6, F0, D0, D6, D3 }
#define MATRIX_COL_PINS { B3, B2, B1, B7, B0, F1, D7, F7, C7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define CAPS_LOCK_LED_PIN F4
#define SCROLL_LOCK_LED_PIN D5

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
