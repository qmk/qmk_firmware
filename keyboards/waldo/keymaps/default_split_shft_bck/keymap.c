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

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum waldo_layers {
  _QWERTY,
  _FUNC
};

enum waldo_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------------.
 * | Esc  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  | Del |
 * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Backspace |
 * |------------------------------------------------------------------------------------------|
 * | Control |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter    |
 * |------------------------------------------------------------------------------------------|
 * |   L Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  R Shift  |  Fn |
 * |------------------------+-----------------------------------------------------------------|
 * |  Ctrl  |  GUI  |  Alt  |              Space                    |   GUI  |  Menu |  Ctrl  |
 * `------------------------------------------------------------------------------------------'
 */

[_QWERTY] = LAYOUT_60_ansi_split_bs_rshift( \
  KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL, \
  KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
  KC_LCTL, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT, \
  KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT,          MO(_FUNC), \
  KC_LCTL,        KC_LGUI,      KC_LALT,      KC_SPC,       XXXXXXX,         KC_RALT,          KC_RGUI, KC_RCTL \
),

/* Function
 * ,------------------------------------------------------------------------------------------.
 * |   ~  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |     |     |
 * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |      |     |  Up |     |     | Vol+|     |     | Prnt| PgUp|PgDwn|  Up |     |           |
 * |------------------------------------------------------------------------------------------|
 * |   Caps  | left| down|right|     | Vol-|     |     | Home| End | left|right|              |
 * |------------------------------------------------------------------------------------------|
 * |            |GBTOG|GBMOD|GBHUD|GBHUI|GBSAD|GBSAI|GBVAD|GBVAI|     | down|           |  Fn |
 * |------------------------+-----------------------------------------------------------------|
 * | Backlit|       |       |                                        |       |       |        |
 * `------------------------------------------------------------------------------------------'
 */

[_FUNC] = LAYOUT_60_ansi_split_bs_rshift( \
  KC_TILD, KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,    KC_F10,  KC_F11, KC_F12,  _______, _______, \
  _______, _______, KC_UP,   _______, _______, KC_VOLU, _______, _______, KC_PSCR, KC_PGUP,  KC_PGDN, KC_UP,  _______, _______, \
  KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_VOLD, _______, _______, KC_HOME, KC_END,   KC_LEFT, KC_RGHT,         _______, \
  _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD,  RGB_VAI, _______, KC_DOWN,        _______, KC_TRNS, \
  BACKLIT,        _______,      _______,      _______,       XXXXXXX,         _______,          _______, _______ \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      }
      return false;
      break;
  }
  return true;
}
