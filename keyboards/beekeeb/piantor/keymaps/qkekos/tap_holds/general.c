
#include "../__init__.h"

uint16_t next_keycode;
keyrecord_t *next_record;

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("pre_process_record_user: %d\n", keycode);

    if (record->event.pressed) {
        next_keycode = keycode;
        next_record = record;
    }

    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_NAV:
        case HR_DEL:
        case HR_RMLN:
        case HR_SAVE:
        case HR_CPLN:
        case HR_SRCH:
            return true;
    }

    return get_hold_on_next_key(keycode, next_keycode);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_NUM:
            return 120;

        case TD_PASS:
            return 1000;
    }

    return TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_NUM:
        case TH_FUNC:
        case TH_NAV:
        case MHR_F:
        case MHR_J:
        case MHR_D:
        case MHR_N:
            return 0;
    }

    return get_hold_on_next_key(keycode, next_keycode) ? 0 : TAPPING_TERM;
}
