
#include "../__init__.h"

void call_db_trie(void) {
    dequeue_keycode();
    set_last_keycode(DB_LTTR);
    process_magic_key(DB_LTTR);
}

enum pr_response sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    if (!process_context_magic(keycode, record))
        return false;

    switch (keycode) {
        case SMT_N:
        case ALT_T:
            if (record->tap.count != 2) return PR_IGNORE;
            if (record->event.pressed) call_db_trie();

            return false;

        case KC_B:
        case KC_Z:
        case KC_H:
        case KC_F:
        case KC_Q:
        case KC_C:
        case KC_L:
            return process_double_tap(keycode, record, DB_LTTR);
    }

    return PR_IGNORE;
}

enum pr_response process_double_tap(uint16_t keycode, keyrecord_t *record, uint16_t magic_key) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        queue(-2) != keycode ||
        timer_elapsed(prev_key_timestamp) > (get_tapping_term(keycode, NULL) + 50)
    ) return PR_IGNORE;

    call_db_trie();
    return false;
}

void record_tap_code(uint8_t keycode) {
    if (!keycode) return;

    if (is_caps_word_on())
        add_weak_mods(MOD_BIT(KC_LSFT));

    tap_code(keycode);
    enqueue_keycode(keycode);
}

void record_send_string(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
        record_tap_code(char_to_keycode(str[i]));
}
