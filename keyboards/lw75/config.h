// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix pins */
#define MATRIX_ROW_PINS { E6, B7, D0, D1, D2, B1 }
#define MATRIX_COL_PINS { D3, D5, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4, B0, B2 }

/*ENCODER*/
#define ENCODERS_PAD_A { F0 }
#define ENCODERS_PAD_B { F1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
