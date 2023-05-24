/*
Copyright 2021 MisonoWorks

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
    DEFAULT,
    META,
    SUPER,
	CALC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
    [DEFAULT] = LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 						KC_P7, KC_P8, KC_P9, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, 	     						KC_P4, KC_P5, KC_P6, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, 	     KC_UP, 				KC_P1, KC_P2, KC_P3, 
		KC_LCTL, KC_LALT, MO(META), KC_SPC, KC_BSPC, MO(SUPER), KC_LCTL, 	KC_LEFT, KC_DOWN, KC_RGHT,			   KC_P0, MO(CALC)),

    [META] = LAYOUT(
		KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DELETE, 		            KC_7, KC_8, KC_9, 
		KC_TAB, KC_GRAVE, KC_MINUS, KC_EQUAL, KC_F, KC_G, KC_H, KC_J, KC_K, KC_QUOT, KC_SCLN, 		        KC_4, KC_5, KC_6, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SLASH, KC_BSLASH,		  KC_PGUP,				KC_1, KC_2, KC_3, 
		KC_LCTL, KC_LALT, KC_TRNS, KC_SPC, KC_BSPC, KC_TRNS, KC_LCTL,		 KC_WBAK, KC_PGDN, KC_WFWD,		KC_0, KC_NLCK),
		
	[SUPER] = LAYOUT(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 			    RGB_MOD, RGB_RMOD, RGB_SAI, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_LBRC, KC_RBRC, 							RGB_HUI, RGB_HUD, RGB_SAD, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, 			  KC_UP, 			RGB_VAI, RGB_VAD, KC_3, 
		KC_APP, KC_LALT, KC_TRNS, KC_SPC, KC_BSPC, KC_TRNS, KC_MENU,		 KC_LEFT, KC_DOWN, KC_RGHT, 	KC_0, RGB_TOG),
		
	[CALC] = LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,			    KC_PSLS, KC_PAST, KC_PMNS, 
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, 				  	 			KC_KP_DOT, KC_NO, KC_PPLS, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_DOT, KC_DOT,     	      KC_UP, 			    KC_BSPC, KC_NO, KC_PENT, 
		KC_LCTL, KC_LALT, KC_TRNS, KC_SPC, KC_BSPC, KC_TRNS, KC_LCTL,		 KC_LEFT, KC_DOWN, KC_RGHT, 		     KC_NLCK, KC_TRNS),
		
};
