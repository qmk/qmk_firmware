/* Copyright 2019 gtips
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
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)

#define CT_TB LCTL_T(KC_TAB)
#define CT_Q  LCTL_T(KC_Q)
#define SF_Z  LSFT_T(KC_Z)
#define SF_SS RSFT_T(KC_SLSH)
#define AL_X  LALT_T(KC_X)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung34(
    CT_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,
    SF_Z,     AL_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   SF_SS,
                        CT_TB,    LOWER,    RAISE,              KC_SPC
  ),
  
  [_LOWER] = LAYOUT_reviung34(
    KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,
    KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_QUOT,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_CAPS,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_DEL,
                        _______,  _______,  _______,            KC_BSPC
  ),
	
	[_RAISE] = LAYOUT_reviung34(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,            XXXXXXX,  XXXXXXX,  KC_GRV,   KC_TILD,  KC_DQUO,
    KC_LSFT,  KC_ESC,   KC_RGUI,  KC_LALT,  KC_CAPS,            KC_TAB,   KC_RALT,  KC_RCTL,  KC_RSFT,  KC_BSPC,
                        _______,  _______,  _______,            KC_ENT
  ),
  
  [_ADJUST] = LAYOUT_reviung34(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_F7,    KC_F7,    KC_F8,    KC_F9,    KC_F10,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  KC_PSCR,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                        _______,  _______,  _______,            XXXXXXX
  ),
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

