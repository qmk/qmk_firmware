// Copyright 2023 Ismaïl Senhaji (@iSma)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 12
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 12
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#endif

#define DEBOUNCE 5

// Enter bootmagic with top right encoder
#define BOOTMAGIC_LITE_ROW 3
#define BOOTMAGIC_LITE_COLUMN 3
