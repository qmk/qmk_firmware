// Tap Dance Controller - returns a state based on the pattern pressed
uint8_t tap_dance_controller(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) return SINGLE_TAP_INT;
        else if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_TAP_INT;
        else if (!state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else if (state->count == 4) {
        if (state->interrupted || !state->pressed) return QUAD_TAP;
        else return QUAD_HOLD;
    } else return 11;
}
