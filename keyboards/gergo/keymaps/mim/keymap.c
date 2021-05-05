/* Copyright 2021 Martin Guilloux
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

enum combos {
  FJ_ENTER,
  G_INS_ENTER,
  XCV_CAPSLOCK,
};

const uint16_t PROGMEM fj_combo[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM gins_combo[] = {KC_G, KC_INS, COMBO_END};
const uint16_t PROGMEM xcv_combo[] = {KC_X, KC_C, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [FJ_ENTER] = COMBO(fj_combo, KC_ENTER),
  [G_INS_ENTER] = COMBO(gins_combo, KC_ENTER),
  [XCV_CAPSLOCK] = COMBO(xcv_combo, KC_CAPSLOCK)
};

enum custom_keycodes {
    TMUX = SAFE_RANGE,
};

// Tap Dance declarations 
enum {
    TD_QUOTE_GRAVE,
    TD_GRAVE_CIRCUMFLEX
};
// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOTE_GRAVE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRV),
    [TD_GRAVE_CIRCUMFLEX] = ACTION_TAP_DANCE_DOUBLE(KC_GRV,KC_CIRCUMFLEX)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_gergo(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_PIPE, LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_INS, KC_CIRCUMFLEX, KC_H, KC_J, KC_K, KC_L, KC_SCLN, TD(TD_QUOTE_GRAVE), KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LSFT(KC_INS), LT(2,KC_F1), KC_F2, DYN_REC_START1, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, KC_LCTL, KC_LGUI, LT(1,KC_SPC), KC_LALT, LSFT_T(KC_DEL), LT(2,KC_BSPC), KC_RALT, C(KC_X)),
        [1] = LAYOUT_gergo(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL, KC_TRNS, KC_TRNS, KC_TILD, KC_LCBR, KC_LCBR, KC_LBRC, KC_LPRN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RPRN, KC_RBRC, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [2] = LAYOUT_gergo(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_VOLU, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLD, KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC_MSTP, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
