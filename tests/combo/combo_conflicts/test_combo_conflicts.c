// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

enum combos {ab_1, xy_2, axy_3, bxy_4, cxy_5, abcxy_6};

uint16_t const ab_1_combo[]     = {KC_A, KC_B, COMBO_END};
uint16_t const xy_2_combo[]     = {KC_X, KC_Y,  COMBO_END};
uint16_t const axy_3_combo[]     = {KC_A, KC_X, KC_Y, COMBO_END};
uint16_t const bxy_4_combo[]   = {KC_B, KC_X, KC_Y, COMBO_END};
uint16_t const cxy_5_combo[]   = {KC_C, KC_X, KC_Y, COMBO_END};
uint16_t const abcxy_6_combo[] = {KC_A, KC_B, KC_C, KC_X, KC_Y, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_1]     = COMBO(ab_1_combo, KC_1),
    [xy_2]     = COMBO(xy_2_combo, KC_2),
    [axy_3]     = COMBO(axy_3_combo, KC_3),
    [bxy_4]   = COMBO(bxy_4_combo, KC_4),
    [cxy_5]   = COMBO(cxy_5_combo, KC_5),
    [abcxy_6] = COMBO(abcxy_6_combo, KC_6)
};
// clang-format on

bool is_combo_contiguous(uint16_t index, combo_t *combo, keyrecord_t *record, uint8_t n_unpressed_keys) {
    switch (index) {
        case xy_2:
        case cxy_5:
            return true; // xy_2 and cxy_5 are contiguous combos
        default:
            return false; // no other combos are contiguous
    }
}
