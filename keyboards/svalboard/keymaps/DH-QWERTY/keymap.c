/*
Copyright 2023 Morgan Venable @_claussen

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

#include <stdbool.h>
#include <stdint.h>

enum my_keycodes {
 KC_NORMAL_HOLD = SAFE_RANGE,
  KC_FUNC_HOLD
  //
  //KC_GAME_HOLD,
  //KC_GAZE,
};

enum layer {
  NORMAL,
    COLEMAK_ASRT,
    NORMAL_HOLD,
    FUNC,
    FUNC_HOLD,
    NAS,
    //COLEMAK,

//    COLEMAK_HOLD,
    // GAME,
    // GAME_HOLD,
    // GAME_MOD_1,
    // GAME_MOD_2,
    NUM_LAYERS
};

#define KC_RIGHT_CURLY KC_RIGHT_CURLY_BRACE
#define KC_LEFT_CURLY KC_LEFT_CURLY_BRACE


/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
 [NORMAL] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_J,            KC_U,           KC_QUOTE,       KC_M,           KC_H,
        /*R2*/ KC_K,            KC_I,           KC_COLON,       KC_COMMA,       KC_Y,
        /*R3*/ KC_L,            KC_O,           KC_LGUI,         KC_DOT,      KC_N,
        /*R4*/ KC_SEMICOLON,    KC_P,           KC_BSLS,      KC_SLASH,       KC_RBRC,

        /*L1*/ KC_F,            KC_R,           KC_G,           KC_V,           KC_DOUBLE_QUOTE,
        /*L2*/ KC_D,            KC_E,           KC_T,           KC_C,           KC_GRAVE,
        /*L3*/ KC_S,            KC_W,           KC_B,           KC_X,           KC_ESC,
        /*L4*/ KC_A,            KC_Q,           KC_LBRC,        KC_Z,           KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT,  TG(NAS),
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, KC_CAPS
    ),

    [COLEMAK_ASRT] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_N,            KC_L,           KC_QUOTE,       KC_M,           KC_H,
        /*R2*/ KC_E,            KC_U,           KC_COLON,       KC_COMMA,       KC_K,
        /*R3*/ KC_I,            KC_Y,           KC_LGUI,         KC_DOT,        KC_J,
        /*R4*/ KC_O,            KC_SEMICOLON,        KC_BSLS,      KC_SLASH,       KC_RBRC,

        /*L1*/ KC_T,            KC_P,           KC_G,           KC_V,           KC_DOUBLE_QUOTE,
        /*L2*/ KC_R,            KC_F,           KC_D,           KC_C,           KC_GRAVE,
        /*L3*/ KC_S,            KC_W,           KC_B,           KC_X,           KC_ESC,
        /*L4*/ KC_A,            KC_Q,           KC_LBRC,        KC_Z,           KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, _______
    ),

    [NORMAL_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_LEFT,         LCTL(KC_UP),   LCTL(KC_RIGHT), LCTL(KC_DOWN), LCTL(KC_LEFT),
        /*R2*/ KC_UP,           KC_MS_U,        KC_MS_R,        KC_MS_D,        KC_MS_L,
        /*R3*/ KC_DOWN,         KC_WH_U,        KC_WH_R,        KC_WH_D,        KC_WH_L,
        /*R4*/ KC_RIGHT,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,

        /*L1*/ RGUI(KC_H),         XXXXXXX,        XXXXXXX,        LCTL(KC_V),     XXXXXXX,
        /*L2*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        LCTL(KC_C),     XXXXXXX,
        /*L3*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        LCTL(KC_X),     XXXXXXX,
        /*L4*/ DF(NORMAL),      _______,        _______,        XXXXXXX/*DF(COLEMAK_ASRT)*/,       _______,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ _______,         _______,        _______,        _______,        _______, _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______, _______
    ),

    [NAS] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_7,            KC_AMPR,        KC_UNDS,        KC_KP_PLUS,     KC_6,
        /*R2*/ KC_8,            KC_KP_ASTERISK, KC_COLON,       KC_COMMA,       KC_CIRCUMFLEX,
        /*R3*/ KC_9,            KC_LPRN,        KC_LGUI,        KC_DOT,         KC_SEMICOLON,
        /*R4*/ KC_0,            KC_RPRN,        XXXXXXX,        KC_QUES,        KC_RBRC,

        /*L1*/ KC_4,            KC_DOLLAR,      KC_5,           KC_MINUS,       KC_SLASH,
        /*L2*/ KC_3,            KC_HASH,        KC_GT,          KC_PERCENT,     KC_LT,
        /*L3*/ KC_2,            KC_AT,          XXXXXXX,        KC_X,           KC_ESC,
        /*L4*/ KC_1,            KC_EXCLAIM,     KC_TILDE,       KC_EQUAL,       KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, TG(NAS),
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, _______
    ),

    [FUNC] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*R2*/ XXXXXXX,         KC_F8,          XXXXXXX,        KC_F7,          KC_END,
        /*R3*/ KC_PSCR,      KC_F10,         KC_LGUI,        KC_F9,          KC_INS,
        /*R4*/ KC_PAUSE,        KC_PGUP,        KC_F12,         KC_PGDN,        KC_F11,

        /*L1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*L2*/ XXXXXXX,         KC_F6,          XXXXXXX,        KC_F5,          XXXXXXX,
        /*L3*/ XXXXXXX,         KC_F4,          XXXXXXX,        KC_F3,          KC_ESC,
        /*L4*/ XXXXXXX,         KC_F2,          XXXXXXX,        KC_F1,          KC_DEL,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL,_______
    ),

    [FUNC_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_LEFT,         LCTL(KC_UP),   LCTL(KC_RIGHT), LCTL(KC_DOWN), LCTL(KC_LEFT),
        /*R2*/ KC_UP,           KC_MS_U,        KC_MS_R,        KC_MS_D,        KC_MS_L,
        /*R3*/ KC_DOWN,         KC_WH_U,        KC_WH_R,        KC_WH_D,        KC_WH_L,
        /*R4*/ KC_RIGHT,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,

        /*L1*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        LCTL(KC_V),     XXXXXXX,
        /*L2*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        LCTL(KC_C),     XXXXXXX,
        /*L3*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        LCTL(KC_X),     XXXXXXX,
        /*L4*/ _______,      _______,        _______,        _______,       _______,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ _______,         _______,        _______,        _______,        _______,_______,
        /*LT*/ _______,         _______,        _______,        _______,        _______, _______
    ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

     case KC_NORMAL_HOLD:
      if (record->event.pressed) {
          layer_clear();
          layer_on(NORMAL_HOLD);
          //SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F19)))));
      } else {
          layer_off(NORMAL_HOLD);
      }
      return false;
     case KC_FUNC_HOLD:
      if (record->event.pressed) {
          layer_clear();
          layer_on(FUNC_HOLD);
          //SEND_STRING(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_F19)))));
      } else {
          layer_off(FUNC_HOLD);
      }
      return false;
    default:
      return true;
  }
};

