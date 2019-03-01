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

//Tap Dance Declarations
enum {
	TD_WIN = 0,
	TD_ESC
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_CAD, KC_LOCK),
	[TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_ansi(
		TD_TESC, KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CTLE, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		KC_LCTL, KC_LGUI, KC_LALT,          LT_SPCF,          KC_RALT, TD_TWIN, MO(3),   KC_RCTL),

	[1] = LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
		KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC ,          KC_RALT, MO(2),  MO(3),   KC_RCTL),

	[2] = LAYOUT_60_ansi(
		KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
		_______, _______, CA_QUOT, KC_VOLU, CA_SCLN, _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, KC_INS,
		KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_MPLY, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                   _______,                   _______, _______, _______, _______),

	[3] = LAYOUT_60_ansi(
		_______, RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, RGB_SAI, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
		TG(1),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______,                   _______,                   _______, _______, _______, _______)
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case 1:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case 2:
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case 3:
        rgblight_setrgb (0xFF,  0xFF, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
