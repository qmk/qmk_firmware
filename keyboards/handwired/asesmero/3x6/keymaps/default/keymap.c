#include "3x6.h"

enum {
    LAYER_0 = 0,
	// ..., the rest of your layers
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[LAYER_0] = LAYOUT_18(
		MEH(KC_A), MEH(KC_B), MEH(KC_C), MEH(KC_D), MEH(KC_E), MEH(KC_F), 
		MEH(KC_G), MEH(KC_H), MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L), 
		MEH(KC_M), MEH(KC_N), MEH(KC_O), MEH(KC_P), MEH(KC_Q), MEH(KC_R)), 
	
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    // INSERT CODE HERE: turn off all leds

    switch (layer) {
        case LAYER_0:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
			rgblight_setrgb(RGB_BLUE);
            break; 
			
        // add case for each layer
    }
};
