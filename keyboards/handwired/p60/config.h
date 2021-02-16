#pragma once

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001

#define MANUFACTURER p3lim
#define PRODUCT P60

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS {B0, B1, B2, B3, B7}
#define MATRIX_COL_PINS {F0, F1, F4, F5, F6, F7, B6, B5, B4, D7, D2, D3, C6, C7}

#define DIODE_DIRECTION COL2ROW
