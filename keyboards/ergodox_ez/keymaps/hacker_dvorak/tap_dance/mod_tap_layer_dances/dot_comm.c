//instanalize an instance of 'tap' for the Dot - Comma tap dance.
static tap dot_comm_state = {
    .is_press_action = true,
    .state           = 0
};

void dot_comm_finished(qk_tap_dance_state_t *state, void *user_data) {
    dot_comm_state.state = current_dance(state);
    switch (dot_comm_state.state) {
        case SINGLE_TAP:
            register_code(KC_DOT);
            break;

        case SINGLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            break;

        case DOUBLE_TAP:
            register_code(KC_COMM);
            break;
    }
}

void dot_comm_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (dot_comm_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_DOT);
            break;

        case SINGLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            break;

        case DOUBLE_TAP:
            unregister_code(KC_COMM);
            break;
    }
    dot_comm_state.state = 0;
}
