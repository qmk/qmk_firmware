// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/autocorrection

#include "autocorrection.h"
#include <string.h>

#if __has_include("autocorrection_data.h")
#    include "autocorrection_data.h"

bool process_autocorrection(uint16_t keycode, keyrecord_t* record) {
    static uint8_t typo_buffer[AUTOCORRECTION_MAX_LENGTH] = {0};
    static uint8_t typo_buffer_size                       = 0;

    // Ignore key release; we only process key presses.
    if (!record->event.pressed) {
        return true;
    }

    // Disable autocorrection while a mod other than shift is active.
    if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
        typo_buffer_size = 0;
        return true;
    }

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

    // If the buffer is full, rotate it to discard the oldest character.
    if (typo_buffer_size >= AUTOCORRECTION_MAX_LENGTH) {
        memmove(typo_buffer, typo_buffer + 1, AUTOCORRECTION_MAX_LENGTH - 1);
        typo_buffer_size = AUTOCORRECTION_MAX_LENGTH - 1;
    }

    // Append `keycode` to the buffer.
    typo_buffer[typo_buffer_size++] = (uint8_t)keycode;
    if (typo_buffer_size < AUTOCORRECTION_MAX_LENGTH) {
        typo_buffer[typo_buffer_size] = 0;
        // Early return if not many characters have been buffered so far.
        if (typo_buffer_size < AUTOCORRECTION_MIN_LENGTH) {
            return true;
        }
    }

    // Check whether the buffer ends in a typo. This is done using a trie
    // stored in `autocorrection_data`.
    uint16_t state = 0;
    for (int i = typo_buffer_size - 1; i >= 0; --i) {
        const uint8_t keycode = typo_buffer[i];
        uint8_t       code    = autocorrection_data[state];

        if (code & 128) {  // Check for match in node with multiple children.
            code &= 127;
            for (; code != keycode; code = autocorrection_data[state += 3]) {
                if (!code) {
                    return true;
                }
            }

            // Follow link to child node.
            state = (uint16_t)((uint_fast16_t)autocorrection_data[state + 1] | (uint_fast16_t)autocorrection_data[state + 2] << 8);
            if ((state & 0x8000) != 0) {
                goto found_typo;
            }
            // Otherwise check for match in node with a single child.
        } else if (code != keycode) {
            return true;
        } else if (!autocorrection_data[++state] && !(autocorrection_data[++state] & 128)) {
            goto found_typo;
        }
    }

    return true;

found_typo:  // A typo was found! Apply autocorrection.
    state &= 0x7fff;
    const int backspaces = autocorrection_data[state];
    for (int i = 0; i < backspaces; ++i) {
        tap_code(KC_BSPC);
    }
    send_string((const char*)(autocorrection_data + state + 1));

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
#pragma message "Warning!!! Autocorrect is not corretly setup!"
bool process_autocorrection(uint16_t keycode, keyrecord_t* record) { return true; }
#endif
