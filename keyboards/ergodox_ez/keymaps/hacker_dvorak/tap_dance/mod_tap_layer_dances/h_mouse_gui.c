//instanalize an instance of 'tap' for the H - Mouse - Gui tap dance.
static tap h_mouse_gui_state = {
    .is_press_action = true,
    .state           = 0
};

void h_mouse_gui_finished(qk_tap_dance_state_t *state, void *user_data) {
    h_mouse_gui_state.state = current_dance(state);
    switch (h_mouse_gui_state.state) {
        case SINGLE_TAP:
            register_code(KC_H);
            break;

        case SINGLE_HOLD:
            layer_on(MOUSE);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LGUI);
            break;
    }
}

void h_mouse_gui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (h_mouse_gui_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_H);
            break;

        case SINGLE_HOLD:
            layer_off(MOUSE);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            break;
    }
    h_mouse_gui_state.state = 0;
}
