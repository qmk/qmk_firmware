/*
Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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


#include QMK_KEYBOARD_H
#include "config_common.h"

#define LTCAPS LT(2, KC_CAPS)
#define MTRSFT RSFT_T(KC_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_all(
              KC_MUTE, KC_PSLS, KC_PAST, KC_BSPC, KC_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
              KC_PMNS, KC_P7  , KC_P8  , KC_P9  , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,
              KC_PPLS, KC_P4  , KC_P5  , KC_P6  , LTCAPS , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , KC_BSPC,
	      KC_PENT, KC_P1  , KC_P2  , KC_P3  , KC_LSFT, KC_BSLS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, MTRSFT , KC_NUHS,
              KC_PENT, KC_P0  , KC_P0  , KC_PDOT, KC_LCTL,          KC_LGUI, KC_LALT,                   KC_SPC ,          TG(1)  , MO(2)  , KC_LEFT, KC_DOWN, KC_RGHT, MO(2) 
	),
   [1] = LAYOUT_all(
              KC_MUTE, KC_PSLS, KC_PAST, KC_BSPC, KC_GESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_BSPC,
              KC_PMNS, KC_P7  , KC_P8  , KC_P9  , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,
              KC_PPLS, KC_P4  , KC_P5  , KC_P6  , LTCAPS , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , KC_BSPC,
	      KC_PENT, KC_P1  , KC_P2  , KC_P3  , KC_LSFT, KC_BSLS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, MTRSFT , KC_NUHS,
              KC_PENT, KC_P0  , KC_P0  , KC_PDOT, KC_LCTL,          KC_LGUI, KC_LALT,                   KC_SPC ,          TG(1)  , MO(2)  , KC_LEFT, KC_DOWN, KC_RGHT, MO(2)
	),
   [2] = LAYOUT_all(
              KC_MUTE, KC_F10 , KC_F11 , KC_NUM , KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_NO  , 
              KC_MINS, KC_F7  , KC_F8  , KC_F9  , KC_TAB , KC_NO  , KC_PGUP, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_INS , KC_NO  , KC_PSCR, KC_NO  , KC_NO  , KC_DEL ,
              KC_EQL , KC_F4  , KC_F5  , KC_F6  , KC_TRNS, KC_HOME, KC_PGDN, KC_END , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
              KC_NO  , KC_F1  , KC_F2  , KC_F3  , KC_NO  , KC_NO  , KC_LPRN, KC_RPRN, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_MUTE, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , 
              KC_NO  , KC_CALC, KC_CALC, KC_DEL , KC_NO  ,          GUI_TOG, KC_SLEP,                   KC_NO  ,          KC_NO  , KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_TRNS
        ),
   [3] = LAYOUT_all(
              KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
              KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
              KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
              KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
              KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  , KC_NO  ,                   KC_NO  ,          KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  
        )
};
