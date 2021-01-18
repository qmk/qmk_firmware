/* Copyright 2020 Draevin Luke <contact@drae.vin> @draevin
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
#include "draevin.h"

#define LAYOUT_65wm_wrapped(...) LAYOUT_65_with_macro(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CM] = LAYOUT_65wm_wrapped(
    HYPR_T(KC_MPLY), KC_ESC,  KC_GRV,      ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_DEL,
    KC_MPRV,         KC_MNXT, KC_TAB,      _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
    KC_F15,          KC_F16,  KC_BSPC,     _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_QUOT, KC_ENT,  KC_END,
    KC_F17,          KC_F18,  TD(TD_CAPS), _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, KC_RSFT, KC_UP,   MO(_FN),
    KC_F19,          KC_F20,  KC_LCTL,     KC_LGUI, KC_LALT, MO(_FN), KC_SPC,           XXXXXXX, KC_SPC,  KC_RCTL, KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_QW] = LAYOUT_65wm_wrapped(
    HYPR_T(KC_MPLY), KC_ESC,  KC_GRV,      ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_DEL,
    KC_MPRV,         KC_MNXT, KC_TAB,      _________________QWERTY_L1_________________, _________________QWERTY_L1_________________, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
    KC_F15,          KC_F16,  KC_BSPC,     _________________QWERTY_L2_________________, _________________QWERTY_L2_________________, KC_QUOT, KC_ENT,  KC_END,
    KC_F17,          KC_F18,  TD(TD_CAPS), _________________QWERTY_L3_________________, _________________QWERTY_L3_________________, KC_RSFT, KC_UP,   MO(_FN),
    KC_F19,          KC_F20,  KC_LCTL,     KC_LGUI, KC_LALT, MO(_FN), KC_SPC,           XXXXXXX, KC_SPC,  KC_RCTL, KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_FN] = LAYOUT_65wm_wrapped(
    _______,         _______, _______,     _________________FROW_LEFT_________________, _________________FROW_RIGHT________________, KC_F11,  KC_F12,  XXXXXXX, _______, _______,
    RGB_TOG,         RGB_MOD, _______,     ___________________FN_L1___________________, ___________________FN_R1___________________, _______, _______, KC_MAKE, KC_PGUP,
    _______,         _______, KC_DEL,      ___________________FN_L2___________________, ___________________FN_R2___________________, _______, _______, KC_PGDN,
    _______,         _______, _______,     ___________________BLANK___________________, ___________________FN_R3___________________, _______, _______, _______,
    _______,         CM_QW,   _______,     ___________________BLANK___________________, ___________________BLANK___________________, _______, _______//_______
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(_FN)) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
