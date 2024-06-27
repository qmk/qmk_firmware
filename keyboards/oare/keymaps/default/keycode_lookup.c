// Copyright 2024 Snipeye (@Snipeye)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode_lookup.h"
#include "keymap_introspection.h"

// Now we implement a custom "semi-transparent" keycode using KC_ENC:
// We fall through to layer 0 to get the actual keycode, then modify it according to what's in key_offsets
uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column) {
    uint16_t code = keycode_at_keymap_location_raw(layer_num, row, column);
    if (code == KC_ENC) {
        // don't return this, we need to fall through but then modify
        // Could make it more generic to fall to the next active layer instead of straight to 0, but I don't care that much.
        code = keycode_at_keymap_location_raw(0, row, column);
        // Only want to mess with it if it's in the alphas, so other functions like delete and such work right
        if (code >= KC_A && code <= KC_Z) {
            uint8_t index = key_positions[row][column];
            code += key_offsets[index];
            // key_offsets only holds positive numbers, 0-25.  If we go beyond z, need to wrap back to stay in the alphas
            if (code > KC_Z) {
                code -= KEY_OFFSET_SIZE;
            }
        }
    }
    return code;
}