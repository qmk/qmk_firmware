
#include "../__init__.h"

int rep_key_count = 0;
int alt_rep_key_count = 0;
int last_key_pressed_time = 0;
int prev_keys_queue[PREV_KEYS_QUEUE_SIZE] = {KC_NO};
deferred_token magic_timeout_token = INVALID_DEFERRED_TOKEN;

uint32_t enqueue_space(uint32_t trigger_time, void *cb_arg) {
    enqueue(TH_NUM);
    return 0;
}

void refresh_token(void) {
    if (magic_timeout_token != INVALID_DEFERRED_TOKEN)
        cancel_deferred_exec(magic_timeout_token);

    magic_timeout_token = defer_exec(MAGIC_KEY_TIMEOUT, enqueue_space, NULL);
}

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

    enqueue(keycode);
    return true;
}

bool strd_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = false;

    if (record->event.pressed) {
        if (keycode != US_REP && keycode != US_AREP) {
            last_key_pressed_time = timer_read();
            refresh_token();
        }

        if (keycode != US_REP) rep_key_count = 0;
        else rep_key_count += 1;

        if (keycode != US_AREP) alt_rep_key_count = 0;
        else alt_rep_key_count += 1;
    }

    switch (keycode) {
        case US_REP:
            if (record->event.pressed)
                process_rep_key();

            return true;

        case US_AREP:
            if (record->event.pressed)
                process_magic_key();

            return true;

        case SMT_N:
            if (record->tap.count == 2) {
                if (record->event.pressed)
                    process_magic_key();

                return true;
            }

            return false;
    }

    return false;
}
