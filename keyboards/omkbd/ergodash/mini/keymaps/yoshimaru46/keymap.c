/* Copyright 2021 Yoshihiro Saito
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

// Shift + ( = <
const key_override_t left_paren_angle_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_PAREN, KC_LEFT_ANGLE_BRACKET);

// Shift + ) = >
const key_override_t right_paren_angle_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_RIGHT_PAREN, KC_RIGHT_ANGLE_BRACKET);

const key_override_t **key_overrides = (const key_override_t *[]){
	&left_paren_angle_bracket_override,
	&right_paren_angle_bracket_override,
	NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty */
    [_QWERTY] = LAYOUT(
    KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LPRN,                           KC_RPRN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                           KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DEL,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,                           XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_LGUI, LOWER,   CTL_T(KC_SPC), KC_SFTENT, RAISE,   KC_RGUI,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* Lower */
  [_LOWER] = LAYOUT(
    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_F11,                            KC_GRV,  KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F12,                            KC_TILD, KC_BSLS, KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,                           XXXXXXX, KC_PIPE, KC_UNDS, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, XXXXXXX, _______,       _______,   XXXXXXX, _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* Raise */
  [_RAISE] = LAYOUT(
    XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   XXXXXXX,                           XXXXXXX, KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, XXXXXXX, _______,       _______,   XXXXXXX, _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* Adjust */
  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______ ,_______, _______,       _______,   XXXXXXX, _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}
