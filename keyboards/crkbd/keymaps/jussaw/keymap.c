/*
Copyright 2019 @foostan
Copyrig2ht 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>

enum layers {
    _QWERTY,
    _LOWER,
    _UPPER,
    _ADJUST,
    _GAME,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    UPPER,
    ADJUST,
    GAME,
};

/* Layer Keys */
#define LOWER MO(_LOWER)
#define UPPER MO(_UPPER)
#define ADJUST MO(_ADJUST)
#define DF_QWRT DF(_QWERTY)
#define TG_GAME TG(_GAME)

/* Mod Tap Keys for Qwerty Layer */
#define A_LGUI LGUI_T(KC_A)
#define S_LALT LALT_T(KC_S)
#define D_LCTL LCTL_T(KC_D)
#define F_LSFT LSFT_T(KC_F)
#define J_RSFT RSFT_T(KC_J)
#define K_RCTL RCTL_T(KC_K)
#define L_RALT RALT_T(KC_L)
#define SC_RGUI RGUI_T(KC_SCLN)

/* Mod Tap Keys for Lower Layer */
#define MIN_RSFT RSFT_T(KC_MINS)
#define EQL_RCTL RCTL_T(KC_EQL)
#define LBC_RALT RALT_T(KC_LBRC)
#define RBC_RGUI RGUI_T(KC_RBRC)

/* Mod Tap Keys for Upper Layer */
#define F1_LGUI LGUI_T(KC_F1)
#define F2_LALT LALT_T(KC_F2)
#define F3_LCTL LCTL_T(KC_F3)
#define F4_LSFT LSFT_T(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------.  ,-----------------------------------------------------.
   * |  Tab   |    Q   |    W   |    E   |    R   |    T   |  |    Y   |    U   |    I   |    O   |    P   |  Del   |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |  Esc   | A,LGUI | S,LALT | D,LCTL | F,LSFT |    G   |  |    H   | J,RSFT | K,RCTL | L,RALT | ;,RGUI |   ""   |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |  CAPS  |    Z   |    X   |    C   |    V   |    B   |  |    N   |    M   |    ,   |    .   |    /   | Enter  |
   * `--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------'
   *                            |  Hyper | Lower  | Space  |  |  Bksp  | Upper  |        |
   *                            `--------------------------'  `--------------------------'
   */
  [_QWERTY] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_DEL,
       KC_ESC,  A_LGUI,  S_LALT,  D_LCTL,  F_LSFT,    KC_G,       KC_H,  J_RSFT,  K_RCTL,  L_RALT, SC_RGUI, KC_QUOT,
      KC_CAPS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                 KC_HYPR,   LOWER,  KC_SPC,    KC_BSPC,   UPPER, XXXXXXX
  ),

  /* Lower
   * ,-----------------------------------------------------.  ,-----------------------------------------------------.
   * |  Tab   |    !   |    @   |    #   |    $   |    %   |  |    ^   |    &   |    *   |    (   |    )   |  Del   |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |  Esc   |  GUI   |  Alt   |  Ctrl  | Shift  |        |  |    `   | -,RSFT | =,RCTL | [,RALT | ],RGUI |   \    |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |        |        |        |        |        |        |  |    ~   |    _   |    +   |    {   |    }   |   |    |
   * `--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------'
   *                            |  Hyper | Trans  | Space  |  |  Bksp  | Adjust |        |
   *                            `--------------------------'  `--------------------------'
   */
  [_LOWER] = LAYOUT_split_3x6_3(
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
       KC_ESC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,     KC_GRV,MIN_RSFT,EQL_RCTL,LBC_RALT,RBC_RGUI, KC_BSLS,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                 KC_HYPR, KC_TRNS,  KC_SPC,    KC_BSPC,  ADJUST, XXXXXXX
  ),

  /* Upper
   * ,-----------------------------------------------------.  ,-----------------------------------------------------.
   * |  Tab   |    1   |    2   |    3   |    4   |    5   |  |    6   |    7   |    8   |    9   |    0   |  Del   |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |   F11  |F1,LGUI |F2,LALT |F3,LCTL |F4,LSFT |   F5   |  |  Ins   |  Left  |  Down  |   Up   | Right  |   \    |
   * +--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |   F12  |   F6   |   F7   |   F8   |   F9   |  F10   |  |PrntScrn|  Home  |Pg Down | Pg Up  |  End   | Enter  |
   * `--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------'
   *                            |  Hyper | Adjust | Space  |  |  Bksp  | Trans  |        |
   *                            `--------------------------'  `--------------------------'
   */
  [_UPPER] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
       KC_F11, F1_LGUI, F2_LALT, F3_LCTL, F4_LSFT,   KC_F5,     KC_INS, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSLS,
       KC_F12,   KC_F5,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    KC_PSCR, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_ENT,
                                 KC_HYPR,  ADJUST,  KC_SPC,    KC_BSPC, KC_TRNS, XXXXXXX
  ),

  /* Adjust
   * ,-----------------------------------------------------.  ,-----------------------------------------------------.
   * |  RESET |        |        |        |        |TG(GAME)|  |  Play  |  Prev  |  Next  |        |        |        |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |DF(QWRT)|        |        | Mouse2 | Mouse1 |        |  |  Vol+  |Ms Left |Ms Down | Ms Up  |Ms Right|        |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |        |        |        | Mouse4 | Mouse5 |        |  |  Vol-  | MsWl L | MsWl D | MsWl U | MsWl R |        |
   * `--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------'
   *                            |  Hyper | Lower  |        |  |        | Upper  |        |
   *                            `--------------------------'  `--------------------------'
   */
  [_ADJUST] = LAYOUT_split_3x6_3(
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_GAME,     KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
      DF_QWRT, XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN1, XXXXXXX,     KC_VOLU, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN4, KC_BTN5, XXXXXXX,     KC_VOLD, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
                                 KC_HYPR, KC_TRNS, XXXXXXX,     XXXXXXX, KC_TRNS, XXXXXXX
  ),

  /* Game
   * ,-----------------------------------------------------.  ,-----------------------------------------------------.
   * |    T   |  Tab   |    Q   |    W   |    E   |    R   |  |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |    G   |  Shift |    A   |    S   |    D   |    F   |  |    H   |    J   |    K   |    L   |    ;   |   ""   |
   * |--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
   * |    B   |  Ctrl  |    Z   |    X   |    C   |    V   |  |    N   |    M   |    ,   |    .   |    /   | Enter  |
   * `--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------'
   *                            |   Esc  |  Alt   | Space  |  |        |        |TG(GAME)|
   *                            `--------------------------'  `--------------------------'
   */
  [_GAME] = LAYOUT_split_3x6_3(
         KC_T,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
         KC_G,  KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
         KC_B,  KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                  KC_ESC, KC_LALT,  KC_SPC,     XXXXXXX, XXXXXXX, TG_GAME
  ),
};
