#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x4(
        KC_NLCK, KC_PSLS,      KC_PAST, KC_PMNS, 
        KC_P7,   KC_P8,        KC_P9,   KC_PPLS, 
        KC_P4,   KC_P5,        KC_P6,   KC_COMM, 
        KC_P1,   KC_P2,        KC_P3,   KC_EQL, 
        KC_P0,   KC_P0(KC_P0), KC_PDOT, KC_PENT)
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_WH_U); /*mouse wheel up*/
    } else {
      tap_code(KC_WH_D); /*mouse wheel down */
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_MS_U); /*mouse up*/
    } else {
      tap_code(KC_MS_D); /*volume down*/
    }
  } else if (index == 2) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_MS_L); /*mouse left*/
    } else {
      tap_code(KC_MS_R); /*mouse right*/
    }
  }
}
