#include "6x6.h"

enum {
    LAYER_0 = 0,
    LAYER_1 = 1,
	LAYER_2 = 2,
	
	// ..., the rest of your layers
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[LAYER_0] = LAYOUT_36(
		MEH(KC_A), MEH(KC_B), MEH(KC_C), MEH(KC_D), MEH(KC_E), MEH(KC_F), 
		MEH(KC_G), MEH(KC_H), MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L), 
		MEH(KC_M), MEH(KC_N), MEH(KC_O), MEH(KC_P), MEH(KC_Q), MEH(KC_R), 
		MEH(KC_S), MEH(KC_T), MEH(KC_U), MEH(KC_V), MEH(KC_W), MEH(KC_X), 
		MEH(KC_Y), MEH(KC_Z), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), 
		MEH(KC_5), MEH(KC_6), MEH(KC_7), MEH(KC_8), MEH(KC_9), TO(1) ),
		
	[LAYER_1] = LAYOUT_36(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(2) ),

	[LAYER_2] = LAYOUT_36(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(0) ),

};

// Runs constantly in the background, in a loop.

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        
		case LAYER_0:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_0
			rgblight_setrgb(RGB_BLUE);
            break;
        
		case LAYER_1:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
			rgblight_setrgb(RGB_RED);
            break;
        
		case LAYER_2:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_GREEN);
            break;
        
		// add case for each layer
    }
};
