// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// key matrix settings
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS \
    { B6, B2, B3, B1, F7 }
#define MATRIX_COL_PINS \
    { D4, C6, D2, E6, B4, B5, F6 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }

// Underglow LED settings

#define RGB_DI_PIN D7
#define RGBLED_NUM 9
