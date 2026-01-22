// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos { ab_1, xy_2 };

uint16_t const ab_1_combo[] = {KC_A, KC_B, COMBO_END};
uint16_t const xy_2_combo[] = {KC_X, KC_Y, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_1]     = COMBO(ab_1_combo, KC_1),
    [xy_2]     = COMBO(xy_2_combo, KC_2),
};
// clang-format on

bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case ab_1:
            return true;
        default:
            return false;
    }
}

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case xy_2:
            return true;
        default:
            return false;
    }
}
