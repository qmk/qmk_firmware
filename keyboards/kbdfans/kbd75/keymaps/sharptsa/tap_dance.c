#include "tap_dance.h"

uint16_t led_dance_timer;
bool led_dance_triggered = false;

void td_reset_keyboard(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
        reset_keyboard();
    }
};

void td_led_dance(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        led_dance_timer = timer_read();
        led_dance_triggered = true;
        set_led_dance();
    }
};

// Reset default rgb lighting after 10sec
void td_led_dance_stop(void) {
    if (led_dance_triggered && (timer_elapsed(led_dance_timer) >= 10000) ) {
        set_default_keyboard_rgb();
        led_dance_triggered = false;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Reset
    [TD_RESET] = ACTION_TAP_DANCE_FN(td_reset_keyboard),
    // Tap once for Grave, twice for arrow operator
    [TD_GRV_ARROWOPS] = ACTION_TAP_DANCE_FN(td_grv_arrow_ops),
    // Tap thrice for a led dance
    [TD_LD] = ACTION_TAP_DANCE_FN(td_led_dance)
};
