// Copyright 2022 Daniel Osipishin (@subrezon)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// key matrix
#define MATRIX_ROWS 6
#define MATRIX_ROW_PINS {D3, F4, D2, B2, B5, B6}

#define MATRIX_COLS 10
#define MATRIX_COL_PINS {B3, B1, F7, F6, F5, D4, C6, D7, E6, B4}

#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

// Bootmagic Lite
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// uncomment to reduce firmware size
//#define NO_DEBUG
//#define NO_PRINT
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
