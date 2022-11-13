// Copyright 2021-22 Willem McGloughlin (wymcg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D0, D4, C6 }
#define MATRIX_COL_PINS { D7, E6, B4, B5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
