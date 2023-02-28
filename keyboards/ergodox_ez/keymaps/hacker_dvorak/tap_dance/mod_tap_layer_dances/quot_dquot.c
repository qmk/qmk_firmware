//instanalize an instance of 'tap' for the Quote - Double Quote tap dance.
static tap quot_dquot_state = {
    .is_press_action = true,
    .state           = 0
};

void quot_dquot_finished(tap_dance_state_t *state, void *user_data) {
    quot_dquot_state.state = current_dance(state);
    switch (quot_dquot_state.state) {
        case SINGLE_TAP:
            register_code(KC_QUOT);
            break;

        case SINGLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            break;

        case DOUBLE_TAP:
            register_code16(KC_DQUO);
            break;
    }
}

void quot_dquot_reset(tap_dance_state_t *state, void *user_data) {
    switch (quot_dquot_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_QUOT);
            break;

        case SINGLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            break;

        case DOUBLE_TAP:
            unregister_code16(KC_DQUO);
            break;
    }
    quot_dquot_state.state = 0;
}
