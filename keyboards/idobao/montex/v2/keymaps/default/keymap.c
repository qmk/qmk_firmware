/* Copyright 2021 NachoxMacho
*  Copyright 2022 peepeetee
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │ ` │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│ 0     │ . │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_6x5(
        KC_GRAVE,  KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
        KC_COMMA,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_LGUI,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LALT,   KC_P4,   KC_P5,   KC_P6,
        KC_LSHIFT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTRL,  KC_P0,            KC_PDOT
    ),

    /*
     * ┌───┌───┐───┬───┬───┐
     * │Rst│ ` │Tab│MO1│Bsp│
     * ├───┼───┘───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│Hom│ ↑ │PgU│   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ ← │   │ → │   │
     * ├───┼───┼───┼───┤───┤
     * │Shi│End│ ↓ │PgD│   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│Insert │Del│   │
     * └───┴───────┴───┘───┘
     */
    [1] = LAYOUT_numpad_6x5(
        RESET,   RGB_TOG, RGB_MOD, _______, _______,
        _______, _______, _______, _______, _______,
        RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, _______,
        RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, 
        _______, _______, _______, _______, _______,
        _______, _______,           _______  
    )

};
