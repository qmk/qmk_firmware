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
		_PUSH,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define PUSH  MO(_PUSH)
#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

// Layer tap
#define PUSH_TB  LT(PUSH, KC_TAB)
#define LOWER_ENT  LT(_LOWER, KC_ENT)
#define RAISE_SPC  LT(_RAISE, KC_SPC)

// mod tap
#define LCTRL_Q  LCTL_T(KC_Q)
#define LSIFT_Z  LSFT_T(KC_Z)
#define RSIFT_SL  RSFT_T(KC_SLSH)
#define KC_X_AL  LALT_T(KC_X)
#define KC_C_GU  LGUI_T(KC_C)
#define KC_SSCT  LCTL_T(KC_SLSH)
#define KC_ENSF  LSFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung34(
    LCTRL_Q, KC_W,     KC_E,     KC_R,      KC_T,            KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   
    KC_A,    KC_S,     KC_D,     KC_F,      KC_G,            KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,
    LSIFT_Z, KC_X,     KC_C,     KC_V,      KC_B,            KC_N,     KC_M,     KC_COMM,  KC_DOT,   RSIFT_SL,
                       KC_LCTL,  PUSH_TB,   LOWER_ENT,       RAISE_SPC
  ),
  
  [_PUSH] = LAYOUT_reviung34(
    KC_TAB,   XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_BSPC,
    KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_QUOT,
    KC_LSFT,  KC_LGUI,  KC_LALT,  KC_CAPS,   XXXXXXX,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_ENT,
                        _______,  _______,   _______,            _______
  ),
  
  [_LOWER] = LAYOUT_reviung34(
    KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,
    KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,   KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_GRV, 
    KC_ESC,   KC_LGUI,  KC_LALT,  KC_CAPS,   KC_DQUO,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_PSCR,
                        _______,  _______,   _______,            _______
  ),
	
	[_RAISE] = LAYOUT_reviung34(
    KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  
    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_BSLS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5, 
    KC_ESC,   KC_RGUI,  KC_RALT,  KC_CAPS,   KC_QUOT,            KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
                        _______,  _______,   _______,            _______
  ),
  
  [_ADJUST] = LAYOUT_reviung34(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,               XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_F7,    KC_F7,    KC_F8,    KC_F9,    KC_F10,              XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                        _______,  _______,   _______,            _______
  ),
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}