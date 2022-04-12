#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x9789
#define DEVICE_VER      0x0001
#define MANUFACTURER    Eagle
#define PRODUCT         II

#define MATRIX_ROWS 12
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { D0, B5, F1, B2, F7, F6, D4, D7, B4, B7, F5, B0 }
#define MATRIX_COL_PINS { D2, C6, E6, D5, B3, D3, D1, C7, F0, B6, B1, F4 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5
