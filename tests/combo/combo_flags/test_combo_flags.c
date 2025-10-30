// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos { big, small };

uint16_t const big_combo[]   = {KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, COMBO_END};
uint16_t const small_combo[] = {KC_A, KC_D, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [big]     = COMBO(big_combo, KC_LEFT_SHIFT),
    [small]   = COMBO(small_combo, KC_LEFT_CTRL),
};
// clang-format on
