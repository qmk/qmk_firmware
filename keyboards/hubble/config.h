// Copyright 2022 Anton Chernenko (@ch3rny)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, F4, F7, B5, B1, B3, B6, B2 }
#define MATRIX_COL_PINS { F5, F6, B4, E6, D7, C6, D4, D0 }

#define DIODE_DIRECTION COL2ROW

/* rgb */
#define RGB_DI_PIN D2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 7
#define RGBLIGHT_SLEEP

#define DEBOUNCE 5
