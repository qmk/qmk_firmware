/* Copyright 2021 Ben Gruver <jesusfreke@jesusfreke.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include QMK_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

enum my_keycodes {
  KC_NORMAL_HOLD = SAFE_RANGE,
  KC_GAME_HOLD,
};

enum layer {
    NORMAL,
    NORMAL_HOLD,
    FUNC,
    NAS,
    GAME,
    GAME_HOLD,
    GAME_MOD_1,
    GAME_MOD_2,
    NUM_LAYERS
};

#define KC_RIGHT_CURLY KC_RIGHT_CURLY_BRACE
#define KC_LEFT_CURLY KC_LEFT_CURLY_BRACE


/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_H,            KC_G,           KC_QUOTE,       KC_M,           KC_D,
        /*R2*/ KC_T,            KC_W,           KC_GRAVE,       KC_C,           KC_F,
        /*R3*/ KC_N,            KC_V,           XXXXXXX,        KC_R,           KC_B,
        /*R4*/ KC_S,            KC_Z,           KC_BSLS,      KC_L,           KC_RIGHT_PAREN,

        /*L1*/ KC_U,            KC_Q,           KC_I,           KC_P,           KC_DOUBLE_QUOTE,
        /*L2*/ KC_E,            KC_DOT,         KC_Y,           KC_J,           XXXXXXX,
        /*L3*/ KC_O,            KC_COMMA,       KC_X,           KC_K,           KC_ESC,
        /*L4*/ KC_A,            KC_SLASH,       KC_LEFT_PAREN,  KC_SEMICOLON,      KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, /*NAS layerlock-macro instead?*/_______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, KC_CAPS
    ),

    [NORMAL_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ _______,         _______,        _______,        _______,        _______,
        /*R2*/ _______,         _______,        _______,        _______,        _______,
        /*R3*/ _______,         _______,        _______,        _______,        _______,
        /*R4*/ _______,         _______,        _______,        _______,        _______,

        /*L1*/ _______,         _______,        _______,        LCTL(KC_V),     _______,
        /*L2*/ _______,         _______,        _______,        LCTL(KC_C),     _______,
        /*L3*/ _______,         _______,        _______,        LCTL(KC_X),     _______,
        /*L4*/ TO(NORMAL),      _______,        _______,        TO(GAME),       _______,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ _______,         _______,        _______,        _______,        _______, _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______, _______
    ),

    [NAS] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_7,            KC_AMPR,        XXXXXXX,        KC_KP_PLUS,     KC_6,
        /*R2*/ KC_8,            KC_KP_ASTERISK, XXXXXXX,        KC_HASH,        KC_CIRCUMFLEX,
        /*R3*/ KC_9,            KC_LBRACKET,    KC_APP,         XXXXXXX,        XXXXXXX,
        /*R4*/ KC_0,            KC_RBRACKET,    XXXXXXX,        XXXXXXX,        KC_RIGHT_CURLY,

        /*L1*/ KC_4,            KC_DOLLAR,      KC_5,           KC_MINUS,    XXXXXXX,
        /*L2*/ KC_3,            KC_DOT,         XXXXXXX,        KC_PERCENT,     XXXXXXX,
        /*L3*/ KC_2,            KC_AT,          XXXXXXX,        XXXXXXX,        KC_ESC,
        /*L4*/ KC_1,            KC_EXCLAIM,     KC_LEFT_CURLY,  KC_EQUAL,       KC_DEL,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
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
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, _______
    ),

    [GAME] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_H,            KC_G,           KC_QUOTE,       KC_M,           KC_D,
        /*R2*/ KC_T,            KC_W,           KC_GRAVE,       KC_C,           KC_F,
        /*R3*/ KC_N,            KC_V,           XXXXXXX,        KC_R,           KC_B,
        /*R4*/ KC_S,            KC_Z,           KC_BSLS,      KC_L,           KC_RIGHT_PAREN,

        /*L1*/ KC_U,            KC_Q,           KC_I,           KC_P,           KC_R,
        /*L2*/ KC_E,            KC_DOT,         KC_Y,           KC_J,           KC_GRAVE,
        /*L3*/ KC_O,            KC_COMMA,       KC_X,           KC_K,           KC_ESC,
        /*L4*/ KC_A,            KC_SLASH,       KC_V,           KC_SEMICOLON,      KC_DEL,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_SPACE,       KC_GAME_HOLD,   MO(GAME_MOD_1), KC_LCTL, _______
    ),

    [GAME_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ _______,         _______,        _______,        _______,        _______,
        /*R2*/ _______,         _______,        _______,        _______,        _______,
        /*R3*/ _______,         _______,        _______,        _______,        _______,
        /*R4*/ _______,         _______,        _______,        _______,        _______,

        /*L1*/ _______,         _______,        _______,        LCTL(KC_V),     _______,
        /*L2*/ _______,         _______,        _______,        LCTL(KC_C),     _______,
        /*L3*/ _______,         _______,        _______,        LCTL(KC_X),     _______,
        /*L4*/ TO(NORMAL),      _______,        _______,        TO(GAME),       _______,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ _______,         _______,        _______,        _______,        _______, _______,
        /*LT*/ _______,         _______,        _______,        _______,        _______, _______
    ),

    [GAME_MOD_1] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_H,            KC_G,           KC_QUOTE,       KC_M,           KC_D,
        /*R2*/ KC_T,            KC_W,           KC_GRAVE,       KC_C,           KC_F,
        /*R3*/ KC_N,            KC_V,           XXXXXXX,        KC_R,           KC_B,
        /*R4*/ KC_S,            KC_Z,           KC_BSLS,      KC_L,           KC_RIGHT_PAREN,

        /*L1*/ KC_4,            KC_F4,          KC_5,           KC_9,           KC_0,
        /*L2*/ KC_3,            KC_F3,          KC_F11,         KC_8,           KC_F7,
        /*L3*/ KC_2,            KC_F2,          KC_F10,         KC_7,           KC_F6,
        /*L4*/ KC_1,            KC_F1,          KC_F9,          KC_6,           KC_F5,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_GAME_HOLD,   MO(GAME_MOD_1), KC_LCTL, _______
    ),

    [GAME_MOD_2] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_H,            KC_G,           KC_QUOTE,       KC_M,           KC_D,
        /*R2*/ KC_T,            KC_W,           KC_GRAVE,       KC_C,           KC_F,
        /*R3*/ KC_N,            KC_V,           XXXXXXX,        KC_R,           KC_B,
        /*R4*/ KC_S,            KC_Z,           KC_BSLS,      KC_L,           KC_RIGHT_PAREN,

        /*L1*/ KC_F8,            KC_F4,          KC_5,           KC_9,           KC_F8,
        /*L2*/ KC_F7,            KC_F3,          KC_F11,         KC_8,           KC_F7,
        /*L3*/ KC_F6,            KC_F2,          KC_F10,         KC_7,           KC_F6,
        /*L4*/ KC_F5,            KC_F1,          KC_F9,          KC_6,           KC_F5,

             /*Down             Inner           Upper           Outer Upper     Outer Lower*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPACE,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_GAME_HOLD,   MO(GAME_MOD_1), KC_LCTL, _______
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_NORMAL_HOLD:
      if (record->event.pressed) {
          layer_clear();
          default_layer_set(1 >> NORMAL);
          layer_on(NORMAL_HOLD);
      } else {
          layer_off(NORMAL_HOLD);
      }
      return false;
    case KC_GAME_HOLD:
      if (record->event.pressed) {
          layer_clear();
          default_layer_set(1 >> GAME);
          layer_on(GAME_HOLD);
      } else {
          layer_off(GAME_HOLD);
      }
      return false;
    default:
      return true;
  }
}
