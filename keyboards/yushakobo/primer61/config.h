// Copyright 2023 yushakobo (@yushakobo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_COLS 7
#define MATRIX_ROWS 10

// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
