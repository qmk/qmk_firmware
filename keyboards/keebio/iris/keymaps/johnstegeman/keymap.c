/*
Copyright 2023 John Stegeman

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

#include "print.h"
#include "light_layers.h"

enum layers {
_COLEMAK,
_NAVNUM,
_CONTROL,
};

// Enter when tapped, shift when held
#define SHEN MT(MOD_LSFT, KC_ENT) 

// Enter when tapped, alt when held
#define ALEN MT(MOD_LALT, KC_ENT) 

#define CTX LT(0,KC_X)
#define CPC LT(0,KC_C)
#define PSV LT(0,KC_V)

// Space when tapped, shift when held 
#define SHSP MT(MOD_RSFT, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, KC_SCLN,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,     CTX,     CPC,    KC_D,     PSV,    KC_HOME,          KC_RALT,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     MO(1),    ALEN,  KC_LGUI,                  KC_BSPC,   SHSP,  LT(2,KC_ENT)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAVNUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     QK_BOOT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                            KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,    _______, _______, KC_DOWN, KC_LCBR, KC_END,           KC_RALT, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_DEL,                    KC_DEL,  _______, KC_P0
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_CONTROL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_MOD, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                            KC_EQL,  KC_HOME, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_END,  RGB_HUD, RGB_SAD, RGB_VAD, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};     

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
   case LT(0,KC_X):
      if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_X)); // Intercept hold function to send GUI-X
            return false;
      }
      return true;
      break;
   case LT(0,KC_C):
      if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_C)); // Intercept hold function to send GUI-C
            return false;
      }
      return true;
      break;
   case LT(0,KC_V):
      if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_V)); // Intercept hold function to send GUI-V
            return false;
      }
      return true;
      break;
   }
  return true;
}

// Key overrides

// GUI + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, S(KC_GRV));

// Shift + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, KC_GRV);

// Shift + bkspc = delete word
const key_override_t shift_bkspc_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, A(KC_BSPC));

const key_override_t **key_overrides = (const key_override_t *[]){
    &tilde_esc_override,
    &grave_esc_override,
//    &shift_bkspc_override,
    NULL
};


void keyboard_post_init_user(void) {
    rgblight_layers = MY_LIGHT_LAYERS;
}

layer_state_t layer_state_set_user(layer_state_t state) {
 
    rgblight_set_layer_state(_COLEMAK, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(_NAVNUM, layer_state_cmp(state, _NAVNUM));

    return state;
}
