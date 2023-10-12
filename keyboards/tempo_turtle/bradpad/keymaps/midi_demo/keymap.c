/*
Copyright 2021 v3ritas <v3ritas@tempoturtle.com>
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
    _NATURAL,
    _SHARP,
    _FLAT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NATURAL] = LAYOUT(
        MI_C, MI_BNDD,  MI_BNDU,  MI_G,
        MI_D, MI_VELD,  MI_VELU,  MI_A,
        MI_E, MI_TRSD,  MI_TRSU,  MI_B,
        MI_F, MI_OCTD,  MI_OCTU,  MI_C,
             MO(_SHARP), MO(_FLAT)),
    [_SHARP] = LAYOUT(
        MI_Cs, KC_TRNS, KC_TRNS, MI_Gs,
        MI_Ds, KC_TRNS, KC_TRNS, MI_As,
        MI_F , KC_TRNS, KC_TRNS, MI_C ,
        MI_Fs, KC_TRNS, KC_TRNS, MI_Cs,
             KC_TRNS, KC_TRNS),
    [_FLAT] = LAYOUT(
        MI_B , KC_TRNS, KC_TRNS, MI_Gb,
        MI_Db, KC_TRNS, KC_TRNS, MI_Ab,
        MI_Eb, KC_TRNS, KC_TRNS, MI_Bb,
        MI_E , KC_TRNS, KC_TRNS, MI_B,
             KC_TRNS, KC_TRNS),
};
