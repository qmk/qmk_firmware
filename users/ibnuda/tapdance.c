#include "tapdance.h"

static td_state_t td_state;

void dance_dlt_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_DELT);
    } else {
        register_code16(C(KC_DELT));
    }
}

void dance_dlt_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_DELT);
    } else {
        unregister_code16(C(KC_DELT));
    }
}

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LSFT);
    }
    register_code(KC_SCLN);
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
    }
    unregister_code(KC_SCLN);
}

int current_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    } else {
        return 3;
    }
}

void dance_tmb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_ESC);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
            register_code16(KC_DELT);
            break;
    }
}

void dance_tmb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_ESC);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_DELT);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DLT_CTLDLT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dlt_finished, dance_dlt_reset),
    [TD_SCLN_CLN]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_LEFT_THUMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tmb_finished, dance_tmb_reset),
};
