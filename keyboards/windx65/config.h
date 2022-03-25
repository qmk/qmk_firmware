// Copyright 2022 thewerther (@thewerther)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define MANUFACTURER    WINDSTUDIO
#define PRODUCT         WINDX65
#define DEVICE_VER      0x0001

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, E6, D2, D1, D0 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D6, D4, F7, F6, F5, F4, F1, B2, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 6

    #define RGBLIGHT_HUE_STEP 15
    #define RGBLIGHT_SAT_STEP 15
    #define RGBLIGHT_VAL_STEP 15
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #define RGBLIGHT_ANIMATIONS
#endif

