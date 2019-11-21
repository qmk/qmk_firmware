#include "quantum.h"

typedef enum { NONE, TAP, HOLD, DOUBLE_TAP } action_type_t;

bool shift_holded = false;
action_type_t _last_action_type = NONE;

void shift_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (_last_action_type == HOLD) {
        unregister_code(KC_LSFT);
    }
}

void shift_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (_last_action_type == DOUBLE_TAP) {
        unregister_code(KC_LSFT);
        _last_action_type = NONE;
        shift_holded = false;
    } else if (state->pressed) {
        _last_action_type = HOLD;
        register_code(KC_LSFT);
    } else if (state->count == 1) {
        _last_action_type = TAP;
        unregister_code(KC_LSFT);
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 2) {
        _last_action_type = DOUBLE_TAP;
        register_code(KC_LSFT);
        shift_holded = true;
    } else {
        _last_action_type = NONE;
    }
}
