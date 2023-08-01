/* Copyright 2020 OJtheTiny
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

enum layers{
  _QW,
  _DV,
  _CM,
  _L1,
  _L2,
  _L3
};
enum custom_keycodes {
    DVORAK = SAFE_RANGE,
    QWERTY,
    COLEMAK
};


const uint16_t PROGMEM keymaps [][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT( /* Qwerty */
      KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_ENT,
      KC_LSFT,   KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,    KC_DOT,
      KC_TAB,  KC_LGUI,                  KC_SPC,              MO(_L1), MO(_L2)
    ),
    [_DV] = LAYOUT( /* Dvorak */
      KC_ESC, KC_SLSH, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_QUOT,
      KC_LCTL, KC_A,    KC_O,    KC_E,   KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S,
      KC_LSFT,   KC_Q,    KC_J,   KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z,
      KC_TAB,  KC_LGUI,                         KC_SPC,                       MO(_L1), MO(_L2)
    ),
    [_CM] = LAYOUT( /* Colemak */
      KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_QUOT,
      KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O,
      KC_LSFT,   KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM,    KC_DOT,
      KC_TAB, KC_LGUI,                  KC_SPC,              MO(_L1), MO(_L2)
    ),
    [_L1] = LAYOUT( /* NUM */
      KC_GRV, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_MINUS,
      _______, _______, _______, _______, _______, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_SCLN,      KC_BSLS,
      _______,   _______, _______, KC_PSCR, _______, _______, KC_LBRC, KC_RBRC, KC_MINUS,      KC_EQL,
      _______, _______,                             _______,                        _______, _______
    ),
    [_L2] = LAYOUT( /* F Keys */
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,     KC_F11,
      _______,  KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,  _______, _______, UC(0xc3b6), UC(0xc3a4),    KC_ENT,
      _______,    QWERTY,  DVORAK,  COLEMAK, TG(_L3), _______, _______, _______, _______,            _______,
      _______, _______,                              _______,                           _______, _______
    ),
    [_L3] = LAYOUT( /*Gaming */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,    _______, KC_F1, KC_F2, KC_F3, KC_F4, _______,
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, _______,  KC_F5, KC_F6, KC_F7, KC_F8,    _______,
    KC_LCTL,   KC_A, KC_S, KC_D, KC_F, KC_G, _______, _______, _______,       _______,
    KC_LSFT, KC_B,                    KC_SPC,                      MO(_L2), _______
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      switch(keycode) {
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DV);
          }
          return false;
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QW);
          }
          return false;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_CM);
          }
          return false;
        default:
          return true;
      }
    return true;
};
