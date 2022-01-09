#include "keyrecords/tap_dances.h"


// + --------- +
// + TAP DANCE |
// + --------- +

// https://github.com/qmk/qmk_firmware/blob/9294258c02d3e025e01935a06c4d9f1997535bda/users/gordon/gordon.c#L112-L135
td_state_t hold_cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        }
        else {
            if (!state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        }
    }
    else if (state->count == 2) {
        if (state->pressed) return TD_NONE;
        else return TD_DOUBLE_TAP;
    }
    else return TD_NONE;
}

// + ------------------------------------------------ +
// + LEFT SHIFT PARENTHESIS OPEN (LSPO) AND CAPS LOCK |
// + ------------------------------------------------ +

// Create an instance of 'td_tap_t' for the 'LSPO_CAPS' tap dance.
static td_tap_t LSPO_CAPS_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void LSPO_CAPS_finished(qk_tap_dance_state_t *state, void *user_data) {
    LSPO_CAPS_state.state = hold_cur_dance(state);
    switch (LSPO_CAPS_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: register_code16(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_code16(KC_CAPS); break;
        case TD_NONE: break;
    }
}

void LSPO_CAPS_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (LSPO_CAPS_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_CAPS); break;
        case TD_NONE: break;
    }
    LSPO_CAPS_state.state = TD_NONE;
}

// + -------------------------------------------------- +
// + RIGHT SHIFT PARENTHESIS CLOSE (RSPC) AND CAPS LOCK |
// + -------------------------------------------------- +

// Create an instance of 'td_tap_t' for the 'RSPC_CAPS' tap dance.
static td_tap_t RSPC_CAPS_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void RSPC_CAPS_finished(qk_tap_dance_state_t *state, void *user_data) {
    RSPC_CAPS_state.state = hold_cur_dance(state);
    switch (RSPC_CAPS_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_RPRN); break;
        case TD_SINGLE_HOLD: register_code16(KC_RSFT); break;
        case TD_DOUBLE_TAP: register_code16(KC_CAPS); break;
        case TD_NONE: break;
    }
}

void RSPC_CAPS_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (RSPC_CAPS_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_RPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RSFT); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_CAPS); break;
        case TD_NONE: break;
    }
    RSPC_CAPS_state.state = TD_NONE;
}
