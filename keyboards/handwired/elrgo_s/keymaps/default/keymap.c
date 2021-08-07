#include QMK_KEYBOARD_H

/*
Copyright 2021 Yaroslav Smirnov <elorenn@bk.ru>
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

#define _QWERTY 0

#define KC_RBGI  RGUI_T(KC_RBRC)
#define KC_BSCT  RCTL_T(KC_BSLS)
#define KC_QTSH  RSFT_T(KC_QUOT)
#define KC_SLSF  RSFT_T(KC_LSCR)
#define KC_NLCT  RCTL_T(KC_LNUM)
#define KC_ETAL  RALT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_5(
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T  ,                  KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
        KC_LBRC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G  ,                  KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_RBRC, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B  ,                  KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_GRAVE,
                KC_LGUI ,KC_LCTL ,KC_LSFT , KC_F1  ,KC_HOME,                  KC_END, KC_F2 , KC_SPC,KC_LALT, KC_ENT,      
    ),
};
