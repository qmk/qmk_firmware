#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C47 // LG
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Luigi311
#define PRODUCT         Stream Cheap

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

#define DIRECT_PINS { { D7, E6, B3, B1}, { B5, B4, B2, B6} }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
