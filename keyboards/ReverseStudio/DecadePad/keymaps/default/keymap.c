#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_M_R,
  KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_P7,    KC_P8,    KC_P9,    KC_NO,      
  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
  KC_P1,    KC_P2,    KC_P3,    KC_NO,
  KC_P0,    KC_NO,    KC_PDOT,  KC_PENT        
) 
};
