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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT(
  //┌──────────────┬────────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬──────────────┐
     KC_GRV,        KC_1,        KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
     KC_TAB,        KC_Q,        KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────────────┤
     CTL_T(KC_ESC), KC_A,        KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├──────────────┼────────────┼────────┼────────┼────────┼────────┼───────────────┐ ┌────────┼────────┼────────┼────────┼────────┼────────┼──────────────┤
     OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,           KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT),
  //└──────────────┴────────────┴────────┴────────┼────────┼────────┼───────────────┤ ├────────┼────────┼────────┼────────┴────────┴────────┴──────────────┘
                                                   KC_LALT, KC_BSPC, TD(TD_SYM_VIM),   KC_ENT,  KC_SPC,  KC_RGUI
                                               // └────────┴────────┴───────────────┘ └────────┴────────┴────────┘
  ),


  [SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PLUS,                            _______, KC_7,    KC_8,    KC_9,    _______, KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_EQL,                             _______, KC_4,    KC_5,    KC_6,    _______, KC_VOLU,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_UP,            KC_UP,   KC_0,    KC_1,    KC_2,    KC_3,    _______, KC_VOLD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───────┴─────┬───┴────┐   └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, TD(TD_COPY_PASTE), _______,         KC_MPRV, KC_MPLY, KC_MNXT
                                // └────────┴──────────────────┴────────┘       └────────┴────────┴────────┘
  ),


  [VIM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, KC_LSFT, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, DLEFT,   DRIGHT,  KC_LCTL, KC_LGUI, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_process_keycode(keycode);
    return !try_handle_macro(keycode, record);
}
