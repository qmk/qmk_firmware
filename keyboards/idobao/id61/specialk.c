// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "specialk.h"

bool special_registered;
bool delkey_registered;
bool keycode_raised[15];

bool ID61_process_special_k(uint16_t keycode, keyrecord_t *record, bool arrow_mode, uint8_t k_norm, uint8_t k_spcl, uint8_t k_altr) {
    bool is_raised = get_highest_layer(layer_state|default_layer_state) != 0;

    if (record->event.pressed) {
        keycode_raised[keycode - USER00] = is_raised;  // save for key release event
        if (is_raised) {
            // *** Fn keyed ***
            if (arrow_mode) {
                // alternate key
                register_code(k_altr);
            } else {
                // special key
                register_code(k_spcl);
            }
        } else {
            // *** normal, un-Fn'ed ***
            if (arrow_mode) {
                // special key
                register_code(k_spcl);
            } else {
                // normal key
                register_code(k_norm);
            }
        }
    } else {
        if (keycode_raised[keycode - USER00]) {
            // *** Fn keyed ***
            if (arrow_mode) {
                // alternate key
                unregister_code(k_altr);
            } else {
                // special key
                unregister_code(k_spcl);
            }
        } else {
            // *** normal, un-Fn'ed ***
            if (arrow_mode) {
                // special key
                unregister_code(k_spcl);
            } else {
                // normal key
                unregister_code(k_norm);
            }
        }
    }
    return false;
}

bool ID61_backspace_special(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();

    if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            register_code(KC_DEL);
            delkey_registered = true;
            set_mods(mod_state);
            return false;
        }
    } else {
        if (delkey_registered) {
            unregister_code(KC_DEL);
            delkey_registered = false;
            return false;
        }
    }
    return true;  // normal backspace, pass on
}
