#pragma once

#include "config_common.h"

#define VENDOR_ID       0x4244 //-B-pen-D-ragon
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Bpendragon
#define PRODUCT         Selene
#define DESCRIPTION     A 109 key ANSI keyboard

#define MATRIX_ROWS 6
#define MATRIX_COLS 21

#define MATRIX_ROW_PINS { B10, B9, B15, B14, B13, B8}
#define MATRIX_COL_PINS { A9, A10, B11, B7, B6, B5, B4, B3, B2, B1, B0, C14, A4, A5, A6, A7, A8, A15, A13, A14, B12 }
#define UNUSED_PINS
#define RGB_DI_PIN A3
#define RGBLED_NUM 20
#define DYNAMIC_KEYCAP_LAYER_COUNT 4

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
