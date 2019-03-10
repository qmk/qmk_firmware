#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Jotix
#define PRODUCT         Jotanck
#define DESCRIPTION     A Jotantastic compact ortholinear keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* pro_micro pin-out */
#define MATRIX_ROW_PINS { D7, E6, B6, B2 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, D3, D2, D1, D0, D4, C6 }
#define UNUSED_PINS

/* leds */
#define QMK_LED B4
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_PIN B5

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
