// Tap object to track status of Quick Undo
static tap quick_undo_state = {
    .state = 0,
    .count = 0
};

void quick_undo_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    quick_undo_state.state = tap_dance_controller(state);

    // Send keys
    switch (quick_undo_state.state) {
        case DOUBLE_HOLD:
            register_code(KC_LALT); // Left Alt
            register_code(KC_Z);    // + Z = Undo on macOS
            break;
        default:
            register_code(KC_LALT); // Left Alt
            break;
    }
}

void quick_undo_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    // Unregister keys
    switch (quick_undo_state.state) {
        case DOUBLE_HOLD:
            unregister_code(KC_Z);
            unregister_code(KC_LALT);
            break;
        default:
            unregister_code(KC_LALT);
            break;
    }

    quick_undo_state.state = 0;
}
