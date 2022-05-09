// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spreadwriter.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;

    keypos_t key;
    if (index == 0) {
        if (clockwise) {
            key.row = 4;
            key.col = 0;
        } else {
            key.row = 0;
            key.col = 6;
        }
        uint8_t layer = layer_switch_get_layer(key);
        uint16_t keycode = keymap_key_to_keycode(layer, key);

        tap_code16(keycode);
        return false;
    }

    return true;
}
#endif
