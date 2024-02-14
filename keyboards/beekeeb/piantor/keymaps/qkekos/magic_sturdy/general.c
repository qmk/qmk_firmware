
#include "../__init__.h"

int rep_key_count = 0;
int alt_rep_key_count = 0;
int last_key_pressed_time = 0;
int prev_key_time;

int prev_keys_queue[PREV_KEYS_QUEUE_SIZE] = {KC_NO};
deferred_token magic_timeout_token = INVALID_DEFERRED_TOKEN;

uint32_t enqueue_space(uint32_t trigger_time, void *cb_arg) {
    enqueue(KC_SPC);
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

void refill_queue(void) {
    for (int i = 0; i < PREV_KEYS_QUEUE_SIZE - 1; i += 1)
        prev_keys_queue[i] = KC_NO;

    prev_keys_queue[PREV_KEYS_QUEUE_SIZE - 1] = KC_SPC;
}

void print_queue(void) {
    uprintf("queue: ");

    for (int i = 0; i < PREV_KEYS_QUEUE_SIZE - 1; i += 1)
        uprintf("%d, ", prev_keys_queue[i]);

    uprintf("\n");
}

enum pr_response sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    prev_key_time = last_key_pressed_time;

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

//    switch (keycode) {
//        case US_REP:
//            if (record->event.pressed)
//                process_rep_key();
//
//            return false;
//
//        case US_AREP:
//            if (record->event.pressed)
//                process_magic_key();
//
//            return false;

//        case SMT_N:
//            if (record->tap.count != 2) return PR_IGNORE;
//
//            if (record->event.pressed)
//                process_magic_key();
//
//            return false;
//
//        case KC_B:
//        case KC_Z:
//        case KC_F:
//        case KC_H:
//            return process_double_tap(keycode, record);
//    }

    if (!process_context_magic(keycode, record))
        return false;

    return PR_IGNORE;
}

enum pr_response process_double_tap(uint16_t keycode, keyrecord_t *record) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        queue(-2) != keycode ||
        timer_elapsed(prev_key_time) > (get_tapping_term(keycode, NULL) + 50)
    ) return PR_IGNORE;

    dequeue();
    process_magic_key();

    return false;
}

bool is_ctrl_backspace(uint16_t keycode, keyrecord_t* record, uint8_t* mods) {
    if (keycode == HK_RMWR) return true;
    if (!(*mods & MOD_MASK_CTRL)) return false;

    if (keycode == TH_NAV && record->tap.count) return true;
    if (keycode == KC_BSPC) return true;

    return false;
}
