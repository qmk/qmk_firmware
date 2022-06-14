#pragma once

#include "config_common.h"

#define VENDOR_ID       0xDE29
#define PRODUCT_ID      0x7325
#define DEVICE_VER      0x0001
#define MANUFACTURER    Leo Deng
#define PRODUCT         DJMax

#define MATRIX_ROWS 3
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { F0, F1, F4 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D6, D4 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_ON_STATE 0
