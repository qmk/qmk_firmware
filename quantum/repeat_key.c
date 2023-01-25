// Copyright 2022-2023 Google LLC
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

#include "repeat_key.h"

// Variables saving the state of the last key press.
static keyrecord_t last_record = {0};
static uint8_t     last_mods   = 0;
// Signed count of the number of times the last key has been repeated or reverse
// repeated: it is 0 when a key is pressed normally, positive when repeated,
// and negative when reverse repeated.
static int8_t last_repeat_count = 0;

// The repeat_count, but set to 0 outside of repeat_key_invoke() so that it is
// nonzero only while a repeated key is being processed.
static int8_t processing_repeat_count = 0;

static void update_last_repeat_count(int8_t dir) {
    if (dir * last_repeat_count < 0) {
        last_repeat_count = dir;
    } else if (dir * last_repeat_count < 127) {
        last_repeat_count += dir;
    }
}

int8_t get_repeat_key_count(void) {
    return processing_repeat_count;
}

uint16_t get_repeat_key_keycode(void) {
    return last_record.keycode;
}

uint8_t get_repeat_key_mods(void) {
    return last_mods;
}

void set_repeat_key_keycode(uint16_t keycode) {
    set_repeat_key_record(keycode, &(keyrecord_t){
#ifndef NO_ACTION_TAPPING
                                       .tap.interrupted = false,
                                       .tap.count       = 1,
#endif
                                   });
}

void set_repeat_key_mods(uint8_t mods) {
    last_mods = mods;
}

void set_repeat_key_record(uint16_t keycode, keyrecord_t* record) {
    last_record         = *record;
    last_record.keycode = keycode;
    last_repeat_count   = 0;
}

void repeat_key_invoke(const keyevent_t* event) {
    static keyrecord_t registered_record       = {0};
    static int8_t      registered_repeat_count = 0;
    // Since this function calls process_record(), it may recursively call
    // itself. We return early if `processing_repeat_count` is nonzero to
    // prevent infinite recursion.
    if (processing_repeat_count || !last_record.keycode) {
        return;
    }

    if (event->pressed) {
        update_last_repeat_count(1);
        // On press, apply the last mods state, stacking on top of current mods.
        register_weak_mods(last_mods);
        registered_record       = last_record;
        registered_repeat_count = last_repeat_count;
    }

    // Generate an event and plumb it into the event pipeline.
    registered_record.event = *event;
    processing_repeat_count = registered_repeat_count;
    process_record(&registered_record);
    processing_repeat_count = 0;

    // On release, restore the mods state.
    if (!event->pressed) {
        unregister_weak_mods(last_mods);
    }
}

#ifndef NO_REVERSE_REPEAT_KEY
/**
 * @brief Find reverse keycode from a table of opposing keycode pairs.
 * @param table Array of pairs of basic keycodes, declared as PROGMEM.
 * @param table_size_bytes The size of the table in bytes.
 * @param target The basic keycode to find.
 * @return The reverse basic keycode, or KC_NO if none was found.
 *
 * @note The table keycodes and target must be basic keycodes.
 *
 * Given a table of pairs of basic keycodes, finds the pair containing `target`
 * and returns the other keycode in the pair.
 */
static uint8_t find_rev_keycode(const uint8_t (*table)[2], uint8_t table_size_bytes, uint8_t target) {
    const uint8_t* keycodes = (const uint8_t*)table;
    for (uint8_t i = 0; i < table_size_bytes; ++i) {
        if (target == pgm_read_byte(keycodes + i)) {
            // Xor (i ^ 1) the index to get the other element in the pair.
            return pgm_read_byte(keycodes + (i ^ 1));
        }
    }
    return KC_NO;
}

uint16_t get_rev_repeat_key_keycode(void) {
    uint16_t keycode     = last_record.keycode;
    uint8_t  mods        = last_mods;
    uint16_t rev_keycode = get_rev_repeat_key_keycode_user(keycode, mods);

    if (rev_keycode) {
        return rev_keycode;
    }

    // Convert 8-bit mods to the 5-bit format used in keycodes.
    mods = ((mods & 0xf0) ? 0x10 : 0) | (((mods >> 4) | mods) & 0xf);

    switch (keycode) {
        case QK_MODS ... QK_MODS_MAX: // Unpack modifier + basic key.
            mods |= QK_MODS_GET_MODS(keycode);
            keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
            break;

#    ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#        endif // NO_ACTION_LAYER
#    endif     // NO_ACTION_TAPPING

#    ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode)) {
                return KC_NO;
            }
            keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
            break;
#    endif // SWAP_HANDS_ENABLE
    }

    if (IS_QK_BASIC(keycode)) {
        if ((mods & (MOD_LCTL | MOD_LALT | MOD_LGUI))) {
            // The last key was pressed with a modifier other than Shift.
            // The following maps
            //   mod + F <-> mod + B
            // and a few others, supporting several core hotkeys used in
            // Emacs, Vim, less, and other programs.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_F   , KC_B   },  // Forward / Backward.
                {KC_D   , KC_U   },  // Down / Up.
                {KC_N   , KC_P   },  // Next / Previous.
                {KC_A   , KC_E   },  // Home / End.
            };
            // clang-format on
            rev_keycode = find_rev_keycode(pairs, sizeof(pairs), keycode);
        } else {
            // The last key was pressed with no mods or only Shift. The
            // following map a few more Vim hotkeys.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_J   , KC_K   },  // Down / Up.
                {KC_H   , KC_L   },  // Left / Right.
                // These two lines map W and E to B, and B to W.
                {KC_W   , KC_B   },  // Forward / Backward by word.
                {KC_E   , KC_B   },  // Forward / Backward by word.
            };
            // clang-format on
            rev_keycode = find_rev_keycode(pairs, sizeof(pairs), keycode);
        }

        if (!rev_keycode) {
            // The following key pairs are considered with any mods.
            // clang-format off
            static const uint8_t pairs[][2] PROGMEM = {
                {KC_LEFT, KC_RGHT},  // Left / Right Arrow.
                {KC_UP  , KC_DOWN},  // Up / Down Arrow.
                {KC_HOME, KC_END },  // Home / End.
                {KC_PGUP, KC_PGDN},  // Page Up / Page Down.
                {KC_BSPC, KC_DEL },  // Backspace / Delete.
                {KC_LBRC, KC_RBRC},  // Brackets [ ] and { }.
#ifdef EXTRAKEY_ENABLE
                {KC_WBAK, KC_WFWD},  // Browser Back / Forward.
                {KC_MNXT, KC_MPRV},  // Next / Previous Media Track.
                {KC_MFFD, KC_MRWD},  // Fast Forward / Rewind Media.
                {KC_VOLU, KC_VOLD},  // Volume Up / Down.
                {KC_BRIU, KC_BRID},  // Brightness Up / Down.
#endif  // EXTRAKEY_ENABLE
#ifdef MOUSEKEY_ENABLE
                {KC_MS_L, KC_MS_R},  // Mouse Cursor Left / Right.
                {KC_MS_U, KC_MS_D},  // Mouse Cursor Up / Down.
                {KC_WH_L, KC_WH_R},  // Mouse Wheel Left / Right.
                {KC_WH_U, KC_WH_D},  // Mouse Wheel Up / Down.
#endif  // MOUSEKEY_ENABLE
            };
            // clang-format on
            rev_keycode = find_rev_keycode(pairs, sizeof(pairs), keycode);
        }

        if (rev_keycode) {
            // Combine basic keycode with mods.
            return (mods << 8) | rev_keycode;
        }
    }

    return KC_NO; // No reverse key found.
}

void rev_repeat_key_invoke(const keyevent_t* event) {
    static keyrecord_t registered_record       = {0};
    static int8_t      registered_repeat_count = 0;
    // Since this function calls process_record(), it may recursively call
    // itself. We return early if `processing_repeat_count` is nonzero to
    // prevent infinite recursion.
    if (processing_repeat_count) {
        return;
    }

    if (event->pressed) {
        registered_record = (keyrecord_t){
#    ifndef NO_ACTION_TAPPING
            .tap.interrupted = false,
            .tap.count       = 0,
#    endif
            .keycode = get_rev_repeat_key_keycode(),
        };
    }

    if (!registered_record.keycode) {
        return;
    }

    if (event->pressed) {
        update_last_repeat_count(-1);
        registered_repeat_count = last_repeat_count;
    }

    // Generate an event and plumb it into the event pipeline.
    registered_record.event = *event;
    processing_repeat_count = registered_repeat_count;
    process_record(&registered_record);
    processing_repeat_count = 0;
}

// Default implementation of get_rev_repeat_key_keycode_user().
__attribute__((weak)) uint16_t get_rev_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    return KC_NO;
}
#endif // NO_REVERSE_REPEAT_KEY
