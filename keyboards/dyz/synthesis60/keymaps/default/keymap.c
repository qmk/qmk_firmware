/* Copyright 2019 Ryota Goto
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

enum layer_names {
    _BASE,
    _FN,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all( /* Base */
        KC_HOME,    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_PGUP,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_PGDN,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
                    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DEL,
                    KC_LCTL,          KC_LALT,          KC_SPC,  MO(1),               KC_SPC,  KC_SPC,  KC_RALT,                   KC_RGUI, KC_APP,  KC_RCTL
    ),
    [_FN] = LAYOUT_all(
        RGB_TOG,    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        KC_VOLU,    _______, _______, KC_HOME, KC_UP,   KC_END,  _______,             _______, _______, _______, _______, _______, _______, _______, _______,
        KC_VOLD,    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,             _______, _______, _______, _______, _______, _______,          _______,
                    _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______, _______,
                    _______,          _______,          _______, _______,             _______, _______, _______,                   _______, _______, _______
    ),
    [_FN2] = LAYOUT_all(
        _______,    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,          _______,
                    _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______, _______,
                    _______,          _______,          _______, _______,             _______, _______, _______,                   _______, _______, _______
    )
};


layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) != 0) {
        gpio_write_pin_low(C6);
    } else {
        gpio_write_pin_high(C6);
    }
    return state;
}
