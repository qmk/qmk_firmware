/* Copyright 2021 kuriatsu
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                          KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                         KC_ESC, KC_RGUI, KC_LALT,  KC_SPC, KC_LSFT,     KC_BSPC,  KC_ENT, MO(_FN), KC_BSLS,  KC_GRV
    ),
    [_FN] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
      _______, XXXXXXX, MS_BTN1, MS_UP,   MS_BTN2, UG_TOGG,                       KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX,
      _______, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, UG_NEXT,                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, UG_VALU, UG_HUEU,              _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______, _______, _______,                        KC_DEL, _______, _______, _______, _______
    )
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [_FN]   =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)}
};
#endif


