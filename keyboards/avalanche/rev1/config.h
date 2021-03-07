#pragma once

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6062
#define DEVICE_VER      0x0001
#define MANUFACTURER    vitvlkv
#define PRODUCT         Avalanche
#define DESCRIPTION     QMK keyboard firmware for Avalanche

#define MATRIX_ROWS 12
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define USE_I2C
