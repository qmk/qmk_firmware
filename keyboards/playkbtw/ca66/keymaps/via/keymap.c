  
/*
Copyright 2021 J.Flanagan
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
	//Base Layer
	[0] = LAYOUT(
		KC_ESC, 		   KC_1,     KC_2, 	   KC_3, 	KC_4, 	KC_5, 	  KC_6, 	KC_7, 	 KC_8, 		KC_9, 	KC_0, 	 KC_MINS, 	KC_EQL, 	KC_BSPC, KC_BSPC, 		KC_PSCR,
		KC_TAB, 		   KC_Q, 	 KC_W, 	   KC_E, 	KC_R, 	KC_T, 	  KC_Y, 	KC_U, 	 KC_I, 		KC_O, 	KC_P, 	 KC_LBRC, 	KC_RBRC, 	KC_BSLS, 				KC_DEL,
		MO(3), 			   KC_A, 	 KC_S, 	   KC_D, 	KC_F, 	KC_G, 	  KC_H, 	KC_J, 	 KC_K, 		KC_L, 	KC_SCLN, KC_QUOT, 				KC_ENT, 				KC_PGUP,
		KC_LSFT, KC_LSFT,  KC_Z, 	 KC_X, 	   KC_C, 	KC_V, 	KC_B, 	  KC_N, 	KC_M, 	 KC_COMM, 	KC_DOT, KC_SLSH, KC_RSFT, 	KC_UP, 								KC_PGDN,
		KC_NO, 			   KC_LCTL,  KC_LALT,  LT(1, KC_BSPC), 	LT(2, KC_SPC),  	KC_RALT, KC_RGUI,   KC_RCTL, 		   KC_LEFT, KC_DOWN, KC_RGHT),

	//Layer1 Functions and Gaming Arrows over WASD
	[1] = LAYOUT(
		KC_GRV, 		   KC_F1, 	 KC_F2,    KC_F3, 	KC_F4, 	KC_F5, 	  KC_F6, 	KC_F7, 	 KC_F8,		KC_F9, 	KC_F10,   KC_F11, 	KC_F12, 	KC_NO, 	 KC_NO, 		KC_NO,
		KC_NO, 			   KC_NO, 	 KC_UP,    KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 	 KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 		KC_NO, 					KC_NO,
		KC_TRNS, 		   KC_LEFT,  KC_DOWN,  KC_RGHT, KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 	 KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 				KC_NO, 					KC_NO,
		KC_NO, KC_NO, 	   KC_NO, 	 KC_NO,    KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 	 KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 								KC_NO,
		KC_NO,			   KC_NO, 	 KC_NO,    KC_NO, 			KC_NO, 				KC_NO, 	 KC_NO, 	KC_NO, 				 KC_NO, KC_NO, KC_NO),

	//Layer2 Same as Layer1, for easy use of layers...you'll see.
	[2] = LAYOUT(
		KC_GRV, 		   KC_F1, 	 KC_F2,    KC_F3, 	KC_F4,  KC_F5, 	  KC_F6, 	KC_F7,   KC_F8, 	KC_F9, 	KC_F10,   KC_F11, 	KC_F12, 	KC_NO, 	 KC_NO, 		KC_NO,
		KC_NO, 			   KC_NO, 	 KC_UP,    KC_NO, 	KC_NO,  KC_NO,    KC_NO,  	KC_NO,   KC_NO,     KC_NO,  KC_NO,    KC_NO,    KC_NO, 		KC_NO, 					KC_NO,
		KC_NO, 			   KC_LEFT,  KC_DOWN,  KC_RGHT, KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 	 KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 				KC_NO, 					KC_NO,
		KC_NO, KC_NO, 	   KC_NO, 	 KC_NO,    KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO,   KC_NO, 	KC_NO, 	KC_NO, 	  KC_NO, 	KC_NO, 								KC_NO,
		KC_NO, 			   KC_NO, 	 KC_NO,    KC_DEL, 			KC_NO, 				KC_NO, 	 KC_NO, 	KC_NO, 				 KC_NO, KC_NO, KC_NO),

	//Layer3, Lighting Function keys, soft reset on Tab.
	[3] = LAYOUT(
		KC_NO, 			   KC_NO, 	 KC_NO,    KC_NO, 	KC_NO, 	 KC_NO,   KC_NO, 	KC_NO,   KC_NO, 	KC_NO, 	 KC_NO,   KC_NO, 	KC_NO, 		KC_NO, 	 KC_NO, 		KC_NO,
		QK_BOOT, 			   KC_NO, 	 RGB_HUD,  RGB_HUI, RGB_VAD, RGB_VAI, KC_NO, 	BL_TOGG, BL_DOWN,	BL_UP,   BL_STEP, KC_NO, 	KC_NO, 		MO(4), 	 				KC_NO,
		KC_TRNS, 		   KC_NO, 	 RGB_RMOD, RGB_MOD, RGB_TOG, KC_NO,   KC_MSTP,  KC_MPLY, KC_MPRV,   KC_MNXT, KC_VOLD, KC_VOLU, 				KC_NO, 					KC_NO,
		KC_NO, KC_NO, 	   KC_NO, 	 RGB_SAD,  RGB_SAI, KC_NO, 	 KC_NO,   KC_NO,	KC_NO, 	 KC_NO, 	KC_NO, 	 KC_NO,   KC_NO, 	KC_NO, 								KC_NO,
		KC_NO, 			   KC_NO, 	 KC_NO,    KC_NO, 			 KC_NO, 			KC_NO, 	 KC_NO, 	KC_NO, 				 KC_NO, KC_NO, KC_NO),
};
