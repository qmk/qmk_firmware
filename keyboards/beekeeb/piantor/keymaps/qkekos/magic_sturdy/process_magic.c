// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// Copyright 2024 Guillaume Stordeur <guillaume.stordeur@gmail.com>
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "../__init__.h"

trie_t tries[] = {
    {US_AREP, MAGIC_DICTIONARY_SIZE,     magic_data,    NULL, db_arep_provider},
    {US_REP,  REPEAT_DICTIONARY_SIZE,    repeat_data,   repeat_key_fallback},
    {DB_AREP, DB_MAGIC_DICTIONARY_SIZE,  db_magic_data, magic_key_fallback},
    {DB_LTTR, DB_LETTER_DICTIONARY_SIZE, db_letter_data, repeat_key_fallback},

    // terminator
    { KC_NO }
};

const char* get_magic_key_symbol(uint16_t magic_key) {
    switch (magic_key) {
        case US_AREP: return "☆";
        case US_REP:  return "✵";
        case DB_AREP: return "★";
        case DB_LTTR: return "✪";
    }

    return "\0";
}

void pontential_match_found(uint16_t magic_key, char *context, char *completion) {
    if (!strcmp(context, "a")) return;

    flick_leds(1.5, 250);

    uprintf(
        "Could have used %s%s -> %s%s!\n",
        context, get_magic_key_symbol(magic_key),
        context, completion
    );
}

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

    trie_t* trie = get_trie(keycode);

    if (trie->magic_key != KC_NO) {
        if (!trie->next_magic_provider) {
            process_trie(trie);
            return false;
        }

        // handle next magic key if provided
        uint16_t next_magic = trie->next_magic_provider(magic_tap_count);
        if (next_magic) trie = get_trie(next_magic);

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
            for (int i = 0; i < TRIE_SYMBOLS_COUNT; i += 1)
                if (trie_symbols[i] == keycode) {
                    enqueue_keycode(keycode);
                    return true;
                }

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
    check_potential_matches(pontential_match_found);

    return true;
}


uint8_t magic_tap_count = 1;

deferred_token magic_timeout_token = INVALID_DEFERRED_TOKEN;
int prev_key_timestamp = 0;
int current_key_timestamp;

uint32_t enqueue_space(uint32_t trigger_time, void *cb_arg) {
    enqueue_keycode(KC_SPC);
    return 0;
}

void refresh_token(void) {
    if (magic_timeout_token != INVALID_DEFERRED_TOKEN) {
        int difference = MAGIC_KEY_TIMEOUT - timer_elapsed(prev_key_timestamp);
        extend_deferred_exec(magic_timeout_token, difference);

        return;
    }

    magic_timeout_token = defer_exec(MAGIC_KEY_TIMEOUT, enqueue_space, NULL);
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* mods) {
    prev_key_timestamp = current_key_timestamp;
    current_key_timestamp = timer_read();
    refresh_token();

    trie_t* trie = get_trie(keycode);
    if (trie->magic_key == KC_NO) return true;

    if (keycode == get_last_keycode()) magic_tap_count += 1;
    else magic_tap_count = 1;

    return true;
}

uint16_t db_arep_provider(uint8_t tap_count) {
    if (tap_count >= 2) return DB_AREP;
    return KC_NO;
}

void magic_key_fallback(void) {
    record_send_string("n");
}

void repeat_key_fallback(void) {
    uint16_t last_key = get_buffer_element(-1);
    if (!last_key) return;

    if (is_caps_word_on()) last_key = S(last_key);

    tap_code16(last_key);
    enqueue_keycode(last_key);
}

void process_magic_key(uint16_t keycode) {
    trie_t* trie = get_trie(keycode);
    if (trie->magic_key != KC_NO) process_trie(trie);
}

trie_t* get_trie(uint16_t keycode) {
    int i = 0;

    for (; tries[i].magic_key != KC_NO; i++)
        if (tries[i].magic_key == keycode) return &tries[i];

    return &tries[i];
}
