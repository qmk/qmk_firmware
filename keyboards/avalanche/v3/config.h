// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VENDOR_ID       0xCEE2
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0003
#define MANUFACTURER    vitvlkv
#define PRODUCT         Avalanche

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2

#define RGB_DI_PIN D3

#define RGBLED_NUM 12
#define RGBLED_SPLIT { 7, 7 }
#define RGBLIGHT_SPLIT

#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 2
