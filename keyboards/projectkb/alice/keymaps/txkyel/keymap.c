/*
Copyright 2020 Ryan Castillo <castillo.ryanmiguel@gmail.com>
Copyright 2021 Kyle Xiao @txkyel

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

/*
This keymap is meant for preparing/practicing usage of a 3x6 + 3 split layout
*/
#include QMK_KEYBOARD_H
#include "txkyel.h"

enum layer {
    _BASE = 0,
    _SYMB = 1,
    _MATH = 2,
    _NAVI = 3,
};

// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_alice(
    KC_ESC,  	XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_PGUP, 	TD(TH_ESC_TAB),TD(HC_Q),TD(HC_W),TD(HC_E), TD(HC_R),  TD(HC_T),       TD(HC_Y),  TD(HC_U),  TD(HC_I),  TD(HC_O),  TD(HC_P),  TD(HC_BSPC), XXXXXXX, XXXXXXX,
    RESET, 	  KC_LCTL,  TD(HC_A),  TD(HC_S),  TD(HC_D),  TD(HC_F),  TD(HC_G),       TD(HC_H),  TD(HC_J),  TD(HC_K),  TD(HC_L),  KC_SCLN,   KC_QUOT,     XXXXXXX,
              KC_ESC,   TD(HC_Z),  TD(HC_X),  TD(HC_C),  TD(HC_V),  TD(HC_B),TD(HC_B),TD(HC_N),TD(HC_M),  KC_COMM,   KC_DOT,    KC_SLSH,   KC_LGUI,     XXXXXXX,
              XXXXXXX,             KC_LALT,          KC_SPC,        KC_LGUI,              KC_LSFT,        OSL(1),               XXXXXXX
  ),
  [_SYMB] = LAYOUT_alice(
    KC_ESC,  	XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_PGUP, 	KC_TRNS,  KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,        KC_CIRC,   KC_AMPR,   KC_ASTR,   XXXXXXX,   TO(3),     TD(HC_BSPC), XXXXXXX, XXXXXXX,
    RESET, 	  KC_TRNS,  KC_SLSH,   KC_BSLS,   KC_GRV,    KC_QUOT,   KC_UNDS,        KC_MINS,   KC_LPRN,   KC_RPRN,   KC_LBRC,   KC_RBRC,   KC_ENT,      XXXXXXX,
              KC_TRNS,  XXXXXXX,   KC_PIPE,   KC_TILD,   KC_DQT,    KC_PLUS,XXXXXXX,KC_EQL,    KC_LCBR,   KC_RCBR,   KC_DOT,    KC_SLSH,   XXXXXXX,     XXXXXXX,
              XXXXXXX,             TO(0),     KC_SPC,    KC_TRNS,                   KC_LSFT,              TO(2),                XXXXXXX
  ),
  [_MATH] = LAYOUT_alice(
    KC_ESC,  	XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_PGUP, 	TD(HC_DEL),KC_1,     KC_2,      KC_3,      KC_4,      KC_5,           KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      TD(HC_BSPC), XXXXXXX, XXXXXXX,
    RESET, 	  KC_TRNS,  XXXXXXX,   XXXXXXX,   KC_GRV,    KC_QUOT,   KC_UNDS,        KC_MINS,   KC_LPRN,   KC_RPRN,   KC_LBRC,   KC_RBRC,   KC_ENT,      XXXXXXX,
              KC_TRNS,  XXXXXXX,   XXXXXXX,   KC_TILD,   KC_DQT,    KC_PLUS,XXXXXXX,KC_EQL,    KC_LCBR,   KC_RCBR,   KC_DOT,    KC_SLSH,   KC_TRNS,     XXXXXXX,
              XXXXXXX,             TO(0),     KC_SPC,    KC_TRNS,                   KC_LSFT,              XXXXXXX,              XXXXXXX
  ),
  [_NAVI] = LAYOUT_alice(
    KC_ESC,  	XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,
    KC_PGUP, 	XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   KC_HOME,   KC_PGDN,   KC_PGUP,   KC_END,     TD(HC_BSPC),XXXXXXX, XXXXXXX,
    RESET, 	  KC_TRNS,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   TD(HC_LEFT),KC_DOWN,  KC_UP,     TD(HC_RGHT),KC_ENT,     XXXXXXX,
              KC_TRNS,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,XXXXXXX,XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    KC_TRNS,    XXXXXXX,
              XXXXXXX,             TO(0),     KC_SPC,    MO(3),                     KC_LSFT,              KC_TRNS,              XXXXXXX
  ),
};
