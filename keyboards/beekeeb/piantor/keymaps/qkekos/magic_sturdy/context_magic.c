// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// Copyright 2024 Guillaume Stordeur <guillaume.stordeur@gmail.com>
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "../__init__.h"

// todo capsword support
// todo enqueue space after some time

trie_t tries[] = {
    {US_AREP, MAGIC_DICTIONARY_SIZE,  magic_data,  magic_key_fallback },
    {US_REP,  REPEAT_DICTIONARY_SIZE, repeat_data, repeat_key_fallback},

    // terminator
    {KC_NO, 0, NULL}
};

/**
 * @brief Process handler for context_magic feature.
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_context_magic(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if (!record->event.pressed) return true;

    // keycode verification and extraction
    if (!process_check(&keycode, record, &key_buffer_size, &mods)) return true;

    trie_t trie = get_trie(keycode);

    if (trie.magic_key != KC_NO) {
        process_trie(trie);
        return false;
    }

    // keycode buffer check
    switch (keycode) {
        case KC_A ... KC_Z:
            // process normally
            break;

        case KC_1 ... KC_0:
        case KC_GRV ... KC_SLSH:
        case KC_TAB ... KC_SCLN:
            // Set a word boundary if space, period, digit, etc. is pressed.
            keycode = KC_SPC;
            break;

        case KC_QUOTE:
            // Treat " (shifted ') as a word boundary.
            if (is_shift_held_core(mods)) keycode = KC_SPC;
            break;

        case KC_BSPC:
            // Remove last character from the buffer.
            dequeue_keycode();
            return true;

        default:
            // Clear state if some other non-alpha key is pressed.
            clear_buffer();
            return true;
    }

    enqueue_keycode(keycode);
    return true;
}

uint8_t key_buffer[MAX_CONTEXT_LENGTH] = { KC_SPC };
uint8_t key_buffer_size = 1;
uint8_t magic_tap_count = 1;

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* mods) {
    trie_t trie = get_trie(keycode);
    if (trie.magic_key == KC_NO) return true;

    if (keycode == get_last_keycode()) magic_tap_count += 1;
    else magic_tap_count = 1;

    return true;
}

void magic_key_fallback(uint8_t tap_count) {
    if (tap_count < 2) return;
    record_send_string("n");
}

void repeat_key_fallback(uint8_t tap_count) {
    uint16_t last_key = get_buffer_element(-1);
    if (!last_key) return;

    tap_code16(last_key);
    enqueue_keycode(last_key);
}

/**
 * @brief Add keycode to our key buffer.
 *
 * @param keycode lower 8bits of Keycode registered by matrix press, per keymap
 */
void enqueue_keycode(uint8_t keycode) {
    // Rotate oldest character if buffer is full.
    if (key_buffer_size >= MAX_CONTEXT_LENGTH) {
        memmove(key_buffer, key_buffer + 1, MAX_CONTEXT_LENGTH - 1);
        key_buffer_size = MAX_CONTEXT_LENGTH - 1;
    }

    key_buffer[key_buffer_size++] = keycode;
}

/**
 * @brief Remove num keys from our buffer.
 *
 * @param count number of keys to remove
 */
void dequeue_keycodes(uint8_t count) {
    key_buffer_size -= MIN(count, key_buffer_size);
}

void dequeue_keycode(void) { dequeue_keycodes(1); }

void clear_buffer(void) {
    key_buffer_size = 0;
    enqueue_keycode(KC_SPC);
}

trie_t get_trie(uint16_t keycode) {
    int i = 0;

    for (; tries[i].magic_key != KC_NO; i++)
        if (tries[i].magic_key == keycode) return tries[i];

    return tries[i];
}

/**
 * @brief determine if context_magic should process this keypress,
 *        and remove any mods from keycode.
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @param key_buffer_size passed along to allow resetting of buffer
 * @param mods allow processing of mod status
 * @return true Allow autocorection
 * @return false Stop processing and escape from autocorrect.
 */
bool process_check(uint16_t *keycode, keyrecord_t *record, uint8_t *key_buffer_size, uint8_t *mods) {
    // See quantum_keycodes.h for reference on these matched ranges.
    switch (*keycode) {
        // Exclude these keycodes from processing.
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_TO ... QK_TO_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return false;

        // Mask for base keycode from shifted keys.
        case QK_LSFT ... QK_LSFT + 255:
        case QK_RSFT ... QK_RSFT + 255:
            if (*keycode >= QK_LSFT && *keycode <= (QK_LSFT + 255)) {
                *mods |= MOD_LSFT;
            } else {
                *mods |= MOD_RSFT;
            }
            *keycode = QK_MODS_GET_BASIC_KEYCODE(*keycode); // Get the basic keycode.
            return true;
#ifndef NO_ACTION_TAPPING
        // Exclude tap-hold keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    ifdef NO_ACTION_LAYER
            // Exclude Layer Tap, if layers are disabled
            // but action tapping is still enabled.
            return false;
#    else
            // Exclude hold keycode
            if (!record->tap.count) {
                return false;
            }
            *keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(*keycode);
            break;
#    endif
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Exclude hold keycode
            if (!record->tap.count) {
                return false;
            }
            *keycode = QK_MOD_TAP_GET_TAP_KEYCODE(*keycode);
            break;
#else
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Exclude if disabled
            return false;
#endif
        // Exclude swap hands keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
#ifdef SWAP_HANDS_ENABLE
            // Note: IS_SWAP_HANDS_KEYCODE() actually tests for the special action keycodes like SH_TOGG, SH_TT, ...,
            // which currently overlap the SH_T(kc) range.
            if (IS_SWAP_HANDS_KEYCODE(*keycode)
#    ifndef NO_ACTION_TAPPING
                || !record->tap.count
#    endif // NO_ACTION_TAPPING
            ) {
                return false;
            }
            *keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(*keycode);
            break;
#else
            // Exclude if disabled
            return false;
#endif
    }
    // Disable autocorrect while a mod other than shift is active.
    if ((*mods & ~MOD_MASK_SHIFT) != 0) {
        *key_buffer_size = 0;
        return false;
    }
    return true;
}

/**
 * @brief Find longest chain in trie matching our current key_buffer.
 *
 * @param trie   trie_t struct containing trie data/size
 * @param res    result containing current best
 * @param offset current offset in trie data
 * @param depth  current depth in trie
 */
void find_longest_chain(trie_t *trie, trie_search_result_t *res, int offset, int depth) {
    // Sanity checks
    if (offset >= trie->data_size) {
        uprintf("find_longest_chain() Error: tried reading outside trie data! Offset: %d", offset);
        res->depth = 0;

        return;
    }

    uint8_t code = TDATA(offset);

    if (!code) {
        uprintf("find_longest_chain() Error: unexpected null code! Offset: %d", offset);
        res->depth = 0;

        return;
    }

	// Match Node
	if (code & 128) {
		depth--;
        // Record result if depth better than current best
        if (depth > res->depth) {
            res->depth = depth;
            res->completion_offset = offset + 1;
            res->num_backspaces = (code & 63);
        }

		// Traverse down child node if this isn't the only match
        if (code & 64) {
            // Next node is after completion string
		    for (offset += 2; TDATA(offset); offset++);
		    find_longest_chain(trie, res, offset+1, depth+1);
        }
	} else if (code & 64) {  // Branch Node (with multiple children)
		code &= 63;
        // Find child that matches our current buffer location
        const uint8_t cur_key = key_buffer[key_buffer_size - depth];
		for (; code && code != cur_key; offset += 3, code = TDATA(offset));

        if (code) {
			// 16bit offset to child node is built from next 2 bytes
			const int child_offset = TDATA(offset+1) | (TDATA(offset+2) << 8);
			// Traverse down child node
			find_longest_chain(trie, res, child_offset, depth+1);
		}
	} else {  // Chain node
		// Travel down chain until we reach a zero byte, or we no longer match our buffer
		for (; code; depth++, code = TDATA(++offset)) {
			if (code != key_buffer[key_buffer_size - depth])
				return;
		}
		// After a chain, there should be a leaf or branch
		find_longest_chain(trie, res, offset+1, depth);
	}
}

/**
 * @brief Handles magic/repeat key press
 *
 * @param keycode Keycode registered by matrix press, per keymap
 */
void process_trie(trie_t trie) {
    if (!key_buffer_size) return;

    // Look for chain matching our buffer in the trie.
    trie_search_result_t res  = {0, 0, 0};
    find_longest_chain(&trie, &res, 0, 1);

    // If we found one, apply completion
    if (!res.depth) {
        if (trie.fallback) trie.fallback(magic_tap_count);
        return;
    }

    // Send backspaces and dequeue buffer
    multi_tap(KC_BSPC, res.num_backspaces);
    dequeue_keycodes(res.num_backspaces);

    // Add completion string to key buffer
    char c = pgm_read_byte(trie.data + res.completion_offset);

    for (int i = res.completion_offset; c; c = pgm_read_byte(trie.data + ++i))
        enqueue_keycode(char_to_keycode(c));

    // Send it!
    send_string_P((const char *) &trie.data[res.completion_offset]);
}

void proces_magic_key(uint16_t keycode) {
    trie_t trie = get_trie(keycode);
    if (trie.magic_key != KC_NO) process_trie(trie);
}

void record_send_string(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        uint16_t keycode = char_to_keycode(str[i]);

        if (keycode == KC_BSPC) dequeue_keycode();
        if (keycode == KC_NO) continue;

        enqueue_keycode(keycode);
    }

    SEND_STRING(is_caps_word_on() ? to_upper_case(str) : str);
}

uint16_t get_buffer_element(int index) {
    index = key_buffer_size + index;

    if (index >= MAX_CONTEXT_LENGTH || index < 0) return KC_NO;
    return key_buffer[index];
}
