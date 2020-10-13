/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 * Copyright 2020 Okke Formsma <okke@formsma.nl>
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

enum layers { QWERTY = 0, COLEMAK, NUMBERS, MOVE };

enum custom_keycodes { KC_CCCV = SAFE_RANGE };

#define OK_A MT(MOD_LCTL, KC_A)
#define OK_S MT(MOD_LGUI, KC_S)
#define OK_D MT(MOD_LALT, KC_D)
#define OK_F MT(MOD_LSFT, KC_F)
#define OK_J MT(MOD_RSFT, KC_J)
#define OK_K MT(MOD_RALT, KC_K)
#define OK_L MT(MOD_RGUI, KC_L)
#define OK_SCLN MT(MOD_RCTL, KC_SCLN)

#define CM_A MT(MOD_LCTL, KC_A)
#define CM_R MT(MOD_LGUI, KC_R)
#define CM_S MT(MOD_LALT, KC_S)
#define CM_T MT(MOD_LSFT, KC_T)
#define CM_N MT(MOD_RSFT, KC_N)
#define CM_E MT(MOD_LALT, KC_E)
#define CM_I MT(MOD_LGUI, KC_I)
#define CM_O MT(MOD_LCTL, KC_O)

#define OK_GRV MT(MOD_LCTL, KC_GRV)
#define OK_1 MT(MOD_LCTL, KC_1)
#define OK_2 MT(MOD_LGUI, KC_2)
#define OK_3 MT(MOD_LALT, KC_3)
#define OK_4 MT(MOD_LSFT, KC_4)
#define OK_7 MT(MOD_LSFT, KC_7)
#define OK_8 MT(MOD_LALT, KC_8)
#define OK_9 MT(MOD_LGUI, KC_9)
#define OK_0 MT(MOD_LCTL, KC_0)

#define OK_F5 MT(MOD_LCTL, KC_F5)
#define OK_F6 MT(MOD_LGUI, KC_F6)
#define OK_F7 MT(MOD_LALT, KC_F7)
#define OK_F8 MT(MOD_LSFT, KC_F8)

#define OK_ESC MT(MOD_LCTL, KC_ESC)
#define OK_TAB MT(MOD_LCTL, KC_TAB)
// #define OK_GENT MT(MOD_LGUI, KC_ENT) /* gui enter */
// #define OK_SPNUM LT(NUMBERS, KC_SPC) /* space numbers */
// #define OK_BKFM LT(MOVE, KC_BSPC) /* backspace f-move */
// #define OK_DLFM LT(MOVE, KC_DEL) /* del f-move */
// #define OK_AENT MT(MOD_RALT, KC_ENT) /* alt enter */
#define OK_ENNUM LT(NUMBERS, KC_ENT) /* enter numbers */
#define OK_SPMOV LT(MOVE, KC_SPC)    /* space numbers */
#define OK_NUM MO(NUMBERS)
#define OK_MOV MO(MOVE)
#define OK_QWE TO(QWERTY)
#define OK_COL TO(COLEMAK)
// #define OK_MOVE TT(MOVE)
// #define OK_NUMBERS TT(NUMBERS)


#define TAB_MOV LT(MOVE, KC_TAB)
#define SP_NUM LT(NUMBERS, KC_SPC)
#define EN_MOV LT(MOVE, KC_ENT)
#define DEL_MOV LT(MOVE, KC_DEL)
#define BSP_NUM LT(NUMBERS, KC_BSPC)
#define ESC_MOV LT(MOVE, KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                ,-------------------------------------------.
 * | esc    |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |  Bspc  |
 * |--------+------+------+------+------+------|                |------+------+------+------+------+--------|
 * | tab    |   A  |   S  |  D   |   F  |   G  |                |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * | ctrl   |  ctrl|  gui | alt  | shift|      |                |      | shift| alt  |  gui | ctrl |        |
 * |--------+------+------+------+------+------|                |------+------+------+------+------+--------|
 * | shift  |   Z  |   X  |   C  |   V  |   B  |                |   N  |   M  | ,  < | . >  | /  ? |  \ |   |
 * `----------------------+------+------+------+------,  ,------+------+------+------+----------------------'
 *                               | tab  |space |enter |  | del  | bspc | esc  |
 *                               | mous |num   |mov   |  | mov  | num  | mous |
 *                               `--------------------'  '--------------------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      OK_TAB,  OK_A,   OK_S,   OK_D,   OK_F,   KC_G,                    KC_H,    OK_J,    OK_K,    OK_L,    OK_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                     KC_1,   KC_2,  OK_TAB, SP_NUM, EN_MOV, DEL_MOV, BSP_NUM, KC_ESC,  KC_NO, KC_NO
    ),
    [COLEMAK] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSPC,
      OK_TAB,  CM_A,   CM_R,   CM_S,   CM_T,   KC_G,                        KC_M,    CM_N,    CM_E,    CM_I,    CM_O,    KC_SCLN,
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,                        KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                   OK_QWE, _______,  _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Numbers: numbers, specials
 * keep ,. for easy typing of numbers and IPs, keep backspace for obvious reasons
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |  ^   |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |  -     |
 * |        |  ctrl|  gui | alt  | shift|      |                              |      | shift| alt  |  gui | ctrl |        |
 * |--------+------+------+------+------+------+-                            -+------+------+------+------+------+--------|
 * |        |      |      |  _   |  [   |  {   |                              |  }   |  ]   |      |      |  +   |  =     |
 * `----------------------+------+------+------+-                            -+------+------+------+----------------------'

 */
    [NUMBERS] = LAYOUT(
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR , KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, OK_1,    OK_2,   OK_3,    OK_4,    KC_5,                     KC_6,    OK_7,    OK_8,    OK_9,    OK_0,    KC_MINS,
      _______, KC_TILD, KC_GRV, KC_UNDS, KC_LBRC, KC_RBRC,                  KC_LCBR, KC_RCBR, _______, _______, KC_PLUS, KC_EQL,
                        _______, _______, _______, _______, _______, KC_DEL, KC_BSPC, _______, _______, _______
    ),
/*
 * F-keys, navigation
 *
 * ,-------------------------------------------.      ,-------------------------------------------.
 * | VOL UP |  F1  |  F2  |  F3  |  F4  |      |      | home | pgdn | pgup | end  |      | BRIU   |
 * |--------+------+------+------+------+------|      |------+------+------+------+------+--------|
 * | VOL DN |  F5  |  F6  |  F7  |  F8  |      |      | left | down | up   | right|      | BRID   |
 * |        |  ctrl|  gui | alt  | shift|      |
 * |--------+------+------+------+------+------+-     +------+------+------+------+------+--------|
 * | PL/PAUS|  F9  |  F10 |  F11 |  F12 | CAPS |      | mous4|      |      | mous5|      | PSCR   |
 * `----------------------+------+------+------+-     +------+------+------+----------------------'
 * mous4 = back
 * mous5 = forward
 */
    [MOVE] = LAYOUT(
      KC_VOLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_BRIU,
      KC_VOLD, OK_F5,   OK_F6,   OK_F7,   OK_F8,   _______,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BRID,
      KC_MPLY, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS,                  KC_BTN4, _______, _______, KC_BTN5, _______, KC_PSCR,
                        RESET, RESET, _______, _______, _______, _______, _______, _______, RESET, RESET
    )
};
