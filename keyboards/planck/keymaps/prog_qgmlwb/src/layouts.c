// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "layouts.h"
#ifdef LAYER_NO
#   include "sendstring_norwegian.h"
#endif

KEYMAP keymaps [][MATRIX_ROWS][MATRIX_COLS] = {
    [QGMLWB_NO] = qgmlwb_no_map,
    [QGMLWB_EN] = qgmlwb_en_map,

    [QWERTY] = qwerty_map,
    [COLEMAK] = colemak_map,
    [DVORAK] = dvorak_map,

    [NORMAL_LOWER] = normal_lower_map,
    [NORMAL_RAISE] = normal_raise_map,

    [QGMLWB_LOWER] = qgmlwb_lower_map,
    [QGMLWB_RAISE] = qgmlwb_raise_map,

    [ADJUST] = adjust_map,
    [NUMPAD] = numpad_map,
};
