#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x2341
#define PRODUCT_ID      0x8036
#define DEVICE_VER      0x0001
#define MANUFACTURER    Short Circuits
#define PRODUCT         Hacro 8

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */

#define MATRIX_ROW_PINS { B7, D7 }
#define MATRIX_COL_PINS { B5, B4, D6, D4 } 

// ws2812 options
#define RGB_DI_PIN D2 // pin the DI on the ws2812 is hooked-up to
#define RGBLED_NUM 10 // number of LEDs
#define RGBLIGHT_ANIMATIONS

