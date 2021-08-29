/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
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

#define CTL_TAB CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho(
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_BSPC, RGB_TOG,
        CTL_TAB, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_LSFT, KC_UP  ,
        KC_APP , KC_LCTL, KC_LGUI, KC_LALT, MO(1)  , KC_SPC , KC_SPC , MO(2)  , KC_RALT, KC_RCTL, KC_DEL , KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_ortho(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_RBRC, KC_BSLS, RGB_MOD,
        _______, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_SCLN, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, KC_PGUP,
        _______, _______, _______, _______, _______, _______, _______, MO(3)  , _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [2] = LAYOUT_ortho(
        KC_TILD, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, _______, RGB_VAI,
        _______, _______, _______, _______, MO(3)  , _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_VAD, RGB_HUI
    ),

    [3] = LAYOUT_ortho(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

void matrix_init_user(void) {
  setPinOutput(B5);
  writePinLow(B5);
  setPinOutput(B6);
  writePinLow(B6);
  setPinOutput(B7);
  writePinLow(B7);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePinLow(B5);
    writePinLow(B6);
    writePinLow(B7);
    switch (get_highest_layer(state)) {
    case 1:
        writePinHigh(B5);
        break;
    case 2:
        writePinHigh(B6);
        break;
    case 3:
        writePinHigh(B7);
        break;
    }
    return state;
}
