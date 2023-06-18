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

void keyboard_post_init_user(void) {
  // Customise these values if you need to debug the matrix
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

enum my_keycodes {
  KC_NORMAL_HOLD = SAFE_RANGE,
  KC_FUNC_HOLD
};

enum layer {
    NORMAL,
    NORMAL_HOLD,
    FUNC,
    FUNC_HOLD,
    NAS,
    NUM_LAYERS
};

/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
 [NORMAL] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_J,            KC_U,           KC_QUOTE,       KC_M,           KC_H,
        /*R2*/ KC_K,            KC_I,           KC_COLON,       KC_COMMA,       KC_Y,
        /*R3*/ KC_L,            KC_O,           KC_LGUI,        KC_DOT,         KC_N,
        /*R4*/ KC_SEMICOLON,    KC_P,           KC_BSLS,        KC_SLASH,       KC_RBRC,

        /*L1*/ KC_F,            KC_R,           KC_G,           KC_V,           KC_DOUBLE_QUOTE,
        /*L2*/ KC_D,            KC_E,           KC_T,           KC_C,           KC_GRAVE,
        /*L3*/ KC_S,            KC_W,           KC_B,           KC_X,           KC_ESC,
        /*L4*/ KC_A,            KC_Q,           KC_LBRC,        KC_Z,           KC_DEL,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/  
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPC,        KC_LALT,     TG(NAS),
        /*LT*/ KC_LSFT,         KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL,     KC_CAPS
    ),

    [NORMAL_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_LEFT,         KC_WH_L,        XXXXXXX,        KC_MS_L,        LCTL(KC_LEFT),
        /*R2*/ KC_UP,           KC_WH_U,        XXXXXXX,        KC_MS_U,        LCTL(KC_UP),
        /*R3*/ KC_DOWN,         KC_WH_D,        XXXXXXX,        KC_MS_D,        LCTL(KC_DOWN),
        /*R4*/ KC_RIGHT,        KC_WH_R,        XXXXXXX,        KC_MS_R,        LCTL(KC_RIGHT),
//mirror right alphas while holding Normal key for easy access while mousing (e.g. CAD)
        /*L1*/ KC_J,            KC_U,           KC_QUOTE,       KC_M,           KC_H,
        /*L2*/ KC_K,            KC_I,           KC_COLON,       KC_COMMA,       KC_Y,
        /*L3*/ KC_L,            KC_O,           KC_LGUI,        KC_DOT,         KC_N,
        /*L4*/ KC_SEMICOLON,    KC_P,           KC_BSLS,        KC_SLASH,       KC_RBRC,

        /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/
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

        /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/  
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPC,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL, _______
    ),

    [FUNC] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*R2*/ XXXXXXX,         KC_F8,          XXXXXXX,        KC_F7,          KC_END,
        /*R3*/ KC_PSCR,         KC_F10,         KC_LGUI,        KC_F9,          KC_INS,
        /*R4*/ KC_PAUSE,        KC_PGUP,        KC_F12,         KC_PGDN,        KC_F11,

        /*L1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT,
        /*L2*/ XXXXXXX,         KC_F6,          XXXXXXX,        KC_F5,          XXXXXXX,
        /*L3*/ XXXXXXX,         KC_F4,          XXXXXXX,        KC_F3,          KC_ESC,
        /*L4*/ XXXXXXX,         KC_F2,          XXXXXXX,        KC_F1,          KC_DEL,

             /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/  
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPC,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,       KC_NORMAL_HOLD, KC_TAB,         KC_LCTL,_______
    ),

    [FUNC_HOLD] = LAYOUT(
             /*Center           North           East            South           West*/
        /*R1*/ KC_LEFT,         LCTL(KC_UP),   LCTL(KC_RIGHT), LCTL(KC_DOWN), LCTL(KC_LEFT),
        /*R2*/ KC_UP,           KC_MS_U,        KC_MS_R,        KC_MS_D,        KC_MS_L,
        /*R3*/ KC_DOWN,         KC_WH_U,        KC_WH_R,        KC_WH_D,        KC_WH_L,
        /*R4*/ KC_RIGHT,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,

        /*L1*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,     XXXXXXX,
        /*L2*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,     XXXXXXX,
        /*L3*/ XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,     XXXXXXX,
        /*L4*/ _______,      _______,        _______,        _______,       _______,

             /*Down                  Inner           Upper           Outer Upper     Outer Lower  Pushthrough*/  
        /*RT*/ _______,         _______,        _______,        _______,        _______,_______,
        /*LT*/ _______,         _______,        _______,        _______,        _______, _______
    ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  switch (keycode) {

     case KC_NORMAL_HOLD:
      if (record->event.pressed) {
          layer_clear();
          layer_on(NORMAL_HOLD);
      } else {
          layer_off(NORMAL_HOLD);
      }
      return false;
     case KC_FUNC_HOLD:
      if (record->event.pressed) {
          layer_clear();
          layer_on(FUNC_HOLD);
      } else {
          layer_off(FUNC_HOLD);
      }
      return false;
    default:
      return true;
  }
};

