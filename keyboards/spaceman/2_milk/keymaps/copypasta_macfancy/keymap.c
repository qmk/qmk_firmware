// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum tapdance_keycodes { 
    TD_KEY_1,
    TD_KEY_2
};

void dance_key_one(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        /* Copy for Mac. */
        /* Windows & Linux use Ctrl+C: tap_code16(C(KC_C)) */
        tap_code16(G(KC_C));
        reset_tap_dance(state);
    } else if (state->count == 2) {
        /* Cut for Mac. */
        /* Windows & Linux use Ctrl+X: tap_code16(C(KC_X)) */
        tap_code16(G(KC_X));
        reset_tap_dance(state);
    } else if (state->count == 3) {
        /* Plain old Tab. */
        tap_code(KC_TAB);
        reset_tap_dance(state);
    }
}

void dance_key_two(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        /* Paste for Mac. */
        /* Windows & Linux use Ctrl+V: tap_code16(C(KC_V)) */
        tap_code16(G(KC_V));
        reset_tap_dance(state);
    } else if (state->count == 2) {
        /* Paste as value Gui+Shift+V for Mac. */
        /* Windows & Linux use Ctrl+Shift V: tap_code16(C(S(KC_V))) */
        tap_code16(G(S(KC_V)));
        reset_tap_dance(state);
    } else if (state->count == 3) {
        /* Tab between programs for mac Gui+Tab.  */
        /* Windows & Linux use Ctrl+Tab: tap_code16(C(KC_TAB)) */
        tap_code16(G(KC_TAB));
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_KEY_1] = ACTION_TAP_DANCE_FN(dance_key_one), 
    [TD_KEY_2] = ACTION_TAP_DANCE_FN(dance_key_two)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(TD(TD_KEY_1),
    TD(TD_KEY_2))
};
