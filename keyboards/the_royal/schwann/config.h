#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3521
#define DEVICE_VER      0x0001
#define MANUFACTURER    TheRoyalSweatshirt
#define PRODUCT         The Schwann PCB

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { F0, F1, F6, C7 }
#define MATRIX_COL_PINS { F4, F5, D5, D3, D2, C6, B6, B5, B4, D7, D6, D1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN B3
#define RGBLED_NUM 8    // Number of LEDs

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 4
#define RGBLIGHT_VAL_STEP 8
