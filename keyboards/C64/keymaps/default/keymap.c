/* Copyright 2021 Dean Woodyatt
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
#include "C64.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QW,
    _ALT,
    _SHFT
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

// CHANGED 0603 DW TO EXPERIMENT WITH JOYSTICK
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


// STANDARD COMMODORE 64 KEYBOARD LAYOUT
//   ,-------------------------------------------------------------------------------.     ,-----.
//   |LEFT|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  + |  - |  £ |HOME| Del|     |  F1 |
//   |-------------------------------------------------------------------------------|     |-----|
//   | CTRL  |  Q |  W |  E |  R |  T |  Y |  U | I |  O |  P |  @ |  * | UP | RESTO |     |  F3 |
//  ,|-------------------------------------------------------------------------------|.    |-----|
//  |RNSTP|SFTLK|  A |  S |  D |  F |  G |  H |  J |  K |  L |  : |  ; |  = |  Enter   |   |  F5 |
//  |----------------------------------------------------------------------------------|   |-----|
//  | COMM|  LSFT |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |  RSFT | UD |  LR |   |  F7 |
//  |----------------------------------------------------------------------------------|   `-----'
//  |                |                      SPACE                 |                    |
//  `----------------------------------------------------------------------------------'
// UD = UP DOWN CURSOR KEYS. DEFAULT IS DOWN, SHIFTS TO UP
// LR = LEFT RIGHT CURSOR KEYS, DEFAULT IS LEFT, SHIFTS TO RIGHT

// JOYSTICK 1  , UP, DOWN, LEFT, RIGHT, SPACE, Enter
// JOYSTICK 2  , UP, DOWN, LEFT, RIGHT, SPACE, Enter

// REPLACE COLUMN 8 WITH REQUIRED KEYPRESSES, I.E. W A S D ENTER
// REPLACE ROW 8 WITH REQUIRED KEYPRESSES. I.E. Q,A,O,P, SPACE



/*BASE LAYER QWERTY LAYOUT UK BASED KEYMAP - OTHER NATIONALITIES TO FOLLOW */
[_QW] = LAYOUT(
  KC_GRV,   KC_1,       KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,      KC_0,   KC_PLUS,    KC_MINS,    KC_HASH,    KC_HOME,   KC_BSPC,  KC_F1,
  KC_LCTRL, KC_Q,       KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,      KC_P,   S(KC_QUOT), KC_ASTR,    KC_CIRC,    KC_TAB,              KC_F3,
  KC_ESC,               KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,   S(KC_SCLN), KC_SCLN,    KC_EQL,     KC_ENT,              KC_F5,
  KC_LGUI,  MO(_SHFT),  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT, KC_SLSH,    KC_LSFT,    KC_DOWN,    KC_LEFT,             KC_F7,
                                                                    KC_SPC,
  KC_UP,  KC_DOWN,   KC_LEFT, KC_RIGHT, KC_SPC, KC_ENT,
  KC_UP,  KC_DOWN,   KC_LEFT, KC_RIGHT, KC_SPC, KC_ENT
                     
),

// SHIFTED COMMODORE 64 KEYBOARD LAYOUT
//   ,-------------------------------------------------------------------------------.     ,-----.
//   |LEFT|  ! |  " |  # |  $ |  % |  & |  ' |  ( |  ) |  0 |  + |  | |  £ | *1 | Del|     |  F2 |
//   |-------------------------------------------------------------------------------|     |-----|
//   | CTRL  |  Q |  W |  E |  R |  T |  Y |  U | I |  O |  P |  *2 |  * | PI |RESTO |     |  F4 |
//  ,|-------------------------------------------------------------------------------|.    |-----|
//  |RNSTP|SFTLK|  A |  S |  D |  F |  G |  H |  J |  K |  L |  [ |  ] |  = |  Enter   |   |  F6 |
//  |----------------------------------------------------------------------------------|   |-----|
//  | COMM|  LSFT |  Z |  X |  C |  V |  B |  N |  M |  < |  > |  ? |  RSFT | DU |  RL |   |  F8 |
//  |----------------------------------------------------------------------------------|   `-----'
//  |                |                      SPACE                 |                    |
//  `----------------------------------------------------------------------------------'
// *1 PETSCI DIAGONAL WITH BOTTOM RIGHT EMPTY
// *2 PETSCI LARGE BACKWARDS L GRAPHIC
// *3 PETSCI LARGE MIDDLE LINE - GRAPHIC
// CURSOR KEYS (LR UD) SHIFT TO DOWN AND RIGHT
// 

/*Shifted QWERTY LAYOUT*/
[_SHFT] = LAYOUT(
  KC_KP_1,  S(KC_1),   S(KC_2),  S(KC_BSLS), S(KC_4),  S(KC_5), S(KC_7),  KC_QUOT,  S(KC_9),  S(KC_0),    KC_0,       A(KC_PLUS),  S(KC_MINS),  A(KC_3),     KC_HOME,   KC_DEL,  KC_F2,
  KC_LCTRL, S(KC_Q),   S(KC_W),  S(KC_E),    S(KC_R),  S(KC_T), S(KC_Y),  S(KC_U),  S(KC_I),  S(KC_O),    S(KC_P),    A(KC_QUOT),  A(KC_8),     A(KC_6),     KC_TAB,             KC_F4,
  KC_ESC,              S(KC_A),  S(KC_S),    S(KC_D),  S(KC_F), S(KC_G),  S(KC_H),  S(KC_J),  S(KC_K),    S(KC_L),    KC_LBRC,     KC_RBRC,     KC_EQL,      KC_ENT,             KC_F6,
  KC_LGUI,  _______,   S(KC_Z),  S(KC_X),    S(KC_C),  S(KC_V), S(KC_B),  S(KC_N),  S(KC_M),  S(KC_COMM), S(KC_DOT),  S(KC_SLSH),  KC_LSFT,     S(KC_LEFT),  S(KC_DOWN),         KC_F8,
                                                                    KC_SPC,
  KC_UP,    KC_DOWN,    KC_LEFT, KC_RIGHT, KC_SPC, KC_ENT,
  KC_UP,    KC_DOWN,    KC_LEFT, KC_RIGHT, KC_SPC, KC_ENT
                     
),

// KC_NUBS = POUND
// KC_BSLS = HASH


 /* ALT SHIFT */
 [_ALT] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ , _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______ ,
  _______, _______, _______, _______, _______, _______, _______
 ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}
// NEWEST KEY OVERRIDE FEATURE AS ENABLED IN QMK 28 AUGUST 2021

  //Replace Shift+Arrow Up (Circ) with Alt+6
const key_override_t alt6_override = ko_make_basic(MOD_MASK_SHIFT, KC_CIRC, A(KC_6));         // OK CHANGES SHIFTED UP ARROW TO PI SYMBOL
const key_override_t altPLUS_override = ko_make_basic(MOD_MASK_SHIFT, KC_PLUS, A(KC_PLUS));   // OK CHANGES SHIFTED + SYMBOL TO LARGE + GRAPHIC
const key_override_t altSTAR_override = ko_make_basic(MOD_MASK_SHIFT, KC_ASTR, A(KC_8));      // OK CHANGES SHIFTED * TO A lARGE - GRAPHIC
const key_override_t altPOUND_override = ko_make_basic(MOD_MASK_SHIFT, KC_HASH, A(KC_3));     // OK CHANGES SHIFTED £ SIGN TO DIAGONAL GRAPHIC LOWER RIGHT EMPTY TOP LEFT FILLED

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]) {
    &alt6_override,
    &altPLUS_override,
    &altPOUND_override,
    &altSTAR_override,
    NULL // Null terminate the array of overrides!
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
