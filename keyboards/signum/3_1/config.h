#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    troy fletcher
#define PRODUCT         signum 3.1
#define DESCRIPTION     small ortholinear keyboard
#define MATRIX_ROWS 6
#define MATRIX_COLS 10
#define MATRIX_ROW_PINS { D2, D1, F5, B5, B2, C6 }
#define MATRIX_COL_PINS { B4, D7, D0, E6, D4, F6, F4, F7, B1, B3 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNE 5
