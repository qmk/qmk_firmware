
#include "../__init__.h"

int prev_last_key = KC_NO;
int rep_key_count = 0;
int alt_rep_key_count = 0;
int last_key_pressed_time = 0;

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case TH_NAV:
        case KC_BSPC:
        case US_REP:
        case US_AREP:
            return false;

        case MHR_N:
            if (record->tap.count == 2) return false;
            break;
    }

    prev_last_key = get_last_keycode();
    return true;
}

uint32_t defer_process_magic_key(uint32_t trigger_time, void *cb_arg) {
    process_magic_key(get_last_keycode(), get_last_mods());
    return 0;
}

uint32_t defer_process_rep_key(uint32_t trigger_time, void *cb_arg) {
    process_rep_key(get_last_keycode(), get_last_mods());
    return 0;
}

bool strd_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = false;

    if (record->event.pressed) {
        if (keycode != US_REP && keycode != US_AREP)
            last_key_pressed_time = timer_read();

        if (keycode != US_REP) rep_key_count = 0;
        else rep_key_count += 1;

        if (keycode != US_AREP) alt_rep_key_count = 0;
        else alt_rep_key_count += 1;
    }

    switch (keycode) {
        case TH_NAV:
            if (record->tap.count && record->event.pressed) {
                    process_rep_key(get_last_keycode(), get_last_mods());
                    return true;
                }

            return false;

        case US_REP:
            if (record->event.pressed)
                defer_exec(COMBO_TERM * 2, defer_process_rep_key, NULL);

            return true;

        case US_AREP:
            if (record->event.pressed)
                defer_exec(COMBO_TERM * 2, defer_process_magic_key, NULL);

            return true;

        case MHR_N:
            if (record->tap.count == 2) {
                if (record->event.pressed)
                    process_magic_key(get_last_keycode(), get_last_mods());

                return true;
            }

            return false;
    }

    return false;
}
