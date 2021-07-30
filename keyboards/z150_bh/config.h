#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    blindassassin111
#define PRODUCT         Z-150 PCB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 20

/* key matrix pins */
#define MATRIX_ROW_PINS { C3, C2, C1, C0, E1 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D4, D5, D7, E0, C7, C6, C5, C4, F0, F1, F2, F3, F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN E7
#define LED_CAPS_LOCK_PIN B0
#define LED_SCROLL_LOCK_PIN E6

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* force n-key rollover*/
#define FORCE_NKRO

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
