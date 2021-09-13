/* Copyright 2021 lmlmask
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
#include "keymap_br_abnt2.h"

enum layers {
  _WORKMAN,
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _SYM,
  _FUNCTION,
  _NAV,
  _NUM,
  _ADJUST
};

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
  DVORAK,
  COLEMAK,
};

#define SYM MO(_SYM)
#define FUN LT(_FUNCTION, KC_ENT)
#define MYTAB LT(_NAV, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//qwerty base layer ok
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BR_TILD,
    MYTAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_C,    BR_ACUT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     LT(_NAV, KC_DEL),         KC_SPC,   LT(_NUM, KC_BSPC),     FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//workman base layer ok
[_WORKMAN] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    BR_SCLN, BR_TILD,
    MYTAB,   KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    BR_ACUT,
    KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  BR_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     LT(_NAV, KC_DEL),         KC_SPC,   LT(_NUM, KC_BSPC),     FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//dvorak base layer ok
[_DVORAK] = LAYOUT_planck_mit(
    KC_ESC,  BR_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_C,    KC_R,    KC_L,    BR_SLSH, BR_TILD,
    MYTAB,   KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    BR_ACUT,
    KC_LSFT, BR_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     LT(_NAV, KC_DEL),         KC_SPC,   LT(_NUM, KC_BSPC),     FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//colemak base layer ok
[_COLEMAK] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    BR_SCLN, BR_TILD,
    MYTAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    BR_ACUT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     LT(_NAV, KC_DEL),         KC_SPC,   LT(_NUM, KC_BSPC),     FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//navigation and utility layer ok
[_NAV] = LAYOUT_planck_mit(
    KC_TRNS, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_VOLU,
    _______, _______, _______, _______, BR_QUOT, _______, KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_VOLD,
    KC_TRNS, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, _______, _______, KC_BSPC, KC_DEL,  _______, _______, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, _______,     _______,      LT(_NUM, KC_BSPC), _______, KC_MPRV, KC_MPLY, KC_MNXT
),

//symbols layer ok
[_SYM] = LAYOUT_planck_mit(
    BR_DQUO, BR_EXLM, BR_AT,   BR_HASH, BR_DLR,  BR_PERC, BR_DIAE, BR_AMPR, BR_ASTR, BR_LPRN, BR_RPRN, BR_COLN,
    BR_QUOT, BR_PIPE, _______, _______, _______, _______, _______, BR_PLUS, BR_UNDS, BR_LBRC, BR_RBRC, BR_SCLN,
    KC_TRNS, BR_BSLS, _______, _______, _______, _______, _______, BR_EQL,  BR_MINS, BR_LCBR, BR_RCBR, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, _______,     _______,      _______, _______, KC_TRNS, KC_TRNS, KC_TRNS
),

//numbers layer ok
[_NUM] = LAYOUT_planck_mit(
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    BR_MINS, _______,
    _______, BR_ASTR, BR_SLSH, BR_MINS, BR_PLUS, _______, _______, KC_4,    KC_5,    KC_6,    BR_PLUS, _______,
    KC_TRNS, BR_PERC, BR_EQL,  BR_DOT,  BR_COMM,  _______, _______, KC_1,    KC_2,    KC_3,    BR_DOT,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, LT(_NAV, KC_DEL),     _______,      _______, KC_0,    KC_0,    KC_COMM, KC_ENT
),

//FN layer ok
[_FUNCTION] = LAYOUT_planck_mit(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, KC_PAUS, _______,
    KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, KC_INS,  _______,
    KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, KC_PSCR, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, _______,     _______,      _______, _______, KC_TRNS, KC_TRNS, KC_TRNS
),

// adjust layer ok
[_ADJUST] = LAYOUT_planck_mit(
    RESET,   _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    KC_CAPS, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  DVORAK,  COLEMAK, WORKMAN, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  RGB_M_R, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
   }
   return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _NUM, _ADJUST);
}
