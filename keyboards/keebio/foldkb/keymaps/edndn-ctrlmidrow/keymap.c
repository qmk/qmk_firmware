/* Copyright 2021 Danny Nguyen <danny@keeb.io>
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
#define C_CAD LSFT(LCTL(KC_ESC))
#define C_AF4 LALT(KC_F4)
#define C_CWL LCTL(LGUI(KC_LEFT))
#define C_CWR LCTL(LGUI(KC_RIGHT))
#define C_EMOJI LWIN(KC_DOT)

// TAP DANCE 

enum{   
    TD_PGUP,    // Once PGUP, twice HOME
    TD_PGDN,     // Once PGDN, twice END
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
    [TD_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MUTE, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    C_CAD,            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_BSPC,          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    TD(TD_PGUP),      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
    TD(TD_PGDN),      MO(1), KC_LALT, KC_LGUI, KC_LEFT, KC_SPC,  KC_RIGHT,      KC_SPC,  KC_SPC,  KC_RALT, KC_RCTL, KC_MENU, KC_LCTL
  ),
  [1] = LAYOUT(
    _______,   RESET, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
    C_AF4,            RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,     KC_P7,   KC_P8,   KC_P9,   _______, KC_MRWD, KC_MFFD, _______, KC_DEL,
    KC_DEL,           _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,     KC_P4,   KC_P5,   KC_P6,   _______, KC_MPRV, KC_MNXT,          _______,
    KC_HOME,          _______, _______, _______, KC_CALC, KC_UP,   _______,     KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______,
    KC_END,           _______, C_CWL,   C_CWR,   KC_LEFT, KC_DOWN, KC_RIGHT,    KC_P0,   KC_P0,   _______, _______, _______, _______
  ),
  [2] = LAYOUT(
    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
    _______,          KC_CAPS, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,     _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______, KC_DEL,
    _______,          _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,     _______, _______, _______, _______, KC_LEFT, KC_RGHT,          _______,
    _______,          _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_DOWN, KC_DOWN, _______,
    _______,          _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, C_EMOJI, _______
  )
};
   
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch(get_highest_layer(layer_state)){
            case 0:
                if (clockwise){
                    tap_code(KC_VOLU);
                }else{
                    tap_code(KC_VOLD);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
        }
    }
    return false;
}