/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC
};

enum {
  TD_ESC_TAB = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Esc, twice for tab
  [TD_ESC_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_TAB)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
*  ,-----------------------------------------------------------------------------------.
*  |  `   |   q  |   w  |   e  |   r  |   t  |   y  |   u  |   i  |   o  |   p  | Bksp |
*  |------+------+------+------+------+-------------+------+------+------+------+------|
*  | Esc  |   a  |   s  |   d  |   f  |   g  |   h  |   j  |   k  |   l  |   ;  |  '   |
*  |------+------+------+------+------+------|------+------+------+------+------+------|
*  | Shift|   z  |   x  |   c  |   v  |   b  |   n  |   m  |   ,  |   .  |   /  |Enter |
*  |------+------+------+------+------+------+------+------+------+------+------+------|
*  | Ctrl |  Alt | GUI  | GUI  |Lower |      |      |Raise |   [  |   ]  |   \  |  FN  |
*  `-----------------------------------------------------------------------------------'
*/
[_QWERTY] = {
  {KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT)},
  {KC_LCTL, KC_LALT, KC_LGUI, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LBRC, KC_RBRC, KC_BSLS, FUNC}
},


/* Lower
*  ,-----------------------------------------------------------------------------------.
*  |      |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |      |
*  |------+------+------+------+------+-------------+------+------+------+------+------|
*  | Tab  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |      |
*  |------+------+------+------+------+------|------+------+------+------+------+------|
*  |      |      |      |      |      |      |  -   |  =   |      |      |      |      |
*  |------+------+------+------+------+------+------+------+------+------+------+------|
*  |      |      |      |      |Lower |      |      |Raise |      |      |      |      |
*  `-----------------------------------------------------------------------------------'
*/
[_LOWER] = {
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______},
  {KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
*  ,-----------------------------------------------------------------------------------.
*  |      |      |      |      |      |      |      |      |      |      |      | Home |
*  |------+------+------+------+------+-------------+------+------+------+------+------|
*  |      |      |      |      |      |      | Left | Down |  Up  | Right|      | PgUp |
*  |------+------+------+------+------+------|------+------+------+------+------+------|
*  |      |      |      |      |      |      |      |      |      |      |      | PgDn |
*  |------+------+------+------+------+------+------+------+------+------+------+------|
*  |      |      |      |      |      |      |      |      |      |      |      | End  |
*  `-----------------------------------------------------------------------------------'
*/
[_RAISE] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME},
  {_______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, KC_PGUP},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END }
},

/* Function
*  ,-----------------------------------------------------------------------------------.
*  | RESET|      |      |      |      |      |      |      |      |      |      |      |
*  |------+------+------+------+------+-------------+------+------+------+------+------|
*  |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Home |
*  |------+------+------+------+------+------|------+------+------+------+------+------|
*  |      |      |      |      |      |      |      | Vol- | Vol+ | Prev | Next | Play |
*  |------+------+------+------+------+------+------+------+------+------+------+------|
*  |      |      |      |      |      |      |      |      |      |      |      |      |
*  `-----------------------------------------------------------------------------------'
*/
[_FUNC] = {
  {RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, KC_MPLY},
  {QWERTY,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _FUNC);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _FUNC);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _FUNC);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _FUNC);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
  }

  return true;
}
