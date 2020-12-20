/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "defenitions.c"
#include "keymap_german.h"
#include "rgb.c"
#include "oled.c"
#include "logics.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Neo Base Layer: NEO2
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   X  |   V  |   L  |   C  |   W  |                              |   K  |   H  |   G  |   F  |   Q  |   ß    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Ctrl/BS|   U  |   I  |   A  |   E  |   O  |                              |   S  |   N  |   R  |   T  |   D  |   Y    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | NEO 2S |   Ü  |   Ö  |   Ä  |   P  |   Z  |  Tab |LSHIFT|  |LSHIFT| Tab  |   B  |   M  |   ,  |   .  |   J  |   -    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  GUI | Del  | Alt  | Space| Enter|  | Enter| Space| Alt  | Bksp |NEO 2S|
 *                        |      |      |      |  Num |  Sym |  |  Sym |  Num |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 *
    [_NEO2] = LAYOUT(
      KC_ESC,                DE_X,   DE_V,   DE_L,   DE_C,   DE_W,                                                  DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      MO(_NEO2_2),           DE_U,   DE_I,   DE_A,   DE_E,   DE_O,                                                   DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTL, DE_UE,  DE_OE,  DE_AE,  DE_P,   DE_Z, KC_TAB, KC_LSHIFT,               KC_LEAD, KC_TAB, DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
                 KC_RGUI, KC_LALT, LT(_NUMLEFT, KC_DEL), LT(_NUMBER, KC_SPC), LT(_SYMBOLS, KC_ENT), LT(_SYMBOLS, KC_ENT), LT(_NUMBER, KC_SPC),  KC_BSPC, KC_LALT, MO(_NEO2_2)
    ),
 */
    [_NEO2] = LAYOUT(
      LT(_NUMLEFT, KC_ESC), DE_X,   DE_V,   DE_L,   DE_C,   DE_W,                                 /*|*/                 DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      LALT_T(KC_TAB),        DE_U,   DE_I,   DE_A,   DE_E,   DE_O,                                 /*|*/                 DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTRL,              DE_UE,  DE_OE,  DE_AE,  DE_P,   DE_Z, KC_TAB, KC_LSHIFT,              /*|*/KC_LEAD, KC_TAB, DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
              KC_RGUI, KC_LSHIFT, LT(_SYMBOLS, KC_DEL), LSFT_T(KC_SPC), LT(_NUMBER, KC_ENT),/*|*/LT(_NUMBER, KC_ENT), LSFT_T(KC_SPC),  LT(_SYMBOLS, KC_BSPC), KC_RSHIFT, KC_LGUI
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  @   |  _   |  [   |  ]   |  ^   |                              |   !  |  <   |  >   |  =   |   &  |   §    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  \   |  /   |  {   |  }   |  *   |                              |   ?  |  (   |  )   |  -   |   :  |   €    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  #   |  $   |  |   |  ~   |  `   |      |      |  |      |      |   +  |  %   |  "   |  '   |   ;  |   ´    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
      _______, DE_AT,   DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,                 /*|*/                  DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, DE_SECT,
      LCTL(KC_Z), DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,                 /*|*/                  DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_EURO,
      LCTL(KC_S), DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV, _______, _______,/*|*/_______, _______, DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, _______,
                             _______, _______, _______, _______, _______,/*|*/_______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Number keys, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | REDO | BSPC |  UP  | DEL  | PUP  |                              |  *   |  7   |  8   |  9   |  -   |STALINS |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSHIFT | HOME | LEFT | DOWN | RIGHT| END  |                              |  /   |  4   |  5   |  6   |  +   |STALEND |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Undo | Tab  | S-F5 |  F12 | PDOWN|      |      |  |      |      |  0   |  1   |  2   |  3   |  .   | STALEN |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  F2  |      |      |      |      |  |      |      |      |      |LSHIFT|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______,   KC_AGAIN, LCA(DE_R), S(KC_F5),KC_F12,   KC_PGUP,                    /*|*/                  KC_PAST, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_PEQL,
      BACK_TAB, KC_HOME,  KC_BSPC, KC_UP,   KC_DEL, KC_END,                     /*|*/                  KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PPLS, _______,
      ALT_TAB,   KC_UNDO,  KC_LEFT, KC_DOWN, KC_RIGHT,   KC_PGDOWN, _______, _______,/*|*/LCA(KC_DEL), _______, KC_P0,    KC_P1, KC_P2, KC_P3, KC_PDOT,  KC_PCMM,
                                         _______, _______, KC_F2, _______, _______,/*|*/LCA(KC_END), _______, _______, _______, LCA(KC_INS)
    ),
/*
 * Base Layer: NUMLEFT
 *
 * ,-------------------------------------------.
 * |MEDIAPL |PL/PAU|   7  |   8  |   9  |      |
 * |--------+------+------+------+------+------|
 * |  PREV  | NEXT |   4  |   5  |   6  |      |
 * |--------+------+------+------+------+------+-------------.
 * |        |   0  |   1  |   2  |   3  |      |      |      |
 * |        |      |      |      |      |      |      |      |
 * `----------------------+------+------+------+------+------|
 *                        |      |      |      |      |      |
 *                        |      |      |      |      |      |
 *                        `----------------------------------'
 */
    [_NUMLEFT] = LAYOUT(
      _______, DE_0, DE_1, DE_2, DE_3, DE_Q,                  /*|*/                  _______, _______, _______, _______, _______, _______,
      _______, _______, DE_4, DE_5, DE_6, DE_F,                  /*|*/                  _______, _______, _______, _______, _______, _______,
      _______, KC_MSEL,    DE_7, DE_8, DE_9, DE_G, _______, _______,/*|*/_______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,/*|*/_______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   PWD  | F11  | F12  |QUERTY| SHOOT| NEO2 |                              | TOG  | HUI  | SAI  | VAI  | MOD  |  PWDD  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   WAKE | F6   | F7   |  F8  | F9   | F10  |                              |      | HUD  | SAD  | VAD  | RMOD |  SLEP  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | F1   | F2   |  F3  | F4   | F5   |      |      |  |      |      |      | DLEFT| DESK |DRIGHT|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
        KC_SYSTEM_WAKE, KC_F11, KC_F12, KC_SLCK, DF(_SHOOT), DF(_NEO2),                  /*|*/                  RGB_TOG, RGB_HUI,             RGB_SAI,    RGB_VAI,              RGB_MOD,  KC_SYSTEM_POWER,
        _______,  KC_F6,  KC_F7,  KC_F8,   KC_F9,     KC_F10,                     /*|*/                  _______, RGB_HUD,             RGB_SAD,    RGB_VAD,              RGB_RMOD, KC_SYSTEM_SLEEP,
        _______,         KC_F1,  KC_F2,  KC_F3,   KC_F4,     KC_F5,     _______, _______,/*|*/_______, _______, _______, LCTL(LGUI(KC_LEFT)), LGUI(KC_D), LCTL(LGUI(KC_RIGHT)), _______,  _______,
                                             _______, _______, _______, _______, _______,/*|*/_______, _______, _______, _______, _______
    ),
/*
 * Base Layer: Shooter
 *
 * ,-------------------------------------------.
 * |   ESC  |   T  |   Q  |   W  |   E  |   R  |
 * |--------+------+------+------+------+------|
 * |  CTRL  |   G  |   A  |   S  |   D  |   F  |
 * |--------+------+------+------+------+------+-------------.
 * | LShift |   B  |   Z  |   X  |   C  |   V  | Tab  |LShift|
 * |        |      |      |      |      |      | Num  | Sym  |
 * `----------------------+------+------+------+------+------|
 *                        | GUI  | Del  | Alt  | Space| Enter|
 *                        |      |      |      |      |      |
 *                        `----------------------------------'
 */
    [_SHOOT] = LAYOUT(
      LALT_T(KC_ESC), _______, _______, _______, _______, _______,                   /*|*/                  _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   /*|*/                  _______, _______, _______, _______, _______, _______,
      _______, DE_COMM, DE_DOT, DE_D, _______, _______, DE_J, DE_Q,/*|*/_______, _______, _______, _______, _______, _______, _______, _______,
                                    DE_MINS, DE_F, _______, KC_SPC, _______ ,/*|*/_______, _______, _______, _______, KC_RGUI
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
