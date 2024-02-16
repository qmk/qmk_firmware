
#include "../__init__.h"

uint8_t key_buffer[MAX_CONTEXT_LENGTH] = { KC_SPC };
char string_buffer[MAX_CONTEXT_LENGTH] = { "\0" };
uint8_t key_buffer_size = 1;

void record_longest_match(trie_visitor_t *v, int bspaces, const char *completion) {
    uint8_t context_len = v->stack.size;
    search_result_t *result = (search_result_t*)(v->cb_data);

    if (context_len < result->max_condext_len) return;

    result->completion = (char*)completion;
    result->bspace_count = bspaces;
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

uint16_t get_buffer_element(int index) {
    index = key_buffer_size + index;

    if (index >= MAX_CONTEXT_LENGTH || index < 0) return KC_NO;
    return key_buffer[index];
}

void stack_push(stack_t *s, char c) {
	if (s->size < MAX_CONTEXT_LENGTH)
		s->buffer[s->size++] = c;
}

void stack_pop(stack_t *s) {
	if (s->size > 0)
		s->size--;
}

void print_buffer(void) {
    uprintf("buffer: ");

    for (int i = 0; i < key_buffer_size; i += 1)
        uprintf("%c", keycode_to_char(key_buffer[i]));

    uprintf("\n");
}

void stack_print(stack_t *s) {
	for (int i = s->size - 1; i >= 0; --i)
		uprintf("%c", s->buffer[i]);
}

void stack_dump(stack_t *stack, char *str) {
	for (int i = stack->size - 1; i >= 0; i -= 1)
        str[stack->size - 1 - i] = stack->buffer[i];

	str[stack->size] = '\0';
}

void search_trie(const uint8_t *trie, int offset, trie_visitor_t *v) {
	uint8_t code = trie[offset];
	assert(code);
	// MATCH node
	if (code & 128) {
		const int bspaces = (code & 63);
		const char *completion = (const char *)(trie + offset + 1);
		v->cb_func(v, bspaces, completion);		
		// Traverse down child node if this isn't the only match
		if (code & 64) {
			for (offset += 2; trie[offset]; offset++);
			search_trie(trie, offset+1, v);
		}
	}
	// BRANCH node
	else if (code & 64) {
		if ((v->stack.size+1) > key_buffer_size) return;

		code &= 63;
		uint8_t cur_keycode = key_buffer[key_buffer_size - (v->stack.size+1)];

		// find child that matches our current buffer location
		for (; code; offset += 3, code = trie[offset]) {
			if (cur_keycode == code) {
			    const char c = keycode_to_char(code);
				// 16bit offset to child node is built from next 2 bytes
				const int child_offset = trie[offset + 1] | (trie[offset + 2] << 8);
				// Traverse down child node
				stack_push(&v->stack, c);
				search_trie(trie, child_offset, v);
				stack_pop(&v->stack);
				return;
			}
		}
	}
	// Chain node
	else {
		// Travel down chain until we reach a zero byte, or we no longer match our buffer
		const int prev_stack_size = v->stack.size;
		for (; code; code = trie[++offset]) {
			const char c = keycode_to_char(code);
			stack_push(&v->stack, c);
			if (v->stack.size > key_buffer_size ||
				code != key_buffer[key_buffer_size - v->stack.size]
				) {
				v->stack.size = prev_stack_size;
				return;
			}
		}
		// After a chain, there should be a leaf or branch
		search_trie(trie, offset+1, v);
		v->stack.size = prev_stack_size;
	}
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
        clear_buffer();
        return false;
    }

    return true;
}

/**
 * @brief Handles magic/repeat key press
 *
 * @param keycode Keycode registered by matrix press, per keymap
 */
void process_trie(trie_t* trie) {
    if (!key_buffer_size) return;

    search_result_t result = {};
    trie_visitor_t search_visitor = { record_longest_match, &result };

    search_trie(trie->data, 0, &search_visitor);

    // If we found one, apply completion
    if (!result.completion) {
        if (trie->fallback) trie->fallback();
        return;
    }

    // Send backspaces and dequeue buffer
    multi_tap(KC_BSPC, result.bspace_count);
    dequeue_keycodes(result.bspace_count);

    record_send_string(result.completion);
}
