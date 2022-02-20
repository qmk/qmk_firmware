// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bamfk1.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    uint8_t layer = get_highest_layer(layer_state);
    uint16_t code = pgm_read_word(&(keymaps[layer][1][2 * index + clockwise]));
    tap_code16(code);
    return false;
}
