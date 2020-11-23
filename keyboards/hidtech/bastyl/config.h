#pragma once
#include "config_common.h"
#define VENDOR_ID 0x2F8A
#define PRODUCT_ID 0x1827
#define DEVICE_VER 0x0001
#define MANUFACTURER HID Technologies
#define PRODUCT Bastyl
#define DESCRIPTION A high-end split keyboard

#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS { D7, B5, F7, F6, B6 }
#define MATRIX_COL_PINS { B4, E6, C6, B1, B3, B2 }
#define RGB_DI_PIN D2
#define RGBLED_NUM 38
#define RGBLIGHT_SPLIT
#define RGBLIGHT_ANIMATIONS
#define DEBOUNCE 5
#define SOFT_SERIAL_PIN D0
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PERMISSIVE_HOLD
#define USE_SERIAL
#define MASTER_RIGHT
