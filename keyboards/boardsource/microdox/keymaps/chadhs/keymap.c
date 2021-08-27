/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

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

enum layers {
    _COLEMAKDH,
    _NUMSYMNAV,
    _FUNCTION,
    _GAMING,
};

/* thumb  mods */
#define LTHUMB1 LT(_NUMSYMNAV,KC_TAB)
#define LTHUMB2 CMD_T(KC_BSPC)
#define LTHUMB3 OPT_T(KC_ESC)
#define RTHUMB1 LT(_FUNCTION,KC_ENT)
#define LTHUMBG TG(_GAMING)

/* home row mods */
#define LHRMA SFT_T(KC_A)
#define LHRMR CTL_T(KC_R)
#define LHRMS OPT_T(KC_S)
#define LHRMT CMD_T(KC_T)
#define LHRMZ SFT_T(KC_Z)
#define LHRMGR SFT_T(KC_GRV)
#define RHRMN CMD_T(KC_N)
#define RHRME OPT_T(KC_E)
#define RHRMI CTL_T(KC_I)
#define RHRMO SFT_T(KC_O)
#define RHRMSL SFT_T(KC_SLSH)
#define RHRMDWN CMD_T(KC_DOWN)
#define RHRMUP OPT_T(KC_UP)
#define RHRMRGT CTL_T(KC_RGHT)
#define RHRMQT SFT_T(KC_QUOT)
#define RHRMBSL SFT_T(KC_BSLS)

/* aliases */
#define RGB_RMD RGB_RMOD

/* layer definitions */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAKDH] = LAYOUT_split_3x5_3(
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  LHRMA,   LHRMR,   LHRMS,   LHRMT,   KC_G,         KC_M,    RHRMN,   RHRME,   RHRMI,   RHRMO,
  LHRMZ,   KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H,    KC_COMM, KC_DOT,  RHRMSL,
                    LTHUMB3, LTHUMB2, LTHUMB1,      RTHUMB1, KC_SPC,   KC_BSPC
),

[_NUMSYMNAV] = LAYOUT_split_3x5_3(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  LHRMGR,  KC_LCTL, KC_LOPT, KC_LCMD, XXXXXXX,      KC_LEFT, RHRMDWN, RHRMUP,  RHRMRGT, RHRMQT,
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_MINS, KC_EQL,  KC_LBRC, RHRMBSL, KC_RBRC,
                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
),

[_FUNCTION] = LAYOUT_split_3x5_3(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,
  RGB_TOG, RGB_RMD, RGB_MOD, RGB_VAD, RGB_VAI,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    LTHUMBG, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
),
[_GAMING] = LAYOUT_split_3x5_3(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_ESC,  KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_BSLS,
                    LTHUMBG, KC_LCMD, KC_SPC,       KC_TRNS, KC_TRNS, KC_TRNS
),
};
