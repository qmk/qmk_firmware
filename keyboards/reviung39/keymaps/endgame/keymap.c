/* Copyright 2019 gtips
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
  [_BASE] = LAYOUT_reviung39(
    KC_GESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LSPO,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_RSPC,
    CTL_T(KC_TAB),  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  ALT_T(KC_F6),
                                                       LT(_RAISE, KC_ENT),    RCMD_T(KC_F3),   LT(_LOWER, KC_SPC)
  ),
  
  [_LOWER] = LAYOUT_reviung39(
    _______,  _______,  KC_UP,    _______,  _______,    _______,            _______,  _______,  KC__MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,   _______,            _______,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,  _______,   _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,  _______,   _______,  _______,  _______,  KC_CAPSLOCK,
                                                       _______,  _______,   _______
  ),
  
  [_RAISE] = LAYOUT_reviung39(
    KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  _______,  _______,   KC_QUOT,  KC_LBRC,   KC_RBRC,            KC_BSLS,    KC_MINS,    KC_EQL,    KC_SLSH,    _______,    _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,    _______,    _______,    _______,   _______,   ALT_T(KC_F5),
                                                       _______,  _______,  _______
  ),
  
  [_ADJUST] = LAYOUT_reviung39(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                       _______,  XXXXXXX,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
