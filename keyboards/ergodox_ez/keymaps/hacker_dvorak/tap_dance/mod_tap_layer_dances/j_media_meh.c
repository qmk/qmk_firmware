//instanalize an instance of 'tap' for the J - Media - Meh tap dance.
static tap j_media_meh_state = {
    .is_press_action = true,
    .state           = 0
};

void j_media_meh_finished(qk_tap_dance_state_t *state, void *user_data) {
    j_media_meh_state.state = current_dance(state);
    switch (j_media_meh_state.state) {
        case SINGLE_TAP:
            register_code(KC_J);
            break;

        case SINGLE_HOLD:
            layer_on(MEDIA_FN);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_LALT);
            break;
    }
}

void j_media_meh_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (j_media_meh_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_J);
            break;

        case SINGLE_HOLD:
            layer_off(MEDIA_FN);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            break;
    }
    j_media_meh_state.state = 0;
}
