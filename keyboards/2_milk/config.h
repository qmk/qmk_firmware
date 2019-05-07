#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0xB195
#define DEVICE_VER      0x0001
#define MANUFACTURER    rionlion100
#define PRODUCT         2% Milk
#define DESCRIPTION     A milk themed 2% Keyboard

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 1

/* Milk defualt pinout*/
#define DIRECT_PINS { \
    { D4, C6 }, \
}
#define UNUSED_PINS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B6
#define RGBLED_NUM 1
#endif
