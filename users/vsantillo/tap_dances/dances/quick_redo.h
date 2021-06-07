// Tap object to track status of Quick redo
static tap quick_redo_state = {
    .state = 0,
    .count = 0
};

void quick_redo_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    quick_redo_state.state = tap_dance_controller(state);

    // Send keys
    switch (quick_redo_state.state) {
        case DOUBLE_HOLD:
            register_code(KC_RALT);    // Right Alt
            register_code(KC_RSHIFT);  // + Right Shift
            register_code(KC_Z);       // + Z = redo on macOS
            break;
        default:
            register_code(KC_RALT); // Right Alt
            break;
    }
}

void quick_redo_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    // Unregister keys
    switch (quick_redo_state.state) {
        case DOUBLE_HOLD:
            unregister_code(KC_Z);
            unregister_code(KC_RSHIFT);
            unregister_code(KC_RALT);
            break;
        default:
            unregister_code(KC_RALT);
            break;
    }

    quick_redo_state.state = 0;
}
