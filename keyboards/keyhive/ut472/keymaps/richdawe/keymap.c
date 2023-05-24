/* Copyright 2018 Carlos Filoteo
 * Copyright 2021-2023 Richard Dawe
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

// Convert this into a printable keymap on Linux using:
/*
grep -A11 '^LAYOUT(' keyboards/keyhive/ut472/keymaps/richdawe/keymap.c > ut472-keymap-richdawe.txt
enscript -v -r -f Courier9 --media=A4 ut472-keymap-richdawe.txt -o ut472-keymap-richdawe.ps
ps2pdf ut472-keymap-richdawe.ps ut472-keymap-richdawe.pdf
*/

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT3_TAB LT(3, KC_TAB)

enum custom_keycodes {
  MACRO_RGBI   = SAFE_RANGE,     /* Output current RGB info */
  MACRO_RGBRST = SAFE_RANGE + 1, /* Reset RGB underglow colour to default */
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

LAYOUT(
  /* Base Layer
   * ,-------------------------------------------------------------------------.
   * |Tb/L3|  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * | Esc  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '  |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Up  |Sh/En|
   * |-------------------------------------------------------------------------+
   * |  \  |Ctrl | Gui | Alt |  L2  |  Space/L1 |  L2  |  /  | Left|Down |Right|
   * `-------------------------------------------------------------------------'
   */
  LT3_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SFTENT,
  KC_BSLS, KC_LCTL, KC_LGUI, KC_LALT, MO(2),     LT1_SPC,        MO(2),   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),


LAYOUT( /* Right */
  /* FN Layer 1
   * ,-------------------------------------------------------------------------.
   * |  `  |  1  |  2  |  3  |  :  |     |     |     |  :  |  0  |  .  |       |
   * |-------------------------------------------------------------------------+
   * |      |  4  |  5  |  6  |  .  |     |     |  -  |  =  |  [  |  ]  |  \   |
   * |-------------------------------------------------------------------------+
   * |       |  7  |  8  |  9  |  0  |     |     |     |  [  |  ]  | PgUp|     |
   * |-------------------------------------------------------------------------+
   * |  ~  |     |     |     |      |          |       |  `  | Home| PgDn| End |
   * `-------------------------------------------------------------------------'
   */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_COLON, _______, _______, _______, KC_COLON, KC_0,    KC_DOT,  _______,
  _______, KC_4,    KC_5,    KC_6,    KC_DOT,   _______, _______, KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_7,    KC_8,    KC_9,    KC_0,     _______, _______, _______, KC_LBRC,  KC_RBRC, KC_PGUP, _______,
  KC_TILDE,_______, _______, _______, _______,     _______,       _______, KC_GRV,   KC_HOME, KC_PGDN, KC_END
),


LAYOUT( /* Left */
  /* FN Layer 2
   * ,-------------------------------------------------------------------------.
   * |  `   |  !  |  @  |  #  |     |     |     |     |     |  0  |     |      |
   * |-------------------------------------------------------------------------+
   * |      |  $  |  %  |  ^  |     |     |     |  _  |  +  |  { |  }  |   |   |
   * |-------------------------------------------------------------------------+
   * |       |  &  |  *  |  (  |  )  |     |     |     |  {  |  }  | PgUp|     |
   * |-------------------------------------------------------------------------+
   * |  ~  |     |     |     |      |    -     |       |  `  | Home| PgDn| End |
   * `-------------------------------------------------------------------------'
   */
  KC_GRV,   KC_EXCLAIM,  KC_AT,  KC_HASH,  _______, _______, _______, _______, _______, KC_0, _______, _______,
  _______,  KC_DOLLAR,  KC_PERCENT, KC_CIRCUMFLEX,  _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
  _______,  KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, _______, _______, _______, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PGUP, _______,
  KC_TILDE,_______, _______, _______, _______,     KC_MINS,      _______, KC_GRV,   KC_HOME, KC_PGDN, KC_END
),


LAYOUT( /* Tab */
  /* FN Layer 3
   * ,-------------------------------------------------------------------------.
   * |     | F1  | F2  | F3  | RGB |RGBMO|BRT+ |HUE+ |SAT+ |     |PrtSc|Delete |
   * |-------------------------------------------------------------------------+
   * | Esc  | F4  | F5  | F6  |RGBI |RGBP |BRT- |HUE- |SAT- |     |     |      |
   * |-------------------------------------------------------------------------+
   * |       | F7 | F8  | F9  | F10 | F11 | F12 |     |     |MUTE |VOLUP |     |
   * |-------------------------------------------------------------------------+
   * |RESET|RGBRS|     |Capsl|      |          |       |MPLAY|MPREV|VOLDN|MNEXT|
   * `-------------------------------------------------------------------------'
   */
  _______, KC_F1,   KC_F2,   KC_F3,   RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, _______, KC_PSCR, KC_DELETE,
  KC_ESC,  KC_F4,   KC_F5,   KC_F6, MACRO_RGBI,RGB_M_P, RGB_VAD, RGB_HUD, RGB_SAD, _______, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_MUTE, KC_VOLU, _______,
  RESET,   MACRO_RGBRST, _______, KC_CAPS, _______,     _______,      _______, KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT
),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case MACRO_RGBI: /* Output current RGB info */
    if (record->event.pressed) {
      char buf[32];
      const uint8_t hue = rgblight_get_hue();
      const uint8_t sat = rgblight_get_sat();
      const uint8_t val = rgblight_get_val();

      snprintf(buf, sizeof(buf), "H: %u S: %u V: %u", hue, sat, val);
      send_string(buf);
    } else {
      // when keycode QMKBEST is released
    }
    break;

  case MACRO_RGBRST: /* Reset RGB underglow colour to default */
    if (record->event.pressed) {
      rgblight_sethsv(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
    } else {
      // when keycode QMKBEST is released
    }
    break;
  }
  return true;
}
