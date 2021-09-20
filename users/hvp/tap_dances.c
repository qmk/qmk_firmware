#include "tap_dances.h"

// Tap dance function for enable swedish characters on first layer. Unregister to not let tap bleed over to next keypress.
// Tap dance 1
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code(KC_SCLN);
    } else {
        tap_code16(ALGR(KC_A));
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code16(ALGR(KC_A));
    }
}

// Tap dance 2
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code(KC_QUOT);
    } else {
        tap_code16(ALGR(KC_W));
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_QUOT);
    } else {
        unregister_code16(ALGR(KC_W));
    }
}

// Tap dance 3
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if (state->count == 2)
    if (state->count == 2) {
        tap_code(KC_SLSH);
    } else {
        tap_code16(ALGR(KC_O));
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_SLSH);
    } else {
        unregister_code16(ALGR(KC_O));
    }
}

// Tap dance 4
void dance_4_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if (state->count == 2)
    if (state->count == 2) {
        tap_code(KC_DOT);
    } else {
        tap_code16(ALGR(KC_W));
    }
}

void dance_4_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_DOT);
    } else {
        unregister_code16(ALGR(KC_W));
    }
}

// Tap dance 5
void dance_5_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if (state->count == 2)
    if (state->count == 2) {
        tap_code(KC_DOT);
    } else {
        tap_code16(ALGR(KC_O));
    }
}

void dance_5_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_DOT);
    } else {
        unregister_code16(ALGR(KC_O));
    }
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),

    [TD2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),

    [TD3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),

    [TD4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_finished, dance_4_reset),

    [TD5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_finished, dance_5_reset)};