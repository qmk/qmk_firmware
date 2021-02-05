/* Copyright 2018 Stanrc85
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
#include "stanrc85.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_60_ansi(
	TD_TESC, KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
	KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CTLE, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
	KC_LCTL, KC_LGUI, KC_LALT,          LT_SPCF,          KC_RALT, TD_TWIN, MO(_FN2_60),   TD_TCTL),

  [_DEFAULT] = LAYOUT_60_ansi(
	KC_GESC, KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
	KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_RALT, MO(_FN1_60), MO(_FN2_60), KC_RCTL),

  [_FN1_60] = LAYOUT_60_ansi(
	KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
	_______, _______, CA_QUOT, KC_VOLU, CA_SCLN, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR, _______, _______, KC_INS,
	KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_MPLY, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
	_______, KC_RDP,  _______, _______, _______, _______, _______, _______, KC_WBAK, KC_WFWD, _______, _______,
	_______, _______, _______,                   _______,                   _______, _______, _______, _______),

  [_FN2_60] = LAYOUT_60_ansi(
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EEP_RST,
	_______, EF_INC,  ES_INC,  S1_INC,  H1_INC,  S2_INC,  H2_INC,  BR_INC,  _______, _______, _______, _______, _______, RESET,
	_______, EF_DEC,  ES_DEC,  S1_DEC,  H1_DEC,  S2_DEC,  H2_DEC,  BR_DEC,  _______, _______, _______, _______, KC_MAKE,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______,                   _______,                   _______, _______, _______, TG(_DEFAULT))
};

// Backlight specific keys:
//  EF_INC, EF_DEC,   // next/previous backlight effect
//  H1_INC, H1_DEC,   // Color 1 hue increase/decrease
//  S1_INC, S1_DEC,   // Color 1 saturation increase/decrease
//  H2_INC, H2_DEC,   // Color 2 hue increase/decrease
//  S2_INC, S2_DEC,   // Color 2 saturation increase/decrease
//  BR_INC, BR_DEC,   // backlight brightness increase/decrease

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
