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
  _SYM,
  _NUM,
  _ADJUST,
  _NAVIGATION
};

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
};

#define SYM LT(MO(_SYM), KC_BSPC)
#define NUM LT(MO(_NUM), KC_ENT)
#define ADJU MO(_ADJUST)
#define NAV LT(MO(_NAVIGATION), KC_DEL)
#define LT_TAB LT(MO(_NAVIGATION), KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//qwerty ok
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BR_TILD,
    LT_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_C,    BR_ACUT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     NAV,         KC_SPC,       NUM,     SYM,     KC_RGUI, KC_RALT, RCTL_T(KC_ENT)
),

//workman ok
[_WORKMAN] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    BR_SCLN, BR_TILD,
    LT_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    BR_ACUT,
    KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  BR_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     NAV,         KC_SPC,       NUM,     SYM,     KC_RGUI, KC_RALT, RCTL_T(KC_ENT)
),

[_NAVIGATION] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
    _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_NO,   KC_NO,   KC_BSPC, KC_DEL,  _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      ADJU,    _______, KC_MPRV, KC_MPLY, KC_MNXT
),

[_SYM] = LAYOUT_planck_mit(
    BR_DQUO, BR_EXLM, BR_AT,   BR_HASH, BR_DLR,  BR_PERC, BR_DIAE, BR_AMPR, BR_ASTR, BR_LPRN, BR_RPRN, BR_UNDS,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   BR_MINS, BR_PLUS, BR_LBRC, BR_RBRC, BR_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, BR_LCBR, BR_RCBR, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),


[_NUM] = LAYOUT_planck_mit(
    BR_QUOT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   BR_MINS,
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, BR_PIPE,
    _______,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, ADJU, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_ADJUST] = LAYOUT_planck_mit(
    RESET,   _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
    KC_CAPS, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, WORKMAN,  QWERTY, _______,  _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  RGB_M_R, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
  }
  return true;
}

