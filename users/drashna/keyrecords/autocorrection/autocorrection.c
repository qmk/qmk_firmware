// Copyright 2021 Google LLC
// Copyright 2022 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"
#include <string.h>

#if __has_include("autocorrection_data.h")
#    include "autocorrection_data.h"

bool process_autocorrection(uint16_t keycode, keyrecord_t* record) {
    static uint8_t typo_buffer[AUTOCORRECTION_MAX_LENGTH] = {KC_SPC};
    static uint8_t typo_buffer_size                       = 1;

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

    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            return true;
#    ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (((keycode >> 8) & 0x0f) == MOD_LSFT && record->event.pressed || !record->tap.count) {
                    return true;
            }
            keycode &= 0xFF;
            break;
#        ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->event.pressed || !record->tap.count) {
                return true;
            }
            keycode &= 0xFF;
            break;
#        endif
#    endif
#    ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            if ((keycode & 0xF) == MOD_LSFT) {
                return true;
            }
            keycode &= 0xF;
            break;
#    endif
        default:
            if (!record->event.pressed) {
                return true;
            }
    }

    // Subtract buffer for Backspace key, reset for other non-alpha.
    if (!(KC_A <= keycode && keycode <= KC_Z) && keycode != KC_SPC) {
        if (keycode == KC_BSPC && typo_buffer_size) {
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
    typo_buffer[typo_buffer_size++] = keycode;
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
        typo_buffer[0]   = KC_SPC;
        typo_buffer_size = 1;
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
