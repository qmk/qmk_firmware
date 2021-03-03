/* Copyright 2020 Eye Oh! Designs
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

// Tap Dance declarations
enum {
    TD_LRCBR, TD_LRBRC, TD_LRBK
};

  // Tap once for left curly brace ({), twice for right
  // Tap once for left bracket ([), twice for right
  // Tap once for left angle bracket (<), twice for right
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LRCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [TD_LRBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_LRBK] = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT),
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
   
    QWERTY,
    NUMBRS,
    SYMBLS,
    NAV,
    FUNCTN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [QWERTY] = LAYOUT_1u(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,       KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,       KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,       KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_LCTL,                   KC_LGUI, MO(NUMBRS), KC_SPC,           KC_ENT,     MO(NAV), MO(SYMBLS),       KC_RALT
    ),
   [NUMBRS] = LAYOUT_1u(
        KC_TAB,  KC_TRNS, KC_7,   KC_8,    KC_9,    KC_0,        KC_TRNS, KC_F9,   KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_ESC,  KC_TRNS, KC_4,   KC_5,    KC_6,    KC_TRNS,     KC_TRNS, KC_F5,   KC_F6,  KC_F7,  KC_F8,  KC_TRNS,
        KC_LSPO, KC_TRNS, KC_1,   KC_2,    KC_3,    KC_TRNS,     KC_TRNS, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_RSPC,
        KC_LCTL,                  KC_LGUI, KC_TRNS, KC_SPC,      KC_TRNS, KC_TRNS, MO(SYMBLS),             KC_RALT
    ),
    [SYMBLS] = LAYOUT_1u(
        KC_TAB,  KC_TRNS, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_BSPC,
        KC_ESC,  KC_TRNS, KC_DLR,  KC_PERC, KC_CIRC, KC_TRNS,     TD(TD_LRCBR), KC_MINS, KC_EQL,  TD(TD_LRBK), KC_PIPE, KC_GRV,
        KC_LSPO, KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_TRNS,     TD(TD_LRBRC), KC_UNDS, KC_PLUS, KC_TRNS,     KC_BSLS, KC_TILD,
        KC_LCTRL,                  KC_LGUI, KC_TRNS, KC_SPC,      KC_ENT,       KC_TRNS, KC_TRNS,                       KC_RALT
    ),
    [NAV] = LAYOUT_1u(
        KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_BSPC,
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
        KC_LSPO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_RSPC,
        KC_LCTL,                   KC_LGUI, KC_TRNS, KC_SPC,      KC_ENT,  KC_TRNS, KC_TRNS,                    KC_RALT
    ),
    [FUNCTN] = LAYOUT_1u(
        KC_VOLU, KC_Q,    KC_PGUP, RGB_TOG, BL_STEP, KC_T,        KC_Y,    KC_U,    KC_TRNS, RGB_MOD,  RGB_RMOD, KC_DEL,
        KC_VOLD, KC_HOME, KC_PGDN, KC_D,    KC_U,    KC_MINS,     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT,  RESET,
        KC_LSFT, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_LBRC,     KC_RBRC, RGB_VAI, RGB_VAD, KC_DOT,   KC_BSLS,  KC_RSFT,
        KC_LCTL,                   KC_TRNS, KC_TRNS, KC_SPC,      KC_ENT,  KC_TRNS, KC_TRNS,                     KC_TRNS
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NUMBRS, SYMBLS, FUNCTN);
}
