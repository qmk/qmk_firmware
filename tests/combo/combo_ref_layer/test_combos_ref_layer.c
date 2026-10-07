// Copyright 2026 Dave Thompson (@dave-thompson)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

enum combos { ab_x, one_two_y };

uint16_t const ab_combo[]      = {KC_A, KC_B, COMBO_END};
uint16_t const one_two_combo[] = {KC_1, KC_2, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_x]      = COMBO(ab_combo, KC_X),
    [one_two_y] = COMBO(one_two_combo, KC_Y),
};
// clang-format on

// Layer 1 matches combos against layer 0's keycodes; every other layer
// (including layer 2) references itself.
uint8_t combo_ref_from_layer(uint8_t layer) {
    return layer == 1 ? 0 : layer;
}
