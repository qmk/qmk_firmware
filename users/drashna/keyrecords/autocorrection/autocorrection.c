// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"
#include <string.h>

#if __has_include("autocorrection_data.h")
#    pragma GCC push_options
#    pragma GCC optimize("O0")
#    include "autocorrection_data.h"
#    if AUTOCORRECTION_MIN_LENGTH < 4
#        error Minimum Length is too short and may cause overflows
#    endif
#    if DICTIONARY_SIZE > SIZE_MAX
#        error Dictionary size excees maximum size permitted
#    endif

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
            if (((keycode >> 8) & 0xF) == MOD_LSFT) {
                return true;
            }
#        ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#        endif
            if (record->event.pressed || !record->tap.count) {
                return true;
            }
            keycode &= 0xFF;
            break;
#    endif
#    ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            if ((keycode & 0xF) == MOD_LSFT) {
                return true;
            }
#    endif
        default:
            // Disable autocorrection while a mod other than shift is active.
            if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
                typo_buffer_size = 0;
                return true;
            }
            if (!record->event.pressed) {
                return true;
            }
    }


    // Subtract buffer for Backspace key, reset for other non-alpha.
    if (!(KC_A <= keycode && keycode <= KC_Z)) {
        if (keycode == KC_BSPC) {
            // Remove last character from the buffer.
            if (typo_buffer_size > 0) {
                --typo_buffer_size;
            }
            return true;
        } else if (KC_1 <= keycode && keycode <= KC_SLSH && keycode != KC_ESC) {
            // Set a word boundary if space, period, digit, etc. is pressed.
            // Behave more conservatively for the enter key. Reset, so that enter
            // can't be used on a word ending.
            if (keycode == KC_ENT) {
                typo_buffer_size = 0;
            }
            keycode = KC_SPC;
        } else {
            // Clear state if some other non-alpha key is pressed.
            typo_buffer_size = 0;
            return true;
        }
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
    uint8_t  code  = pgm_read_byte(autocorrection_data + state);
    for (uint8_t i = typo_buffer_size - 1; i >= 0; --i) {
        uint8_t const key_i = typo_buffer[i];

        if (code & 64) {  // Check for match in node with multiple children.
            code &= 63;
            for (; code != key_i; code = pgm_read_byte(autocorrection_data + (state += 3))) {
                if (!code) return true;
            }
            // Follow link to child node.
            state = (pgm_read_byte(autocorrection_data + state + 1) | pgm_read_byte(autocorrection_data + state + 2) << 8);
            // Check for match in node with single child.
        } else if (code != key_i) {
            return true;
        } else if (!(code = pgm_read_byte(autocorrection_data + (++state)))) {
            ++state;
        }

        code = pgm_read_byte(autocorrection_data + state);

        if (code & 128) {  // A typo was found! Apply autocorrection.
            const uint8_t backspaces = code & 63;
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
    }
    return true;
}
#    pragma GCC pop_options
#else
#    pragma message "Warning!!! Autocorrect is not corretly setup!"
bool process_autocorrection(uint16_t keycode, keyrecord_t* record) { return true; }
#endif
