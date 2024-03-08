
#include "../__init__.h"

int prev_key_timestamp;
int current_key_timestamp;

int trigger_magic_key(uint16_t magic_key, keyrecord_t *record) {
    if (!process_sequence_transform(magic_key, record, US_AREP))
        return false;

    return PR_IGNORE;
}

enum pr_response sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    prev_key_timestamp = current_key_timestamp;
    current_key_timestamp = timer_read();

    switch (keycode) {
        case SMT_N:
            if (record->tap.count != 2) break;
            return trigger_magic_key(DB_LTTR, record);

        case KC_B:
        case KC_Z:
        case KC_H:
        case KC_F:
        case KC_Q:
            return process_double_tap(keycode, record, DB_LTTR);

        case LT_I:
            if (record->event.pressed && record->tap.count == 2 && get_buffer_keycode(1) != KC_V) {
                tap_code16(KC_BSPC);
                add_weak_mods(MOD_BIT(KC_LSFT));
                return PR_IGNORE;
            }

            break;
    }

    if (!process_sequence_transform(keycode, record, US_AREP))
        return false;

    return PR_IGNORE;
}

int process_double_tap(uint16_t keycode, keyrecord_t *record, uint16_t magic_key) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        get_buffer_keycode(0) != keycode ||
        timer_elapsed(prev_key_timestamp) > (get_tapping_term(keycode, NULL) + 50)
    ) {
        if (!process_sequence_transform(keycode, record, US_AREP))
            return false;

        return PR_IGNORE;
    }

    return trigger_magic_key(magic_key, record);
}
