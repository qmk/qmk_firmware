#include "3x6.h"
enum {
    LAYER_0 = 0,
    LAYER_1 = 1,
	LAYER_2 = 2,
	// ..., the rest of your layers
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[LAYER_0] = LAYOUT_18(
		MEH(KC_A), MEH(KC_B), MEH(KC_C), MEH(KC_D), MEH(KC_E), MEH(KC_F), 
		MEH(KC_G), MEH(KC_H), MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L), 
		MEH(KC_M), MEH(KC_N), MEH(KC_O), MEH(KC_P), MEH(KC_Q), TO(1)), 
	
	[LAYER_1] = LAYOUT_18(
		MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6), 
		MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_DOT), MEH(KC_MINUS), 
		MEH(KC_EQUAL), MEH(KC_SLASH), MEH(KC_GRAVE), MEH(KC_COMMA), MEH(KC_SEMICOLON), TO(2)),


	[LAYER_2] = LAYOUT_18(
		KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, 
		KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, 
		MEH(KC_KP_PLUS), MEH(KC_KP_ASTERISK), MEH(KC_KP_MINUS), MEH(KC_KP_SLASH), MEH(KC_NONUS_BACKSLASH), TO(0)),

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
        case LAYER_1:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_RED);
            break;
        case LAYER_2:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_GREEN);
            break;
        // add case for each layer
    }
};
