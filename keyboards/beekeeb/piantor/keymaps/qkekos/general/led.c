
#include "../__init__.h"

bool inited = false;

void toggle_left_pin(void) {
    togglePin(GP25);
}

void toggle_right_pin(void) {
    bool toggle = true;
    transaction_rpc_send(USER_SYNC_A, sizeof(bool), &toggle);
}

void toggle_both_pins(void) {
    toggle_left_pin();
    toggle_right_pin();
}

void caps_word_set_user(bool active) {
    toggle_right_pin();
}

bool led_update_user(led_t led_state) {
    if (!inited && led_state.caps_lock)
        toggle_left_pin();

    inited = true;
    return true;
}

int led_pr(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) toggle_left_pin();
            return PR_TRUE;

        case TG_GAME:
        case TG_NUM:
        case TG_NAV:
        case TG_LOCK:
            if (record->event.pressed) toggle_both_pins();
            return PR_TRUE;
    }

    return PR_IGNORE;
}
