// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "elpekenin.h"

void td_ntil_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(ES_ACUT); // {
            break;

        case 2:
            tap_code16(ES_LBRC); // [
            break;

        case 3:
            tap_code16(ES_LPRN); // (
            break;

        case 4:
            tap_code16(ES_NTIL); // ñ
            break;

        default:
            break;
    }
}

void td_z_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_Z);    // z
            break;

        case 2:
            tap_code16(ES_LABK); // <
            break;

        case 3:
            tap_code16(ES_RABK); // >
            break;

        default:
            break;
    }
}

void td_spc_each(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_SPC);
    register_code16(KC_SPC);

    if ((state->count % 2) == 0) {
        unregister_code16(KC_SPC);
        tap_code16(KC_SPC);
        register_code16(KC_SPC);
    }
}

void td_spc_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_SPC);
}

void td_grv_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(ES_GRV);
        return;
    }

    SEND_STRING("```" SS_LSFT("\n\n") "```");
    tap_code16(KC_UP);
}

tap_dance_action_t tap_dance_actions[] = {
    [_TD_NTIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ntil_finished, NULL),
    [_TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_z_finished, NULL),
    [_TD_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(td_spc_each, NULL, td_spc_reset),
    [_TD_GRV]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_grv_finished, NULL),
};
