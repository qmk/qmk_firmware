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

/*
// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
		KC_P7, 	KC_P8, 	  KC_P9, 	KC_PAST, 				KC_ESC, 	KC_Q, 		KC_W, 		KC_E, 			KC_R, 		KC_T,				 		KC_Y, 		KC_U, 		KC_I, 	  KC_O, 		KC_P,     KC_DEL,  KC_BSPC,
		KC_P4, 	KC_P5, 		KC_P6, 	KC_PMNS,					KC_TAB, 	KC_A, 		KC_S, 		KC_D, 			KC_F, 		KC_G,			 	 		KC_H, 		KC_J, 		KC_K, 		KC_L, 		KC_QUOT, 	         KC_ENT,
		KC_P1,	KC_P2,		KC_P3,	KC_PPLS,				KC_LSFT, 	KC_Z, 		KC_X, 		KC_C, 			KC_V, 		KC_B,				 		MO(2), 		KC_N, 		KC_M, 		KC_COMM,  KC_DOT, 	KC_SLSH, KC_RSFT,
		MO(3),	KC_PDOT,	KC_P0,	KC_PENT,				KC_LCTL, 	KC_LALT, 	                      KC_LBRC, 	MO(1),					KC_SPC, 	KC_MINS,                                KC_RGUI, KC_RCTL
    ),

	  LAYOUT(
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 				KC_GRV, 		KC_1, 				KC_2, 				KC_3, 				KC_4, 				KC_5,				 				KC_TRNS, 	KC_TRNS, 	KC_UP, 			KC_TRNS, 	KC_TRNS, KC_TRNS,	KC_DEL,
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,				KC_CAPS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,			 	 		KC_TRNS, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_SCLN, 	KC_BSLS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,				 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		BL_TOGG,	BL_STEP,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		 					KC_TRNS,												KC_TRNS, 			KC_VOLD, 	 	KC_MUTE, 	KC_TRNS
    ),

		LAYOUT(
		KC_2, 	KC_3, 	KC_4, 		KC_F9, 				KC_ESC, 		KC_Q, 			KC_W, 		KC_E, 			KC_R, 		KC_T,				 		KC_Y, 			KC_U, 			KC_I, 			KC_O, 				KC_P, 	KC_TRNS,		KC_BSPC,
		KC_W, 	KC_E, 	KC_R, 		KC_T,					KC_TAB, 		KC_A, 			KC_S, 			KC_D, 			KC_F, 		KC_G,			 	 		KC_H, 			KC_J, 			KC_K, 			KC_L, 				KC_QUOT, 	KC_ENT,
		KC_S,		KC_D,		KC_F,			KC_G,					KC_LSFT, 	KC_Z, 			KC_X, 			KC_C, 			KC_V, 		KC_B,				 		MO(3), 		KC_N, 			KC_M, 		KC_COMM,	KC_DOT, 	KC_SLSH, 	KC_LSFT,
		KC_X,		KC_C,		KC_V,			KC_B,					KC_LCTL, 	KC_LALT, 	 	KC_RBRC, 			MO(5),									KC_SPC, 					KC_MINS, 			KC_LGUI, 	MO(4)
    ),

		LAYOUT(
		RESET,  	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 				KC_TRNS, 		KC_1, 				KC_2, 				KC_3, 				KC_4, 				KC_5,				 				KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, KC_TRNS,			KC_TRNS,
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,			 	 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS, 		KC_TRNS,				 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS, 		KC_TRNS, 		KC_TRNS, 					KC_TRNS,												KC_TRNS, 			KC_TRNS, 	 	KC_TRNS, 	KC_TRNS
    )
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}
*/

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  //setPinOutput(D5);
 // writePinLow(D5);
  // set NumLock LED to output and low
  setPinOutput(B7);
  writePinLow(B7);
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(B7);
  } else {
    writePinLow(B7);
  }
  /*if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(D5);
  } else {
    writePinLow(D5);
  }*/

  /*
  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(C6);
  } else {
    writePinLow(C6);
  }
  */
}

/*
//function for layer indicator LED
uint32_t layer_state_set_user(uint32_t state)
{
    if (biton32(state) == 1) {
    writePinHigh(C6);
	} else {
		writePinLow(C6);
    }
    return state;
}
*/