/* Copyright 2021 James Sa
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
    _COLEMAKDHM,
    _EXTEND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAKDHM] LAYOUT(
          KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,   KC_QUOT, KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,
MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_R),MT(MOD_LSFT,KC_S),MT(MOD_LGUI,KC_T), KC_G,  KC_LBRC,  KC_RBRC, KC_M, MT(MOD_RGUI,KC_N),MT(MOD_RSFT,KC_E),MT(MOD_RALT,KC_I),MT(MOD_RCTL,KC_O),
      KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,  KC_MINS, KC_GRV, KC_EQL,  KC_K,   KC_H,   KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL,KC_LALT,KC_LGUI,LT(_EXTEND,KC_BSPC), KC_CAPS, KC_ENT,    KC_TAB,    KC_SPC, KC_DOWN,KC_UP,   KC_RGHT
    ),
    [_EXTEND] LAYOUT(
          KC_EXLM,  KC_AT, KC_HASH, KC_DLR,   KC_PERC,   KC_QUOT, KC_CIRC,   KC_AMPR,   KC_UP,   KC_ASTR,   KC_BSLS,
MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_R),MT(MOD_LSFT,KC_S),MT(MOD_LGUI,KC_T), KC_LPRN,  KC_LBRC,  KC_RBRC, KC_RPRN, MT(MOD_RGUI,KC_N),KC_LEFT,KC_DOWN,KC_RIGHT,
        KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,   KC_MINS,KC_GRV, KC_EQL, KC_K,   KC_H,   KC_COMM, KC_DOT,  KC_SLSH,
                KC_LCTL,KC_LALT,KC_LGUI,KC_BSPC,KC_TRNS,KC_TRNS,KC_TRNS,KC_SPC, KC_DOWN,KC_UP,  KC_RGHT
    )
};

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
}
