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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERT__Y = 0,
  _NP = 1, // Number Pad
  _FN = 2, // Function Key
  _PLOVER = 3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERT__Y] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,           KC_T,   CTL_T(KC_ESC),   CTL_T(KC_GRV),   KC_Y,          KC_U,    KC_I,    KC_O,     KC_P},
  {KC_A,    KC_S,    KC_D,    LT(_NP,KC_F),   KC_G,   ALT_T(KC_TAB),  ALT_T(KC_QUOT),   KC_H,  LT(_FN,KC_J),    KC_K,    KC_L,  KC_SCLN},
  {KC_Z,    KC_X,    KC_C,    KC_V,           KC_B,   KC_LBRC,               KC_RBRC,   KC_N,          KC_M, KC_COMM,  KC_DOT,  KC_SLSH},
  {KC_LEFT, KC_DOWN, KC_MINS, SFT_T(KC_BSPC), KC_ENT, MEH_T(KC_UNDS), GUI_T(KC_BSLS), KC_SPC, SFT_T(KC_DEL),  KC_EQL,   KC_UP,  KC_RGHT}
},

[_NP] = {
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8, KC_9,   KC_PPLS, XXXXXXX, KC_N},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5, KC_6,   KC_PMNS, XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2, KC_3,   KC_PAST, XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_0, KC_0, KC_DOT, KC_PSLS, XXXXXXX, XXXXXXX}
},

[_FN] = {
  {KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F},
  {KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {TO(_QWERT__Y), XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif
