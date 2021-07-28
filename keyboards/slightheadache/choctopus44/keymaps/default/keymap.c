/* Copyright 2021 SlightHeadache
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC, \
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_ENT,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT), \
                        KC_LCTRL, KC_LALT,  LOWER,     KC_SPC,             KC_BSPC,  RAISE,    KC_RGUI,  KC_RALT \
  ),
  
  [_LOWER] = LAYOUT(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS, \
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,              KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12, \
    _______,  _______,  _______,  _______,  _______,   KC_CAPS,  KC_MPLY,  KC_NUBS,  KC_NUHS,  KC_EQUAL, KC_GRV,   _______,  _______, \
                        _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______ \
  ),
  
  [_RAISE] = LAYOUT(
    _______,  ALGR(KC_8),ALGR(KC_9),KC_UP,  S(KC_8),   S(KC_9),            S(KC_SLSH),KC_SLSH, _______,KC_RBRC,S(KC_RBRC),ALGR(KC_RBRC), \
    KC_GRV,   S(KC_EQL),KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_EQL,             ALGR(KC_MINS),S(KC_MINS),_______,_______,_______, _______, \
    _______,KC_NUBS,S(KC_NUBS),ALGR(KC_NUBS),ALGR(KC_7),ALGR(KC_0),KC_MUTE,S(KC_NUHS),KC_NUHS, _______,  _______,  _______,  _______, \
                        _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______ \
  ),
  
  [_ADJUST] = LAYOUT(
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  KC_PSCR,  KC_SLCK,  KC_PAUSE, XXXXXXX, \
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  KC_INS,   KC_HOME,  KC_PGUP,  XXXXXXX, \
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  RESET,    XXXXXXX,  KC_DEL,   KC_END,   KC_PGDN,  XXXXXXX, \
                        _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______ \
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)) {
      case _RAISE:
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
        break;
      case _LOWER:
        clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
        break;
      default:
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
        break;
    }
    return true;
}
