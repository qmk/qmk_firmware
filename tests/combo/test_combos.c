// Copyright 2023 Stefan Kerkmann (@KarlK90)
// Copyright 2023 @filterpaper
// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

uint16_t const modtest_combo[]    = {KC_Y, KC_U, COMBO_END};
uint16_t const osmshift_combo[]   = {KC_Z, KC_X, COMBO_END};
uint16_t const single_key_combo[] = {KC_A, COMBO_END};
uint16_t const ab_1_combo[]     = {KC_A, KC_B, COMBO_END};
uint16_t const cd_2_combo[]     = {KC_C, KC_D,  COMBO_END};
enum combos { modtest, osmshift, single_key_combo, ab_1, cd_2 };

// clang-format off
combo_t key_combos[] = {
    [modtest]  = COMBO(modtest_combo, RSFT_T(KC_SPACE)),
    [osmshift] = COMBO(osmshift_combo, OSM(MOD_LSFT)),
    [single_key] = COMBO(single_key_combo, KC_B),
    [ab_1]     = COMBO(ab_1_combo, KC_1),
    [cd_2]     = COMBO(cd_2_combo, KC_2)
};
// clang-format on
