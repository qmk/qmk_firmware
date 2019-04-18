#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xF1E7
#define PRODUCT_ID      0x5163
#define DEVICE_VER      0x0000
#define MANUFACTURER    troyfletcher
#define PRODUCT         Signum
#define DESCRIPTION     q.m.k. keyboard firmware for Signum 3.0

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { D2, D1, F5, B5 }
#define MATRIX_COL_PINS { B4, D7, D0, E6, D4, F6, F4, F7, B1, B3, C6, B2 }
#define UNUSED_PINS

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
