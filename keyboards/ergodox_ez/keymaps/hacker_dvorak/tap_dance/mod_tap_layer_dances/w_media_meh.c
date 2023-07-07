//instanalize an instance of 'tap' for the W - Media - Meh tap dance.
static tap w_media_meh_state = {
    .is_press_action = true,
    .state           = 0
};

void w_media_meh_finished(tap_dance_state_t *state, void *user_data) {
    w_media_meh_state.state = current_dance(state);
    switch (w_media_meh_state.state) {
        case SINGLE_TAP:
            register_code(KC_W);
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

void w_media_meh_reset(tap_dance_state_t *state, void *user_data) {
    switch (w_media_meh_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_W);
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
    w_media_meh_state.state = 0;
}
