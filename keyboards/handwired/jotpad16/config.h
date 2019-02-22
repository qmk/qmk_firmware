#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jotix
#define PRODUCT         JotPad16
#define DESCRIPTION     A Jotantastic compact NumPad

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* pro_micro pin-out */
#define MATRIX_ROW_PINS { B6, B2, D2, D3 }
#define MATRIX_COL_PINS { B5, B4, B3, B1 }
#define UNUSED_PINS

/* leds */
#define QMK_LED E6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_PIN D7

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

