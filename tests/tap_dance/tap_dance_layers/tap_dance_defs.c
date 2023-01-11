// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "tap_dance_defs.h"

// Implement custom keycodes which are used to check that the layer switching
// behaves properly.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FAST_AB:
        case SLOW_AB:
            if (record->event.pressed) {
                tap_code(KC_A);
            } else {
                tap_code(KC_B);
            }
            return keycode == SLOW_AB;
        case FAST_CD:
        case SLOW_CD:
            if (record->event.pressed) {
                tap_code(KC_C);
            } else {
                tap_code(KC_D);
            }
            return keycode == SLOW_CD;
    }
    return true;
}

// Implement a custom tap dance with the following behavior:
// - single tap: KC_APP
// - single hold: MO(1)
// - double tap/hold: KC_RCTL
// (The single tap and hold actions are mostly equivalent to LT(1, KC_APP).)

enum lt_app_state {
    LTA_NONE,
    LTA_SINGLE_TAP,
    LTA_SINGLE_HOLD,
    LTA_DOUBLE_HOLD,
};

static enum lt_app_state saved_lt_app_state;

static enum lt_app_state get_lt_app_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return LTA_SINGLE_TAP;
        } else {
            return LTA_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return LTA_DOUBLE_HOLD;
    } else {
        return LTA_NONE;
    }
}

static void lt_app_finished(qk_tap_dance_state_t *state, void *user_data) {
    saved_lt_app_state = get_lt_app_state(state);
    switch (saved_lt_app_state) {
        case LTA_NONE:
            break;
        case LTA_SINGLE_TAP:
            register_code(KC_APP);
            break;
        case LTA_SINGLE_HOLD:
            layer_on(1);
            break;
        case LTA_DOUBLE_HOLD:
            register_code(KC_RCTL);
            break;
    }
}

static void lt_app_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (saved_lt_app_state) {
        case LTA_NONE:
            break;
        case LTA_SINGLE_TAP:
            unregister_code(KC_APP);
            break;
        case LTA_SINGLE_HOLD:
            layer_off(1);
            break;
        case LTA_DOUBLE_HOLD:
            unregister_code(KC_RCTL);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_L_MOVE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_APP, 1),
    [TD_L_TOGG] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_APP, 1),
    [TD_LT_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lt_app_finished, lt_app_reset),
};
