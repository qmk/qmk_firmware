/* Copyright 2020 customMK
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

#include QMK_KEYBOARD_H

//#define GENESIS_LAYER_COLORS
#define GENESIS_LAYER1_COLOR HSV_CYAN
#define GENESIS_LAYER2_COLOR HSV_GREEN
#define GENESIS_LAYER3_COLOR HSV_WHITE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_numpad_5x4(
			MO(1),  KC_PSLS,  KC_PAST, KC_PMNS, 
			KC_P7,  KC_P8,    KC_P9,    
			KC_P4,  KC_P5,    KC_P6,   KC_PPLS, 
			KC_P1,  KC_P2,    KC_P3,    
			KC_P0,            KC_PDOT, KC_ENT),

	[1] = LAYOUT_numpad_5x4(
			KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, 
			KC_TRNS, KC_TRNS, KC_TRNS,   
			RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, 
			KC_TRNS, KC_TRNS, KC_TRNS, 	 
			RGB_HUI, 	      KC_TRNS, RGB_HUD),

	[2] = LAYOUT_numpad_5x4(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS,   
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS,   
			KC_TRNS,          KC_TRNS, KC_TRNS),

	[3] = LAYOUT_numpad_5x4(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS,   
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS,   
			KC_TRNS,          KC_TRNS, KC_TRNS),

};


#ifdef GENESIS_LAYER_COLORS
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,13,GENESIS_LAYER1_COLOR}
	);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,13,GENESIS_LAYER2_COLOR}
	);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,13,GENESIS_LAYER3_COLOR}
	);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_layer1_layer,
		my_layer2_layer,
		my_layer3_layer
	);

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    rgblight_set_layer_state(2, layer_state_cmp(state, 3));
    return state;
}

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
}
#endif