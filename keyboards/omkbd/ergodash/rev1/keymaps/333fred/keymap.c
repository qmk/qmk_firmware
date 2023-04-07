/*
  Copyright (c) 2020 Fred Silberberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include QMK_KEYBOARD_H
#include "333fred.h"

extern keymap_config_t keymap_config;

// Use an expanded macro with VA_ARGS to ensure that the common
// rows get expanded out before getting passed to the LAYOUT
// macro.

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_wrapper(
    ROW5_LEFT_BASE,          KC_F5,                                     KC_F6,            ROW5_RGHT_BASE,
    ROW4_LEFT_BASE,          TG(GAME),                                  TG(GAME_ARROW),   ROW4_RGHT_BASE,
    ROW3_LEFT_BASE,          KC_LGUI,                                   KC_BSPC,          ROW3_RGHT_BASE,
    ROW2_LEFT_BASE,          TD(TD_COPY_PASTE),                         KC_UP ,           ROW2_RGHT_BASE,
    ROW1_LEFT_BASE, KC_BSPC, TD(TD_SYM_VIM),    KC_DEL,         KC_ENT, KC_SPC , KC_DOWN, ROW1_RGHT_BASE
  ),

  [SYMB] = LAYOUT_wrapper(
    ROW5_LEFT_SYMB,          _______,                           _______,          ROW5_RGHT_SYMB,
    ROW4_LEFT_SYMB,          PSCREEN_APP,                       _______,          ROW4_RGHT_SYMB,
    ROW3_LEFT_SYMB,          KC_PSCR,                           KC_VOLU,          ROW3_RGHT_SYMB,
    ROW2_LEFT_SYMB,          _______,                           KC_VOLD,          ROW2_RGHT_SYMB,
    ROW1_LEFT_SYMB, _______, _______, _______,         KC_MPRV, KC_MPLY, KC_MNXT, ROW1_RGHT_SYMB
  ),

  [VIM] = LAYOUT_wrapper(
    ROW5_LEFT_VIM,          _______,                           _______,          ROW5_RGHT_VIM,
    ROW4_LEFT_VIM,          _______,                           _______,          ROW4_RGHT_VIM,
    ROW3_LEFT_VIM,          _______,                           _______,          ROW3_RGHT_VIM,
    ROW2_LEFT_VIM,          _______,                           _______,          ROW2_RGHT_VIM,
    ROW1_LEFT_VIM, _______, _______, _______,         _______, _______, _______, ROW1_RGHT_VIM
  ),

  [GAME] = LAYOUT_wrapper(
      KC_ESC,   SIX_TRNS,                                                   _______, SIX_TRNS,
      SIX_TRNS,                                              _______,     _______, SIX_TRNS,
      KC_LCTL,  FOUR_TRNS,                          _______, KC_F6,         _______, SIX_TRNS,
      KC_LSFT,  KC_Z,    FOUR_TRNS,                          KC_F5,         _______, SIX_TRNS,
      KC_ENT,   _______, QK_LOCK, KC_BSPC, KC_LALT, KC_SPC,  OSM(SYMB),     _______, SIX_TRNS
  ),

  [GAME_ARROW] = LAYOUT_wrapper(
      KC_ESC,   SIX_TRNS,                                                  _______, SIX_TRNS,
      _______,  _______, KC_UP,   _______,  _______, _______, _______,     _______, SIX_TRNS,
      KC_LCTL,  KC_LEFT, KC_DOWN, KC_RGHT,  _______, _______, KC_F6,       _______, SIX_TRNS,
      KC_LSFT,  KC_Z,    FOUR_TRNS,                           KC_F5,       _______, SIX_TRNS,
      KC_ENT,   _______, QK_LOCK, KC_BSPC, KC_LALT, KC_SPC,  OSM(SYMB),    _______, SIX_TRNS
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_process_keycode(keycode);
  return !try_handle_macro(keycode, record);
}
