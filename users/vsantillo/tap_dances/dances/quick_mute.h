// Tap object to track status of Quick Mute
static tap quick_mute_state = {
    .state = 0,
    .count = 0
};

void quick_mute(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    quick_mute_state.state = tap_dance_controller(state);
    quick_mute_state.count = state->count;

    // Send keys
    switch (quick_mute_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUAD_HOLD:
            register_code(KC_MUTE);
            unregister_code(KC_MUTE);
            break;
        default:
            for (int vold_counter = 0; vold_counter < quick_mute_state.count; vold_counter++) {
                register_code(KC_VOLD);
                unregister_code(KC_VOLD);
            }
            break;
    }

    // Reset state
    quick_mute_state.state = 0;
}
