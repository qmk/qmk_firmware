#include "2x3.h"
enum {
    LAYER_0 = 0,
    LAYER_1 = 1,
	LAYER_2 = 2,
	// ..., the rest of your layers
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	
	[LAYER_0] = LAYOUT_6(
		MEH(KC_A), MEH(KC_B), MEH(KC_C),
		MEH(KC_D), MEH(KC_E), TO(1)),

	[LAYER_1] = LAYOUT_6(
		MEH(KC_1), MEH(KC_2), MEH(KC_3),
		MEH(KC_4), MEH(KC_5), TO(2)),
		
	[LAYER_2] = LAYOUT_6(
		KC_F13, KC_F14, KC_F15,
		KC_F16, KC_F17, TO(0)),

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

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
