/*
Copyright 2019 Sebastian Spindler <sebastian.spindler@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "keymap_extras/keymap_german.h"

//Layer renaming
#define _DL  0                     //default
#define _FUN 1                     //function layer
#define _LED 2                     //LED configurations

//Keymapping renaming
#define ______  KC_TRNS            //renaming KC_TRNS for readability in keymaps
#define RGB_MI  RGB_MODE_FORWARD   //increase RGB mode
#define RGB_MD  RGB_MODE_REVERSE   //decrease RGB mode
#define RGB_ST  RGB_M_P            //rgb static
#define MONKEY  LCTL(LALT(KC_DEL)) //ctrl+alt+del == monkey grip
#define SPECIAL LT(_FUN, DE_CIRC)  //

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DL] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,      KC_5,    KC_6,    KC_7,   KC_8,    KC_9, KC_0,   DE_SS,   DE_ACUT, ______, KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,      KC_T,    DE_Z,    KC_U,   KC_I,    KC_O, KC_P,   DE_UDIA, DE_PLUS,          ______,
      SPECIAL, KC_A,    KC_S,    KC_D,   KC_F,      KC_G,    KC_H,    KC_J,   KC_K,    KC_L, DE_ODIA,DE_ADIA, DE_HASH,          KC_ENT,
      KC_LSFT, DE_LABK, DE_Y,    KC_X,   KC_C,      KC_V,    KC_B,    KC_N,   KC_M, KC_COMM, KC_DOT, DE_MINS,          KC_RSFT, MONKEY,
      KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC                        , ______, KC_ALGR, TG(_LED),         KC_RCTL   ),

  [_FUN] = LAYOUT(
      ______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,  KC_F12, ______, KC_DEL,
      ______, KC_PGUP, KC_UP,   KC_PGDN,  ______,  ______, ______, ______, ______, ______, ______, ______,  ______,         ______,
      ______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_HOME, ______, ______, KC_END, ______, ______, ______, ______,  ______,         ______,
      ______, ______, ______,   ______,   ______,  ______, ______, ______, ______, ______, ______, ______,           KC_UP, ______,
      ______, ______, ______,                              ______                        , ______, KC_LEFT, KC_DOWN,        KC_RIGHT  ),

  [_LED] = LAYOUT(
      ______, ______,  ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,   ______, QK_BOOT,
      ______, RGB_TOG, RGB_MI,  RGB_MD,  RGB_ST,  ______,  ______,  ______, ______, ______, ______, ______, ______,           ______,
      ______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, ______,  ______,  ______, ______, ______, ______, ______, ______,           ______,
      ______, ______,  RGB_VAI, RGB_VAD, ______,  ______,  ______,  ______, ______, ______, ______, ______,           ______, ______,
      ______, ______,  ______,                             ______                         , ______, ______, TG(_LED),         ______    ),
};
