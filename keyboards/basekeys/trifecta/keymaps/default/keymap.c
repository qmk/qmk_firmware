/* Copyright 2020 Swiftrax and Basekeys.com
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
    _FN,
    _MEDIA };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_DEL,   KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,     KC_END,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                 KC_HOME,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        MO(_MEDIA),   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,        KC_UP,
    KC_LCTL, KC_LGUI,  KC_LALT,         KC_SPC,                         KC_SPC,           KC_RGUI, KC_RCTL,  MO(_FN),        KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN] = LAYOUT(
     KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  _______,     _______,
    _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,
    _______, RGB_MOD, RGB_HUI, RGB_SAI,  RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______,                         _______,
    _______, RGB_TOG, RGB_HUD, RGB_SAD,  RGB_VAD, _______, _______, _______, _______, _______, _______, _______,  _______,                   KC_PGUP,
    _______, _______, _______,           _______, _______,          _______,          _______,          _______,                    KC_HOME, KC_PGDN, KC_END
  ),

  [_MEDIA] = LAYOUT(
     KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  _______,     _______,
    _______, _______, _______, _______,    RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,
    _______, RGB_MOD, RGB_HUI, RGB_SAI,  RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______,                         _______,
    _______, RGB_TOG, RGB_HUD, RGB_SAD,  RGB_VAD, _______, _______, _______, _______, _______, _______, _______,  _______,                   KC_PGUP,
    _______, _______, _______,           _______, _______,          _______,          _______,          _______,                    KC_HOME, KC_PGDN, KC_END
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
     } else if (index == 2) { /* Third encoder */
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    }
    return true;
}
