//instanalize an instance of 'tap' for the U - Arrows - Gui tap dance.
static tap u_arrows_gui_state = {
    .is_press_action = true,
    .state           = 0
};

void u_arrows_gui_finished(tap_dance_state_t *state, void *user_data) {
    u_arrows_gui_state.state = current_dance(state);
    switch (u_arrows_gui_state.state) {
        case SINGLE_TAP:
            register_code(KC_U);
            break;

        case SINGLE_HOLD:
            layer_on(ARROWS);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LGUI);
            break;
    }
}

void u_arrows_gui_reset(tap_dance_state_t *state, void *user_data) {
    switch (u_arrows_gui_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_U);
            break;

        case SINGLE_HOLD:
            layer_off(ARROWS);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            break;
    }
    u_arrows_gui_state.state = 0;
}
