
#include "../__init__.h"

int rep_key_count = 0;
int alt_rep_key_count = 0;
int last_key_pressed_time = 0;
int prev_keys_queue[PREV_KEYS_QUEUE_SIZE] = {KC_NO};

void enqueue(int keycode) {
    for (int i = 0; i < PREV_KEYS_QUEUE_SIZE - 1; i += 1)
        prev_keys_queue[i] = prev_keys_queue[i + 1];

    prev_keys_queue[PREV_KEYS_QUEUE_SIZE - 1] = keycode;
}

void dequeue(void) {
    set_last_keycode(prev_keys_queue[PREV_KEYS_QUEUE_SIZE - 1]);

     for (int i = PREV_KEYS_QUEUE_SIZE - 1; i > 0; i -= 1)
        prev_keys_queue[i] = prev_keys_queue[i - 1];

    prev_keys_queue[0] = KC_NO;
}

void remember_last_key(int prev_keycode, int key_to_remember) {
    enqueue(prev_keycode);
    set_last_keycode(key_to_remember);
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    if (keycode == TH_NAV)
        dequeue();

    switch (keycode) {
        case TH_NAV:
        case KC_BSPC:
        case US_REP:
        case US_AREP:
            return false;

        case SMT_N:
            if (record->tap.count == 2) return false;
            break;
    }

    enqueue(get_last_keycode());
    return true;
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
        case US_REP:
            if (record->event.pressed)
                process_rep_key(get_last_keycode(), get_last_mods());

            return true;

        case US_AREP:
            if (record->event.pressed)
                process_magic_key(get_last_keycode(), get_last_mods());

            return true;

        case SMT_N:
            if (record->tap.count == 2) {
                if (record->event.pressed)
                    process_magic_key(get_last_keycode(), get_last_mods());

                return true;
            }

            return false;
    }

    return false;
}
