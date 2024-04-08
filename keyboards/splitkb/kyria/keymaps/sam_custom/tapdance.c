#include "layers.h"
#include "keymap.h"
#include "tapdance.h"

static td_tap_t tmuxtap_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t wintap_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t alttap_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t encodertap_state = { .is_press_action = true, .state = TD_NONE };

// simple tap-hold
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1 && !state->interrupted) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

// multi-state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    return TD_UNKNOWN;
}

// send tmux leader on tap, tmux scroll on double tap
void tmux_finished(tap_dance_state_t *state, void *user_data) {
    tmuxtap_state.state = cur_dance(state);
    switch (tmuxtap_state.state) {
        case TD_SINGLE_TAP: register_code16(LCTL(KC_A)); break;
        case TD_DOUBLE_TAP: register_code16(LCTL(KC_A)); unregister_code16(LCTL(KC_A)); tap_code(KC_LBRC); break;
        default: break;
    }
}
void tmux_reset(tap_dance_state_t *state, void *user_data) {
    switch (tmuxtap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(LCTL(KC_A)); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    tmuxtap_state.state = TD_NONE;
}

// send LGUI on single tap, toggle window layer on double tap
void win_finished(tap_dance_state_t *state, void *user_data) {
    wintap_state.state = cur_dance(state);
    switch (wintap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: layer_on(_WINDOW); break;
        default: break;
    }
}
void win_reset(tap_dance_state_t *state, void *user_data) {
    switch (wintap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    wintap_state.state = TD_NONE;
}

// send LALT on single tap, toggle magic layer on double tap
void alt_finished(tap_dance_state_t *state, void *user_data) {
    alttap_state.state = cur_dance(state);
    switch (alttap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: layer_on(_MAGIC); break;
        default: break;
    }
}
void alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (alttap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LALT); break;
        case TD_DOUBLE_TAP: break;
        default: break;
    }
    alttap_state.state = TD_NONE;
}

// sned mute on single tap, play/pause on hold, switch inputs on double tap
void encoder_finished(tap_dance_state_t *state, void *user_data) {
    encodertap_state.state = cur_dance(state);
    switch (encodertap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_MUTE); break;
        case TD_SINGLE_HOLD: register_code(KC_MEDIA_PLAY_PAUSE); break;
        case TD_DOUBLE_TAP: register_code16(SOUNDSWITCH); break;
        default: break;
    }
}
void encoder_reset(tap_dance_state_t *state, void *user_data) {
    switch (encodertap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_MUTE); break;
        case TD_SINGLE_HOLD: unregister_code(KC_MEDIA_PLAY_PAUSE); break;
        case TD_DOUBLE_TAP: unregister_code16(SOUNDSWITCH); break;
        default: break;
    }
    encodertap_state.state = TD_NONE;
}
