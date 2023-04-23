/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo.h"
#include "keymap_japanese.h"

enum custom_keycodes {
    JIS2US = SAFE_RANGE,  /* JIS2US keycode                       */
    QWERTY,               /* Layer  keycode                       */
    PSEU_US,              /* Layer  keycode                       */
    LOWER,                /* Layer  keycode                       */
    RAISE,                /* Layer  keycode                       */
    P_LOWER,              /* Layer  keycode                       */
    P_RAISE               /* Layer  keycode                       */
};

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _PSEUDO_US,
    _PSEUDO_US_LOWER,
    _PSEUDO_US_RAISE,
    _ADJUST,
};

// Layer related keycodes
#define ADJUST  MO(_ADJUST)

// Special keycodes
#define SPC_CTL CTL_T(KC_SPC)
#define ENT_SFT SFT_T(KC_ENT)
#define TB_CTSF C_S_T(KC_TAB)
#define IMON_AL ALT_T(KC_F13)
#define IMOF_AL ALT_T(KC_F14)
#define CTALDEL LCA(KC_DEL)
#define ESC_ADJ LT(_ADJUST, KC_ESC)
#define GUI_E LGUI(KC_E)
#define GUI_R LGUI(KC_R)
#define CTLGRV LCTL(KC_GRV)

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
        GUI_E,   ESC_ADJ, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL, KC_DEL,
        GUI_R,   TB_CTSF, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,     KC_BSPC,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CTLGRV,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
                 KC_LGUI,          IMOF_AL,     LOWER,        SPC_CTL,     RAISE,        ENT_SFT, IMON_AL,                   KC_RCTL
    ),

	[_LOWER] = LAYOUT(
        _______, _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
        _______, _______, _______, KC_F2,   KC_F5,   KC_F10,  KC_GRV,  KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,     _______,
                 _______, _______, _______, _______, _______, KC_TILD, _______, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
                 _______,          _______,     _______,      _______,     _______,      _______, _______,                   _______
    ),

	[_RAISE] = LAYOUT(
        _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,      _______,
                 _______, _______, _______, _______, _______, _______, KC_HOME, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, _______, _______,
                 _______,          _______,     _______,      _______,     _______,      _______, _______,                   _______
    ),

	[_PSEUDO_US] = LAYOUT(
        _______, _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______, _______,
        _______, _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JIS2US,      _______,
                 _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    JP_ZKHK, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JIS2US,
                 _______,          _______,     P_LOWER,      _______,     P_RAISE,      _______, _______,                   _______
    ),

	[_PSEUDO_US_LOWER] = LAYOUT(
        _______, _______, JP_EXLM, JP_AT,   JP_HASH, JP_DLR,  JP_PERC, JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, _______, _______,
        _______, _______, _______, KC_F2,   KC_F5,   KC_F10,  JP_GRV,  JP_BSLS, JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC,     _______,
                 _______, _______, _______, _______, _______, JP_TILD, _______, JP_PIPE, JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, _______,
                 _______,          _______,     _______,      _______,     _______,      _______, _______,                   _______
    ),

	[_PSEUDO_US_RAISE] = LAYOUT(
        _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,      _______,
                 _______, _______, _______, _______, _______, _______, KC_HOME, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, _______, _______,
                 _______,          _______,     _______,      _______,     _______,      _______, _______,                   _______
    ),

	[_ADJUST] = LAYOUT(
        QK_BOOT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, QWERTY,  PSEU_US, CTALDEL, _______, _______, _______, _______, _______,     _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______,          _______,     _______,      _______,     _______,      _______, _______,                   _______
    )
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
    case P_LOWER:
      if (record->event.pressed) {
        layer_on(_PSEUDO_US_LOWER);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      } else {
        layer_off(_PSEUDO_US_LOWER);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      }
      return false;
      break;
    case P_RAISE:
      if (record->event.pressed) {
        layer_on(_PSEUDO_US_RAISE);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      } else {
        layer_off(_PSEUDO_US_RAISE);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      break;
    case PSEU_US:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PSEUDO_US);
      }
      break;
    case JIS2US:
      action_pseudo_process(record, _QWERTY, keymap_jis2us);
      return false;
      break;
  }
  return true;
}
