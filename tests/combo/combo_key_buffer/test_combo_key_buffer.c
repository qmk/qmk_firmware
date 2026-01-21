// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos { ab_1, abx_2 };

uint16_t const ab_1_combo[]  = {KC_A, KC_B, COMBO_END};
uint16_t const abx_2_combo[] = {KC_A, KC_B, KC_X, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_1]     = COMBO(ab_1_combo, KC_1),
    [abx_2]    = COMBO(abx_2_combo, KC_2),
};
// clang-format on

bool is_combo_contiguous(uint16_t index, combo_t *combo, uint16_t keycode, keyrecord_t *record, uint8_t n_unpressed_keys) {
    return false; // No combos are contiguous in this test
}
