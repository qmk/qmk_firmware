#include <quantum.h>

// Define some combos to use for the test, including overlapping combos and
// combos that chord tap-hold keys.
enum combo_events { AB_COMBO, BC_COMBO, AD_COMBO, DE_COMBO, FGHI_COMBO };

const uint16_t ab_combo[] PROGMEM   = {KC_A, KC_B, COMBO_END};
const uint16_t bc_combo[] PROGMEM   = {KC_B, KC_C, COMBO_END};
const uint16_t ad_combo[] PROGMEM   = {KC_A, LCTL_T(KC_D), COMBO_END};
const uint16_t de_combo[] PROGMEM   = {LCTL_T(KC_D), LT(1, KC_E), COMBO_END};
const uint16_t fghi_combo[] PROGMEM = {KC_F, KC_G, KC_H, KC_I, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [AB_COMBO] = COMBO(ab_combo, KC_SPC),  // KC_A + KC_B = KC_SPC
    [BC_COMBO] = COMBO(bc_combo, KC_X),    // KC_B + KC_C = KC_X
    [AD_COMBO] = COMBO(ad_combo, KC_Y),    // KC_A + LCTL_T(KC_D) = KC_Y
    [DE_COMBO] = COMBO(de_combo, KC_Z),    // LCTL_T(KC_D) + LT(1, KC_E) = KC_Z
    [FGHI_COMBO] = COMBO(fghi_combo, KC_W) // KC_F + KC_G + KC_H + KC_I = KC_W
};
