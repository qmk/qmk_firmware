// Copyright 2023 BlindAssassin111 (@blindassassin111)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 12
#define MATRIX_COLS 11

#define MATRIX_ROW_PINS { C7, B6, B5, B4, D7, D6 }
#define MATRIX_COL_PINS { C6, F6, F5, F4, F1, F7, B7, D2, D3, D5, D4 }
#define MATRIX_ROW_PINS_RIGHT { C7, B6, F4, F5, F6, F7 }
#define MATRIX_COL_PINS_RIGHT { C6, F1, B4, B5, D2, D3, D5, D4, D6, D7 }

/* Split Defines */
#define SPLIT_USB_DETECT
#define MASTER_LEFT
#define USE_I2C

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
