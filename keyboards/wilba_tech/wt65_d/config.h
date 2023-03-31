// Copyright 2022 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Keyboard Matrix Assignments
#define MATRIX_ROW_PINS { E6, F0, F4, F6, F7 }
#define MATRIX_COL_PINS { F5, D5, D3, D2, B7, B0, B3, C7, C6, B6, B5, B4, D7, D6, D4 }
#define DIODE_DIRECTION COL2ROW

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap 
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE