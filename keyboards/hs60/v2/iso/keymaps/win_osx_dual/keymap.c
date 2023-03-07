/* Copyright 2018 Yiancar
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


#define _QWERTY 0
#define _OSX 1
#define _RAISE 2
#define _SHIFTER 3
#define _ADJUST 16


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  OSX,
  RAISE,
  SHIFTER,
};

#define RAISE  MO(_RAISE)

#define OSX_SHIFT LM(_SHIFTER, MOD_LSFT)
#define OSX_ALT   LM(_SHIFTER, MOD_LALT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_60_iso( /* Windows ISO layout */
    QK_GESC,    KC_1,       KC_2,      KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,        KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,
    KC_CAPS,    KC_Q,       KC_W,      KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,        KC_P,       KC_LBRC,    KC_RBRC,
    KC_TAB,     KC_A,       KC_S,      KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,        KC_SCLN,    KC_QUOT,    KC_NUHS,    KC_ENT,
    KC_LSFT,    KC_NUBS,    KC_Z,      KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,     KC_DOT,     KC_SLSH,                KC_RSFT,
    KC_LCTL,    KC_LGUI,    KC_LALT,                                KC_SPC,                                                 KC_RALT,    KC_RGUI,    RAISE ,     KC_RCTL),

[_OSX] = LAYOUT_60_iso( /* OSX ISO layout */
    KC_ESC,     KC_1,       KC_2,      KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,        KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,
    KC_CAPS,    KC_Q,       KC_W,      KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,        KC_P,       KC_LBRC,    KC_RBRC,
    KC_TAB,     KC_A,       KC_S,      KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,        KC_SCLN,    KC_QUOT,    A(KC_3),    KC_ENT,
    OSX_SHIFT,  KC_NUHS,    KC_Z,      KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,     KC_DOT,     KC_SLSH,                KC_RSFT,
    KC_LCTL,    OSX_ALT,    KC_LGUI,                                KC_SPC,                                                 KC_RGUI,    KC_RALT,    RAISE ,     KC_RCTL),

[_RAISE] = LAYOUT_60_iso( /* Configuration */
    QK_BOOT,     KC_F1,     KC_F2,     KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,       KC_F10,     KC_F11,     KC_F12,     KC_DEL ,
    KC_TRNS,     QWERTY,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    OSX,         KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,     EF_INC,    H1_INC,    S1_INC,     H2_INC,     S2_INC,     BR_INC,     ES_INC,     KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,     KC_UP,     EF_DEC,    H1_DEC,     S2_DEC,     H2_DEC,     S2_DEC,     BR_DEC,     ES_DEC,     KC_TRNS,     KC_TRNS,    KC_TRNS,                KC_TRNS,
    KC_LEFT,     KC_DOWN,   KC_RGHT,                               KC_TRNS,                                                 KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS),

[_SHIFTER] = LAYOUT_60_iso( /* Shift Mods makes a keyboard with windows key layout work on OSX*/
    KC_TRNS,    S(KC_1),    S(KC_QUOT),S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9),     S(KC_0),    S(KC_MINS), S(KC_EQL),   KC_DEL,
    KC_TRNS,    S(KC_Q),    S(KC_W),   S(KC_E),    S(KC_R),    S(KC_T),    S(KC_Y),    S(KC_U),    S(KC_I),    S(KC_O),     S(KC_P),    S(KC_LBRC), S(KC_RBRC),
    KC_TRNS,    S(KC_A),    S(KC_S),   S(KC_D),    S(KC_F),    S(KC_G),    S(KC_H),    S(KC_J),    S(KC_K),    S(KC_L),     S(KC_SCLN), S(KC_2),    S(KC_NUBS),  KC_TRNS,
    KC_TRNS,    S(KC_NUHS), S(KC_Z),   S(KC_X),    S(KC_C),    S(KC_V),    S(KC_B),    S(KC_N),    S(KC_M),    S(KC_COMM),  S(KC_DOT),  S(KC_SLSH),              KC_TRNS,
    KC_TRNS,    KC_TRNS,   KC_TRNS,                                KC_TRNS,                                                 KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS)


};

void matrix_init_user(void) {
  //user initialization
}


void matrix_scan_user(void) {
  //user matrix
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case OSX:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_OSX);
      }
      return false;

  }
  return true;
}
