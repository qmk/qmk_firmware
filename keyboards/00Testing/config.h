// Copyright 2022 no (@Potatpo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 12
#define MATRIX_COLS 9

#define DIODE_DIRECTION COL2ROW

#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xECA2
#define DEVICE_VER      0x0001
#define MANUFACTURER    Potatpo
#define PRODUCT         ArrowTKL
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
