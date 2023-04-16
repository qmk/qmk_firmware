/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#define R_ARR LSFT(KC_COMM)
#define L_ARR LSFT(KC_DOT)
#define L_CBRK LSFT(KC_LBRC)
#define R_CBRK LSFT(KC_RBRC)
#define L_PAR LSFT(KC_9)
#define R_PAR LSFT(KC_0)
#define LT_3_TAB LT(3, KC_TAB)
#define LT_1_ENT LT(1, KC_ENT)
#define LT_2_SPC LT(2, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      GUI_A,   ALT_S,   SFT_D,   CTL_F,   KC_G,                         KC_H,    CTL_J,   SFT_K,   ALT_L,  GUI_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                KC_ESC, LT_3_TAB, LT_1_ENT,  LT_2_SPC,  KC_BSPC, KC_DEL
                             //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX,                      XXXXXXX, L_CBRK,  R_CBRK,  L_PAR,   R_PAR,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------/
      XXXXXXX, XXXXXXX, KC_VOLU, KC_MNXT, KC_MPLY,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MINUS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------/
      XXXXXXX, XXXXXXX, KC_VOLD, KC_MPRV, XXXXXXX,                      XXXXXXX, KC_LBRC, KC_RBRC, R_ARR,   L_ARR,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------/
                                 XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                             //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, KC_ASTR, KC_AMPR, XXXXXXX,                      XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------/                    |--------+--------+--------+--------+--------|
      KC_QUOT, KC_CIRC, KC_PERC, KC_DLR, KC_EQL,                        XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_GRV, KC_HASH,  KC_AT,   KC_EXLM, KC_BSLS,                      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                             //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  KC_0
                             //`--------------------------'  `--------------------------'
  )
};

