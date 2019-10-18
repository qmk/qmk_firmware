#include "tap_dances.h"

// Tap dance function for enable swedish characters on first layer. Unregister to not let tap bleed over to next keypress.
// Tap dance 1
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code(KC_SCLN);
    } else {
        register_code(KC_RALT);
        register_code(KC_O);
        unregister_code(KC_RALT);
        unregister_code(KC_O);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code(KC_RALT);
        unregister_code(KC_O);
    }
}

// Tap dance 2
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code(KC_QUOT);
    } else {
        register_code(KC_RALT);
        register_code(KC_A);
        unregister_code(KC_RALT);
        unregister_code(KC_A);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_QUOT);
    } else {
        unregister_code(KC_RALT);
        unregister_code(KC_A);
    }
}

// Tap dance 3
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if (state->count == 2)
    if (state->count == 2) {
        tap_code(KC_SLSH);
    } else {
        register_code(KC_RALT);
        register_code(KC_W);
        unregister_code(KC_RALT);
        unregister_code(KC_W);
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_SLSH);
    } else {
        unregister_code(KC_RALT);
        unregister_code(KC_W);
    }
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),

    [TD2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),

    [TD3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset)};