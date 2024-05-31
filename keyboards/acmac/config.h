// Copyright 2024 lynton ivins (@stirrem)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

/* key matrix size*/
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7, F6 }
#define MATRIX_COL_PINS { D3, D2, D1, D4, C6, D7, E6, B4 }
//#define UNUSED_PINS
