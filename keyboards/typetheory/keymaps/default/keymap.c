/*
Copyright 2021 Marius Gavrilescu <marius@ieval.ro>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define LOWER MO(1)
#define RAISE MO(2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
     KC_EQL , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
     KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
     KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                       KC_GRV , KC_NUHS,                                                            KC_LBRC, KC_RBRC,
                                         RAISE  , KC_BSPC, KC_DEL ,      KC_LGUI, KC_SPC , LOWER ,
                                                  KC_LALT, KC_ESC ,      KC_RCTL, KC_ENT
  ),

  [1] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                        _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,
     _______, _______, KC_UP  , _______, _______, _______,                        _______, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, _______,
     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                        _______, KC_P4  , KC_P5  , KC_P6  , KC_PENT, _______,
     _______, _______, _______, _______, _______, _______,                        _______, KC_P1  , KC_P2  , KC_P3  , KC_PEQL, _______,
                       _______, _______,                                                            KC_P0  , KC_PDOT,
                                         _______, _______, _______,      _______, _______, _______,
                                                  _______, _______,      _______, _______

  ),

  [2] = LAYOUT(
     KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
     _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGUP, KC_HOME,                        KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
     _______, KC_WH_L, KC_WH_U, KC_WH_R, KC_PGDN, KC_END ,                        _______, _______, _______, _______, _______, RESET  ,
                       KC_WH_D, KC_BTN3,                                                            _______, _______,
                                         _______, _______, _______,      _______, _______, _______,
                                                  _______, _______,      _______, _______

  ),
};
