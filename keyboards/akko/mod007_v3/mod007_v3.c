// Copyright 2024 jonylee@hfd (@jonylee1986)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// clang-format off
enum __layers {
    WIN_B,
    WIN_W,
    WIN_FN,
    MAC_B,
    MAC_W,
    MAC_FN
};
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case DF(WIN_B):
            if ( record->event.pressed) {
                set_single_persistent_default_layer(WIN_B);
            }
            return false;
        case DF(MAC_B):
            if (record->event.pressed) {
                set_single_persistent_default_layer(MAC_B);
                keymap_config.no_gui     = 0;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        default:
            return true;
    }
}
