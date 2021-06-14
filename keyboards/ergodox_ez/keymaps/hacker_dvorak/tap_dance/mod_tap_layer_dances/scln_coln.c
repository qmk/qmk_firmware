//instanalize an instance of 'tap' for the Semicolon - Colon tap dance.
static tap scln_coln_state = {
    .is_press_action = true,
    .state           = 0
};

void scln_coln_finished(qk_tap_dance_state_t *state, void *user_data) {
    scln_coln_state.state = current_dance(state);
    switch (scln_coln_state.state) {
        case SINGLE_TAP:
            register_code(KC_SCLN);
            break;

        case SINGLE_HOLD:
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            break;

        case DOUBLE_TAP:
            register_code16(KC_COLN);
            break;
    }
}

void scln_coln_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (scln_coln_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_SCLN);
            break;

        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
            unregister_code(KC_LGUI);
            break;

        case DOUBLE_TAP:
            unregister_code16(KC_COLN);
            break;
    }
    scln_coln_state.state = 0;
}
