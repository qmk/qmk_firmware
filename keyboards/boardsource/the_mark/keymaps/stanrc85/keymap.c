/* Copyright 2020 Stanrc85
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
#include "stanrc85.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base */
[_QWERTY] = LAYOUT_all(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_MPLY, 
  KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, CA_SCLN, 
  KC_CTLE,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  CA_QUOT, 
  KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   
  KC_LCTL, KC_LGUI, KC_LALT,          LT_SPCF,           LT_SPCF,         LT_SPCF,        TD_TWIN, MO(_FN2_60), KC_GRV,  KC_LEFT, KC_DOWN, KC_RGHT
),
[_DEFAULT] = LAYOUT_all(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_MPLY, 
  KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, CA_SCLN, 
  KC_CTLE,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  CA_QUOT, 
  KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   
  KC_LCTL, KC_LGUI, KC_LALT,          LT_SPCF,           LT_SPCF,         LT_SPCF,        TD_TWIN, MO(_FN2_60), KC_GRV,  KC_LEFT, KC_DOWN, KC_RGHT
),
[_FN1_60] = LAYOUT_all(
  KC_TILD,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_DEL,     KC_DEL,    _______,
  _______,                _______,    CA_QUOT,    KC_VOLU,    CA_SCLN,    _______,    _______,    KC_HOME,    KC_UP,      KC_END,     KC_PSCR,    _______,    _______,    KC_INS,    _______,
  KC_CAPS,                _______,    KC_MUTE,    KC_VOLD,    KC_MPLY,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,    _______,                _______,   _______,
  _______,    _______,    KC_RDP,     _______,    _______,    _______,    _______,    _______,    KC_WBAK,    KC_WFWD,    _______,    _______,    _______,                _______,
  _______,    _______,    _______,                _______,                _______,                _______,                _______,    _______,    _______,    _______,    _______,    _______
),
[_FN2_60] = LAYOUT_all(
  RGB_TOG,   RGB_MOD,     RGB_VAD,    RGB_VAI,    RGB_SAI,    RGB_HUD,    RGB_HUI,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RESET,      _______,
  _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                KC_MAKE,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    
  _______,    _______,    _______,                _______,                _______,                _______,                _______,    _______,    _______,    _______,    _______,    TG(_DEFAULT)
)

};


void rgb_matrix_indicators_user(void) {
  uint8_t layer = get_highest_layer(layer_state);
  switch (layer) {
    case _FN1_60:
      rgb_matrix_set_color(10, 0, 0, 255); 
      break;
    case _FN2_60:
      rgb_matrix_set_color(10, 255, 255, 255); 
      break;
    case _DEFAULT:
      rgb_matrix_set_color(10, 0, 255, 0); 
      break;
    default:
      break;
  }
  if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(10, 255, 0, 0);
  }
}

void matrix_init_kb(void){

#ifdef RGB_MATRIX_ENABLE

  g_led_config = (led_config_t){ {
    // Key Matrix to LED Index
    { 10    , 10    , 9     , 9     , 8     , 7     , 7     , 6     , 5     , 5     , 4     , 3     , 3     , 2     , 1     , 1      },
    { 11    , 11    , 9     , 9     , 8     , 7     , 7     , 6     , 5     , 5     , 4     , 3     , 3     , 2     , 0     , 1      },
    { 12    , 12    , 9     , 9     , 8     , 7     , 7     , 6     , 5     , 5     , 4     , 3     , 3     , 2     , 23    , 1      },
    { 13    , 13    , 14    , 14    , 15    , 16    , 16    , 17    , 18    , 18    , 19    , 20    , 20    , 21    , 22    , 22     },
    { 13    , 13    , 14    , 14    , 15    , 16    , 16    , 17    , 18    , 18    , 19    , 20    , 20    , 21    , 22    , 22     },
  }, {
    // LED Index to Physical Position
    {224, 42}, {224, 21}, {209, 21}, {179, 21}, {164, 21}, {134, 21}, {119, 21}, {89, 21}, {74, 21}, {45, 21}, {30, 21}, {30, 42},
    {30, 64}, {30, 85}, {45, 85}, {74, 85}, {89, 85}, {119, 85}, {134, 85}, {164, 85}, {179, 85}, {209, 85}, {224, 85}, {224, 64}
  }, {
    // LED Index to Flag
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
  } };

#endif
  matrix_init_user();
}
