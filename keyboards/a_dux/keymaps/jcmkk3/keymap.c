/* Copyright 2021 @jcmkk3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "oneshot.h"

#define LA_UPP OSL(UPP)
#define LA_SYM OSL(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    UPP,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
        KC_Y,    KC_C,    KC_L,    KC_M,    KC_K,    KC_Z,    KC_F,    KC_U,    KC_QUOT, KC_DQUO,
        KC_I,    KC_S,    KC_R,    KC_T,    KC_G,    KC_P,    KC_N,    KC_E,    KC_A,    KC_O,
        KC_Q,    KC_V,    KC_W,    KC_D,    KC_J,    KC_B,    KC_H,    KC_COMM, KC_DOT,  KC_X,
                                   LA_NAV,  KC_SPC,  LA_UPP,  LA_SYM
    ),

    [UPP] = LAYOUT(
        S(KC_Y), S(KC_C), S(KC_L), S(KC_M), S(KC_K), S(KC_Z), S(KC_F), S(KC_U), KC_EXLM, KC_QUES,
        S(KC_I), S(KC_S), S(KC_R), S(KC_T), S(KC_G), S(KC_P), S(KC_N), S(KC_E), S(KC_A), S(KC_O),
        S(KC_Q), S(KC_V), S(KC_W), S(KC_D), S(KC_J), S(KC_B), S(KC_H), KC_SCLN, KC_COLN, S(KC_X),
                                   _______, _______, _______, _______
    ),

    [SYM] = LAYOUT(
        KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_CIRC, KC_DLR,  KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK,
        KC_HASH, KC_UNDS, KC_EQL,  KC_MINS, KC_PLUS, KC_AMPR, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        KC_PERC, KC_GRV,  KC_TILD, KC_SLSH, KC_ASTR, KC_PIPE, KC_BSLS, KC_SCLN, KC_COLN, KC_AT,
                                   _______, _______, _______, _______
    ),

    [NAV] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_UP,   KC_ENT,  KC_DEL,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, KC_BSPC, _______
    ),

    [NUM] = LAYOUT(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, XXXXXXX, XXXXXXX, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT, KC_SLSH,
                                   _______, _______, KC_BSPC, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
