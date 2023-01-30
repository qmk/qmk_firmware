/* Copyright 2023 a_marmot
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

//generic default keymap with Razor defaults (+ mode toggle)

    /*
     * ┌───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┼───┤
     * │Tab│ q │ w │ e │ r │
     * ├───┼───┼───┼───┼───┤
     * │Cap│ a │ s │ d │ f │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ z │ x │ c │ v │
     * ├───┼───┼───┼───┼───┤
     * │Alt│ ↑ │ ↓ │ → │ ← │
     * ├───────┴┬──┴───┴───┤
     * │Spacebar│change map│
     * └────────┴──────────┘
     */
     
     [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
        KC_LALT, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE, TO(1)
    ),

//Second example keymap with all modifier keys replaced with numbers or letters

    /*
     * ┌───┬───┬───┬───┬───┐
     * │ 0 │ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┼───┤
     * │ i │ q │ w │ e │ r │
     * ├───┼───┼───┼───┼───┤
     * │ j │ a │ s │ d │ f │
     * ├───┼───┼───┼───┼───┤
     * │ k │ z │ x │ c │ v │
     * ├───┼───┼───┼───┼───┤
     * │ l │ ↑ │ ↓ │ → │ ← │
     * ├───────┴┬──┴───┴───┤
     * │Spacebar│change map│
     * └────────┴──────────┘
     */
     
   [1] = LAYOUT(
        KC_0, KC_1, KC_2, KC_3, KC_4,
        KC_I, KC_Q, KC_W, KC_E, KC_R,
        KC_J, KC_A, KC_S, KC_D, KC_F,
        KC_K, KC_Z, KC_X, KC_C, KC_V,
        KC_L, KC_UP, KC_DOWN, KC_RIGHT, KC_LEFT,
        KC_SPACE, TO(0)
    ) 
//, add more keymaps here

};

static const uint8_t colormap[][20][3] = {

// colors for the default key map in hex RGB values
	{
		{0x00, 0x00, 0xFF},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},
		{0xFF, 0x70, 0x00},{0x00, 0xFF, 0xFF},{0x80, 0x00, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},
		{0xFF, 0x70, 0x00},{0x80, 0x00, 0xFF},{0x80, 0x00, 0xFF},{0x80, 0x00, 0xFF},{0x00, 0xFF, 0xFF},
		{0xFF, 0x70, 0x00},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF}
	},
	
// colors for the 2nd key map 
	{
		{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},{0xE7, 0xFF, 0x00},
		{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x80, 0x00, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},
		{0x00, 0xFF, 0xFF},{0x80, 0x00, 0xFF},{0x80, 0x00, 0xFF},{0x80, 0x00, 0xFF},{0x00, 0xFF, 0xFF},
		{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF},{0x00, 0xFF, 0xFF}
	}
//, add more keymaps here

};	


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
       	rgb_matrix_set_color(i, 
       	colormap[get_highest_layer(layer_state|default_layer_state)][i][0],
       	colormap[get_highest_layer(layer_state|default_layer_state)][i][1],
       	colormap[get_highest_layer(layer_state|default_layer_state)][i][2]);
	}
	
    return false;
}

