#pragma once

#include "config_common.h"

#define VENDOR_ID       0x00FA
#define PRODUCT_ID      0x2022
#define DEVICE_VER      0x0001
#define MANUFACTURER    JJ48_24 & Engineermachine
#define PRODUCT         Gentleman 65
#define DESCRIPTION     A Keyboard Fit For A Gentleman


#define MATRIX_ROWS 5
#define MATRIX_COLS 16


#define MATRIX_ROW_PINS { D3, D2, D1, F7, F1 }
#define MATRIX_COL_PINS { D4, D6, D7, B4, B5, B6, C6, D5, C7, F0, B2, B1, B3, B0, B7, D0 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN F4
#define RGBLED_NUM 14
#define RGBLIGHT_ANIMATIONS

#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 3

#define DRIVER_LED_TOTAL 14


