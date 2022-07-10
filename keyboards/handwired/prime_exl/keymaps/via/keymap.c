/* Copyright 2018 Holten Campbell
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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
		KC_NLCK, 	KC_LPRN, 	KC_RPRN, 	KC_PSLS, 	KC_PAST, 	KC_BSPC, 				KC_ESC, 		KC_Q, 			KC_W, 		KC_E, 			KC_R, 		KC_T,				 		KC_Y, 			KC_U, 			KC_I, 			KC_O, 				KC_P, 			KC_BSPC,
		KC_F1, 		KC_F2, 		KC_P7, 		KC_P8, 		KC_P9, 		KC_DEL,					KC_TAB, 		KC_A, 			KC_S, 			KC_D, 			KC_F, 		KC_G,			 	 		KC_H, 			KC_J, 			KC_K, 			KC_L, 				KC_QUOT, 	KC_ENT,
		KC_F3,		KC_F4,		KC_P4,		KC_P5,		KC_P6,		KC_PMNS,				KC_LSFT, 	KC_Z, 			KC_X, 			KC_C, 			KC_V, 		KC_B,				 		MO(3), 		KC_N, 			KC_M, 		KC_COMM,	KC_DOT, 	KC_SLSH, 	KC_LSFT,
		KC_F5,		KC_F6,		KC_P1,		KC_P2,		KC_P3,		KC_PPLS,				KC_LCTL, 	KC_LALT, 	KC_LBRC, 	KC_RBRC, 			MO(2),									KC_SPC, 					KC_MINS, 	KC_EQL, 			KC_LGUI, 	MO(3),
		KC_F7,		KC_F8,		MO(1),		KC_PDOT,	KC_P0,		KC_PENT
    ),

	LAYOUT(
		KC_ESC, 	KC_1, 		KC_2, 		KC_3, 		KC_4, 		KC_F9, 					KC_ESC, 	KC_Q, 		KC_W, 		KC_E, 			KC_R, 		KC_T,				 		KC_Y, 		KC_U, 		KC_I, 		KC_O, 		KC_P, 		KC_BSPC,
		KC_TAB, 	KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T,					KC_TAB, 	KC_A, 		KC_S, 		KC_D, 			KC_F, 		KC_G,			 	 		KC_H, 		KC_J, 		KC_K, 		KC_L, 		KC_QUOT, 	KC_ENT,
		KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,					KC_LSFT, 	KC_Z, 		KC_X, 		KC_C, 			KC_V, 		KC_B,				 		MO(3), 		KC_N, 		KC_M, 		KC_COMM,	KC_DOT, 	KC_SLSH, 	KC_LSFT,
		KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,					KC_LCTL, 	KC_LALT, 	KC_LBRC, 	KC_RBRC, 		MO(2),									KC_SPC, 				KC_MINS, 	KC_EQL, 	KC_LGUI, 	MO(3),
		KC_LCTL,	KC_LALT,	TO(0),		KC_P,		KC_H,		KC_SPC
    ),

	LAYOUT(
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 				KC_GRV, 		KC_1, 				KC_2, 				KC_3, 				KC_4, 				KC_5,				 				KC_TRNS, 	KC_TRNS, 	KC_UP, 			KC_TRNS, 	KC_TRNS, 	KC_DEL,
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,				KC_CAPS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,			 	 		KC_TRNS, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_SCLN, 	KC_BSLS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,				 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 					KC_TRNS,												KC_TRNS, 			KC_VOLD, 		KC_VOLU, 	KC_MUTE, 	KC_TRNS,
		BL_TOGG,	BL_STEP,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    ),

	LAYOUT(
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 				KC_TRNS, 		KC_1, 				KC_2, 				KC_3, 				KC_4, 				KC_5,				 				KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, 			KC_TRNS,
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,			 	 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,				 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 					KC_TRNS,												KC_TRNS, 			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
    )
};


void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(C6);
  writePinHigh(C6);
  // set NumLock LED to output and low
  setPinOutput(B6);
  writePinHigh(B6);
  // set ScrollLock LED to output and low
  setPinOutput(B5);
  writePinHigh(B5);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(B6);
  } else {
    writePinLow(B6);
  }
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(B5);
  } else {
    writePinLow(B5);
  }
  /*
  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(C6);
  } else {
    writePinLow(C6);
  }
  */
}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state)
{
    if (biton32(state) == 1) {
    writePinHigh(C6);
	} else {
		writePinLow(C6);
    }
    return state;
}
