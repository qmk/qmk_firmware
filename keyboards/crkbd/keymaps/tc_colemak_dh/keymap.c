/* Copyright 2020 foostan
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

// Define Layer Names
enum layers {
  _COL_DH,  // Colemak DH
  _TOPROW,  // Top Rows
  _NUMPAD,  // Numpad
  _BLANK
};
#define COL_DH TO(_COL_DH)
#define TOPROW TO(_TOPROW)
#define NUMPAD TO(_NUMPAD)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COL_DH] = LAYOUT(
//     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
//     KC_ESC,  A_ALTQ,  S_GUIQ,   D_SFT,  F_CTLQ,    KC_G,                         KC_H,  J_CTLQ,   K_SFT,  L_GUIQ,  SCLN_Q, KC_QUOT,
//    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
//                                         BOTTOM,  KC_SPC,   LOWER,      RAISE,  KC_SPC,     TOP
// ** Alpha **
//  .---.---.---.---.---.---.         .---.---.---.---.---.---.
//  |esc| q | w | f | p | b |         | j | l | u | y | ; |bsp|
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |tab| a | r | s | t | g |         | m | n | e | i | o | ' |
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |shf| z | x | c | d | v |         | k | h | , | . | / |gui|
//  '---'---'---'---+---+---+---. .---+---+---+---'---'---'---'
//                  |alt|ent|top| |num|spc|ctl|
//                  '---'---'---' '---'---'---'
//  .--------.--------.--------.--------.--------.--------.                    .--------.--------.--------.--------.--------.--------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_LGUI,
//  '--------'--------'--------'--------+--------+--------+--------.  .--------+--------+--------+--------'--------'--------'--------'
                                          KC_LALT,  KC_ENT,  TOPROW,     NUMPAD,  KC_SPC, KC_LCTL
//                                      '--------'--------'--------'  '--------'--------'--------'
  ),
// ** Top Row **
//  .---.---.---.---.---.---.         .---.---.---.---.---.---.
//  |` ~|1 !|2 @|3 #|4 $|5 %|         |6 ^|7 &|8 *|9 (|0 )|bsp|
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  | F1| F2| F3| F4| F5| F6|         | F7| F8| F9|F10|F11|F12|
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |lsh|brd|bru|prv|ply|nxt|         |shh|vup|vdn|   |   |pnl|
//  '---'---'---'---+---+---+---. .---+---+---+---'---'---'---'
//                  |alt|ent|col| |col|spc|ctl|
//                  '---'---'---' '---'---'---'
[_TOPROW] = LAYOUT(
//  .--------.--------.--------.--------.--------.--------.                    .--------.--------.--------.--------.--------.--------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_BRMD, KC_BRMU, KC_MPRV, KC_MPLY, KC_MNXT,                      KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, KC_CPNL,
//  '--------'--------'--------'--------+--------+--------+--------.  .--------+--------+--------+--------'--------'--------'--------'
                                          _______, _______,  COL_DH,     NUMPAD, _______, _______
//                                      '--------'--------'--------'  '--------'--------'--------'
  ),
// ** Accounting **
//  .---.---.---.---.---.---.         .---.---.---.---.---.---.
//  |esc|- _|= +|[ {|] }|\ ||         |num|7  |8  |9  | - |bsp|
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |   |ins|hom|pup|tab| ( |         | / |4  |5  |6  | + |del|
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |   |del|end|pdn|ent| ) |         | * |1  |2  |3  | . |ent|
//  '---'---'---'---+---+---+---. .---+---+---+---'---'---'---'
//                  |   |   |   | |   |tab|0  |
//                  '---'---'---' '---'---'---'
[_NUMPAD] = LAYOUT(
//  .--------.--------.--------.--------.--------.--------.                    .--------.--------.--------.--------.--------.--------.
       KC_ESC, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,                       KC_NUM, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_BSPC,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_INS, KC_HOME, KC_PGUP,  KC_TAB, KC_LPRN,                      KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,  KC_DEL,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_DEL,  KC_END, KC_PGDN,  KC_ENT, KC_RPRN,                      KC_PAST, KC_KP_1, KC_KP_2, KC_KP_3, KC_PDOT, KC_PENT,
//  '--------'--------'--------'--------+--------+--------+--------.  .--------+--------+--------+--------'--------'--------'--------'
                                          _______, _______,  COL_DH,     TOPROW,  KC_TAB, KC_KP_0
//                                      '--------'--------'--------'  '--------'--------'--------'
  ),
// ** Blank, so far **
//  .---.---.---.---.---.---.         .---.---.---.---.---.---.
//  |   |   |   |   |   |   |         |   |   |   |   |   |   |
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |   |   |   |   |   |   |         |   |   |   |   |   |   |
//  |---+---+---+---+---+---|         |---+---+---+---+---+---|
//  |   |   |   |   |   |   |         |   |   |   |   |   |   |
//  '---'---'---'---+---+---+---. .---+---+---+---'---'---'---'
//                  |   |   |   | |   |   |   |
//                  '---'---'---' '---'---'---'
[_BLANK] = LAYOUT(
//  .--------.--------.--------.--------.--------.--------.                    .--------.--------.--------.--------.--------.--------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//  '--------'--------'--------'--------+--------+--------+--------.  .--------+--------+--------+--------'--------'--------'--------'
                                          _______, _______,  COL_DH,     COL_DH, _______, _______
//                                      '--------'--------'--------'  '--------'--------'--------'
  ),
};
