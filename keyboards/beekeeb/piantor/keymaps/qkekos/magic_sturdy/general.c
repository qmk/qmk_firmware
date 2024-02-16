
#include "../__init__.h"

enum pr_response sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    if (!process_context_magic(keycode, record))
        return false;

    switch (keycode) {
        case SMT_N:
        case ALT_T:
            if (record->tap.count != 2) return PR_IGNORE;

            if (record->event.pressed) {
                dequeue_keycode();
                process_magic_key(DB_LTTR);
            }

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

    dequeue_keycode();
    process_magic_key(magic_key);

    return false;
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
