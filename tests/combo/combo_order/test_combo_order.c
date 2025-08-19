// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos {abc_1, cab_2, xyz_3};

uint16_t const abc_1_combo[]     = {KC_A, KC_B, KC_C, COMBO_END};
uint16_t const cab_2_combo[]     = {KC_C, KC_A, KC_B, COMBO_END};
uint16_t const xyz_3_combo[]     = {KC_X, KC_Y, KC_Z, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [abc_1]     = COMBO(abc_1_combo, KC_1),
    [cab_2]     = COMBO(cab_2_combo, KC_2),
    [xyz_3]     = COMBO(xyz_3_combo, KC_3)
};
// clang-format on

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        // these two must be pressed in order
        case abc_1:
        case cab_2:
            return true;
        default:
        // xyz does not require pressing in order
            return false;
    }
}
