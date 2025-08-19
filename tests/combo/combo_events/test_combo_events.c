// Copyright 2025 @johnwilmes
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "stdio.h"

enum combos { ab_action, xy_123 };

uint16_t const ab_action_combo[] = {KC_A, KC_B, COMBO_END};
uint16_t const xy_123_combo[]    = {KC_X, KC_Y, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ab_action]     = COMBO_ACTION(ab_action_combo),
    [xy_123]     = COMBO(xy_123_combo, KC_1),
};
// clang-format on

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ab_action:
            if (pressed) {
                tap_code(KC_1);
            } else {
                tap_code(KC_2);
            }
            break;
    }
}

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case xy_123:
            switch (keycode) {
                case KC_X:
                    tap_code(KC_2);
                    break;
                case KC_Y:
                    tap_code(KC_3);
                    return true; // deactivate combo
                    break;
            }
    }
    return false;
}

bool combo_override = false;

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return !combo_override;
}
