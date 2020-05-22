#include "imchipwood.h"

static td_state_t td_state;

// determine the tapdance state to return
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    } else {
        return 3;
    }  // any number higher than the maximum state value you return above
}

void altf2_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code(KC_F2);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LALT));
            tap_code(KC_F2);
            break;
    }
}

void altf2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code(KC_F2);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F2);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
    }
}


void ctlf5_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code(KC_F5);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            tap_code(KC_F5);
            break;
    }
}

void ctlf5_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code(KC_F5);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F5);
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
    }
}

void altf7_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code(KC_F7);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LALT));
            tap_code(KC_F7);
            break;
    }
}

void altf7_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code(KC_F7);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F7);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT_F2]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altf2_finished, altf2_reset),
    [CTL_F5]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlf5_finished, ctlf5_reset),
    [ALT_F7]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altf7_finished, altf7_reset),
    [DEL_NLCK] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_NLCK),
    // Double tap right -> END
    [TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
    // Double tap left -> HOME
    [TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
    // Double tap right shift -> CAPS LOCK
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};
