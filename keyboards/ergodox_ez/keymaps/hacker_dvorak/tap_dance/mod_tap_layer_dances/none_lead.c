//instanalize an instance of 'tap' for the None - Lead tap dance.
static tap none_lead_state = {
    .is_press_action = true,
    .state           = 0
};

void none_lead_finished(tap_dance_state_t *state, void *user_data) {
    none_lead_state.state = current_dance(state);
    switch (none_lead_state.state) {
        case SINGLE_TAP:
            register_code(KC_NO);
            break;

        case SINGLE_HOLD:
            register_code(KC_LALT);
            register_code(KC_LSFT);
            break;

        case DOUBLE_TAP:
            leader_start();
            break;
    }
}

void none_lead_reset(tap_dance_state_t *state, void *user_data) {
    switch (none_lead_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_NO);
            break;

        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
            break;

        case DOUBLE_TAP:
            break;
    }
    none_lead_state.state = 0;
}
