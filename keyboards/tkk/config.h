// Copyright 2022 Joe Fass (@jfass)
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

#define MATRIX_ROWS 1
#define MATRIX_COLS 10
//#define DIRECT_PINS { { "B0", "B1", "B2", "B3", "B7", "D0", "D1", "D2", "D3", "C6" } }

//#define ONESHOT_TAP_TOGGLE 1000  /* Tapping this number of times holds the key until tapped once again. */
//#define ONESHOT_TIMEOUT 100      /* Time (in ms) before the one shot key is released */

