//instanalize an instance of 'tap' for the M - Chords - Hyper tap dance.
static tap m_chords_hyper_state = {
    .is_press_action = true,
    .state           = 0
};

void m_chords_hyper_finished(qk_tap_dance_state_t *state, void *user_data) {
    m_chords_hyper_state.state = current_dance(state);
    switch (m_chords_hyper_state.state) {
        case SINGLE_TAP:
            register_code(KC_M);
            break;

        case SINGLE_HOLD:
            layer_on(CHORD);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_LALT);
            register_code(KC_LGUI);
            break;
    }
}

void m_chords_hyper_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (m_chords_hyper_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_M);
            break;

        case SINGLE_HOLD:
            layer_off(CHORD);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LGUI);
            break;
    }
    m_chords_hyper_state.state = 0;
}
