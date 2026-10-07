// Copyright 2021 SawnsProjects
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x3(
        KC_ESC,  KC_GRV,  TO(1),
        KC_Z,    KC_X,    KC_C
    ),
    [1] = LAYOUT_ortho_2x3(
        _______, _______, TO(0),
        _______, _______, _______
    )
};
