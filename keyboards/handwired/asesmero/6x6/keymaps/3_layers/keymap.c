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
		MEH(KC_S), MEH(KC_T), MEH(KC_U), MEH(KC_W), MEH(KC_X), MEH(KC_Y), 
		MEH(KC_MINUS), MEH(KC_EQUAL), MEH(KC_DOT), MEH(KC_SLASH), MEH(KC_GRAVE), MEH(KC_COMMA), 
		TO(1), KC_B, KC_N, KC_M, KC_0, LSG(KC_S)),
		
	[LAYER_1] = LAYOUT_36(
		KC_8, KC_E, KC_N, KC_E, KC_5, KC_6, 
		KC_6, KC_8, KC_9, KC_Q, KC_E, KC_R, 
		KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_F, KC_G, KC_H, KC_J, 
		KC_A, KC_L, KC_D, KC_Z, KC_X, KC_C, 
		TO(2), KC_B, KC_N, KC_M, KC_0, KC_W),

	[LAYER_2] = LAYOUT_36(
		KC_8, KC_E, KC_N, KC_E, KC_5, KC_6, 
		KC_6, KC_8, KC_9, KC_Q, KC_E, KC_R, 
		KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_F, KC_G, KC_H, KC_J, 
		KC_A, KC_L, KC_D, KC_Z, KC_X, KC_C, 
		TO(0), KC_B, KC_N, KC_M, KC_0, KC_W),	

};

// Runs constantly in the background, in a loop.

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        
		case LAYER_0:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_0
			rgblight_setrgb(RGB_WHITE);
            break;
        
		case LAYER_1:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
			rgblight_setrgb(RGB_GREEN);
            break;
        
		case LAYER_2:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_RED);
            break;
        
		// add case for each layer
    }
};
