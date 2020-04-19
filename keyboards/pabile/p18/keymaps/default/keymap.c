#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
					         KC_P7,   KC_P8,   KC_P9, KC_PMNS, 
					         KC_P4,   KC_P5,   KC_P6, KC_PPLS,
					KC_MUTE, KC_P1,   KC_P2,   KC_P3, KC_TAB,
					KC_ESC,  KC_DEL, KC_P0, KC_PDOT, KC_PENT)
        
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
