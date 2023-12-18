/*
  Copyright (c) 2022 Adam Applegate

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

enum custom_layers {
  _QWERTY,
  _LOWER,
  _GAMING,
  _RISE,
}

/*****************
*** TAPDANCES ***
*****************/
enum custom_tapdances {
   TD_SHFT_CAPS = 0,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS), //shift if pressed 1x, caps lock if pressed 2x
};

/*****************
***  KEYMAPS  ***
*****************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   // layout for everyday use
  [_QWERTY] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
     TD(TD_SHFT_CAPS), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,              KC_ENT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                        KC_RALT, KC_LGUI, KC_BSPC,         KC_SPC, TT(_LOWER), _______
  ),

  [_LOWER] = LAYOUT(
     KC_GRAVE, KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PEQL,
     KC_F11,  KC_F12,  KC_UP,  _______, _______, KC_LPRN,                            KC_RPRN,  KC_7,    KC_8,    KC_9,   KC_PSLS, KC_PAST,
     KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LCBR,                           KC_RCBR,  KC_4,    KC_5,    KC_6,   KC_PMNS, KC_PPLS,
     KC_LCTL, _______, _______, _______, _______, KC_LBRC, KC_DEL,            KC_ENT, KC_RBRC,  KC_1,    KC_2,    KC_3,   KC_PDOT, _______,
                                       _______, TO(_QWERTY), KC_BSPC,         KC_SPC, TG(_GAMING), KC_0
  ),

  //makes gaming easier, adding a space for jumping closer to the movement keys
  [_GAMING] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,             KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                        KC_RALT, KC_SPC, KC_BSPC,           KC_SPC, TG(_RAISE), TO(_LOWER) 
  ),

  //used for editing rgb settings, sound, and misc commands
  [_RAISE] = LAYOUT(
     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            KC_MUTE, KC_VOLU, KC_MNXT, _______, KC_BRIU, KC_CALC,
    _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,                            KC_MSTP, KC_VOLD, KC_MPRV, _______, KC_BRID, KC_MYCM,
     DM_REC1, DM_REC2, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, KC_WSCH,
     DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______,         _______, _______, _______,  _______, _______, _______, _______,
                                       DM_RSTP, TO(_GAMING), _______,        _______, _______, _______
  )
};
