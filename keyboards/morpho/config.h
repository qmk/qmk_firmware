#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    zk-phi
#define PRODUCT         Morpho
#define DESCRIPTION     An experimental keyboard to taste multiple row-staggered layouts

/* serial pin */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

/* key matrix */
// Rows are doubled-up for SPLIT_KEYBOARD
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5
