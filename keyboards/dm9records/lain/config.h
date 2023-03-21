// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/*
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS \
    { C6, D7, D6, D4 }
#define MATRIX_COL_PINS \
    { C7, F7, F6, F5, F4, F1, F0, B3, B2, B1, D2, D3, D5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* LED Settings */
#define LED_NUM 3
#define LED_PINS \
    { B6, B5, B4 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
