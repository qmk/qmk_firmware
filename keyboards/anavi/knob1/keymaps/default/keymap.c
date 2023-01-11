// Copyright 2022 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//#include <stdio.h>

enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_k1(
        KC_MUTE
    )
};
