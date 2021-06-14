//instanalize an instance of 'tap' for the K - Numpad - Hyper tap dance.
static tap k_numpad_hyper_state = {
    .is_press_action = true,
    .state           = 0
};

void k_numpad_hyper_finished(qk_tap_dance_state_t *state, void *user_data) {
    k_numpad_hyper_state.state = current_dance(state);
    switch (k_numpad_hyper_state.state) {
        case SINGLE_TAP:
            register_code(KC_K);
            break;

        case SINGLE_HOLD:
            layer_on(NUMPAD);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_LALT);
            register_code(KC_LGUI);
            break;
    }
}

void k_numpad_hyper_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (k_numpad_hyper_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_K);
            break;

        case SINGLE_HOLD:
            layer_off(NUMPAD);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LGUI);
            break;
    }
    k_numpad_hyper_state.state = 0;
}
