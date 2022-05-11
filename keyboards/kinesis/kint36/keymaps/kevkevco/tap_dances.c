// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tap_dances.h"

// Tap Dance processing function option #1
// This tap dance favors keys that are used frequently in typing like 'f'
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return UNKNOWN;
}

// Tap Dance processing function option #2
// This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed)
                return SINGLE_TAP;
            else
                return SINGLE_HOLD;
        } else {
            if (!state->pressed)
                return SINGLE_TAP;
            else
                return SINGLE_HOLD;
        }
    }
    // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated with single tap.
    else if (state->count == 2) {
        if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    } else if (state->count == 3) {
        if (!state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return UNKNOWN;
}

// Triple Tap Dance function definition for period key
void triple_tap_dance_period(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_DOT);
    } else if (state->count == 2) {
        tap_code16(KC_RABK);
    } else if (state->count == 3) {
        SEND_STRING("...");
    } else {
        reset_tap_dance(state);
    }
}

// Triple Tap Dance function definition for Esc key
void triple_tap_dance_esc(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_ESC);
        if (caps_word_get()) {
            caps_word_set(false);
        }
    } else if (state->count == 2) {
        tap_code16(KC_GRV);
    } else if (state->count == 3) {
        tap_code16(KC_TILD);
    } else {
        reset_tap_dance(state);
    }
}

// ENTR Tap Dance
// Create an instance of 'td_tap_t' for the 'entr' tap dance.
static td_tap_t entr_td_state = {.is_press_action = true, .state = TD_NONE};

void entr_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    //   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
    entr_td_state.state = hold_cur_dance(state);
    switch (entr_td_state.state) {
        case SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case SINGLE_HOLD:
            layer_on(_KEYPAD);
            break;
        case DOUBLE_TAP:
            layer_invert(_KEYPAD);
            break;
        case DOUBLE_HOLD:
            toggle_num_word();
            break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
}

void entr_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (entr_td_state.state) {
        // case SINGLE_TAP: break;
        case SINGLE_HOLD:
            layer_off(_KEYPAD);
            break;
        // case DOUBLE_TAP: break;
        // case DOUBLE_HOLD: break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
    entr_td_state.state = 0;
}

// SLSH Tap Dance
// Create an instance of 'td_tap_t' for the 'slsh' tap dance.
static td_tap_t slsh_td_state = {.is_press_action = true, .state = TD_NONE};

void slsh_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    slsh_td_state.state = hold_cur_dance(state);
    switch (slsh_td_state.state) {
        case SINGLE_TAP:
            tap_code(KC_SLSH);
            break;
        case SINGLE_HOLD:
            tap_code16(G(KC_SLSH));
            break;
        case DOUBLE_TAP:
            SEND_STRING("// ");
            break;
        case DOUBLE_HOLD:
            SEND_STRING("/*" SS_DELAY(50) SS_TAP(X_ENT) SS_TAP(X_ENT) "*/" SS_DELAY(50) SS_TAP(X_UP));
            break;
        case TRIPLE_TAP:
            tap_code16(KC_QUES);
            break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
}

void slsh_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    //   switch (slsh_td_state.state) {
    // case SINGLE_TAP: break;
    // case SINGLE_HOLD: break;
    // case DOUBLE_TAP: break;
    // case DOUBLE_HOLD: break;
    // case TRIPLE_TAP: break;
    // case TRIPLE_HOLD: break;
    // default: break;
    //   }
    slsh_td_state.state = 0;
}

// COLON Tap Dance
// Create an instance of 'td_tap_t' for the 'colon' tap dance.
static td_tap_t colon_td_state = {.is_press_action = true, .state = TD_NONE};

void colon_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    colon_td_state.state = hold_cur_dance(state);
    switch (colon_td_state.state) {
        case SINGLE_TAP:
            clear_mods();
            set_oneshot_layer(_SYMBOLS, ONESHOT_START);
            break;
        case SINGLE_HOLD:
            set_mods(MOD_BIT(KC_RCTL));
            break;
        case DOUBLE_TAP:
            layer_invert(_NAV);
            break;
        case DOUBLE_HOLD:
            layer_on(_NAV);
            break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
}

void colon_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (colon_td_state.state) {
        case SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            break;
        // case DOUBLE_TAP: break;
        case DOUBLE_HOLD:
            layer_off(_NAV);
            break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
    colon_td_state.state = 0;
}

// RPINKY Tap Dance
// Create an instance of 'td_tap_t' for the 'rpinky' tap dance.
static td_tap_t rpinky_td_state = {.is_press_action = true, .state = TD_NONE};

void rpinky_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    rpinky_td_state.state = hold_cur_dance(state);
    switch (rpinky_td_state.state) {
        case SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case SINGLE_HOLD:
            layer_on(_SYMBOLS);
            set_oneshot_layer(_SYMBOLS, ONESHOT_START);
            break;
        case DOUBLE_TAP:
            layer_invert(_NUMSHIFT);
            break;
        case DOUBLE_HOLD:
            caps_word_set(true);
            break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
}

void rpinky_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (rpinky_td_state.state) {
        case SINGLE_TAP:
            layer_off(_NAV);
            break;
        case SINGLE_HOLD:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        // case DOUBLE_TAP: break;
        // case DOUBLE_HOLD: break;
        // case TRIPLE_TAP: break;
        // case TRIPLE_HOLD: break;
        default:
            break;
    }
    rpinky_td_state.state = 0;
}

// LPINKY Tap Dance
// Create an instance of 'td_tap_t' for the 'lpinky' tap dance.
static td_tap_t lpinky_td_state = {.is_press_action = true, .state = TD_NONE};

void lpinky_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    lpinky_td_state.state = cur_dance(state);
    switch (lpinky_td_state.state) {
        case SINGLE_TAP:
            layer_on(_SYMBOLS);
            set_oneshot_layer(_SYMBOLS, ONESHOT_START);
            break;
        case SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case DOUBLE_TAP:
            layer_invert(_NAV);
            break;
        case DOUBLE_HOLD:
            layer_on(_NAV);
            set_mods(MOD_MASK_CA);
            break;
        case TRIPLE_TAP:
            layer_invert(_LKEYPAD);
            break;
        case TRIPLE_HOLD:
            register_code16(C(KC_C));
            break;
        default:
            break;
    }
}

void lpinky_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (lpinky_td_state.state) {
        case SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            layer_off(_NAV);
            break;
        // case DOUBLE_TAP: break;
        case DOUBLE_HOLD:
            layer_off(_NAV);
            clear_mods();
            break;
        // case TRIPLE_TAP: break;
        case TRIPLE_HOLD:
            unregister_code16(C(KC_C));
            break;
        default:
            break;
    }
    lpinky_td_state.state = 0;
}

// Window Management Tap Dance
static td_tap_t window_td_state = {.is_press_action = true, .state = TD_NONE};

void window_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    //   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
    window_td_state.state = hold_cur_dance(state);
    switch (window_td_state.state) {
        case SINGLE_TAP:
            add_oneshot_mods(MOD_MASK_CA);
            layer_on(_NAV);
            set_oneshot_layer(_NAV, ONESHOT_START);
            break;
        case SINGLE_HOLD:
            layer_on(_NAV);
            set_mods(MOD_MASK_CA);
            break;
        case DOUBLE_TAP:
            register_code16(G(KC_GRV));
            break;
        case DOUBLE_HOLD:
            layer_on(_NAV);
            set_mods(MOD_MASK_CAG);
            break;
        case TRIPLE_TAP:
            add_oneshot_mods(MOD_MASK_SA);
            layer_on(_NAV);
            set_oneshot_layer(_NAV, ONESHOT_START);
            break;
        case TRIPLE_HOLD:
            register_code16(G(KC_H));
            break;
        default:
            break;
    }
}

void window_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    //   qk_tap_dance_full_t *keycodes = (qk_tap_dance_full_t *)user_data;
    switch (window_td_state.state) {
        case SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            layer_off(_NAV);
            clear_mods();
            break;
        case DOUBLE_TAP:
            unregister_code16(G(KC_GRV));
            break;
        case DOUBLE_HOLD:
            layer_off(_NAV);
            clear_mods();
            break;
        case TRIPLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TRIPLE_HOLD:
            unregister_code16(G(KC_H));
            break;
        default:
            break;
    }
    window_td_state.state = 0;
}

// Declare the functions to be used with tap dance key(s)
qk_tap_dance_action_t tap_dance_actions[] = {

    [CMAG] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LABK),  // Comma on a single-tap, left angle bracket on a double-tap
    [SPOT] = ACTION_TAP_DANCE_DOUBLE(G(KC_SPC), KC_SPC), // Command+Space (Spotlight) on a single-tap, space on a double-tap
    [ISPT] = ACTION_TAP_DANCE_DOUBLE(KC_I, G(KC_SPC)),   // I key on a single-tap, Command+Space (Spotlight) on a double-tap

    // Triple Tap Dance functions
    [PDAG] = ACTION_TAP_DANCE_FN(triple_tap_dance_period), // Dot on a single-tap, right angle bracket on a double-tap, three dots on a triple tap
    [GVES] = ACTION_TAP_DANCE_FN(triple_tap_dance_esc),    // Esc on a single-tap, grave on a double-tap, tilde on a triple tap

    // Advanced Tap Dance functions
    [ENTR]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, entr_td_finished, entr_td_reset),
    [SLSH]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slsh_td_finished, slsh_td_reset),
    [COLON]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, colon_td_finished, colon_td_reset),
    [RPINKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rpinky_td_finished, rpinky_td_reset),
    [LPINKY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lpinky_td_finished, lpinky_td_reset),
    [WIND]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, window_td_finished, window_td_reset),
};
