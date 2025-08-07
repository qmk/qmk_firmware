// Copyright 2024 @Filios92
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

enum combos { alttab, esc };

uint16_t const alttab_combo[] = {KC_F, KC_G, COMBO_END};
uint16_t const esc_combo[]    = {KC_H, KC_J, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [alttab]  = COMBO(alttab_combo, KC_NO),
    [esc]     = COMBO(esc_combo, KC_ESC)
};
// clang-format on

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case alttab:
            if (pressed) {
                register_mods(MOD_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_mods(MOD_LALT);
            }
            break;
    }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case alttab:
            switch (keycode) {
                case KC_F:
                    tap_code16(S(KC_TAB));
                    return true;
                case KC_G:
                    tap_code(KC_TAB);
                    return true;
            }
    }
    return false;
}
