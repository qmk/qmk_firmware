/*
Copyright 2019 Boy_314

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _BL 0
#define _F1 1
#define _F2 2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BL] = LAYOUT(
      QK_GESC,        KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_LBRC,  KC_RBRC, KC_BSPC,  KC_DEL,
      KC_TAB,         KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,    KC_L,    KC_SLSH,  KC_EQL,  KC_BSLS,  KC_PGUP,
      CTL_T(KC_CAPS), KC_A,    KC_O,    KC_E,    KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,    KC_S,    KC_MINS,  KC_ENT,            KC_PGDN,
      SC_LSPO,                 KC_SCLN, KC_Q,    KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,    KC_V,    KC_Z,     SC_RSPC, KC_UP,    MO(_F2),
      KC_LCTL,        KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, MO(_F1),           KC_LEFT, KC_DOWN,  KC_RIGHT),

  [_F1] = LAYOUT(
	  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,   KC_TRNS,
      KC_TRNS, KC_NO,   KC_UP,   KC_NO,   RGB_TOG,RGB_VAI,RGB_HUI,RGB_SAI,KC_INS, QK_BOOT, KC_PSCR, KC_TRNS,  KC_PAUS, KC_BSLS,  KC_TRNS,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,RGB_MOD,RGB_VAD,RGB_HUD,RGB_SAD,KC_NO,  KC_NO,   KC_F14,  KC_F15,   KC_INS,            KC_HOME,
      SC_LSPO,          KC_MPRV, KC_MPLY, KC_MNXT,KC_NO,  KC_NO,  KC_NO,  KC_MUTE,KC_VOLD, KC_VOLU, KC_NO,    SC_RSPC, KC_VOLU,  KC_TRNS,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_TRNS,                KC_RALT, KC_TRNS,           KC_MPLY, KC_VOLD,  KC_MNXT),
	  
  [_F2] = LAYOUT(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,   KC_PAUS,
      KC_TRNS, KC_NO,   KC_UP,   KC_NO,   RGB_TOG,RGB_VAI,RGB_HUI,RGB_SAI,KC_INS, QK_BOOT, KC_PSCR, KC_SCRL,  KC_PAUS, KC_BSLS,  KC_SCRL,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,RGB_MOD,RGB_VAD,RGB_HUD,RGB_SAD,KC_NO,  KC_NO,   KC_F14,  KC_F15,   KC_INS,            KC_HOME,
      SC_LSPO,          KC_MPRV, KC_MPLY, KC_MNXT,KC_NO,  KC_NO,  KC_NO,  KC_MUTE,KC_VOLD, KC_VOLU, KC_NO,    SC_RSPC, KC_PGUP,  KC_TRNS,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_TRNS,                KC_RALT, KC_TRNS,           KC_HOME, KC_PGDN,  KC_END)

};

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_sethsv(HSV_RED);
    } else {
        rgblight_sethsv(HSV_TURQUOISE);
    }
    return false;
}