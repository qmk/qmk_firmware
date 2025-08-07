/*
Copyright 2020 <contact@vwolf.be>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
    *       ┌───┬───┬───┬───┐
    *       │Num│ / │ * │ - │
    * ┌───┬─┼───┼───┼───┼───┤
    * │Cal│ │ 7 │ 8 │ 9 │   │
    * ├───┼─┼───┼───┼───┤ + │
    * │WWW│ │ 4 │ 5 │ 6 │   │
    * ├───┼─┼───┼───┼───┼───┤
    * │Mai│ │ 1 │ 2 │ 3 │ E │
    * ├───┼─┼───┴───┼───┤ N │
    * │FN │ │   0   │ . │ T │
    * └───┴─┴───────┴───┴───┘
    */

    [_LAYER0] = LAYOUT(
                 KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_CALC, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_WSCH, KC_P4,   KC_P5,   KC_P6,
        KC_MAIL, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        MO(1),   KC_P0,            KC_PDOT     
    ),

    /*
    *       ┌───┬───┬───┬───┐
    *       │Num│ / │ * │-BR│
    * ┌───┬─┼───┼───┼───┼───┤
    * │   │ │F7 │F8 │F9 │   │
    * ├───┼─┼───┼───┼───┤+BR│
    * │   │ │F4 │F5 │F6 │   │
    * ├───┼─┼───┼───┼───┼───┤
    * │   │ │F1 │F2 │F3 │RGB│
    * ├───┼─┼───┴───┼───┤   │
    * │FN │ │       │TOG│MOD│
    * └───┴─┴───────┴───┴───┘
    */

    [_LAYER1] = LAYOUT(
                 KC_NUM,  KC_PSLS, KC_PAST, UG_VALD,
        KC_TRNS, KC_F7,   KC_F8,   KC_F9,   UG_VALU,
        KC_TRNS, KC_F4,   KC_F5,   KC_F6,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   UG_NEXT,
        KC_TRNS, KC_TRNS,          UG_TOGG     
    )
};
