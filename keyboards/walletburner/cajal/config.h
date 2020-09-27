#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Walletburner
#define PRODUCT         Cajal

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, D5, C7, C6 }
#define MATRIX_COL_PINS { F4, F1, F0, E6, B0, B1, B2, B3, D0, D1, D2, D3, B4, F6 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 18
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

