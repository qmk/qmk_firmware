#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_5x4(
    KC_NLCK, 	KC_PSLS,    KC_PAST,    	KC_PMNS,
    KC_P7,  	KC_P8,    	KC_P9,    		KC_PPLS,
    KC_P4,  	KC_P5,    	KC_P6,    		KC_BSPC,
    KC_P1,  	KC_P2,    	KC_P3,    		KC_PEQL,
    KC_P0, 	KC_PSCR , 	LT(1,KC_PDOT),  KC_PENT
  ),

  [1] = LAYOUT_ortho_5x4(
    KC_TRNS, 	RGB_HUI,    RGB_HUD,    	RGB_VAD,
    KC_TRNS, 	KC_VOLU,    RGB_TOG,    	RGB_VAI,
    KC_MPRV, 	KC_MUTE,    KC_MNXT,    	KC_TRNS,
    KC_TRNS,  KC_VOLD,    KC_TRNS,    	KC_TRNS,
    QK_BOOT,    KC_TRNS,    KC_TRNS,        RGB_MOD
  )
};
