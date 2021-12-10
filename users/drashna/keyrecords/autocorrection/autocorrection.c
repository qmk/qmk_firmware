// Copyright 2021 Google LLC
// Copyright 2022 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"
#include <string.h>

#if __has_include("autocorrection_data.h")
#    include "autocorrection_data.h"

bool process_autocorrection(uint16_t keycode, keyrecord_t* record) {
    static uint8_t typo_buffer[AUTOCORRECTION_MAX_LENGTH] = {0};
    static uint8_t typo_buffer_size                       = 0;

    if (keycode == AUTO_CTN) {
        if (record->event.pressed) {
            typo_buffer_size = 0;
            userspace_config.autocorrection ^= 1;
            eeconfig_update_user(userspace_config.raw);
        }
        return false;
    }

    if (!userspace_config.autocorrection) {
        typo_buffer_size = 0;
        return true;
    }
    // Exclude Shift hold from resetting autocorrection.
    if (keycode == KC_LSFT || keycode == KC_RSFT ||
         (QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX &&
         ((keycode >> 8) & 0x0f) == MOD_LSFT && !record->tap.count) ||
         (QK_ONE_SHOT_MOD <= keycode && keycode <= QK_ONE_SHOT_MOD_MAX &&
         (((keycode & 0xFF) & ~MOD_MASK_SHIFT) != 0))) {
        return true;
    }

    // Subtract buffer for Backspace key, reset for other non-alpha.
    if (!(KC_A <= (uint8_t)keycode && (uint8_t)keycode <= KC_Z) && (uint8_t)keycode != KC_SPC) {
        if ((uint8_t)keycode == KC_BSPC && typo_buffer_size) {
            --typo_buffer_size;
        } else {
            typo_buffer_size = 0;
        }
        return true;
    }

    // Rotate oldest character if buffer is full.
    if (typo_buffer_size >= AUTOCORRECTION_MAX_LENGTH) {
        memmove(typo_buffer, typo_buffer + 1, AUTOCORRECTION_MAX_LENGTH - 1);
        typo_buffer_size = AUTOCORRECTION_MAX_LENGTH - 1;
    }

    // Append `keycode` to buffer.
    typo_buffer[typo_buffer_size++] = (uint8_t)keycode;
    // Return if buffer is smaller than the shortest word.
    if (typo_buffer_size < AUTOCORRECTION_MIN_LENGTH) {
        return true;
    }

    // Check for typo in buffer using a trie stored in `autocorrection_data`.
    uint16_t state = 0;
    for (uint8_t i = typo_buffer_size - 1; i >= 0; --i) {
        uint8_t const buffer = typo_buffer[i];
        uint8_t       code   = pgm_read_byte(autocorrection_data + state);

        if (code & 128) {  // Check for match in node with multiple children.
            code &= 127;
            for (; code != buffer; code = pgm_read_byte(autocorrection_data + (state += 3))) {
                if (!code) {
                    return true;
                }
            }
            // Follow link to child node.
            state = (pgm_read_byte(autocorrection_data + state + 1) | pgm_read_byte(autocorrection_data + state + 2) << 8);
            if ((state & 0x8000) != 0) {
                goto found_typo;
            }
            // Check for match in node with single child.
        } else if (code != buffer) {
            return true;
        } else if (!pgm_read_byte(autocorrection_data + (++state)) && !(pgm_read_byte(autocorrection_data + (++state)) & 128)) {
            goto found_typo;
        }
    }
    return true;

found_typo:  // A typo was found! Apply autocorrection.
    state &= 0x7fff;
    uint8_t const backspaces = pgm_read_byte(autocorrection_data + state);
    for (uint8_t i = 0; i < backspaces; ++i) {
        tap_code(KC_BSPC);
    }
    send_string_P((char const*)(autocorrection_data + state + 1));

    if (keycode == KC_SPC) {
        typo_buffer[0] = KC_SPC;
        typo_buffer_size    = 1;
        return true;
    } else {
        typo_buffer_size = 0;
        return false;
    }
}
#else
#    pragma message "Warning!!! Autocorrect is not corretly setup!"
bool process_autocorrection(uint16_t keycode, keyrecord_t* record) { return true; }
#endif
