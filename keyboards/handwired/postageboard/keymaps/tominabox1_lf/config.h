#pragma once

#include "config_common.h"

// /* USB Device descriptor parameter */
// #define VENDOR_ID       0xFEED
// #define PRODUCT_ID      0x6060
// #define DEVICE_VER      0x0001
// #define MANUFACTURER    Kingly-Keys
// #define PRODUCT         The Little Foot
// #define DESCRIPTION     A Mighty Small, 45-Percent, Ortholinear Keyboard.

/* key matrix size */
#undef MATRIX_ROWS
#define MATRIX_ROWS 5
#undef MATRIX_COLS
#define MATRIX_COLS 10

/* key matrix pins */
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { F6, B6, B2, B3, B1 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { F5, F7, B5, B4, E6, D7, C6, D4, D0, D1 }
#undef UNUSED_PINS
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
#define FORCE_NKRO

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN F4
#define RGBLED_NUM 17    // Number of LEDs
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 8

#undef COMBO_COUNT
#define COMBO_COUNT 6
