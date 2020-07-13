#pragma once

#include "config_common.h"

#define VENDOR_ID       0x1234
#define PRODUCT_ID      0x5678
#define DEVICE_VER      0x0001
#define MANUFACTURER    QMK
#define PRODUCT         Selen
#define DESCRIPTION     A 109 key ANSI keyboard

#define MATRIX_ROWS 8
#define MATRIX_COLS 23

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5, C6, C7, D0, D1, F0, D3, D4, F1, D6, D7, E0, E1, E2, E3, E4, E5, E6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
