/* Copyright 2020 Paul James
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

/* Base layer
 * ,-----------------------------------------. ,-------------. ,-----------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   | |  -   |  =   | |  6   |  7   |  8   |  9   |  0   | Del  |
 * |------+------+------+------+------+------| |------+------| |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   | |  [   |  ]   | |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------| |------+------| |------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   | |  {   |  }   | |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------| |------+------| |------+------+------+------+------+------|
 * | Shft |  Z   |  X   |  C   |  V   |  B   | |  (   |  )   | |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------| |------+------| |------+------+------+------+------+------|
 * | Ctrl | Symb | Alt  | Cmd  | Symb | Spce | |      |      | | Spce |  Fn  | Left | Down |  Up  | Rght |
 * `-----------------------------------------' `-------------' `-----------------------------------------'
 */
#define BASE_ROW_1_L KC_1,    KC_2,   KC_3,    KC_4,    KC_5
#define BASE_ROW_2_L KC_Q,    KC_W,   KC_E,    KC_R,    KC_T
#define BASE_ROW_3_L KC_A,    KC_S,   KC_D,    FN_F,    KC_G
#define BASE_ROW_4_L KC_Z,    KC_X,   KC_C,    KC_V,    KC_B
#define BASE_ROW_5_L KC_LCTL, SYMBOL, KC_LALT, KC_LGUI, SYMBOL, KC_SPC

#define BASE_ROW_1_R KC_6, KC_7, KC_8, KC_9, KC_0
#define BASE_ROW_2_R KC_Y, KC_U, KC_I, KC_O, KC_P
#define BASE_ROW_3_R KC_H, SY_J, KC_K, KC_L, KC_SCLN
#ifdef ARROW_LAYOUT
    #define BASE_ROW_4_R KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_UP
    #define BASE_ROW_5_R KC_SPC, FN_SPC, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
#else
    #define BASE_ROW_4_R KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH
    #define BASE_ROW_5_R KC_SPC, FUNCT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#endif

#define BASE_ROW_1_M KC_MINS, KC_EQL
#define BASE_ROW_2_M KC_LBRC, KC_RBRC
#define BASE_ROW_3_M KC_LCBR, KC_RCBR
#define BASE_ROW_4_M KC_LPRN, KC_RPRN

#define BASE_ROW_1 QK_GESC, BASE_ROW_1_L, BASE_ROW_1_R, KC_DEL
#define BASE_ROW_2 KC_TAB,  BASE_ROW_2_L, BASE_ROW_2_R, KC_BSPC
#define BASE_ROW_3 QK_GESC, BASE_ROW_3_L, BASE_ROW_3_R, KC_QUOT
#define BASE_ROW_4 KC_LSFT, BASE_ROW_4_L, BASE_ROW_4_R, KC_ENTER
#define BASE_ROW_5          BASE_ROW_5_L, BASE_ROW_5_R


/* Function layer
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  | |  F6  |  F7  |  F8  |  F9  | F10  | Lock |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Adju |  F1  |  F2  |  F3  |  F4  |  F5  | |      | Home |  Up  | PgUp |   \  |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft | Ctrl | Alt  | Cmd  |      |      | |      | Left | Down | Rght |      |   `  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  | F10  | |      | End  | Shft | PgDn |   \  |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      | Adju | BkSp | |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------' `-----------------------------------------'
 */
#define FUNCTION_ROW_1_L KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define FUNCTION_ROW_2_L KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define FUNCTION_ROW_3_L KC_LCTL, KC_LALT, KC_LGUI, _______, _______
#define FUNCTION_ROW_4_L KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define FUNCTION_ROW_5_L _______, _______, _______, _______, ADJUST, KC_BSPC

#define FUNCTION_ROW_1_R KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define FUNCTION_ROW_2_R _______, KC_HOME, KC_UP,   KC_PGUP, KC_BSLS
#define FUNCTION_ROW_3_R _______, KC_LEFT, KC_DOWN, KC_RGHT, _______
#ifdef ARROW_LAYOUT
    #define FUNCTION_ROW_4_R _______, KC_END,  KC_LSFT, KC_PGDN, KC_PGUP
    #define FUNCTION_ROW_5_R _______, _______, KC_BSLS, KC_HOME, KC_PGUP, KC_END
#else
    #define FUNCTION_ROW_4_R _______, KC_END,  KC_LSFT, KC_PGDN, KC_BSLS
    #define FUNCTION_ROW_5_R _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
#endif

#define FUNCTION_ROW_1 _______, FUNCTION_ROW_1_L, FUNCTION_ROW_1_R, LOCK
#define FUNCTION_ROW_2 ADJUST,  FUNCTION_ROW_2_L, FUNCTION_ROW_2_R, _______
#define FUNCTION_ROW_3 KC_LSFT, FUNCTION_ROW_3_L, FUNCTION_ROW_3_R, KC_GRV
#define FUNCTION_ROW_4 _______, FUNCTION_ROW_4_L, FUNCTION_ROW_4_R, _______
#define FUNCTION_ROW_5          FUNCTION_ROW_5_L, FUNCTION_ROW_5_R


/* Symbol layer
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  | |  F6  |  F7  |  F8  |  F9  | F10  | Lock |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft |   _  |   +  |   (  |   {  |   [  | |   ]  |      | Shft |   {  |   }  |   `  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |   -  |   =  |  =>  |  ->  |   -  | |   =  |  ==  |  === |   [  |   ]  |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | | Del  | Adju | Home | PgDn | PgUp | End  |
 * `-----------------------------------------' `-----------------------------------------'
 */
#define SYMBOL_ROW_2_L KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define SYMBOL_ROW_3_L KC_UNDS, KC_PLUS, KC_LPRN, KC_LCBR, KC_LBRC
#define SYMBOL_ROW_4_L KC_MINS, KC_EQL,  MC_DARR, MC_ARR,  KC_MINS
#define SYMBOL_ROW_5_L _______, _______, _______, _______, _______, _______

#define SYMBOL_ROW_2_R KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define SYMBOL_ROW_3_R KC_RBRC, _______, KC_RSFT, KC_LCBR, KC_RCBR
#ifdef ARROW_LAYOUT
    #define SYMBOL_ROW_4_R KC_EQL, MC_DEQL, MC_TEQL, KC_LBRC, KC_PGUP
    #define SYMBOL_ROW_5_R KC_DEL, ADJUST,  KC_BSLS, KC_HOME, KC_PGUP, KC_END
#else
    #define SYMBOL_ROW_4_R KC_EQL, MC_DEQL, MC_TEQL, KC_LBRC, KC_RBRC
    #define SYMBOL_ROW_5_R KC_DEL, ADJUST,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
#endif

#define SYMBOL_ROW_1 _______, FUNCTION_ROW_1_L, FUNCTION_ROW_1_R, LOCK
#define SYMBOL_ROW_2 _______, SYMBOL_ROW_2_L,   SYMBOL_ROW_2_R,   _______
#define SYMBOL_ROW_3 KC_LSFT, SYMBOL_ROW_3_L,   SYMBOL_ROW_3_R,   KC_GRV
#define SYMBOL_ROW_4 _______, SYMBOL_ROW_4_L,   SYMBOL_ROW_4_R,   _______
#define SYMBOL_ROW_5          SYMBOL_ROW_5_L,   SYMBOL_ROW_5_R


/* Adjust layer */
#define ADJUST_ROW_2_L KC_RESET, XXXXXXX, XXXXXXX, BL_STEP, BL_TOGG
#define ADJUST_ROW_2_R RGB_TOG,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX

#define ADJUST_ROW_3_L XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ADJUST_ROW_3_R RGB_MOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX

#define ADJUST_ROW_4_L AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX
#define ADJUST_ROW_4_R RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_G, RGB_M_T

#define ADJUST_ROW_5_L XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
#define ADJUST_ROW_5_R XXXXXXX, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE

#define ADJUST_ROW_1 LOCK,    ADJUST_ROW_2_L, ADJUST_ROW_2_R, LOCK
#define ADJUST_ROW_2 _______, ADJUST_ROW_2_L, ADJUST_ROW_2_R, LOCK
#define ADJUST_ROW_3 XXXXXXX, ADJUST_ROW_3_L, ADJUST_ROW_3_R, XXXXXXX
#define ADJUST_ROW_4 XXXXXXX, ADJUST_ROW_4_L, ADJUST_ROW_4_R, XXXXXXX
#define ADJUST_ROW_5          ADJUST_ROW_5_L, ADJUST_ROW_5_R

#define EMPTY_ROW    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
