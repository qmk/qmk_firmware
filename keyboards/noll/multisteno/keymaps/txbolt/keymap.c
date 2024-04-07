/* Copyright 2022 Nathan Olivares
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

enum layers{
  STENO,
  NKRO,
  QWERTY,
  QWERTY_CAPS,
  SYMBOL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [STENO] = LAYOUT_3x6_3(
    STN_RES1,   STN_N1, STN_N2, STN_N3, STN_N4,  STN_N5,   STN_N6,  STN_N7, STN_N8, STN_N9, STN_NA, STN_FN,      
    TO(NKRO),   STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,   STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    MO(SYMBOL), STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,   STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                 STN_A,  STN_O,  STN_NB,   STN_NC,   STN_E,  STN_U 
  ),

  [NKRO] = LAYOUT_3x6_3(
    KC_GRAVE,   KC_1, KC_2, KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8, KC_9, KC_0,    KC_MINS,
    TO(QWERTY), KC_Q, KC_W, KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I, KC_O, KC_P,    KC_LBRC,
    MO(SYMBOL), KC_A, KC_S, KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                            KC_C, KC_V, KC_Z,   KC_X, KC_N, KC_M 
  ),

  [QWERTY] = LAYOUT_3x6_3(
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,       KC_Y, KC_U, KC_I,    KC_O,      KC_P,     KC_BSPC,
    TO(STENO),  KC_A,   KC_S,   KC_D,   KC_F,    KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,     KC_QUOT,
    MO(SYMBOL), KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, MO(QWERTY_CAPS),
                            KC_LCTL, KC_SPACE, KC_ESC,       KC_ENTER, KC_SPACE, KC_RALT
  ),

  [QWERTY_CAPS] = LAYOUT_3x6_3(
    S(KC_TAB),  S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),   S(KC_Y), S(KC_U),  S(KC_I),    S(KC_O),      S(KC_P), S(KC_BSPC),
    TO(STENO),  S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),   S(KC_H), S(KC_J),  S(KC_K),    S(KC_L),   S(KC_SCLN), S(KC_QUOT),
    MO(SYMBOL), S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),   S(KC_N), S(KC_M),  S(KC_COMM), S(KC_DOT), S(KC_SLASH), KC_RSFT,
                                  KC_LCTL, KC_SPACE, KC_ESC,   KC_ENTER, KC_SPACE, KC_RALT 
  ),

  [SYMBOL] = LAYOUT_3x6_3(
    KC_TAB,     KC_1,    KC_2,    KC_3,    KC_4,      KC_5,   KC_6,        KC_7,      KC_8,     KC_9,    KC_0,   KC_SCLN,
    _______, KC_EXLM,   KC_AT,   KC_LT,   KC_GT, KC_BSLS,   KC_DQT,    KC_PLUS,  KC_MINS, KC_SLASH, KC_ASTR,    KC_TAB,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,  KC_GRAVE,   KC_MINS,   KC_AMPR, KC_EQUAL,  KC_COMM,  KC_DOT, KC_RSFT,
                                KC_LCTL, KC_SPACE, KC_ESC,   KC_ENTER, KC_SPACE, KC_RALT
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // or uint8_t layer = get_highest_layer(state);
    switch (get_highest_layer(state)) {
        case (STENO):
          //green LED on
          // red LED off
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A0);
          break;
        case (QWERTY):
          // red LED on
          // green LED off
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          break;
        case (QWERTY_CAPS):
          // same as QWERTY
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          break;
        case (NKRO): 
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          break;
        case (SYMBOL):
          // both LEDs on for Symbol
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          break;
        default:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          break;
    }

    return state;
}