// Copyright 2021 Your Name (@artflag)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Tap Dance declarations

enum {
    CT_CLN, // Reverses colon and semicolon and triggers semicolon on tap dance.
};

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_COLN);
    } else {
        register_code(KC_SCLN);
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_COLN);
    } else {
        unregister_code(KC_SCLN);
    }
}

// All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_ESC, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, TD(CT_CLN), KC_BSPC, KC_LGUI, KC_A, KC_S, KC_H, KC_T, KC_G, KC_Y, KC_N, KC_E, KC_O, KC_I, KC_QUOT, KC_TAB, KC_Z, KC_X, KC_M, KC_C, KC_V, KC_BSLS, TT(2), KC_LBRC, KC_RBRC, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, KC_GRV, KC_LCTL, KC_LALT, KC_SPC, SC_LSPO, TT(1), TT(1), SC_RSPC, KC_ENT, KC_MINS, KC_EQL),
	[1] = LAYOUT(KC_TRNS, KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO, KC_NO, KC_UP, KC_PGUP, KC_PSLS, KC_TRNS, KC_TRNS, KC_0, KC_4, KC_5, KC_6, KC_PDOT, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PAST, KC_PPLS, KC_TRNS, KC_NO, KC_1, KC_2, KC_3, KC_PCMM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_HOME, KC_END, KC_PGDN, KC_EXLM, KC_PMNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_NO, KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_MPLY, KC_VOLU, KC_BRIU, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_MSTP, KC_VOLD, KC_BRID, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO)
};
