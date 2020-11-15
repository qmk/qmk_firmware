#pragma once

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x991D
#define DEVICE_VER 0x0001
#define MANUFACTURER Apple
#define PRODUCT M5120
#define DESCRIPTION Apple laptop keyboard controlled by a Teensy

#define MATRIX_ROWS 8
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6, F7, B6, B5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B7, D0, D1, D2, D3, C6, C7, D5 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
