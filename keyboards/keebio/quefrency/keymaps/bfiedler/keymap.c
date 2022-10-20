/* Copyright 2021 Ben Fiedler
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

#define KC_RST QK_BOOT

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
    _BASE,
    _FN1,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65(
    QK_GESC,         KC_1,         KC_2,    KC_3,     KC_4,    KC_5,   KC_6,             KC_7,    KC_8,    KC_9,    KC_0,            KC_MINS, KC_EQL,         KC_DEL,  KC_BSPC, KC_HOME, \
    KC_TAB,          KC_Q,         KC_W,    KC_E,     KC_R,    KC_T,   KC_Y,             KC_U,    KC_I,    KC_O,    KC_P,            KC_LBRC, KC_RBRC,        KC_BSLS, KC_END, \
    LGUI_T(KC_BSPC), KC_A,         KC_S,    KC_D,     KC_F,    KC_G,   KC_H,             KC_J,    KC_K,    KC_L,    KC_SCLN,         KC_QUOT, LGUI_T(KC_ENT), KC_PGUP, \
    KC_LSFT,         LCTL_T(KC_Z), KC_X,    KC_C,     KC_V,    KC_B,   KC_N,             KC_M,    KC_COMM, KC_DOT,  LCTL_T(KC_SLSH), KC_RSFT, KC_UP,          KC_PGDN, \
    KC_LCTL,         KC_LALT,      KC_LGUI, KC_LALT,  KC_SPC,          LT(_FN1, KC_ENT), KC_RALT, _______, KC_RCTL, KC_RGUI,         KC_LEFT, KC_DOWN,        KC_RGHT
  ),

  [_FN1] = LAYOUT_65(
    QK_GESC,         KC_F1,        KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,          KC_F11,  KC_F12,         KC_DEL,  KC_BSPC, _______, \
    RGB_TOG,         RGB_MOD,      _______, _______, _______, _______, _______,          _______, _______, _______, _______,         _______, _______,        _______, _______, \
    _______,         _______,      _______, _______, _______, _______, KC_LEFT,          KC_DOWN, KC_UP,   KC_RGHT, _______,         _______, _______,        _______, \
    _______,         _______,      _______, _______, _______, _______, _______,          _______, _______, _______, _______,         _______, _______,        _______, \
    KC_RST,          _______,      _______, _______, _______,          _______,          _______, _______, _______, _______,         _______, _______,        KC_RST
  )
};
// clang-format on

// TODO: I don't even have a rotary encoder, do I need this?
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
