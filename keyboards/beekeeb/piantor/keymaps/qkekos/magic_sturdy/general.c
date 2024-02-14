
#include "../__init__.h"

enum pr_response sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    if (!process_context_magic(keycode, record))
            return false;

    switch (keycode) {
        case SMT_N:
            if (record->tap.count != 2) return PR_IGNORE;

            if (record->event.pressed)
                process_magic_key(US_AREP);

            return false;

//        case KC_B:
//        case KC_Z:
//        case KC_F:
//        case KC_H:
//            return process_double_tap(keycode, record);
    }

    return PR_IGNORE;
}

enum pr_response process_double_tap(uint16_t keycode, keyrecord_t *record) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        queue(-2) != keycode ||
        timer_elapsed(prev_key_timestamp) > (get_tapping_term(keycode, NULL) + 50)
    ) return PR_IGNORE;

    dequeue();
    process_magic_key(US_AREP);

    return false;
}
