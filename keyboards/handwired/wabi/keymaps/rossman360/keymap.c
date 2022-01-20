/*
Copyright 2020 Ross Montsinger
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
#include "rossman360.h"

#define PGMOD LT(_NUM, KC_PGDN)
#define TABMOD LT(_FN1, KC_TAB)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ENTMOD LT(_FN2, KC_ENTER)
#define RSMOD LT(_FN1, KC_MINS)

enum layer_names {
  _BASE,
  _DEL,
  _FN1,
  _FN2,
  _NUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    JUMPBACK,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSMOD  , KC_UP,
    CMDBSP,  ALTDEL,           CTRLSP,  TABMOD,  PGMOD  , ENTMOD , SPCMOD , MO(_DEL),                  KC_LEFT, KC_DOWN, KC_RGHT
  ),
[_DEL] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    REMCAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,          BLINE  , KC_BSPC, BWORD  , KC_NO  , KC_NO  , _______,                   _______, _______, _______
  ),
[_FN1] = LAYOUT(
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NTAB,
    _______, _______, _______, _______, _______, _______, _______, UNDO   , _______, _______, _______, _______, _______, KC_SLSH,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_UP  , KC_RIGHT,KC_END , _______, CTAB,
    _______, _______, XPANDR , _______, PMERGE , _______, _______, PMERGE , KC_DOWN, _______, _______, _______, _______,
    _______, _______,          _______, LWORD  , RWORD  , KC_NO  , _______, KC_NO  ,                   _______, _______, _______
  ),
[_FN2] = LAYOUT(
    _______, SPEAK1 , SPEAK2 , SPEAK3 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,          _______, PARADOWN, CSPEAK, _______, _______, _______,                   _______, _______, _______
  ),
[_NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_7   , KC_8   , KC_9   , _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_MINS, KC_4   , KC_5   , KC_6   , KC_COLN, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_1   , KC_2   , KC_3   , KC_BSLS, _______, _______,
    _______, _______,          _______, KC_0   , _______, KC_NO  , KC_SPC , KC_0   ,                   _______, _______, _______
  ),
};
