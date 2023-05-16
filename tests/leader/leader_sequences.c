// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_A)) {
        tap_code(KC_1);
    }

    if (leader_sequence_two_keys(KC_A, KC_B)) {
        tap_code(KC_2);
    }

    if (leader_sequence_three_keys(KC_A, KC_B, KC_C)) {
        tap_code(KC_3);
    }

    if (leader_sequence_four_keys(KC_A, KC_B, KC_C, KC_D)) {
        tap_code(KC_4);
    }

    if (leader_sequence_five_keys(KC_A, KC_B, KC_C, KC_D, KC_E)) {
        tap_code(KC_5);
    }
}
