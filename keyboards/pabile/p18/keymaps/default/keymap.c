#include QMK_KEYBOARD_H
/* 


enable rgb here 


*/



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
					KC_NO,KC_PMNS, KC_P9, KC_P8, KC_P7, 
					KC_NO,KC_PPLS,KC_P6, KC_P5, KC_P4, 
					KC_A, KC_TAB, KC_P3, KC_P2, KC_P1, 
					KC_B, KC_PENT, KC_PDOT, KC_P0, KC_DEL)
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder below the controller */
    if (clockwise) {
      tap_code(KC_VOLD); /*volume down*/
    } else {
      tap_code(KC_VOLU); /*volume up*/
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_WH_U); /*mouse wheel up*/
    } else {
      tap_code(KC_WH_D); /*mouse wheel down*/
    }
  }
}
