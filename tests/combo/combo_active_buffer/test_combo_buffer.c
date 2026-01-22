// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos { ab_1, cd_2, ef_3 };

uint16_t const ab_1_combo[] = {KC_A, KC_B, COMBO_END};
uint16_t const cd_2_combo[] = {KC_C, KC_D, COMBO_END};
uint16_t const ef_3_combo[] = {KC_E, KC_F, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_1]     = COMBO(ab_1_combo, KC_1),
    [cd_2]    = COMBO(cd_2_combo, KC_2),
    [ef_3]    = COMBO(ef_3_combo, KC_3),
};
// clang-format on
