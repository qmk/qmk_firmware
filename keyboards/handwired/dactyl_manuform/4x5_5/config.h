// Copyright 2022 Shem Sedrick (@ssedrick)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 10
#define MATRIX_COLUMNS 5

// Wiring pins
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B4 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, F6 }

#define DIODE_DIRECTION COL2ROW

#define EE_HANDS
#define SPLIT_USB_DETECT
