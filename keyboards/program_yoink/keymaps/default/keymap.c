/* Copyright 2020 melonbred
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
    _LAYER1,
    _LAYER2
};

// Defines Combos for use in the keymap
enum combo_events {
  COMBO_SLSH,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_default(
        KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_MUTE,
        KC_TAB,    KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H, KC_J,    KC_K,    KC_L,    KC_ENT,     RGB_VAI,
        KC_LSFT,    KC_Z,    KC_X, KC_C, KC_V, KC_B,  KC_N, KC_M,    KC_COMM, MT(MOD_RSFT, KC_DOT), KC_UP,  RGB_VAD,
        KC_LCTL, MT(MOD_LALT, KC_CAPS),                  LT(_LAYER2, KC_SPC),               LT(_LAYER1, KC_DEL), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LAYER1] = LAYOUT_default(
        KC_MINS,  KC_1,    KC_2,   KC_3,      KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,  _______,
        KC_EQL, _______, _______, _______,   _______, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT,          _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_LGUI, KC_LALT,                             _______,                   _______, _______, _______,          _______         
    ), 

    [_LAYER2] = LAYOUT_default(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, RGB_M_B, RGB_M_P, RGB_M_K, RGB_M_G, RGB_M_R,          RGB_HUI,
        _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______,          RGB_HUD,
        _______, RGB_TOG,                            XXXXXXX,                   RESET, _______,  _______,          _______
   ),
};


void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_slsh[] = {MT(MOD_RSFT, KC_DOT), KC_COMM, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [COMBO_SLSH] = COMBO(combo_slsh,KC_SLSH),

};
#endif
        
