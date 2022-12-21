/*
Copyright 2022 @tommyamoszhao
SPDX-License-Identifier: GPL-2.0-or-later

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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* [0]
     * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS   |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "    |
     * |------------+------+------+------+------+------|------+------+------+------+------+--|
     * | SHIFT |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+--|
     * | Ctrl  | Caps |  ALT |  OS  | Ly1  |    SPACE    | Ly2  |  M1  |  M2  |  M3  | Enter |
     * `-------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_all(
        KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,		KC_I,   	KC_O,   	KC_P,    	KC_BSPC, 
		KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,		KC_K,   	KC_L,   	KC_SCLN, 	KC_QUOT, 
		KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,		KC_COMM,	KC_DOT, 	KC_SLSH, 	KC_RSFT, 
		KC_LCTL,    KC_CAPS,    KC_LALT,    KC_LGUI,    MO(1),          KC_SPC,             MO(2),		MO(3),   	_______,   	_______,    KC_ENT
    ),

    /* [1]
     *  * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * | Reset | PgUp | Home |  Up  |  End |  Del |   \  |   7  |   8  |   9  | RGBtg |  BS  |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * |       | PgDn |  Lft |  Dn  |  Rit |   +  |   -  |   4  |   5  |   6  | RGBmod|      |
     * |------------+------+------+------+------+------|------+------+------+------+------+--|
     * |       | Vol- | Vol+ |   C  |   V  |   *  |   /  |   1  |   2  |   3  |   /  | Shift |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+--|
     * |       |      |      |      | Ly1  |      0      | Ly2  |      |   .  |  M3  |   =   |
     * `-------------------------------------------------------------------------------------'
     */
     
    [1] = LAYOUT_all(
        QK_BOOT,	KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		KC_DEL,		KC_BSLS,	KC_7,		KC_8,		KC_9,		RGB_TOG,	_______, 
		_______, 	KC_PGDN, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_PLUS, 	KC_MINS, 	KC_4, 		KC_5, 		KC_6, 		RGB_MOD, 	_______, 
		_______, 	KC_VOLD, 	KC_VOLU, 	_______, 	_______, 	KC_ASTR, 	KC_SLSH, 	KC_1, 		KC_2, 		KC_3, 		RGB_HUI, 	_______,
		RGB_SAI, 	RGB_SAD, 	RGB_VAI, 	RGB_VAD, 	_______, 			KC_0, 			_______, 	_______, 	KC_DOT, 	RGB_HUD, 	KC_EQL
	),

    /* [2]
     * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11  |  F12  |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * |      |  &   |  |   |  (   |  )   |      |      |  {   |  }   |  [   |  ]    |       |
     * |------------+------+------+------+------+-----+-----+------+------+------+------+----|
     * |      |  !   |  @   |  #   |  ^   |      |      |  ~   |  <   |  >   |  ?    |       |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+---------|
     * |      |      |      |      |      |             |      |      |      |       |       |
     * `-------------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_all(
        KC_F1, 		KC_F2, 		KC_F3, 		KC_F4, 		KC_F5, 		KC_F6, 		KC_F7, 		KC_F8, 		KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 
		_______, 	KC_AMPR, 	KC_PIPE, 	KC_LPRN, 	KC_RPRN, 	KC_PLUS, 	KC_MINS, 	KC_LCBR, 	KC_RCBR, 	KC_LBRC, 	KC_RBRC, 	_______, 
		_______, 	KC_EXLM, 	KC_AT, 		KC_HASH, 	KC_CIRC, 	KC_ASTR, 	KC_SLSH, 	KC_TILD, 	KC_LABK, 	KC_RABK, 	KC_QUES, 	_______, 
		_______, 	_______, 	_______, 	_______, 	_______, 			_______, 		_______, 	_______, 	_______, 	_______, 	_______
	)
}; 

const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS({60, 4, HSV_CYAN}, {70, 4, HSV_CYAN});

const rgblight_segment_t PROGMEM my_arnumpad_layer[] = RGBLIGHT_LAYER_SEGMENTS({40, 2, HSV_WHITE});

const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 2, HSV_WHITE});

const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS({16, 2, HSV_WHITE});
 
const rgblight_segment_t PROGMEM my_macro_layer[] = RGBLIGHT_LAYER_SEGMENTS({5, 1, HSV_WHITE});

/*const rgblight_segment_t PROGMEM my_empty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{ 41, 1, HSV_WHITE		}
);*/
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    //my_capslock_layer,
    my_base_layer,			// Default layer
    my_arnumpad_layer,		// Arrow keys & Numpad & Operator keys (both toogle and hold mode to enter this layer)
	my_symbol_layer,		// F1-F12 keys & Symbols (hold mode to enter this layer)
	my_game_layer,			// Self-Defined hotkey layout for A game (toggle mode to enter this layer)
	my_macro_layer			// Self-Defined macro keys layer (hold mode to enter this layer)
	//my_empty_layer			// Preserved layer for customization (Self-Define way to enter this layer)
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4)); 
    //rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}