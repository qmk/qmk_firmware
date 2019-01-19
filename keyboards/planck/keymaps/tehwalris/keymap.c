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

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  DVORAK,
  OVL_L, // Left overlay
  OVL_R, // Right overlay
  OVL_C, // Corner overlay
  OVL_N, // Number overlay
  OVL_F, // F-key overlay
};

enum planck_keycodes {
  UMLT_A = SAFE_RANGE,
  UMLT_O,
  UMLT_U,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[DVORAK] = {
  {KC_TAB,  KC_QUOT,   KC_COMM, KC_DOT,  KC_P,    KC_Y,      KC_F,      KC_G,    KC_C,    KC_R,      KC_L,    OSL(OVL_C)},
  {KC_ESC,  KC_A,      KC_O,    KC_E,    KC_U,    KC_I,      KC_D,      KC_H,    KC_T,    KC_N,      KC_S,    KC_ENT    },
  {KC_LSFT, KC_SCLN,   KC_Q,    KC_J,    KC_K,    KC_X,      KC_B,      KC_M,    KC_W,    KC_V,      KC_Z,    KC_RSFT   },
  {KC_LGUI, MO(OVL_N), KC_LCTL, KC_RCTL, KC_BSPC, MO(OVL_L), MO(OVL_R), KC_SPC,  KC_LALT, MO(OVL_F), KC_RALT, KC_RGUI   }
},

[OVL_L] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RGHT, _______},
  {_______, KC_UNDS, KC_MINS, KC_BSLS, KC_SLSH, KC_PLUS, KC_DLR,  KC_LEFT, KC_EQL,  KC_LCBR, KC_RCBR, _______},
  {_______, KC_SCLN, _______, _______, _______, _______, _______, _______, KC_GRV,  KC_HASH, KC_PIPE, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[OVL_R] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EXLM, KC_CIRC, KC_QUES, KC_PERC, KC_AMPR, KC_ASTR, _______},
  {_______, KC_TILD, KC_AT,   KC_DOWN, KC_UP,   _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[OVL_C] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,  _______},
  {_______, UMLT_A,  UMLT_O,  _______, UMLT_U,  _______, _______, KC_HOME, _______, _______, _______, _______},
  {_______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_DEL,  _______, _______, KC_INS,  _______, _______, _______, _______}
},

[OVL_N] = {
  {_______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______},
  {_______, KC_PLUS, KC_UNDS, KC_LPRN, KC_RPRN, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______},
  {_______, KC_ASTR, KC_SLSH, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_EQL,  _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_0,    _______, _______, _______, _______}
},

[OVL_F] = {
  {_______, _______, _______, _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_F4,   KC_F5,   KC_F6,   _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_F10,  KC_F11,  KC_F12,  _______, _______}
}

};

static bool is_left_shift_pressed = false;
static bool is_right_shift_pressed = false;

// This will only work on linux with xkbmap option "compose:prsc"
void press_umlaut_of(uint16_t keycode) {
  bool is_shift_pressed = (is_left_shift_pressed || is_right_shift_pressed);
  register_code(KC_PSCREEN);
  unregister_code(KC_PSCREEN);
  if (!is_shift_pressed) {
    register_code(KC_LSFT);
  }
  register_code(KC_QUOT);
  unregister_code(KC_QUOT);
  if (!is_shift_pressed) {
    unregister_code(KC_LSFT);
  }
  register_code(keycode);
  unregister_code(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSFT:
      is_left_shift_pressed = record->event.pressed;
      break;
    case KC_RSFT:
      is_right_shift_pressed = record->event.pressed;
      break;
    case UMLT_A:
      if (record->event.pressed) {
        press_umlaut_of(KC_A);
      }
      break;
    case UMLT_O:
      if (record->event.pressed) {
        press_umlaut_of(KC_O);
      }
      break;
    case UMLT_U:
      if (record->event.pressed) {
        press_umlaut_of(KC_U);
      }
      break;
  }
  return true;
}
