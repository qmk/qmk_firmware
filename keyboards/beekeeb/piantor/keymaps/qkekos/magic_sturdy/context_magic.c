// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// Copyright 2024 Guillaume Stordeur <guillaume.stordeur@gmail.com>
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "../__init__.h"
#include "context_magic.h"
#include <string.h>
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "keycode_config.h"
#include "send_string.h"
#include "action_util.h"
#include "magic_data.h"
#include "print.h"

// todo: compute max in script
#define CONTEXT_MAGIC_MAX_LENGTH MAGIC_MAX_LENGTH

static uint8_t key_buffer[CONTEXT_MAGIC_MAX_LENGTH] = {KC_SPC};
static uint8_t key_buffer_size = 1;

typedef struct
{
    const uint8_t *data;
    int     data_size;
} trie_t;

typedef struct
{
    uint8_t depth;
    uint8_t num_backspaces;
    int     completion_offset;
} trie_search_result_t;

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
bool process_check(uint16_t *keycode, keyrecord_t *record, uint8_t *key_buffer_size, uint8_t *mods)
{
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
 * @brief Add keycode to our key buffer.
 *
 * @param keycode lower 8bits of Keycode registered by matrix press, per keymap
 */
void enqueue_keycode(uint8_t keycode)
{
    // Rotate oldest character if buffer is full.
    if (key_buffer_size >= CONTEXT_MAGIC_MAX_LENGTH) {
        memmove(key_buffer, key_buffer + 1, CONTEXT_MAGIC_MAX_LENGTH - 1);
        key_buffer_size = CONTEXT_MAGIC_MAX_LENGTH - 1;
    }
    key_buffer[key_buffer_size++] = keycode;
}

/**
 * @brief Remove num keys from our buffer.
 *
 * @param num number of keys to remove
 */
void dequeue_keycodes(uint8_t num)
{
    if (key_buffer_size < num)
        key_buffer_size = 0;
    else
        key_buffer_size -= num;
}

/**
 * @brief Find longest chain in trie matching our current key_buffer.
 *
 * @param trie   trie_t struct containing trie data/size
 * @param res    result containing current best
 * @param offset current offset in trie data
 * @param depth  current depth in trie
 */
void find_longest_chain(trie_t *trie, trie_search_result_t *res, int offset, int depth)
{
#define TDATA(L) pgm_read_byte(&trie->data[L])
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
	}
	// Branch Node (with multiple children)
	else if (code & 64) {
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
	}
	// Chain node
	else {
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
void perform_magic(uint16_t keycode)
{
    if (!key_buffer_size)
        return;
    trie_t trie;
    switch (keycode) {
    case US_REP:
        trie.data = repeat_data;
        trie.data_size = REPEAT_DICTIONARY_SIZE;
        uprintf("repeat trie\n");
        break;
    case US_AREP:
        trie.data = magic_data;
        trie.data_size = MAGIC_DICTIONARY_SIZE;
        uprintf("magic trie\n");
        break;
    }
    // Look for chain matching our buffer in the trie.
    trie_search_result_t res  = {0, 0, 0};
    find_longest_chain(&trie, &res, 0, 1);

    // If we found one, apply completion
    if (res.depth) {
        // Send backspaces and dequeue buffer
        for (uint8_t i = 0; i < res.num_backspaces; ++i) {
            tap_code(KC_BSPC);
        }
        dequeue_keycodes(res.num_backspaces);
        // Add completion string to key buffer
        char c = pgm_read_byte(trie.data + res.completion_offset);
        for (int i = res.completion_offset; c; c = pgm_read_byte(trie.data + ++i)) {
            enqueue_keycode(c - 'a' + KC_A);
        }
        // Send it!
        send_string_P((const char *)&trie.data[res.completion_offset]);
    }
}

/**
 * @brief Process handler for context_magic feature.
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_context_magic(uint16_t keycode, keyrecord_t *record)
{
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    mods |= get_oneshot_mods();
#endif

    if (!record->event.pressed) {
        return true;
    }
    // keycode verification and extraction
    if (!process_check(&keycode, record, &key_buffer_size, &mods)) {
        return true;
    }
    if (keycode == US_REP || keycode == US_AREP) {
        perform_magic(keycode);
        return false;
    }
    // keycode buffer check
    switch (keycode) {
        case KC_A ... KC_Z:
            // process normally
            break;
        case KC_1 ... KC_0:
        case KC_TAB ... KC_SEMICOLON:
        case KC_GRAVE ... KC_SLASH:
            // Set a word boundary if space, period, digit, etc. is pressed.
            keycode = KC_SPC;
            break;
        case KC_ENTER:
            // Behave more conservatively for the enter key. Reset, so that enter
            // can't be used on a word ending.
            key_buffer_size = 0;
            keycode = KC_SPC;
            break;
        case KC_BSPC:
            // Remove last character from the buffer.
            if (key_buffer_size > 0) {

                --key_buffer_size;
            }
            return true;
        case KC_QUOTE:
            // Treat " (shifted ') as a word boundary.
            if ((mods & MOD_MASK_SHIFT) != 0) {
                keycode = KC_SPC;
            }
            break;
        default:
            // Clear state if some other non-alpha key is pressed.
            key_buffer_size = 0;
            return true;
    }
    // Append `keycode` to buffer.
    enqueue_keycode(keycode);
    return true;
}
