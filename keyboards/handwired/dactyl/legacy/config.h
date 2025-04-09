// Copyright 2017 Matthew Adereth
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 6
#define MATRIX_COLS 12
#define COL_EXPANDED { true, true, true, true, true, true, false, false, false, false, false, false}
#define MATRIX_ONBOARD_ROW_PINS { F0, F1, F4, F5, F6, F7 }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0, B1, B2, B3, D2, D3, C6 }
#define EXPANDER_COL_REGISTER GPIOA
#define EXPANDER_ROW_REGISTER GPIOB
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3, 4, 5}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3, 4, 5}

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER
