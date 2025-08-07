// Copyright 2022 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_mp10(
        KC_A   , KC_B   , KC_C   ,
	KC_D   , KC_E   , KC_F   ,
	RGB_M_R , UG_NEXT , UG_TOGG
    )
};
