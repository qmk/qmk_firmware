/* Copyright 2018 vitvlkv
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

/* To compile firmware:
qmk compile -kb hs60/v2/ansi -km vitvlkv

To flash firmware:
- plug in keyboard
- press hardware 'reset' button (on the PCB)
- execute command:
qmk flash -kb hs60/v2/ansi -km vitvlkv

Backlight specific keys:
EF_INC, EF_DEC,   // next/previous backlight effect
H1_INC, H1_DEC,   // Color 1 hue increase/decrease
S1_INC, S1_DEC,   // Color 1 saturation increase/decrease
H2_INC, H2_DEC,   // Color 2 hue increase/decrease
S2_INC, S2_DEC,   // Color 2 saturation increase/decrease
BR_INC, BR_DEC,   // backlight brightness increase/decrease
ES_INC, ES_DEC,   // ?..
*/
#include QMK_KEYBOARD_H

//This is the ANSI version of the PCB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_60_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_MINS,        KC_EQL,         KC_BSPC,\
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_LBRC,        KC_RBRC,        KC_BSLS,\
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,       KC_QUOT,                        KC_ENT,\
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,        KC_SLSH,                        KC_RSFT,\
    KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,       MO(1),          LT(2, KC_APP),  KC_GRV),

[1] = LAYOUT_60_ansi( /* Fn */
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,\
    _______,  KC_PGUP,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,    _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,  _______,\
    _______,  KC_PGDN,  _______,  KC_HOME,  KC_END,   KC_DEL,   KC_BSPC,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_INS,   _______,            _______,\
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,  KC_PGDN,  _______,  _______,            _______,\
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  KC_RCTL),

[2] = LAYOUT_60_ansi( /* RGB */
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,\
    _______,  EF_INC,   BR_INC,   ES_INC,   H1_INC,   S1_INC,   H2_INC,   S2_INC,   _______,  _______,  _______,  _______,  _______,  _______,\
    _______,  EF_DEC,   BR_DEC,   ES_DEC,   H1_DEC,   S1_DEC,   H2_DEC,   S2_DEC,   _______,  _______,  _______,  _______,            _______,\
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,            _______,\
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______),
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
