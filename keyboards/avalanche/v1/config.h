#pragma once

#define VENDOR_ID       0x0001
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    vitvlkv
#define PRODUCT         Avalanche
#define DESCRIPTION     QMK keyboard firmware for Avalanche

#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2

#define BACKLIGHT_PIN B0
