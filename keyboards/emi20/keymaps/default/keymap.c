/* Copyright 2021 Aquacylinder
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


enum custom_keycodes {
    MACRO1 = SAFE_RANGE, 	//MACRO1 can be anything you want see the qmk documentation
	MACRO2, 				//MACRO2 Same thing, you can add as many as you like
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
			//Macro's are mentioned here allong with the keycodes
	LAYOUT_ortho_5x4( //Base layer (0)
		TG(1), 		KC_VOLD, 	KC_VOLU, 	KC_BSPC,
		KC_P7, 		KC_P8, 		KC_P9, 		KC_PAST,
		KC_P4, 		KC_P5, 		KC_P6, 		KC_PSLS,
		KC_P1, 		KC_P2, 		KC_P3, 		KC_PPLS,
		KC_P0,  	KC_PDOT,    KC_PENT, 	KC_PMNS),

	LAYOUT_ortho_5x4( //Layer 1
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_CALC,
		KC_MPRV, 	KC_MSTP, 	KC_MPLY, 	KC_MNXT,
		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,
		KC_NO, 		KC_NO, 		KC_UP, 		KC_NO,
		MO(2),      KC_LEFT,    KC_DOWN,    KC_RGHT),

	LAYOUT_ortho_5x4( //Layer 2
		KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO,
		KC_NO, 	    KC_NO, 	    KC_NO, 	    RESET,
		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,
		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,
		KC_TRNS,    KC_NLCK,    KC_NO,      KC_NO),
		//Copy any layer and edit it for more layers, be sure to add a key to go to that layer
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MACRO1: //This is where the macro's are located
        if (record->event.pressed) {
            // when keycode MACRO1 is pressed
			SEND_STRING("Thank you");
        } else {
            // when keycode MACRO1 is released
			SEND_STRING("for being you <3");
        }
        break;

	 case MACRO2:
        if (record->event.pressed) {
            // when keycode MACRO2 is pressed
            SEND_STRING("Pizza is");
        } else {
            // when keycode MACRO2 is released
			SEND_STRING("delicious ;)");
        }
        break;
	}
    return true;
}
