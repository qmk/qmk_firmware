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
#include "keymap_brazilian_abnt2.h"

enum layers {
  _WORKMAN,
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _SYM,
  _FUNCTION,
  _MIDI,
  _NAV,
  _NUM,
  _ADJUST
  
};

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
  DVORAK,
  COLEMAK,
  MIDI
};

#define SYM MO(_SYM)
#define FUN LT(_FUNCTION, KC_ENT)
#define MYTAB LT(_NAV, KC_TAB)
#define MYNAV LT(_NAV, KC_DEL)
#define MYNUM LT(_NUM, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//qwerty base layer ok
[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BR_TILD,
    MYTAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    BR_CCED, BR_ACUT,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     MYNAV,       KC_SPC,       MYNUM,   FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//workman base layer ok
[_WORKMAN] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    BR_CCED, BR_TILD,
    MYTAB,   KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    BR_ACUT,
    SC_LSPO, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     MYNAV,       KC_SPC,       MYNUM,   FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//dvorak base layer ok
[_DVORAK] = LAYOUT_planck_mit(
    KC_ESC,  KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    BR_SLSH, BR_TILD,
    MYTAB,   KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    BR_ACUT,
    SC_LSPO, BR_CCED, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    SC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     MYNAV,       KC_SPC,       MYNUM,   FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//colemak base layer ok
[_COLEMAK] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    BR_CCED, BR_TILD,
    MYTAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    BR_ACUT,
    SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  BR_SLSH, SC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, SYM,     MYNAV,       KC_SPC,       MYNUM,   FUN,     KC_RGUI, KC_LALT, RCTL_T(KC_ENT)
),

//navigation and utility layer ok
[_NAV] = LAYOUT_planck_mit(
    KC_TRNS, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_VOLU,
    _______, _______, _______, _______, BR_QUOT, _______, KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_VOLD,
    KC_TRNS, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, _______, _______, KC_BSPC, KC_DEL,  _______, _______, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, _______,     _______,      MYNUM, _______, KC_MPRV, KC_MPLY, KC_MNXT
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
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    BR_MINS,
    _______, BR_ASTR, BR_SLSH, BR_MINS, BR_PLUS, _______, _______, KC_4,    KC_5,    KC_6,    BR_COMM, BR_PLUS,
    KC_TRNS, BR_PERC, BR_EQL,  BR_DOT,  BR_COMM, _______, _______, KC_1,    KC_2,    KC_3,    BR_DOT,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, MYNAV,       _______,      _______, KC_0,    KC_0,    KC_COMM, KC_ENT
),

//FN layer 
[_FUNCTION] = LAYOUT_planck_mit(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_INS,
    KC_PSCR, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PAUS,
    KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, _______, _______,     _______,      _______, _______, KC_TRNS, KC_TRNS, KC_TRNS
),

// adjust layer ok
[_ADJUST] = LAYOUT_planck_mit(
    QK_BOOT, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______,
    KC_CAPS, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, QWERTY,  DVORAK,  COLEMAK, WORKMAN, MIDI,
    _______, MI_ON,   MI_OFF,  MI_TOGG, MU_ON,   MU_OFF,  MU_TOGG, MU_NEXT, AU_ON,   AU_OFF,  _______, _______,
    RGB_TOG, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

// midi layer
[_MIDI] = LAYOUT_planck_mit(
    MI_Cs,   MI_Ds,   _______, MI_Fs,   MI_Gs,   MI_As,   _______, MI_Cs,   MI_Ds,   _______, MI_Fs,   MI_Gs,
    MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B,    MI_C,    MI_D,    MI_E,    MI_F,    MI_G,
    MI_BNDU, MI_OCTU, MI_TRSU, MI_VELU, _______, _______, _______, _______, _______, MI_ON,   MI_CHNU, MI_TOGG,
    MI_BNDD, MI_OCTD, MI_TRSD, MI_VELD, MYNAV,       MI_SUST,      MYNUM, _______,   MI_OFF,  MI_CHND, MI_AOFF
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
    case MIDI:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MIDI);
      }
      return false;
   }
   return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _NUM, _ADJUST);
}
