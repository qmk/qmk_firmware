#pragma once

#include "config_common.h"

#define VENDOR_ID       0x4B42
#define PRODUCT_ID      0x6068
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDfans
#define PRODUCT         Maja Hotswap

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { F0, B6, B5, B4, D7 }
#define MATRIX_COL_PINS { C6, C7, F7, F6, F5, F4, F1, B0, B1, B2, B3, B7, D2, D3, D5 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#ifdef RGB_MATRIX_ENABLE
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_KEYPRESSES
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 31
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#endif