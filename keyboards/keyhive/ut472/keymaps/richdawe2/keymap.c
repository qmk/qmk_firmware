/* Copyright 2018 Carlos Filoteo
 * Copyright 2021-2023, 2025 Richard Dawe
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
grep -A11 '^LAYOUT(' keyboards/keyhive/ut472/keymaps/richdawe2/keymap.c > ut472-keymap-richdawe2.txt
enscript -v -r -f Courier9 --media=A4 ut472-keymap-richdawe2.txt -o ut472-keymap-richdawe2.ps
ps2pdf ut472-keymap-richdawe2.ps ut472-keymap-richdawe2.pdf
*/

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT2_ESC LT(2, KC_ESC)
#define LT3_TAB LT(3, KC_TAB)

#define MT_LASL LALT_T(KC_SLSH)

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
   * |Esc/L2|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '  |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Up  |Sh/En|
   * |-------------------------------------------------------------------------+
   * |Ctrl |Ctrl | Gui | Alt |Spc/L1| Space/L1  |Spc/L1|/ Alt| Left|Down |Right|
   * `-------------------------------------------------------------------------'
   */
  LT3_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LT2_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SC_SENT,
  KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, LT1_SPC,    LT1_SPC,       LT1_SPC, MT_LASL, KC_LEFT, KC_DOWN, KC_RGHT
),


LAYOUT(
  /* Layer 1: Numbers and symbol layer
   * ,-------------------------------------------------------------------------.
   * |  .  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |Bspace |
   * |-------------------------------------------------------------------------+
   * |  :   |  !  |  "  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  \   |
   * |-------------------------------------------------------------------------+
   * |       |  \  |  ~  |  `  |  |  |  -  |  !  |  =  |  [  |  ]  | PgUp|     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |     | Home| PgDn| End |
   * `-------------------------------------------------------------------------'
   */
  KC_DOT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_COLN, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_BSLS,
  _______, KC_BSLS, KC_TILD, KC_GRV,  KC_PIPE, KC_MINS, S(KC_1), KC_EQL,  KC_LBRC, KC_RBRC, KC_PGUP, _______,
  _______, _______, _______, _______, _______,     _______,      _______, _______, KC_HOME, KC_PGDN, KC_END
),


LAYOUT(
  /* Layer 2: F-keys and media
   * ,-------------------------------------------------------------------------.
   * | F12 | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |  F11  |
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |Left |Down | Up  |Right|     |      |
   * |-------------------------------------------------------------------------+
   * |       |     |     |     |     |     |     |     |     |Mute |VolUp|     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |     |MPrev|VolDn|MNext|
   * `-------------------------------------------------------------------------'
   */
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, _______,
  _______, _______, _______, _______, _______,     _______,      _______, _______, KC_MPLY, KC_VOLD, KC_MNXT
),


LAYOUT(
  /* Layer 3: Boot and RGB
   * ,-------------------------------------------------------------------------.
   * |     |     |     |     | RGB |RGBMO|BRT+ |HUE+ |SAT+ |     |PrtSc|Delete |
   * |-------------------------------------------------------------------------+
   * | Esc  |     |     |     |RGBI |RGBP |BRT- |HUE- |SAT- |     |     |      |
   * |-------------------------------------------------------------------------+
   * |       |    |     |     |     |     |     |     |     |     |      |     |
   * |-------------------------------------------------------------------------+
   * |Boot |RGBRS|     |Capsl|      |          |       |     |     |     |     |
   * `-------------------------------------------------------------------------'
   */
  XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, RGB_TOG,    RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, XXXXXXX, KC_PSCR, KC_DEL,
  KC_ESC,  XXXXXXX,      XXXXXXX, XXXXXXX, MACRO_RGBI, RGB_M_P, RGB_VAD, RGB_HUD, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  QK_BOOT, MACRO_RGBRST, XXXXXXX, KC_CAPS, XXXXXXX,     XXXXXXX,      XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
