// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "layouts.h"

KEYMAP keymaps [][MATRIX_ROWS][MATRIX_COLS] = {
    [QGMLWB_NO] = qgmlwb_no_map,
    [QGMLWB_US] = qgmlwb_us_map,

    [QWERTY] = qwerty_map,
    [COLEMAK] = colemak_map,
    [DVORAK] = dvorak_map,

    [NORMAL_LOWER] = normal_lower_map,
    [NORMAL_RAISE] = normal_raise_map,

    [QGMLWB_NO_LOWER] = qgmlwb_no_lower_map,
    [QGMLWB_US_LOWER] = qgmlwb_us_lower_map,

    [QGMLWB_NO_RAISE] = qgmlwb_no_raise_map,
    [QGMLWB_US_RAISE] = qgmlwb_us_raise_map,

    [ADJUST] = adjust_map,
    [NUMPAD] = numpad_map,
};
