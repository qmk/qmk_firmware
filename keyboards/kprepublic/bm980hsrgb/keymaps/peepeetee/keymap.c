/* Copyright 2021 peepeetee
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,                        KC_INS,  KC_DEL,   KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,
	  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_NLCK,  KC_HOME,  KC_END,  KC_PGUP,
	  KC_TAB, 	     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,       KC_P7,    KC_P8,    KC_P9,    KC_PGDN,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                  KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,   KC_LALT, KC_LGUI,                       KC_SPC,                             KC_RALT, MO(1),   KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT,   KC_P0,   KC_PDOT
  ),

  [1] = LAYOUT(
       RESET,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,                                   _______,    _______,    _______,  _______,
	  _______,   _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,            _______,    _______,    _______,  _______,
	  RGB_MOD, 	     RGB_HUI,     RGB_VAI,     RGB_SAI,     RGB_SPI,     _______,     _______,     _______,     _______,     _______,     _______,     _______,  _______,  _______,         _______,    _______,    _______,  _______,
	  RGB_TOG,          RGB_HUD,     RGB_VAD,     RGB_SAD,     RGB_SPD,     _______,     _______,     _______,     _______,     _______,     _______,  _______,  _______,                   _______,    _______,    _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   _______, _______, _______, _______,
        _______,   _______, _______,                      _______,                             _______, _______, _______,      _______, _______, _______,   _______, _______
  )

    // [X] = LAYOUT(
    //     _______,          _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,     _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
    //     _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    //     _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______,
    //     _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   _______, _______, _______, _______,
    //     _______,   _______, _______,                      _______,                             _______, _______, _______,      _______, _______, _______,   _______, _______
    // ),
};


void rgb_matrix_indicators_user(void) {

    led_t host_leds = host_keyboard_led_state();
    if (host_leds.num_lock) {
        rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF);
        //rgb_matrix_set_color(30, 0x0, 0x0, 0x0);

    } else {
        //rgb_matrix_set_color(30, 0x0, 0x0, 0x0);
    }
        //set_layer_color(get_highest_layer(layer_state));

}
