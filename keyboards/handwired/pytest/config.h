#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6465
#define DEVICE_VER      0x0001
#define MANUFACTURER    none
#define PRODUCT         pytest

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

#define MATRIX_COL_PINS { F4 }
#define MATRIX_ROW_PINS { F5 }
#define DIODE_DIRECTION COL2ROW
