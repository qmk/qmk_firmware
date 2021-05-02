#include "edvorakjp.h"
#include "process_keycode/process_tap_dance.h"

enum tap_state {
    NONE       = 0,
    SINGLE_TAP = 1,
    DOUBLE_TAP = 2,
    HOLD,
};

typedef struct {
    uint8_t lower;
    uint8_t raise;
} td_status_t;
static td_status_t td_status = {NONE, NONE};

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->interrupted || !state->pressed) {
        return state->count == 1 ? SINGLE_TAP : DOUBLE_TAP;
    } else {
        return HOLD;
    }
}

void td_lower_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_status.lower = cur_dance(state);
    switch (td_status.lower) {
        case SINGLE_TAP:
            set_japanese_mode(false);
            break;
        case DOUBLE_TAP:
            set_japanese_mode(false);
            register_code(KC_ESC);
            break;
    }
    layer_on(L_EDVORAKJP_LOWER);
}

void td_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_status.lower) {
        case DOUBLE_TAP:
            unregister_code(KC_ESC);
            break;
    }
    layer_off(L_EDVORAKJP_LOWER);
    td_status.lower = NONE;
}

void td_raise_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_status.raise = cur_dance(state);
    switch (td_status.raise) {
        case DOUBLE_TAP:
            // same as single
        case SINGLE_TAP:
            set_japanese_mode(true);
            break;
    }
    layer_on(L_EDVORAKJP_RAISE);
}

void td_raise_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(L_EDVORAKJP_RAISE);
    td_status.raise = NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EDVORAKJP_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_lower_finished, td_lower_reset, 150),
    [TD_EDVORAKJP_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_raise_finished, td_raise_reset, 150),
};
