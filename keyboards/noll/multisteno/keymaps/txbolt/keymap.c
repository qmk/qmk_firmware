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

#include "keymap_steno.h"
#include QMK_KEYBOARD_H

enum layers{
  STENO,
  NKRO,
  QWERTY,
  QWERTY_CAPS,
  SYMBOL
};

// Most/all of the combo events below are leftover from the Ecosteno code
// I will likely remove them to clear this up later, but I want to have
// the code available now if anyone wants to mess with it
// These combos are mostly for combining the upper/lower rows to get the
// middle qwerty row, as well as dealing with their capitalization

enum combo_events {
  Q_A,
  Q_S,
  Q_D,
  Q_F,
  Q_G,
  Q_H,
  Q_J,
  Q_K,
  Q_L,
  Q_A_UPPER,
  Q_S_UPPER,
  Q_D_UPPER,
  Q_F_UPPER,
  Q_G_UPPER,
  Q_H_UPPER,
  Q_J_UPPER,
  Q_K_UPPER,
  Q_L_UPPER,
  Q_SCLN,
  Q_ONE,
  Q_TWO,
  Q_THREE,
  Q_FOUR,
  Q_FIVE,
  Q_SIX,
  Q_SEVEN,
  Q_EIGHT,
  Q_NINE,
  Q_ZERO,
  Q_SCLN_UPPER,
  Q_ONE_UPPER,
  Q_TWO_UPPER,
  Q_THREE_UPPER,
  Q_FOUR_UPPER,
  Q_FIVE_UPPER,
  Q_SIX_UPPER,
  Q_SEVEN_UPPER,
  Q_EIGHT_UPPER,
  Q_NINE_UPPER,
  Q_ZERO_UPPER
};

const uint16_t PROGMEM Qwerty_A[] = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM Qwerty_S[] = {KC_W, KC_X, COMBO_END};
const uint16_t PROGMEM Qwerty_D[] = {KC_E, KC_C, COMBO_END};
const uint16_t PROGMEM Qwerty_F[] = {KC_R, KC_V, COMBO_END};
const uint16_t PROGMEM Qwerty_G[] = {KC_T, KC_B, COMBO_END};
const uint16_t PROGMEM Qwerty_H[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM Qwerty_J[] = {KC_U, KC_M, COMBO_END};
const uint16_t PROGMEM Qwerty_K[] = {KC_I, KC_COMM, COMBO_END};
const uint16_t PROGMEM Qwerty_L[] = {KC_O, KC_DOT, COMBO_END};

const uint16_t PROGMEM Qwerty_A_UPPER[] = {S(KC_Q), S(KC_Z), COMBO_END};
const uint16_t PROGMEM Qwerty_S_UPPER[] = {S(KC_W), S(KC_X), COMBO_END};
const uint16_t PROGMEM Qwerty_D_UPPER[] = {S(KC_E), S(KC_C), COMBO_END};
const uint16_t PROGMEM Qwerty_F_UPPER[] = {S(KC_R), S(KC_V), COMBO_END};
const uint16_t PROGMEM Qwerty_G_UPPER[] = {S(KC_T), S(KC_B), COMBO_END};
const uint16_t PROGMEM Qwerty_H_UPPER[] = {S(KC_Y), S(KC_N), COMBO_END};
const uint16_t PROGMEM Qwerty_J_UPPER[] = {S(KC_U), S(KC_M), COMBO_END};
const uint16_t PROGMEM Qwerty_K_UPPER[] = {S(KC_I), S(KC_COMM), COMBO_END};
const uint16_t PROGMEM Qwerty_L_UPPER[] = {S(KC_O), S(KC_DOT), COMBO_END};

const uint16_t PROGMEM Qwerty_SCLN[]  = {KC_P, KC_SLASH, COMBO_END};
const uint16_t PROGMEM Qwerty_ONE[]   = {KC_Q, KC_TAB, COMBO_END};
const uint16_t PROGMEM Qwerty_TWO[]   = {KC_W, KC_TAB, COMBO_END};
const uint16_t PROGMEM Qwerty_THREE[] = {KC_E, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_FOUR[]  = {KC_R, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_FIVE[]  = {KC_T, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_SIX[]   = {KC_Y, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_SEVEN[] = {KC_U, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_EIGHT[] = {KC_I, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_NINE[]  = {KC_O, KC_BSPC, COMBO_END};
const uint16_t PROGMEM Qwerty_ZERO[]  = {KC_P, KC_BSPC, COMBO_END};

const uint16_t PROGMEM Qwerty_SCLN_UPPER[]  = {S(KC_P), S(KC_SLASH), COMBO_END};
const uint16_t PROGMEM Qwerty_ONE_UPPER[]   = {S(KC_Q), S(KC_TAB), COMBO_END};
const uint16_t PROGMEM Qwerty_TWO_UPPER[]   = {S(KC_W), S(KC_TAB), COMBO_END};
const uint16_t PROGMEM Qwerty_THREE_UPPER[] = {S(KC_E), S(KC_ESC), COMBO_END};
const uint16_t PROGMEM Qwerty_FOUR_UPPER[]  = {S(KC_R), S(KC_ESC), COMBO_END};
const uint16_t PROGMEM Qwerty_FIVE_UPPER[]  = {S(KC_T), S(KC_ESC), COMBO_END};
const uint16_t PROGMEM Qwerty_SIX_UPPER[]   = {S(KC_Y), S(KC_ENTER), COMBO_END};
const uint16_t PROGMEM Qwerty_SEVEN_UPPER[] = {S(KC_U), S(KC_ENTER), COMBO_END};
const uint16_t PROGMEM Qwerty_EIGHT_UPPER[] = {S(KC_I), S(KC_ENTER), COMBO_END};
const uint16_t PROGMEM Qwerty_NINE_UPPER[]  = {S(KC_O), S(KC_BSPC), COMBO_END};
const uint16_t PROGMEM Qwerty_ZERO_UPPER[]  = {S(KC_P), S(KC_BSPC), COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [Q_A] = COMBO_ACTION(Qwerty_A),
  [Q_S] = COMBO_ACTION(Qwerty_S),
  [Q_D] = COMBO_ACTION(Qwerty_D),
  [Q_F] = COMBO_ACTION(Qwerty_F),
  [Q_G] = COMBO_ACTION(Qwerty_G),
  [Q_H] = COMBO_ACTION(Qwerty_H),
  [Q_J] = COMBO_ACTION(Qwerty_J),
  [Q_K] = COMBO_ACTION(Qwerty_K),
  [Q_L] = COMBO_ACTION(Qwerty_L),
  [Q_A_UPPER] = COMBO_ACTION(Qwerty_A_UPPER),
  [Q_S_UPPER] = COMBO_ACTION(Qwerty_S_UPPER),
  [Q_D_UPPER] = COMBO_ACTION(Qwerty_D_UPPER),
  [Q_F_UPPER] = COMBO_ACTION(Qwerty_F_UPPER),
  [Q_G_UPPER] = COMBO_ACTION(Qwerty_G_UPPER),
  [Q_H_UPPER] = COMBO_ACTION(Qwerty_H_UPPER),
  [Q_J_UPPER] = COMBO_ACTION(Qwerty_J_UPPER),
  [Q_K_UPPER] = COMBO_ACTION(Qwerty_K_UPPER),
  [Q_L_UPPER] = COMBO_ACTION(Qwerty_L_UPPER),
  [Q_SCLN]  = COMBO_ACTION(Qwerty_SCLN),
  [Q_ONE]   = COMBO_ACTION(Qwerty_ONE),
  [Q_TWO]   = COMBO_ACTION(Qwerty_TWO),
  [Q_THREE] = COMBO_ACTION(Qwerty_THREE),
  [Q_FOUR]  = COMBO_ACTION(Qwerty_FOUR),
  [Q_FIVE]  = COMBO_ACTION(Qwerty_FIVE),
  [Q_SIX]   = COMBO_ACTION(Qwerty_SIX),
  [Q_SEVEN] = COMBO_ACTION(Qwerty_SEVEN),
  [Q_EIGHT] = COMBO_ACTION(Qwerty_EIGHT),
  [Q_NINE]  = COMBO_ACTION(Qwerty_NINE),
  [Q_ZERO]  = COMBO_ACTION(Qwerty_ZERO),

  [Q_SCLN_UPPER]  = COMBO_ACTION(Qwerty_SCLN_UPPER),
  [Q_ONE_UPPER]   = COMBO_ACTION(Qwerty_ONE_UPPER),
  [Q_TWO_UPPER]   = COMBO_ACTION(Qwerty_TWO_UPPER),
  [Q_THREE_UPPER] = COMBO_ACTION(Qwerty_THREE_UPPER),
  [Q_FOUR_UPPER]  = COMBO_ACTION(Qwerty_FOUR_UPPER),
  [Q_FIVE_UPPER]  = COMBO_ACTION(Qwerty_FIVE_UPPER),
  [Q_SIX_UPPER]   = COMBO_ACTION(Qwerty_SIX_UPPER),
  [Q_SEVEN_UPPER] = COMBO_ACTION(Qwerty_SEVEN_UPPER),
  [Q_EIGHT_UPPER] = COMBO_ACTION(Qwerty_EIGHT_UPPER),
  [Q_NINE_UPPER]  = COMBO_ACTION(Qwerty_NINE_UPPER),
  [Q_ZERO_UPPER]  = COMBO_ACTION(Qwerty_ZERO_UPPER)
};

void process_combo_event(uint16_t combo_index, bool pressed){
  if(pressed){
    switch(combo_index) {
      case Q_A_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_A));
        }
        break;
      case Q_S_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_S));
        }
        break;
      case Q_D_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_D));
        }
        break;
      case Q_F_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_F));
        }
        break;
      case Q_G_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_G));
        }
        break;
      case Q_H_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_H));
        }
        break;
      case Q_J_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_J));
        }
        break;
      case Q_K_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_K));
        }
        break;
      case Q_L_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_L));
        }
        break;

      case Q_SCLN_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_SCLN));
        }
        break;
      case Q_ONE_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_1));
        }
        break;
      case Q_TWO_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_2));
        }
        break;
      case Q_THREE_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_3));
        }
        break;
      case Q_FOUR_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_4));
        }
        break;
      case Q_FIVE_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_5));
        }
        break;
      case Q_SIX_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_6));
        }
        break;
      case Q_SEVEN_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_7));
        }
        break;
      case Q_EIGHT_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_8));
        }
        break;
      case Q_NINE_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_9));
        }
        break;
      case Q_ZERO_UPPER:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_0));
        }
        break;

      // now the "normal" combos
      case Q_A:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_A));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_A);
        }
        break;
      case Q_S:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_S));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_S);
        }
        break;
      case Q_D:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_D));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_D);
        }
        break;
      case Q_F:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_F));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_F);
        }
        break;
      case Q_G:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_G));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_G);
        }
        break;
      case Q_H:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_H));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_H);
        }
        break;
      case Q_J:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_J));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_J);
        }
        break;
      case Q_K:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_K));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_K);
        }
        break;
      case Q_L:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_L));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_L);
        }
        break;
      case Q_SCLN:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_SCLN));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_SCLN);
        }
        break;
      case Q_ONE:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_1));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_1);
        }
        break;
      case Q_TWO:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_2));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_2);
        }
        break;
      case Q_THREE:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_3));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_3);
        }
        break;
      case Q_FOUR:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_4));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_4);
        }
        break;
      case Q_FIVE:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_5));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_5);
        }
        break;
      case Q_SIX:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_6));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_6);
        }
        break;
      case Q_SEVEN:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_7));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_7);
        }
        break;
      case Q_EIGHT:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_8));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_8);
        }
        break;
      case Q_NINE:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_9));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_9);
        }
        break;
      case Q_ZERO:
        if (IS_LAYER_ON(QWERTY_CAPS)){
          tap_code16(S(KC_0));
        }
        else if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_0);
        }
        break;
    }
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [STENO] = LAYOUT(
    STN_RES1,   STN_N1, STN_N2, STN_N3, STN_N4,  STN_N5,   STN_N6,  STN_N7, STN_N8, STN_N9, STN_NA, STN_FN,      
    TO(NKRO),   STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,   STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    MO(SYMBOL), STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,   STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                 STN_A,  STN_O,  STN_NB,   STN_NC,   STN_E,  STN_U 
  ),

  [NKRO] = LAYOUT(
    KC_GRAVE,   KC_1, KC_2, KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8, KC_9, KC_0,    KC_MINS,
    TO(QWERTY), KC_Q, KC_W, KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I, KC_O, KC_P,    KC_LBRC,
    MO(SYMBOL), KC_A, KC_S, KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                            KC_C, KC_V, KC_Z,   KC_X, KC_N, KC_M 
  ),

  [QWERTY] = LAYOUT(
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,       KC_Y, KC_U, KC_I,    KC_O,      KC_P,     KC_BSPC,
    TO(STENO),  KC_A,   KC_S,   KC_D,   KC_F,    KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,     KC_QUOT,
    MO(SYMBOL), KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, MO(QWERTY_CAPS),
                            KC_LCTL, KC_SPACE, KC_ESC,       KC_ENTER, KC_SPACE, KC_RALT
  ),

  [QWERTY_CAPS] = LAYOUT(
    S(KC_TAB),  S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),   S(KC_Y), S(KC_U),  S(KC_I),    S(KC_O),      S(KC_P), S(KC_BSPC),
    TO(STENO),  S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),   S(KC_H), S(KC_J),  S(KC_K),    S(KC_L),   S(KC_SCLN), S(KC_QUOT),
    MO(SYMBOL), S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),   S(KC_N), S(KC_M),  S(KC_COMM), S(KC_DOT), S(KC_SLASH), KC_RSFT,
                                  KC_LCTL, KC_SPACE, KC_ESC,   KC_ENTER, KC_SPACE, KC_RALT 
  ),

  [SYMBOL] = LAYOUT(
    KC_TAB,     KC_1,    KC_2,    KC_3,    KC_4,      KC_5,   KC_6,        KC_7,      KC_8,     KC_9,    KC_0,   KC_SCLN,
    _______, KC_EXLM,   KC_AT,   KC_LT,   KC_GT, KC_BSLS,   KC_DQT,    KC_PLUS,  KC_MINS, KC_SLASH, KC_ASTR,    KC_TAB,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,  KC_GRAVE,   KC_MINS,   KC_AMPR, KC_EQUAL,  KC_COMM,  KC_DOT, KC_RSFT,
                                KC_LCTL, KC_SPACE, KC_ESC,   KC_ENTER, KC_SPACE, KC_RALT
  )
};

void matrix_init_user(void) {
  // the below should no longer be needed on QMK as of Q3 2022
  //steno_set_mode(STENO_MODE_BOLT); // STENO_MODE_GEMINI or STENO_MODE_BOLT
  //steno_set_mode(STENO_MODE_GEMINI);
  // STENO_MODE_GEMINI only works if you remove references to TX Bolt in QMK
  // follow ecosteno-geminipr.diff to do this (thanks to dnaq in the Plover discord)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // or uint8_t layer = get_highest_layer(state);
    switch (get_highest_layer(state)) {
        case (STENO):
          //green LED on
          palSetPad(GPIOA, 1);
          // red LED off
          palClearPad(GPIOA, 0);
          break;
        case (QWERTY):
          combo_enable();
          // red LED on
          palSetPad(GPIOA, 0);
          // green LED off
          palClearPad(GPIOA, 1);
          break;
        case (QWERTY_CAPS):
          // same as QWERTY
          combo_enable();
          // red LED on
          palSetPad(GPIOA,0);
          // green LED off
          palClearPad(GPIOA,1);
          break;
        case (NKRO): 
          combo_disable();
          palClearPad(GPIOA, 1);
          palClearPad(GPIOA, 0);
          break;
        case (SYMBOL):
          // both LEDs on for Symbol
          combo_disable();
          palSetPad(GPIOA, 1);
          palSetPad(GPIOA, 0);
          break;
        default:
          // shouldn't happen but just in case
          //combo_disable();
          palClearPad(GPIOA, 1);
          palClearPad(GPIOA, 0);
          break;
    }

    return state;
}