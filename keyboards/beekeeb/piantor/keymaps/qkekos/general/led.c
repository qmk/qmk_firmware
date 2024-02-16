
#include "../__init__.h"

deferred_token flick_token = INVALID_DEFERRED_TOKEN;
int flick_interval = 0;

bool inited = false;

void toggle_left_pin(void) {
    togglePin(GP25);
}

void disable_left_pin(void) {
    writePinLow(GP25);
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

enum pr_response led_pr(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) toggle_left_pin();
            return true;

        case TG_GAME:
        case TG_NUM:
        case TG_NAV:
        case TG_LOCK:
            if (record->event.pressed) toggle_both_pins();
            return true;
    }

    return PR_IGNORE;
}

uint32_t flick_leds_core(uint32_t trigger_time, void *cb_arg) {
    toggle_left_pin();
    return flick_interval;
}

uint32_t stop_flick(uint32_t trigger_time, void *cb_arg) {
    cancel_deferred_exec(flick_token);
    disable_left_pin();

    return 0;
}

void flick_leds(float time_seconds, int interval) {
    if (flick_token != INVALID_DEFERRED_TOKEN)
        cancel_deferred_exec(flick_token);

    flick_interval = interval;
    flick_token = defer_exec(1, flick_leds_core, NULL);

    defer_exec(time_seconds * 1000, stop_flick, NULL);
}
